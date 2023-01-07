#include "filter.h"

namespace BmpCV {

//    Eigen::MatrixXd createButterKernel(const Img& src_img, double D0, int n) {
//        Eigen::MatrixXd kernel(src_img.height, src_img.width);
//        for(int i=0; i<src_img.height; i++) {
//            for(int j=0; j<src_img.width; j++) {
//                double D = sqrt(pow(i-double(src_img.height)/2, 2) + pow(j-double(src_img.width)/2, 2));
//                kernel(i, j) = 1.0f / (1.0f + pow(D/D0, 2*n));
//            }
//        }
//        return kernel;
//    }

    Img freqFilterImg(const Img& src_img, const Eigen::MatrixXd& kernel) {
        if(kernel.rows() != src_img.height || kernel.cols() != src_img.width)
            throw CV_runtime_error(INDEX_EQZ, "Kernel size not equal to image");
        Img img_gray = removeColor(src_img);
        Cp_mat img_fft = imgFFT2D(img_gray);
        Cp_mat img_shift = imgFFTShift1(img_fft);
        for(int i=0; i<img_gray.height; i++) {
            for(int j=0; j<img_gray.width; j++) {

                img_shift[i][j].real = img_shift[i][j].real * kernel(i, j);
                img_shift[i][j].imag = img_shift[i][j].imag * kernel(i, j);
            }
        }
        Cp_mat img_shift1 = imgFFTShift1(img_shift);
        Img img_ifft = imgIFFT2D(img_shift1);
        return img_ifft;
    }
    //巴特沃斯低通
    Eigen::MatrixXd createButterLowKernel(const Img& src_img, double D0, int n) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for(int i=0; i<src_img.height; i++) {
            for(int j=0; j<src_img.width; j++) {
                double D = sqrt(pow(i-double(src_img.height)/2, 2) + pow(j-double(src_img.width)/2, 2));
                kernel(i, j) = 1.0f / (1.0f + pow(D/D0, 2*n));
            }
        }
        return kernel;
    }


    //理想低通
    Eigen::MatrixXd createIdealLowKernel(const Img& src_img, double D0) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                if(D < D0)
                    kernel(i, j) = 1.0f;
                else
                    kernel(i, j) = 0.0f;
            }
        }
        return kernel;
    }

    //指数低通
    Eigen::MatrixXd createExponentialLowKernel(const Img& src_img, double D0, int n) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                kernel(i, j) = exp(-pow(D/D0, n));
            }
        }
        return kernel;
    }

    //高斯低通
    Eigen::MatrixXd createGaussianLowKernel(const Img& src_img, double D0) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                kernel(i, j) = exp(-pow(D,2)/(2*pow(D0,2)));
            }
        }
        return kernel;
    }

    //梯形低通 D0<D1
    Eigen::MatrixXd createTrapezoidalLowKernel(const Img& src_img, double D0, double D1) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                kernel(i, j) = exp(-pow(D, 2) / (2 * pow(D0, 2)));
                if(D < D0)
                    kernel(i, j) = 1.0f;
                else if(D >= D0 && D <= D1)
                    kernel(i, j) = (D1 - D) / (D1 - D0);
                else
                    kernel(i, j) = 0.0f;
            }
        }
        return kernel;
    }

    //巴特沃斯高通
    Eigen::MatrixXd createButterHighKernel(const Img& src_img, double D0, int n) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        double a, b, c;
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));

                kernel(i, j) = 1.0f -  1.0f / (1.0f + pow(D / D0, 2 * n));
            }
        }
        return kernel;
    }

    //理想高通
    Eigen::MatrixXd createIdealHighKernel(const Img& src_img, double D0) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                if(D > D0)
                    kernel(i, j) = 1.0f;
                else
                    kernel(i, j) = 0.0f;
            }
        }
        return kernel;
    }

    //指数高通
    Eigen::MatrixXd createExponentialHighKernel(const Img& src_img, double D0, int n) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                kernel(i, j) = exp(-pow(D0 / D, n));
            }
        }
        return kernel;
    }

    //高斯高通
    Eigen::MatrixXd createGaussianHighKernel(const Img& src_img, double D0) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                kernel(i, j) = 1.0f - exp(-pow(D, 2) / (2 * pow(D0, 2)));
            }
        }
        return kernel;
    }

    // 梯形高通 D1<D0
    Eigen::MatrixXd createTrapezoidalHighKernel(const Img& src_img, double D0, double D1) {
        Eigen::MatrixXd kernel(src_img.height, src_img.width);
        for (int i = 0; i < src_img.height; i++) {
            for (int j = 0; j < src_img.width; j++) {
                double D = sqrt(pow(i - double(src_img.height) / 2, 2) + pow(j - double(src_img.width) / 2, 2));
                kernel(i, j) = exp(-pow(D, 2) / (2 * pow(D0, 2)));
                if( D < D1)
                    kernel(i, j) = 0.0f;
                else if( D >= D1 && D <= D0)
                    kernel(i, j) = (D - D1) / (D0 - D1);
                else
                    kernel(i, j) = 1.0f;
            }
        }
        return kernel;
    }



} // BmpCV