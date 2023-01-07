#include "img_proc.h"
#include <sstream>

namespace BmpCV {
    Img low_filter(const Img& src_img, int f_size){
        Img dst_img(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
        for(int i=0; i<dst_img.height; i++) { // per row: y
            for(int j=0; j<dst_img.width; j++) { // per col: x
                int x1=j-f_size/2, x2=j+f_size/2, y1=i-f_size/2, y2=i+f_size/2;
                if(x1<0 || x2>=dst_img.width || y1<0 || y2>=dst_img.height){
                    dst_img.iloc(i, j, 0) = src_img.loc(i, j, 0);
                    if(dst_img.color_bit == COLOR_8UC3){
                        dst_img.iloc(i, j, 1) = src_img.loc(i, j, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(i, j, 2);
                    }
                }
                else{
                    double vol0 = 0.0, vol1 = 0.0, vol2 = 0.0;
                    for(int ii=y1;ii<=y2;ii++){
                        for(int jj=x1;jj<=x2;jj++){
                            vol0 += (src_img.loc(ii, jj, 0)/f_size/f_size);
                            if(dst_img.color_bit == COLOR_8UC3){
                                vol1 += (src_img.loc(ii, jj, 1)/f_size/f_size);
                                vol2 += (src_img.loc(ii, jj, 2)/f_size/f_size);
                            }
                        }
                    }
                    dst_img.iloc(i, j, 0) = vol0;
                    if(dst_img.color_bit == COLOR_8UC3){
                        dst_img.iloc(i, j, 1) = vol1;
                        dst_img.iloc(i, j, 2) = vol2;
                    }
                }
            }
        }
        return dst_img;
    }

    Img low_filter_p(const Img& src_img, int f_size, int lim){
        Img dst_img(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
        for(int i=0; i<dst_img.height; i++) { // per row: y
            for(int j=0; j<dst_img.width; j++) { // per col: x
                int x1=j-f_size/2, x2=j+f_size/2, y1=i-f_size/2, y2=i+f_size/2;
                if(x1<0 || x2>=dst_img.width || y1<0 || y2>=dst_img.height){
                    dst_img.iloc(i, j, 0) = src_img.loc(i, j, 0);
                    if(dst_img.color_bit == COLOR_8UC3){
                        dst_img.iloc(i, j, 1) = src_img.loc(i, j, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(i, j, 2);
                    }
                }
                else{
                    double vol0 = 0.0, vol1 = 0.0, vol2 = 0.0;
                    for(int ii=y1;ii<=y2;ii++){
                        for(int jj=x1;jj<=x2;jj++){
                            vol0 += (src_img.loc(ii, jj, 0)/f_size/f_size);
                            if(dst_img.color_bit == COLOR_8UC3){
                                vol1 += (src_img.loc(ii, jj, 1)/f_size/f_size);
                                vol2 += (src_img.loc(ii, jj, 2)/f_size/f_size);
                            }
                        }
                    }
                    if(src_img.loc(i, j, 0) > vol0+lim || src_img.loc(i, j, 0) < vol0-lim) dst_img.iloc(i, j, 0) = vol0;
                    else dst_img.iloc(i, j, 0) = src_img.loc(i, j, 0);
                    if(dst_img.color_bit == COLOR_8UC3){
                        if(src_img.loc(i, j, 1) > vol1+lim || src_img.loc(i, j, 1) < vol1-lim) dst_img.iloc(i, j, 1) = vol1;
                        else dst_img.iloc(i, j, 1) = src_img.loc(i, j, 1);
                        if(src_img.loc(i, j, 2) > vol2+lim || src_img.loc(i, j, 2) < vol2-lim) dst_img.iloc(i, j, 2) = vol2;
                        else dst_img.iloc(i, j, 2) = src_img.loc(i, j, 2);
                    }
                }
            }
        }
        return dst_img;
    }

    Img med_filter(const Img& src_img, int f_size){
        Img dst_img(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
        for(int i=0; i<dst_img.height; i++) { // per row: y
            for(int j=0; j<dst_img.width; j++) { // per col: x
                int size = f_size*f_size;
                int x1=j-f_size/2, x2=j+f_size/2, y1=i-f_size/2, y2=i+f_size/2;
                if(x1<0 || x2>=dst_img.width || y1<0 || y2>=dst_img.height){
                    dst_img.iloc(i, j, 0) = src_img.loc(i, j, 0);
                    if(dst_img.color_bit == COLOR_8UC3){
                        dst_img.iloc(i, j, 1) = src_img.loc(i, j, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(i, j, 2);
                    }
                }
                else{
                    double vol0[size] = {0.0}, vol1[size] = {0.0}, vol2[size] = {0.0};
                    for(int ii=y1;ii<=y2;ii++){
                        for(int jj=x1;jj<=x2;jj++){
                            vol0[f_size*(ii-y1)+jj-x1] = src_img.loc(ii, jj, 0);
                            if(dst_img.color_bit == COLOR_8UC3){
                                vol1[f_size*(ii-y1)+jj-x1] = src_img.loc(ii, jj, 1);
                                vol2[f_size*(ii-y1)+jj-x1] = src_img.loc(ii, jj, 2);
                            }
                        }
                    }
                    double temp=0.0;
                    for(int iy=0;iy<size;iy++){
                        for(int jx=0;jx<size;jx++){
                            if(vol0[iy]>=vol0[jx]){
                                temp=vol0[iy];
                                vol0[iy]=vol0[jx];
                                vol0[jx]=temp;
                            }
                        }
                    }
                    dst_img.iloc(i, j, 0) = vol0[size/2];
                    if(dst_img.color_bit == COLOR_8UC3){
                        temp=0.0;
                        for(int iy=0;iy<size;iy++){
                            for(int jx=0;jx<size;jx++){
                                if(vol1[iy]>=vol1[jx]){
                                    temp=vol1[iy];
                                    vol1[iy]=vol1[jx];
                                    vol1[jx]=temp;
                                }
                            }
                        }
                        dst_img.iloc(i, j, 1) = vol1[size/2];
                        temp=0.0;
                        for(int iy=0;iy<size;iy++){
                            for(int jx=0;jx<size;jx++){
                                if(vol2[iy]>=vol2[jx]){
                                    temp=vol2[iy];
                                    vol2[iy]=vol2[jx];
                                    vol2[jx]=temp;
                                }
                            }
                        }
                        dst_img.iloc(i, j, 2) = vol2[size/2];
                    }
                }
            }
        }
        return dst_img;
    }

    Img Laplace_sharpen(const Img& src_img,int l_flag){
        int f_size = 3;
        Img dst_img(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
        for(int i=0; i<dst_img.height; i++) { // per row: y
            for(int j=0; j<dst_img.width; j++) { // per col: x
                int x1=j-f_size/2, x2=j+f_size/2, y1=i-f_size/2, y2=i+f_size/2;
                if(x1<0 || x2>=dst_img.width || y1<0 || y2>=dst_img.height){
                    dst_img.iloc(i, j, 0) = src_img.loc(i, j, 0);
                    if(dst_img.color_bit == COLOR_8UC3){
                        dst_img.iloc(i, j, 1) = src_img.loc(i, j, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(i, j, 2);
                    }
                }
                else{
                    int kel[3][3]={{0,-1,0},
                                   {-1,4,-1},
                                   {0,-1,0}};;
                    if(l_flag==1){
                        for(int xx=0;xx<3;xx++){
                            for(int yy=0;yy<3;yy++){
                                kel[xx][yy] = -1;
                            }
                        }
                        kel[1][1] = 9;//变形模板+高增益滤波
                    }
                    double vol0 = 0.0, vol1 = 0.0, vol2 = 0.0;
                    for(int ii=y1;ii<=y2;ii++){
                        for(int jj=x1;jj<=x2;jj++){
                            vol0 += (src_img.loc(ii, jj, 0)*kel[ii-y1][jj-x1]);
                            if(dst_img.color_bit == COLOR_8UC3){
                                vol1 += (src_img.loc(ii, jj, 1)*kel[ii-y1][jj-x1]);
                                vol2 += (src_img.loc(ii, jj, 2)*kel[ii-y1][jj-x1]);
                            }
                        }
                    }
                    dst_img.iloc(i, j, 0) = vol0;
                    if(dst_img.color_bit == COLOR_8UC3){
                        dst_img.iloc(i, j, 1) = vol1;
                        dst_img.iloc(i, j, 2) = vol2;
                    }
                }
            }
        }
        return dst_img;
    }

    Img show_histogram(const Img& src_img){
        int count_0[256]={0};
        int count_1[256]={0};
        int count_2[256]={0};
        //直方图统计
        for(int i=0; i<src_img.height; i++) { // per row: y
            for(int j=0; j<src_img.width; j++) { // per col: x
                for(int k=0;k<256;k++){
                    if(src_img.loc(i, j, 0) == k){
                        count_0[k]++;
                        break;
                    }
                }
                if(src_img.color_bit == COLOR_8UC3){
                    for(int k=0;k<256;k++){
                        if(src_img.loc(i, j, 1) == k){
                            count_1[k]++;
                            break;
                        }
                    }
                    for(int k=0;k<256;k++){
                        if(src_img.loc(i, j, 2) == k){
                            count_2[k]++;
                            break;
                        }
                    }
                }
            }
        }
        //将直方图的像素值归一化到0~256
        long max012=0;
        for(int k=0;k<256;k++){
            max012>count_0[k] ? max012=max012+0 : max012=count_0[k] ;
            max012>count_1[k] ? max012=max012+0 : max012=count_1[k] ;
            max012>count_2[k] ? max012=max012+0 : max012=count_2[k] ;
        }
        for(int k=0;k<256;k++){
            count_0[k] = (double)count_0[k]*255.0/(double)max012;
            count_1[k] = (double)count_1[k]*255.0/(double)max012;
            count_2[k] = (double)count_2[k]*255.0/(double)max012;
        }
        //显示直方图
        Img dst_img(256*3+20+60, 256+20, src_img.color_bit|src_img.color_space);

        for(int j=10;j<266;j++){
            for(int i=10;i<count_0[j-10]+10;i++){
                dst_img.iloc(i, j, 0) = 255;
            }
        }
        if(src_img.color_bit == COLOR_8UC3){
            for(int j=296;j<552;j++){
                for(int i=10;i<count_1[j-296]+10;i++){
                    dst_img.iloc(i, j, 1) = 255;
                }
            }
            for(int j=582;j<838;j++){
                for(int i=10;i<count_2[j-582]+10;i++){
                    dst_img.iloc(i, j, 2) = 255;
                }
            }
        }
        return flipImg(dst_img, BmpCV::FLIP_V);
    }

    int (*get_vol(const Img& src_img))[256]{
        int count_0[256]={0},count_1[256]={0},count_2[256]={0};
        int (*count)[256]=new int[3][256];
        for(int j=10;j<266;j++){
            for(int i=10;i<266;i++){
                if(src_img.loc(i, j, 0)==0) break;
                count_0[j-10]++;
            }
        }
        if(src_img.color_bit == COLOR_8UC3){
            for(int j=296;j<552;j++){
                for(int i=10;i<266;i++){
                    if(src_img.loc(i, j,  1)==0) break;
                    count_1[j-296]++;
                }
            }
            for(int j=582;j<838;j++){
                for(int i=10;i<266;i++){
                    if(src_img.loc(i, j,  2)==0) break;
                    count_2[j-582]++;
                }
            }
        }
        for(int j=0;j<256;j++){
            count[0][j]=count_0[j];
            count[1][j]=count_1[j];
            count[2][j]=count_2[j];
        }
        return count;
    }
    int *gray_map(int *a, int h_size, int w_size){
        int *gm=new int[256];
        double atemp[256];
        for(int i=0;i<256;i++){atemp[i]=a[i];}
        for(int i=0;i<256;i++){//累计分布密度
            if(i==0)
                atemp[i]= a[i] / (double)(h_size*w_size);
            else
                atemp[i]= atemp[i-1] + a[i] / (double)(h_size*w_size);
        }
        for(int i=0;i<256;i++){
            gm[i]=(int)(255*atemp[i]+0.5);
        }
        return gm;
    }
    Img equalize_histogram(const Img& src_img){
        int count_0[256]={0};
        int count_1[256]={0};
        int count_2[256]={0};
        //直方图统计
        for(int i=0; i<src_img.height; i++) { // per row: y
            for(int j=0; j<src_img.width; j++) { // per col: x
                for(int k=0;k<256;k++){
                    if(src_img.loc(i, j, 0) == k){
                        count_0[k]++;
                        break;
                    }
                }
                if(src_img.color_bit == COLOR_8UC3){
                    for(int k=0;k<256;k++){
                        if(src_img.loc(i, j, 1) == k){
                            count_1[k]++;
                            break;
                        }
                    }
                    for(int k=0;k<256;k++){
                        if(src_img.loc(i, j, 2) == k){
                            count_2[k]++;
                            break;
                        }
                    }
                }
            }
        }
        int *count_0_new=gray_map(count_0, src_img.height, src_img.width);
        int *count_1_new=gray_map(count_1, src_img.height, src_img.width);
        int *count_2_new=gray_map(count_2, src_img.height, src_img.width);

        Img dst_img(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
        for(int i=0; i<dst_img.height; i++) { // per row: y
            for(int j=0,w=0,f0=0,f1=0,f2=0; j<dst_img.width; j++,w++) { // per col: x
                unsigned char hist_g=src_img.loc(i, j, 0);
                dst_img.iloc(i, j, 0)=count_0_new[hist_g];
                hist_g=src_img.loc(i, j, 1);
                dst_img.iloc(i, j, 1)=count_0_new[hist_g];
                hist_g=src_img.loc(i, j, 2);
                dst_img.iloc(i, j, 2)=count_0_new[hist_g];
            }
        }
//        writeImg(dst_img, "C:\\Users\\Liutw\\Desktop\\2.bmp");
//        Img dst_img2(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
//        dst_img2=show_histogram(dst_img);
        return dst_img;
    }

    Img hist_search(const Img& src_img, int num){
        int (*count)[256];
        count = get_vol(flipImg(src_img, BmpCV::FLIP_V));
        Img im[num];
        for (int i=0;i<num;i++){
            std::string str1="bmp_hist/search/";
            std::stringstream str2;
            str2<<i+1;
            std::string str=str1+str2.str()+".bmp";
            im[i] = readImg(str);
            int (*count_im[i])[256];
        }
        int a[num]={0};
        int (*count_im_test)[256];
        for(int w=0;w<num;w++){
            Img im_temp = flipImg(show_histogram(im[w]), BmpCV::FLIP_V);
            count_im_test = get_vol(im_temp);
            for(int i=0; i<3; i++) { // per row: y
                for(int j=0; j<256; j++) { // per col: x
                    a[w] += abs(count_im_test[i][j]-count[i][j]);
                }
            }
        }
        for(int i=0;i<num-1;i++){
            for(int j=0;j<num-1-i;j++){
                if(a[j] > a[j+1]){
                    int temp=a[j]; a[j]=a[j+1]; a[j+1]=temp;
                    Img im_temp=im[j]; im[j]=im[j+1]; im[j+1]=im_temp;
                }
            }
        }
        for (int i=0;i<num;i++){
            std::string sstr1="bmp_hist/search_match/m";
            std::stringstream sstr2;
            sstr2<<i+1;
            std::string sstr=sstr1+sstr2.str()+".bmp";
            writeImg(im[i], sstr);
        }
        return im[0];
    }
}
