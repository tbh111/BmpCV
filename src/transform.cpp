#include "transform.h"

namespace BmpCV {

    template<class Type>
    Cp<Type>::Cp() {
        real = 0;
        imag = 0;
    }

    template<class Type>
    Cp<Type>::Cp(Type _r, Type _i) {
        real = _r;
        imag = _i;
    }

    template<class Type>
    Cp<Type> Cp<Type>::operator + (const Cp<Type>& b) {
        Cp<Type> _cp(this->real + b.real, this->imag + b.imag);
        return _cp;
    }

    template<class Type>
    Cp<Type> Cp<Type>::operator - (const Cp<Type>& b) {
        Cp<Type> _cp(this->real - b.real, this->imag - b.imag);
        return _cp;
    }

    template<class Type>
    Cp<Type> Cp<Type>::operator * (const Cp<Type>& b) {
        Cp<Type> _cp(this->real * b.real - this->imag * b.imag, this->real * b.imag + this->imag * b.real);
        return _cp;
    }

    template<class Type>
    Cp<Type> Cp<Type>::operator / (const int& b) {
        Cp<Type> _cp(this->real*1.0 / b, this->imag*1.0 / b);
        return _cp;
    }

    Img imgPadding(const Img& src_img) {
        if(src_img.color_bit != COLOR_8UC1)
            throw CV_runtime_error(COLOR_ERROR, "Pad image should be grayscale");
        int pad_w = ::getPadSize(src_img.width);
        int pad_h = ::getPadSize(src_img.height);
        Img pad_img(pad_w, pad_h, src_img.color_bit|src_img.color_space);
        for(int i=0; i<pad_h; i++) {
            for(int j=0; j<pad_w; j++) {
                if(i<src_img.height && j<src_img.width)
                    pad_img.iloc(i, j, 0) = src_img.loc(i, j, 0);
                else
                    pad_img.iloc(i, j, 0) = 0;
            }
        }
        return pad_img;
    }

    std::vector<Cp<double> > imgFFT1D(std::vector<Cp<double> > vector, int length, int flag) {
        int index;
        std::vector<Cp<double> > vector_reverse(length);
        for(int i=0; i<length; i++) {
            index = reverseBinary(i, log2(length));
            vector_reverse[i] = vector[index];
        }

        std::vector<Cp<double> > WN(length/2);
        for(int i=0; i<length/2; i++) {
            WN[i].real = cos(2*M_PI*i / length);
            WN[i].imag = -sin(2*M_PI*i / length) * flag;
        }

        int index0, index1;
        Cp<double>  temp;
        for(int step_length=2; step_length<=length; step_length*=2) {
            for(int step=0; step<length/step_length; step++) {
                for(int i=0; i<step_length/2; i++) {
                    index0 = step_length * step + i;
                    index1 = step_length * step + i + step_length/2;

                    temp = vector_reverse[index1] * WN[length/step_length*i];
                    vector_reverse[index1] = vector_reverse[index0] - temp;
                    vector_reverse[index0] = vector_reverse[index0] + temp;
                }
            }
        }

        std::vector<Cp<double> > vector_result(length);
        for(int i=0; i<length; i++) {
            if(flag == -1) {
                vector_result[i] = vector_reverse[i] / length;
            }
            else {
                vector_result[i] = vector_reverse[i];
            }
        }
        return vector_result;
    }

