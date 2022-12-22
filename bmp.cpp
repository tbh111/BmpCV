#include "bmp.h"

namespace TbhCV {

    Img::Img() {

    }

    Img::Img(int cols, int rows, int flag) {
        width = cols;
        height = rows;
        color_bit = flag & 0x0F;
        color_space = flag & 0xF0;
    }

    Img::~Img() {
        std::cout << "Img deleted" << std::endl;
    }

    Img img_read(std::string filename) {
        if(filename.empty()) {
            throw CV_runtime_error(FILE_OPEN_ERROR, "Empty filename");
        }
        std::ifstream img_fd;
        img_fd.open(filename, std::ios::in | std::ios::binary); // rb

        if(img_fd.is_open()) {
            // step 1: read bmp file header
            BMP_header header;
            img_fd.read((char*) &header, sizeof header);
            if(header.bfType != 0x4d42) {
                throw CV_runtime_error(BAD_IMAGE_INFO, "File bfType error");
            }

            // step 2: read bitmap info, initialize Img object
            Bitmap_info bitmap;
            img_fd.read((char*) &bitmap, sizeof bitmap);
            if(bitmap.biBitCount != 0x28) {
                throw CV_runtime_error(BAD_IMAGE_INFO, "File bit count != 0x28");
            }
            if(bitmap.biHeight < 0) {
                throw CV_runtime_error(BAD_IMAGE_INFO, "Unsupported BMP origin with height<0");
            }
            Img src_img(bitmap.biWidth, bitmap.biHeight, bitmap.biBitCount/8);
            int row_data = src_img.width * src_img.color_bit;
            int row_size = (row_data + 3) / 4 * 4;

            // step 3: read color palette (optional)
            if (src_img.color_space == 4) {
                if(bitmap.biSize >= (sizeof header + sizeof bitmap)) {
                    Color_palette palette;
                    img_fd.read((char*) &palette, sizeof palette);
                }
                else {
                    throw CV_runtime_error(BAD_IMAGE_INFO, "BMP not contain color header");
                }
            }

            // step 4: read bmp data
            img_fd.seekg(header.bfOffBits, img_fd.beg);
            src_img.data = new uint16_t[src_img.width * src_img.height * src_img.color_bit];
            for(int i=0; i<src_img.height; i++) {
                img_fd.read((char*) (src_img.data + i*row_data), row_data);
                img_fd.seekg(row_size - row_data, img_fd.cur);
            }

            return src_img;
        }
        else {
            throw CV_runtime_error(FILE_OPEN_ERROR, "File open error");
        }

    }

}