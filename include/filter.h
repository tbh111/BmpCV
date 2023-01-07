#ifndef BMPCV_FILTER_H
#define BMPCV_FILTER_H

#include <Eigen>
#include "bmp.h"
#include "transform.h"
#include "img_proc.h"
#include "error.h"


namespace BmpCV {

//    Eigen::MatrixXf createButterKernel(const Img& src_img, float D0, int n);
    Eigen::MatrixXd createButterLowKernel(const Img& src_img, double D0, int n);
    Eigen::MatrixXd createIdealLowKernel(const Img& src_img, double D0);
    Eigen::MatrixXd createExponentialLowKernel(const Img& src_img, double D0, int n);
    Eigen::MatrixXd createGaussianLowKernel(const Img& src_img, double D0);
    Eigen::MatrixXd createTrapezoidalLowKernel(const Img& src_img, double D0, double D1);
    Eigen::MatrixXd createButterHighKernel(const Img& src_img, double D0, int n);
    Eigen::MatrixXd createIdealHighKernel(const Img& src_img, double D0);
    Eigen::MatrixXd createExponentialHighKernel(const Img& src_img, double D0, int n);
    Eigen::MatrixXd createGaussianHighKernel(const Img& src_img, double D0);
    Eigen::MatrixXd createTrapezoidalHighKernel(const Img& src_img, double D0, double D1);
    Img freqFilterImg(const Img& src_img, const Eigen::MatrixXd& kernel);

} // BmpCV

#endif //BMPCV_FILTER_H