    Cp_mat imgFFT2D(const Img& src_img) {
        Img gray_img = removeColor(src_img);
        Img fft_img(src_img.height, src_img.width, COLOR_8UC1|COLOR_GRAY);
        Cp_mat complex_mat(gray_img.height, std::vector<Cp<double> >(gray_img.width));
        std::vector<Cp<double> > row_vector(gray_img.width);
        std::vector<Cp<double> > row_vector_fft(gray_img.width);

        for(int i1=0; i1<gray_img.height; i1++) {
            for(int j1=0; j1<gray_img.width; j1++) {
                row_vector[j1].real = double(gray_img.loc(i1, j1, 0)) / 255;
                row_vector[j1].imag = 0;
            }

            row_vector_fft = imgFFT1D(row_vector, gray_img.width, 1);

            for(int k1=0; k1<gray_img.width; k1++) {
                complex_mat[i1][k1].real = row_vector_fft[k1].real;
                complex_mat[i1][k1].imag = row_vector_fft[k1].imag;
            }
        }

        std::vector<Cp<double> > col_vector(gray_img.height);
        std::vector<Cp<double> > col_vector_fft(gray_img.height);
        for(int i2=0; i2<gray_img.width; i2++) {
            for(int j2=0; j2<gray_img.height; j2++) {
                col_vector[j2].real = complex_mat[j2][i2].real;
                col_vector[j2].imag = complex_mat[j2][i2].imag;
            }

            col_vector_fft = imgFFT1D(col_vector, gray_img.height, 1);

            for(int k2=0; k2<gray_img.height; k2++) {
                complex_mat[k2][i2].real = col_vector_fft[k2].real;
                complex_mat[k2][i2].imag = col_vector_fft[k2].imag;
            }
        }

        return complex_mat;
    }


    Img imgFFTShift(const Cp_mat& mat, int return_flag) {
        int height = mat.size();
        int width = mat[0].size();
        Img dst_img(width, height, COLOR_8UC1);
        Cp_mat shift_mat(height, std::vector<Cp<double> >(width));

        for(int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {
                if(i < height/2 && j < width/2) { // 2
                    shift_mat[i][j] = mat[i+height/2][j+width/2];
                }
                else if(i < height/2 && j >= width/2) { // 1
                    shift_mat[i][j] = mat[i+height/2][j-width/2];
                }
                else if(i >= height/2 && j < width/2) { // 3
                    shift_mat[i][j] = mat[i-height/2][j+width/2];
                }
                else if(i >= height/2 && j >= width/2) { // 4
                    shift_mat[i][j] = mat[i-height/2][j-width/2];
                }
            }
        }

        if(return_flag == 0) {
            for(int i=0; i<height; i++) {
                for(int j=0; j<width; j++) {
                    dst_img.iloc(i, j, 0) = static_cast<uchar>(sqrt(pow(shift_mat[i][j].real, 2) + pow(shift_mat[i][j].imag, 2)));
                }
            }
        }

        else if(return_flag == 1) {
            for(int i=0; i<height; i++) {
                for(int j=0; j<width; j++) {
                    dst_img.iloc(i, j, 0) = static_cast<uchar>(abs(shift_mat[i][j].real));
                }
            }
        }

        else if(return_flag == 2) {
            for(int i=0; i<height; i++) {
                for(int j=0; j<width; j++) {
                    dst_img.iloc(i, j, 0) = static_cast<uchar>(abs(shift_mat[i][j].imag));
                }
            }
        }

        else if(return_flag == -1) {
            for(int i=0; i<height; i++) {
                for(int j=0; j<width; j++) {
                    dst_img.iloc(i, j, 0) = static_cast<uchar>(sqrt(pow(mat[i][j].real, 2) + pow(mat[i][j].imag, 2)));
                }
            }
        }

        return dst_img;
    }


