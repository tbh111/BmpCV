#ifndef TBHCV_BMP_H
#define TBHCV_BMP_H
#include <fstream>
#include <iostream>
#include <exception>

static const int READ_STEP = 4;

namespace TbhCV {

    enum COLOR_DEPTH {COLOR_8UC1 = 0x01, COLOR_8UC3 = 0x03, COLOR_ALPHA = 0x04};
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
        uint16_t bfType = 0;
        uint32_t bfSize = 0;
        uint32_t bfReserved = 0;
        uint32_t bfOffBits = 0;
    };

    struct Bitmap_info {
        uint32_t biSize = 0;
        int32_t biWidth = 0;
        int32_t biHeight = 0;
        uint16_t biPlanes = 1;
        uint16_t biBitCount = 0;
        uint32_t biCompression = 0;
        uint32_t biSizeImages = 0;
        int32_t biXPelsPerMeter = 0;
        int32_t biYPelsPerMeter = 0;
        uint32_t biClrUsed = 0;
        uint32_t biClrImportant = 0;
    };

    struct Color_palette {
        uint32_t blue_mask = 0x000000ff;
        uint32_t green_mask = 0x0000ff00;
        uint32_t red_mask = 0x00ff0000;
        uint32_t alpha_mask = 0xff000000;
        uint32_t color_space_type = 0x73524742; // default sRGB
        uint32_t not_used[16] = {0};
    };

    class Img {
    public:
        int width = -1; // or cols
        int height = -1; // or rows
        int color_bit = COLOR_8UC3;
        int color_space = COLOR_RGB;

        uint16_t* data = nullptr;

        Img();
        Img(int cols, int rows, int flag);
        ~Img();
        // TODO: A copy constructor
    };

    Img img_read(std::string filename);
}


#endif //TBHCV_BMP_H
