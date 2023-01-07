#include "bmp.h"

namespace BmpCV {

    Img::Img() {

    }

    Img::Img(int cols, int rows, int flag) {
        width = cols;
        height = rows;
        color_bit = flag & 0x0F;
        color_space = flag & 0xF0;
        pixel_count = width * height * color_bit;
        data = new uchar[pixel_count]();
    }

    Img::Img(Eigen::MatrixXd matrix, int flag) {
        width = matrix.cols();
        height = matrix.rows();
        color_bit = flag & 0x0f;
        color_space = flag & 0xF0;
        pixel_count = width * height * color_bit;
        data = new uchar[pixel_count]();
        for(int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {
                this->iloc(i, j, 0) = matrix(i, j) * 256;
            }
        }
    }

    Img::Img(const Img& im) {
        width = im.width;
        height = im.height;
        color_bit = im.color_bit;
        color_space = im.color_space;
        pixel_count = im.pixel_count;
        data = new uchar[pixel_count]();
        std::memcpy(data, im.data, pixel_count);
        color_map = im.color_map;
    }

    Img::~Img() {
        delete [] data;
//        std::cout << "Img deleted" << std::endl;
    }

    Img& Img::operator=(const Img &im) {
        if (this == &im)
            return *this;
        width = im.width;
        height = im.height;
        color_bit = im.color_bit;
        color_space = im.color_space;
        pixel_count = im.pixel_count;
        data = new uchar[pixel_count]();
        std::memcpy(data, im.data, pixel_count);
        color_map = im.color_map;
        return *this;
    }

    // 0 -----------> x cols/width
    // |
    // |
    // |
    // y rows/height

    uchar Img::loc(int row, int col, int channel) const{
        if(row < 0 || col < 0 || channel < 0 || row >= height || col >= width || channel >= color_bit) {
            throw CV_runtime_error(INDEX_OVERFLOW, "Loc index overflow");
        }
        if(color_bit == COLOR_8UC1) {
            uchar pixel = *(data+row*width+col);
            return pixel;
        }
        else {
            uchar pixel = *(data+3*(row*width+col)+channel);
            return pixel;
        }
    }

    uchar Img::loc(pt_2d pt, int channel) const{
        if(pt.y < 0 || pt.x < 0 || channel < 0 || pt.y >= height || pt.x >= width || channel >= color_bit) {
            throw CV_runtime_error(INDEX_OVERFLOW, "Loc index overflow");
        }
        if(color_bit == COLOR_8UC1) {
            uchar pixel = *(data+pt.y*width+pt.x);
            return pixel;
        }
        else {
            uchar pixel = *(data+3*(pt.y*width+pt.x)+channel);
            return pixel;
        }
    }

    uchar& Img::iloc(int row, int col, int channel) {
        if(row < 0 || col < 0 || channel < 0 || row >= height || col >= width || channel >= color_bit) {
            throw CV_runtime_error(INDEX_OVERFLOW, "iLoc index overflow");
        }
        if(color_bit == COLOR_8UC1) {
            uchar& pixel = *(data+row*width+col);
            return pixel;
        }
        else {
            uchar& pixel = *(data+3*(row*width+col)+channel);
            return pixel;
        }
    }

    void Img::palette2map(Color_palette* palette, int count) {
        for(int i=0; i<count; i++) {
            color_map.emplace(i, *(palette+i));
        }
    }

