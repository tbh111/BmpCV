#ifndef TBHCV_LIBRARY_H
#define TBHCV_LIBRARY_H
#include <fstream>
#include <iostream>
#include <exception>

typedef unsigned char uchar;
static const int READ_STEP = 4;

namespace TbhCV {

    enum COLOR_DEPTH {COLOR_8UC1 = 0x00, COLOR_8UC3 = 0x01, COLOR_BINARY = 0x02, COLOR_ALPHA = 0x03};
    enum COLOR_SPACE {COLOR_RGB = 0x10, COLOR_GRAY = 0x20, COLOR_HSV = 0x30};
    enum ERROR_CODE  {FILE_OPEN_ERROR = 0, BAD_IMAGE_INFO = 1};

    class CV_runtime_error : public std::runtime_error {
    public:
        CV_runtime_error(int error_code) : std::runtime_error(""), code(error_code) {}
        CV_runtime_error(int error_code, const std::string& error_info) : std::runtime_error(error_info), code(error_code) {}
    private:
        int code = 0;
    };

    struct BMP_header {
        char16_t bfType;
        char32_t bfSize;
        char32_t bfReserved;
        char32_t bfOffBits;
    };

    struct Bitmap_info {
        char32_t biSize;
        char32_t biWidth;
        char32_t biHeight;
        char16_t biPlanes = 1;
        char16_t biBitCount;
        char32_t biCompression = 0;
        char32_t biSizeImages;
        signed int biXPelsPerMeter;
        signed int biYPelsPerMeter;
        int biClrUsed;
        int biClrImportant;
    };

    struct Color_palette {
        uchar blue;
        uchar green;
        uchar red;
        uchar alpha;
    };

    class Img {
    public:
        int width = -1; // or cols
        int height = -1; // or rows
        int channel = -1;
        int color_bit = COLOR_8UC1;
        int color_space = COLOR_RGB;

        uchar* data = nullptr;

        Img();
        Img(int cols, int rows, int flag);
        ~Img();
        void read_data();


    };

    Img img_read(std::string filename);
}


#endif //TBHCV_LIBRARY_H
