#ifndef BMPCV_BMP_H
#define BMPCV_BMP_H
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <unordered_map>
#include <Eigen>
#include "error.h"

static const int READ_STEP = 4;
typedef unsigned char uchar;

namespace BmpCV {

    enum COLOR_DEPTH {COLOR_8UC1 = 0x01, COLOR_8UC3 = 0x03, COLOR_INDEXED = 0x03, COLOR_ALPHA = 0x04};
    enum COLOR_SPACE {COLOR_RGB = 0x10, COLOR_GRAY = 0x20, COLOR_HSV = 0x30};


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

    typedef struct cp {
        uint8_t blue_mask;
        uint8_t green_mask;
        uint8_t red_mask;
        uint8_t alpha_mask;
        cp() = default;
        cp(uint8_t _b, uint8_t _g, uint8_t _r, uint8_t _a): blue_mask(_b), green_mask(_g), red_mask(_r), alpha_mask(_a){}
    }Color_palette;

    typedef struct pt_2d {
        int x;
        int y;
        pt_2d() = default;
        pt_2d(int _x, int _y):x(_x), y(_y){}
    } point_pair_2d;
    typedef struct pt_3d {
        int x;
        int y;
        int z;
        pt_3d() = default;
        pt_3d(int _x, int _y, int _z):x(_x), y(_y), z(_z){}
    } point_pair_3d;

    class Img {
    public:
        int width = -1; // or cols
        int height = -1; // or rows
        int color_bit = COLOR_8UC3;
        int color_space = COLOR_RGB;

        uchar* data = nullptr;
        long pixel_count = 0;
        std::unordered_map<int, Color_palette> color_map;

        Img();
        Img(int cols, int rows, int flag);
        Img(Eigen::MatrixXd matrix, int flag);
        Img(const Img& im);
        ~Img();
        Img& operator=(const Img& im);
        void palette2map(Color_palette* palette, int count);
        uchar loc(int row, int col, int channel) const;
        uchar loc(pt_2d pt, int channel) const;
        uchar& iloc(int row, int col, int channel);

    };

    Img readImg(const std::string& filename);
    void writeImg(const Img& src_img, const std::string& filename);


}


#endif //BMPCV_BMP_H
