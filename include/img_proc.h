#ifndef BMPCV_IMG_PROC_H
#define BMPCV_IMG_PROC_H
#include <cmath>
#include <Eigen>
#include "bmp.h"


namespace BmpCV {

    enum PROC_FLAG {FLIP_V = 0, FLIP_H = 1, INTER_NEARST = 2, INTER_BILINEAR = 3};

    Img rotateImg(const Img& src_img, double angle, int flag);
    Img flipImg(const Img& src_img, int flag);
    Img resizeImg(const Img& src_img, int size_x, int size_y, int flag);
    Img resizeImg(const Img& src_img, double ratio);
    Img getRoi(const Img& src_img, point_pair_2d p1, point_pair_2d p2);
    Img translationImg(const Img& src_img, int offset_x, int offset_y, pt_3d fill_color);
    Img removeColor(const Img& src_img);


} // BmpCV

#endif //BMPCV_IMG_PROC_H