    Img imgIFFT2D(const Cp_mat & mat) {
        int height = mat.size();
        int width = mat[0].size();
        Img dst_img(width, height, COLOR_8UC1|COLOR_GRAY);
        Cp_mat complex_mat(height, std::vector<Cp<double> >(width));
        std::vector<Cp<double> > row_vector(width);
        std::vector<Cp<double> > row_vector_fft(width);

        for(int i1=0; i1<height; i1++) {
            for(int j1=0; j1<width; j1++) {
                row_vector[j1] = mat[i1][j1];
            }

            row_vector_fft = imgFFT1D(row_vector, width, -1);

            for(int k1=0; k1<width; k1++) {
                complex_mat[i1][k1] = row_vector_fft[k1];
            }
        }

        std::vector<Cp<double> > col_vector(height);
        std::vector<Cp<double> > col_vector_fft(height);
        for(int i2=0; i2<width; i2++) {
            for(int j2=0; j2<height; j2++) {
                col_vector[j2] = complex_mat[j2][i2];
            }

            col_vector_fft = imgFFT1D(col_vector, height, -1);

            for(int k2=0; k2<height; k2++) {
                complex_mat[k2][i2] = col_vector_fft[k2];
            }
        }
        double a;
        uchar b;
        for(int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {
                a = complex_mat[i][j].real*255;
                b = static_cast<uchar>(a);
                if(complex_mat[i][j].real*255 < -1) {
                    a = abs(a);
                    b = static_cast<uchar>(a);
                }
                dst_img.iloc(i, j, 0) = b;
            }
        }

        return dst_img;
    }

    Cp_mat imgFFTShift1(const Cp_mat& mat) {
        int height = mat.size();
        int width = mat[0].size();
        Img dst_img(width, height, COLOR_8UC1);
        Cp_mat shift_mat(height, std::vector<Cp<double> >(width));
        for(int i=0; i<height; i++) {
            for(int j=0; j<width; j++) {
                if(i < height/2 && j < width/2) { // 2
//                    std::cout << i << " " << j << " to " <<  i+height/2 << " " << j+width/2 << std::endl;
                    shift_mat[i][j] = mat[i+height/2][j+width/2];
                }
                else if(i < height/2 && j >= width/2) { // 1
//                    std::cout << i << " " << j << " to " <<  i+height/2 << " " << j-width/2 << std::endl;
                    shift_mat[i][j] = mat[i+height/2][j-width/2];
                }
                else if(i >= height/2 && j < width/2) { // 3
//                    std::cout << i << " " << j << " to " <<  i-height/2 << " " << j+width/2 << std::endl;
                    shift_mat[i][j] = mat[i-height/2][j+width/2];
                }
                else if(i >= height/2 && j >= width/2) { // 4
//                    std::cout << i << " " << j << " to " <<  i-height/2 << " " << j-width/2 << std::endl;
                    shift_mat[i][j] = mat[i-height/2][j-width/2];
                }
            }
        }
        return shift_mat;
    }

    double_mat imgDCT2D(const Img& src_img) {
        Img gray_img = removeColor(src_img);
        double_mat mat(gray_img.height, std::vector<double >(gray_img.width));
        double_mat mat1(gray_img.height, std::vector<double >(gray_img.width));
        double a1=0.0, a2 = 0.0;

        for(int i1=0; i1<gray_img.height; i1++) {
            for(int j1=0; j1<gray_img.width; j1++) {
                if(j1 == 0)
                    a1 = sqrt(1.0 / gray_img.width);
                else
                    a1 = sqrt(2.0 / gray_img.width);
                double temp = 0.0;
                for (int k1=0; k1<gray_img.width; k1++) {
                    temp += double(gray_img.loc(i1, k1, 0)) / 255 * cos((2*k1 + 1) * j1 * M_PI / (2*gray_img.width));
                }
                mat[i1][j1] = a1 * temp;
            }
        }

        for(int i2=0; i2<gray_img.width; i2++) {
            for(int j2=0; j2<gray_img.height; j2++) {
                if(j2 == 0)
                    a2 = sqrt(1.0 / gray_img.height);
                else
                    a2 = sqrt(2.0 / gray_img.height);
                double temp = 0.0;
                for (int k2=0; k2<gray_img.height; k2++) {
                    temp += mat[k2][i2] * cos((2*k2 + 1) * j2 * M_PI / (2*gray_img.height));
                }
                mat1[j2][i2] = a2 * temp;
            }
        }
        return mat1;
    }