    Img readImg(const std::string& filename) {
        if(filename.empty()) {
            throw CV_runtime_error(FILE_OPEN_ERROR, "Empty filename");
        }
        FILE *img_fd = fopen(filename.data(), "rb");

        if(img_fd != nullptr) {
            // step 1: read bmp file header
            BMP_header header;
            fread(reinterpret_cast<char*>(&header), 1, 2, img_fd);
            fread(reinterpret_cast<char*>(&header)+4, 1, sizeof(header)-4, img_fd);
            if(header.bfType != 0x4d42) {
                throw CV_runtime_error(BAD_IMAGE_INFO, "File bfType error");
            }
//            std::cout << std::hex << header.bfType << std::endl;
//            std::cout << std::hex << header.bfSize << std::endl;
//            std::cout << std::hex << header.bfReserved << std::endl;
//            std::cout << std::hex << header.bfOffBits << std::endl;

            // step 2: read bitmap info, initialize Img object
            Bitmap_info bitmap;
            fread(reinterpret_cast<char*>(&bitmap), 1, sizeof(bitmap), img_fd);
            if(bitmap.biSize != 0x28) {
                throw CV_runtime_error(BAD_IMAGE_INFO, "File bitmap size != 0x28");
            }
            if(bitmap.biHeight < 0) {
                throw CV_runtime_error(BAD_IMAGE_INFO, "Unsupported BMP origin with height<0");
            }
            Img src_img(bitmap.biWidth, bitmap.biHeight, bitmap.biBitCount/8);
            int row_data = src_img.width * src_img.color_bit;
            int row_size = (row_data + 3) / 4 * 4;

            // step 3: read color palette (optional)
            int palette_count = 1<<bitmap.biBitCount;
            bool palette_flag = ((palette_count*4 + 14 + bitmap.biSize) == header.bfOffBits);
            if (src_img.color_bit == COLOR_8UC1 && palette_flag) {
                std::cout << "indexed image" << std::endl;
                Color_palette* cp = new Color_palette[palette_count]();
                src_img.color_bit = COLOR_INDEXED;
                if(header.bfOffBits >= (sizeof(header) + sizeof(bitmap))) {
                    fread(reinterpret_cast<uchar*>(cp), 1,
                          (1<<bitmap.biBitCount)*sizeof(Color_palette), img_fd);
                    src_img.palette2map(cp, palette_count);
                    delete [] cp;
                }
                else {
                    throw CV_runtime_error(BAD_IMAGE_INFO, "BMP not contain color header");
                }
            }

            // step 4: read bmp data
            fseek(img_fd, header.bfOffBits, SEEK_SET);
            if(src_img.color_bit == COLOR_INDEXED && palette_flag) {
                src_img.pixel_count = src_img.width * src_img.height;
                src_img.data = new uchar[src_img.pixel_count*3]();
                uchar* data_index = new uchar[src_img.pixel_count]();
                for(int i=0; i<src_img.height; i++) {
                    // fseek(img_fd, header.bfOffBits+row_size*(src_img.height-1-i), SEEK_SET);
                    fread(static_cast<uchar*>(data_index + (src_img.height-1-i)*row_data), 1, row_data, img_fd);
                    fseek(img_fd, row_size - row_data, SEEK_CUR);
                }
                for(int j=0; j<src_img.pixel_count; j++) {
                    *(src_img.data+3*j) = (uchar)(src_img.color_map[(int)*(data_index+j)].green_mask);
                    *(src_img.data+3*j+1) = (uchar)(src_img.color_map[(int)*(data_index+j)].red_mask);
                    *(src_img.data+3*j+2) = (uchar)(src_img.color_map[(int)*(data_index+j)].blue_mask);
                }
                src_img.pixel_count*=3;
            }
            else {
                src_img.pixel_count = src_img.width * src_img.height * src_img.color_bit;
                src_img.data = new uchar[src_img.pixel_count];
                for(int i=0; i<src_img.height; i++) {
                    // fseek(img_fd, header.bfOffBits+row_size*(src_img.height-1-i), SEEK_SET);
                    // fread(static_cast<uchar*>(src_img.data + i*row_data), 1, row_data, img_fd);
                    fread(static_cast<uchar*>(src_img.data + (src_img.height-1-i)*row_data), 1, row_data, img_fd);
                    fseek(img_fd, row_size - row_data, SEEK_CUR);
                }
            }
             return src_img;
        }
        else {
            throw CV_runtime_error(FILE_OPEN_ERROR, "File open error");
        }

    }

    void writeImg(const Img& src_img, const std::string& filename) {
        FILE *img_fd = fopen(filename.data(), "wb+");
        BMP_header header;

        header.bfType = 0x4D42;

        header.bfReserved = 0x0000;
        if(src_img.color_bit == COLOR_8UC1) {
            header.bfSize = src_img.pixel_count + 0x0436;
            header.bfOffBits = 0x0436;
        }
        else {
            header.bfSize = src_img.pixel_count + 0x0036;
            header.bfOffBits = 0x0036;
        }


        Bitmap_info bitmap;
        bitmap.biSize = 0x0028;
        bitmap.biWidth = src_img.width;
        bitmap.biHeight = src_img.height;
        bitmap.biPlanes = 0x01;
        bitmap.biBitCount = src_img.color_bit * 8;
        bitmap.biCompression = 0x0000;
        bitmap.biSizeImages = src_img.pixel_count;
        bitmap.biXPelsPerMeter = 0;
        bitmap.biYPelsPerMeter = 0;
        bitmap.biClrUsed = 0;
        bitmap.biClrImportant = 0;

        fwrite(reinterpret_cast<char*> (&header), 1, 2, img_fd);
        fwrite(reinterpret_cast<char*> (&header)+4, 1, sizeof(header)-4, img_fd);
        fwrite(reinterpret_cast<char*> (&bitmap), 1, sizeof(bitmap), img_fd);

        if(src_img.color_bit == COLOR_8UC1) {
            int palette_count = 1<<bitmap.biBitCount;
            bool palette_flag = ((palette_count*4 + 14 + bitmap.biSize) == header.bfOffBits);
            if (palette_flag) {
                for(int i=0; i<palette_count; i++) {
                    Color_palette cp(i, i, i, 0);
                    fwrite(reinterpret_cast<char*> (&cp), 1, sizeof(cp), img_fd);
                }
            }
        }

        uchar* data_inv = new uchar[src_img.pixel_count]();

        if(src_img.color_bit == COLOR_8UC3) {
            for(int i=0; i<src_img.pixel_count; i+=3) {
                *(data_inv + i) = *(src_img.data + src_img.color_bit * (src_img.width * (src_img.height - (i/3/src_img.width)-1) + (i/3)%src_img.width));
                *(data_inv + i+1) = *(src_img.data + src_img.color_bit * (src_img.width * (src_img.height - (i/3/src_img.width)-1) + (i/3)%src_img.width) + 1);
                *(data_inv + i+2) = *(src_img.data + src_img.color_bit * (src_img.width * (src_img.height - (i/3/src_img.width)-1) + (i/3)%src_img.width) + 2);
            }
        }
        else {
            for(int i=0; i<src_img.pixel_count; i++) {
                *(data_inv + i) = *(src_img.data + src_img.width * (src_img.height - (i/src_img.width)-1) + i%src_img.width);
            }
        }

        fwrite(data_inv, 1, src_img.pixel_count, img_fd);
        delete [] data_inv;
        fclose(img_fd);
    }

} //BmpCV