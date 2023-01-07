#ifndef BMPCV_IMG_PROC_2_H
#define BMPCV_IMG_PROC_2_H

#include <cmath>
#include <Eigen>
#include "bmp.h"

namespace BmpCV {

    Img low_filter(const Img& src_img, int f_size);//平滑；f_size*f_size的低通滤波,邻域平均法
    Img low_filter_p(const Img& src_img, int f_size, int lim);//平滑；f_size*f_size的低通滤波,超限邻域平均法T=lim
    Img med_filter(const Img& src_img, int f_size);//平滑；f_size*f_size的中值滤波
    Img Laplace_sharpen(const Img& src_img, int l_flag);//锐化；3*3的拉普拉斯锐化;l_flag=1是变形模板+高增益滤波；=0或是基本模板
    Img show_histogram(const Img& src_img);//(归一化后的)直方图的计算及显示
    int (*get_vol(const Img& src_img))[256];//辅助函数，在直方图搜索中调用，灰度图每个灰度的像素值个数
    int *gray_map(int *a, int h_size, int w_size);//辅助函数，在直方图均衡化中调用，目的是保存灰度映射关系
    Img equalize_histogram(const Img& src_img);//直方图均衡化
    Img hist_search(const Img& src_img, int num);//根据直方图，搜索图片；num是查找图片的数目


} // BmpCV


#endif //BMPCV_IMG_PROC_2_H

