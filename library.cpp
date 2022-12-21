#include "library.h"

namespace TbhCV {

    Img::Img() {

    }

    Img::Img(int cols, int rows, int flag) {

    }

    Img::~Img() {
        std::cout << "Img deleted" << std::endl;
    }

    Img img_read(std::string filename) {
        if(filename.empty()) {
            throw CV_runtime_error(FILE_OPEN_ERROR, "EMPTY FILENAME");
        }
        std::ifstream img_fd;
        img_fd.open(filename, std::ios::in | std::ios::binary); // rb

        if(img_fd.is_open()) {
            // step 1: read bmp file header
            BMP_header header;
            img_fd.read((char*) &header, sizeof header);

            // step 2: read bitmap info
            Bitmap_info bitmap;
            img_fd.read((char*) &bitmap, sizeof bitmap);


            // step 3: read color palette (optional)

            // step 4: read bmp data
        }
        else {
            throw CV_runtime_error(FILE_OPEN_ERROR, "FILE open error");
        }

    }

}