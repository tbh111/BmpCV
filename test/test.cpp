#include <iostream>
#include "bmp.h"
#include "gui.h"
#include "img_proc.h"

int main() {
    std::cout << "test start" << std::endl;
    BmpCV::Img im = BmpCV::readImg("bmp_sample/bmp_24.bmp");

//    BmpCV::writeImg(im, "bmp_sample/RAY2.bmp");
//    BmpCV::Img im_rotated = BmpCV::rotateImg(im, 60, BmpCV::INTER_BILINEAR);
//    BmpCV::Img im_resized = BmpCV::resizeImg(im, 800, 600, BmpCV::INTER_NEARST);
//    BmpCV::Img im_flip_v = BmpCV::flipImg(im, BmpCV::FLIP_V);
//    BmpCV::Img im_flip_h = BmpCV::flipImg(im, BmpCV::FLIP_H);
//    BmpCV::Img im_gray = BmpCV::removeColor(im);
//    BmpCV::Img im_roi = BmpCV::getRoi(im, BmpCV::point_pair_2d(50, 50), BmpCV::point_pair_2d(90, 90));
//    BmpCV::Img im_trans = BmpCV::translationImg(im, 20, 20, BmpCV::point_pair_3d(255, 255, 255));
    BmpCV::createWindow();
    //uchar data[5] = "test";
    //std::cout << TbhCV::dataSend(data, 5);
    BmpCV::imgShow(im);
    system("pause");
    return 0;
}