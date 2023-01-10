#include <iostream>
#include <Eigen>
#include "bmp.h"
#include "gui.h"
#include "img_proc.h"
#include "img_proc_2.h"
#include "transform.h"
#include "filter.h"

int main() {
//    std::cout << "input file" << std::endl;
//    std::string path;
//    std::cin >> path;
    BmpCV::Img im = BmpCV::readImg("bmp_sample/lena_nearest_100_100.bmp");
    BmpCV::double_mat dct = BmpCV::imgDCT2D(im);
    BmpCV::Img dct_img = BmpCV::imgDCTNormalize(dct);
    BmpCV::Img idct_img = BmpCV::imgIDCT2D(dct);

//    BmpCV::Img im_gray = BmpCV::removeColor(im);
//    BmpCV::Img pad = BmpCV::imgPadding(im_gray);
//    BmpCV::Cp_mat fft = BmpCV::imgFFT2D(pad);
//    BmpCV::Img fft_shift = BmpCV::imgFFTShift(fft, 0);
//    BmpCV::Img fft1 = BmpCV::imgIFFT2D(fft);

//    Eigen::MatrixXd k = BmpCV::createButterLowKernel(pad, 80, 2);
//    BmpCV::Img im_f = BmpCV::freqFilterImg(pad, k);
//    BmpCV::Cp_mat fft_f = BmpCV::imgFFT2D(im_f);
//    BmpCV::Img fft_shift_f = BmpCV::imgFFTShift(fft_f, 0);
//    BmpCV::Img im_cut = BmpCV::getRoi(im_f, BmpCV::point_pair_2d(0, 0), BmpCV::point_pair_2d(im.width, im.height));

//    BmpCV::writeImg(im, "bmp_sample/bmp_241.bmp");
//    BmpCV::Img im_rotated = BmpCV::rotateImg(im, 30, BmpCV::INTER_NEARST);
//    BmpCV::Img im_resized = BmpCV::resizeImg(im, 800, 600, BmpCV::INTER_NEARST);
//    BmpCV::Img im_flip_v = BmpCV::flipImg(im, BmpCV::FLIP_V);
//    BmpCV::Img im_flip_h = BmpCV::flipImg(im, BmpCV::FLIP_H);
//    BmpCV::Img im_gray = BmpCV::removeColor(im);
//    BmpCV::Img im_roi = BmpCV::getRoi(im, BmpCV::point_pair_2d(0, 0), BmpCV::point_pair_2d(90, 90));
//    BmpCV::Img im_trans = BmpCV::translationImg(im, 20, 20, BmpCV::point_pair_3d(255, 255, 255));

    BmpCV::createWindow();
    BmpCV::imgShow(idct_img);



    system("pause");
    return 0;
}