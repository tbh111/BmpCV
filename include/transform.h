#ifndef BMPCV_TRANSFORM_H
#define BMPCV_TRANSFORM_H

#include <iostream>
#include <Eigen>
#include <vector>
#include "bmp.h"
#include "img_proc.h"

namespace BmpCV {

    template<class Type>
    class Cp {
    public:
        Type real;
        Type imag;
        Cp();
        Cp(Type _r, Type _i);
        Cp operator + (const Cp& b);
        Cp operator - (const Cp& b);
        Cp operator * (const Cp& b);
        Cp operator / (const int& b);
    };
    typedef std::vector<std::vector<Cp<double> > > Cp_mat;
    typedef std::vector<std::vector<Cp<uchar> > > Cp_uchar_mat;
    typedef std::vector<std::vector<double> > double_mat;
    Img imgPadding(const Img& src_img);
    std::vector<Cp<double> > imgFFT1D(std::vector<Cp<double> > vector, int length, int flag);
    Cp_mat imgFFT2D(const Img& src_img);
    Img imgFFTShift(const Cp_mat& mat, int return_flag);
    Cp_mat imgFFTShift1(const Cp_mat& mat);
    Img imgIFFT2D(const Cp_mat & mat);

    double_mat imgDCT2D(const Img& src_img);
    Img imgDCTNormalize(const double_mat& mat);
    Img imgIDCT2D(const double_mat& mat);

} // BmpCV

static int getPadSize(int size);
static int reverseBinary(int bin, int length);

#endif //BMPCV_TRANSFORM_H