    Img imgDCTNormalize(const double_mat& mat) {
        int height = mat.size();
        int width = mat[0].size();
        Img dct_img = Img(width, height, COLOR_8UC1);

        for(int i=0; i<height; i++) { // same display method as matlab
            for(int j=0; j<width; j++) {
                if(mat[i][j] > 1.0)
                    dct_img.iloc(i, j, 0) = 255;
                else if(mat[i][j] < 0.0)
                    dct_img.iloc(i, j, 0) = 0;
                else {
                    dct_img.iloc(i, j, 0) = mat[i][j] * 255;
                }
            }
        }
        return dct_img;
    }

    Img imgIDCT2D(const double_mat& mat) {
        int height = mat.size();
        int width = mat[0].size();
        Img idct_img = Img(width, height, COLOR_8UC1);
        double_mat mat1(height, std::vector<double >(width));
        double_mat mat2(height, std::vector<double >(width));
        double a1=0.0, a2 = 0.0;

//        for(int i1=0; i1<height; i1++) {
//            for(int j1=0; j1<width; j1++) {
//                double temp = 0.0;
//                for (int k1=0; k1<width; k1++) {
//                    if(k1 == 0)
//                        a1 = sqrt(1.0 / width);
//                    else
//                        a1 = sqrt(2.0 / width);
//                    temp += a1 * double(mat[i1][k1]) * cos((2*k1 + 1) * j1 * M_PI / (2*width));
//                }
//                mat1[i1][j1] = temp;
//            }
//        }
//
//        for(int i2=0; i2<width; i2++) {
//            for(int j2=0; j2<height; j2++) {
//                double temp = 0.0;
//                for (int k2=0; k2<height; k2++) {
//                    if(k2 == 0)
//                        a2 = sqrt(1.0 / height);
//                    else
//                        a2 = sqrt(2.0 / height);
//                    temp += a2 * mat1[k2][i2] * cos((2*k2 + 1) * j2 * M_PI / (2*height));
//                }
//                mat2[j2][i2] = temp * 255;
//                if(mat2[j2][i2] < 0) {
//                    idct_img.iloc(j2, i2, 0) = 0;
//                }
//                else if(mat2[j2][i2] > 255) {
//                    idct_img.iloc(j2, i2, 0) = 255;
//                }
//                else {
//                    idct_img.iloc(j2, i2, 0) = static_cast<uchar>(temp * 255);
//                }
//            }
//        }

        for(int i1=0; i1<height; i1++) { // o((n)^4), very slow
            for(int j1=0; j1<width; j1++) {
                double temp = 0.0;
                for(int i11=0; i11<height; i11++) {
                    for(int j11=0; j11<width; j11++) {
                        if(i11 == 0)
                            a1 = sqrt(1.0 / height);
                        else
                            a1 = sqrt(2.0 / height);
                        if(j11 == 0)
                            a2 = sqrt(1.0 / width);
                        else
                            a2 = sqrt(2.0 / width);
                        temp += a1 * a2 * mat[i11][j11] * cos((2*i1+1)* i11 * M_PI / (2*height))
                                * cos((2*j1+1) * j11 * M_PI /(2*width));
                    }
                }
                idct_img.iloc(i1, j1, 0) = temp * 255;
            }
        }
        return idct_img;
    }

} // BmpCV


static int getPadSize(int size) {
    if(size < 0)
        return 0;
    int temp = size - 1;
    temp |= temp >> 1;
    temp |= temp >> 2;
    temp |= temp >> 4;
    temp |= temp >> 8;
    temp |= temp >> 16;
    return (temp < 0) ? 1: (temp + 1);
}

static int reverseBinary(int bin, int length) {
    int res = 0;
    for(int i=0; i<length; i++) {
        if(bin & (1<<i))
            res |= (1 << (length-1-i));
    }
    return res;
}