#include "img_proc.h"

namespace BmpCV {

    Img rotateImg(const Img& src_img, double angle, int flag) {
        double angle_rad = angle * M_PI/180; // clockwise rotate
        int bound_w = floor(src_img.height * fabs(sin(angle_rad)) + src_img.width * fabs(cos(angle_rad)));
        int bound_h = floor(src_img.height * fabs(cos(angle_rad)) + src_img.width * fabs(sin(angle_rad)));
        Img dst_img(bound_w, bound_h, src_img.color_bit|src_img.color_space);

        Eigen::Matrix3d rotate_mat, centralized_mat1, centralized_mat2, convert_mat;
        rotate_mat << cos(angle_rad), -sin(angle_rad), 0, sin(angle_rad), cos(angle_rad), 0, 0, 0, 1;
        std::cout << rotate_mat << std::endl;
        centralized_mat1 << 1, 0, double(-src_img.width)/2, 0, 1, double(-src_img.height)/2, 0, 0, 1;
        centralized_mat2 << 1, 0, double(bound_w)/2, 0, 1, double(bound_h)/2, 0, 0, 1;
        convert_mat = centralized_mat2 * rotate_mat * centralized_mat1;
        Eigen::Matrix3d convert_mat_inv;
        convert_mat_inv = convert_mat.inverse();

        for(int i=0; i<bound_h; i++) { // per row: y
            for(int j=0; j<bound_w; j++) { // per col: x
                Eigen::MatrixXd pixel_pos(3, 1); // x y 1
                pixel_pos << j, i, 1;
                Eigen::MatrixXd pixel_origin_pos(3, 1);
                pixel_origin_pos = convert_mat_inv * pixel_pos;
                double pos_x = pixel_origin_pos(0, 0)-1;
                double pos_y = pixel_origin_pos(1, 0)-1;
                if((src_img.width > round(pos_x)) && (src_img.height > round(pos_y)) && round(pos_x) >= 0 && round(pos_y) >=0) {
                    if(flag == INTER_NEARST) {
                        int nearest_x = int(round(pos_x));
                        int nearest_y = int(round(pos_y));

                        dst_img.iloc(i, j, 0) = src_img.loc(nearest_y, nearest_x, 0);
                        if(dst_img.color_bit == COLOR_8UC3) {
                            dst_img.iloc(i, j, 1) = src_img.loc(nearest_y, nearest_x, 1);
                            dst_img.iloc(i, j, 2) = src_img.loc(nearest_y, nearest_x, 2);
                        }
                    }
                    else if(flag == INTER_BILINEAR) {
                        // Interpolation point is (x, y), (x+1, y), (x, y+1), (x+1, y+1)
                        point_pair_2d pt1(floor(pos_x), floor(pos_y));
                        point_pair_2d pt2(floor(pos_x+1), floor(pos_y));
                        point_pair_2d pt3(floor(pos_x), floor(pos_y+1));
                        point_pair_2d pt4(floor(pos_x+1), floor(pos_y+1));
                        double offset_x1 = pos_x-floor(pos_x);
                        double offset_x2 = floor(pos_x+1)-pos_x;
                        double offset_y1 = pos_y-floor(pos_y);
                        double offset_y2 = floor(pos_y+1)-pos_y;

                        if(pt4.x == src_img.width) {
                            pt2.x = pt1.x;
                            pt4.x = pt1.x;
                        }
                        if(pt4.y == src_img.height) {
                            pt3.y = pt1.y;
                            pt4.y = pt1.y;
                        }
                        if(pt1.x < 0) {
                            pt1.x = pt2.x;
                            pt3.x = pt2.x;
                        }
                        if(pt1.y < 0) {
                            pt1.y = pt3.y;
                            pt2.y = pt3.y;
                        }

                        dst_img.iloc(i, j, 0) = offset_y2 * offset_x2 * src_img.loc(pt1, 0) +
                                                offset_y1 * offset_x2 * src_img.loc(pt2, 0) +
                                                offset_y2 * offset_x1 * src_img.loc(pt3, 0) +
                                                offset_y1 * offset_x1 * src_img.loc(pt4, 0);
                        if(dst_img.color_bit == COLOR_8UC3) {
                            dst_img.iloc(i, j, 1) = offset_y2 * offset_x2 * src_img.loc(pt1, 1) +
                                                    offset_y1 * offset_x2 * src_img.loc(pt2, 1) +
                                                    offset_y2 * offset_x1 * src_img.loc(pt3, 1) +
                                                    offset_y1 * offset_x1 * src_img.loc(pt4, 1);
                            dst_img.iloc(i, j, 2) = offset_y2 * offset_x2 * src_img.loc(pt1, 2) +
                                                    offset_y1 * offset_x2 * src_img.loc(pt2, 2) +
                                                    offset_y2 * offset_x1 * src_img.loc(pt3, 2) +
                                                    offset_y1 * offset_x1 * src_img.loc(pt4, 2);
                        }

                    }
                    else {
                        int nearest_x = int(round(pos_x));
                        int nearest_y = int(round(pos_y));

                        dst_img.iloc(i, j, 0) = src_img.loc(nearest_y, nearest_x, 0);
                        if(dst_img.color_bit == COLOR_8UC3) {
                            dst_img.iloc(i, j, 1) = src_img.loc(nearest_y, nearest_x, 1);
                            dst_img.iloc(i, j, 2) = src_img.loc(nearest_y, nearest_x, 2);
                        }
                    }
                }
                else { // origin pos is outside the source image
                    dst_img.iloc(i, j, 0) = 0;
                    if(dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = 0;
                        dst_img.iloc(i, j, 2) = 0;
                    }
                }
            }
        }
        // check img height and width mod 4 = 0, to align memory
        int width_align = dst_img.width/4*4;
        int height_align = dst_img.height/4*4;
        dst_img = resizeImg(dst_img, width_align, height_align, INTER_BILINEAR);
        return dst_img;
    }

    Img flipImg(const Img& src_img, int flag) {
        Img dst_img(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
        if(flag == FLIP_V) { // vertical flip
            for(int i=0; i<dst_img.height; i++) { // per row: y
                for(int j=0; j<dst_img.width; j++) { // per col: x
                    dst_img.iloc(i, j, 0) = src_img.loc(dst_img.height-1-i, j, 0);
                    if(dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = src_img.loc(dst_img.height-1-i, j, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(dst_img.height-1-i, j, 2);
                    }
                }
            }
        }
        else {
            for(int i=0; i<dst_img.height; i++) { // per row: y
                for(int j=0; j<dst_img.width; j++) { // per col: x
                    dst_img.iloc(i, j, 0) = src_img.loc(i, dst_img.width-1-j, 0);
                    if(dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = src_img.loc(i, dst_img.width-1-j, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(i, dst_img.width-1-j, 2);
                    }
                }
            }
        }
        return dst_img;
    }

    Img resizeImg(const Img& src_img, double ratio) {
        if(ratio <= 0)
            throw CV_runtime_error(RATIO_EQZ, "Resize ratio should > 0");
        int bound_w = int(round(src_img.width * ratio));
        bound_w = bound_w/4*4;
        int bound_h = int(round(src_img.height * ratio));
        bound_h = bound_h/4*4;
        Img dst_img(bound_w, bound_h, src_img.color_bit|src_img.color_space);

        for(int i=0; i<bound_h; i++) { // per row: y
            for(int j=0; j<bound_w; j++) { // per col: x
                double pos_x = j / ratio;
                double pos_y = i / ratio;
                if((src_img.width > round(pos_x)) && (src_img.height > round(pos_y)) && round(pos_x) >= 0 && round(pos_y) >=0) {
                    int nearest_x = int(round(pos_x));
                    int nearest_y = int(round(pos_y));
                    dst_img.iloc(i, j, 0) = src_img.loc(nearest_y, nearest_x, 0);
                    if(dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = src_img.loc(nearest_y, nearest_x, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(nearest_y, nearest_x, 2);
                    }
                }

            }
        }
        return dst_img;
    }

    Img resizeImg(const Img& src_img, int size_x, int size_y, int flag) {
        if(size_x <= 0 || size_y <= 0)
            throw CV_runtime_error(RATIO_EQZ, "Resize size should > 0");
        Img dst_img(size_x, size_y, src_img.color_bit|src_img.color_space);
        double ratio_x = double(size_x) / src_img.width;
        double ratio_y = double(size_y) / src_img.height;

        for(int i=0; i<size_y; i++) { // per row: y
            for(int j=0; j<size_x; j++) { // per col: x
                double pos_x = j / ratio_x;
                double pos_y = i / ratio_y;

                if(flag == INTER_BILINEAR) {
                    // Interpolation point is (x, y), (x+1, y), (x, y+1), (x+1, y+1)
                    point_pair_2d pt1(floor(pos_x), floor(pos_y));
                    point_pair_2d pt2(floor(pos_x + 1), floor(pos_y));
                    point_pair_2d pt3(floor(pos_x), floor(pos_y + 1));
                    point_pair_2d pt4(floor(pos_x + 1), floor(pos_y + 1));
                    double offset_x1 = pos_x - floor(pos_x);
                    double offset_x2 = floor(pos_x + 1) - pos_x;
                    double offset_y1 = pos_y - floor(pos_y);
                    double offset_y2 = floor(pos_y + 1) - pos_y;

                    if (pt4.x == src_img.width) {
                        pt2.x = pt1.x;
                        pt4.x = pt1.x;
                    }
                    if (pt4.y == src_img.height) {
                        pt3.y = pt1.y;
                        pt4.y = pt1.y;
                    }
                    if (pt1.x < 0) {
                        pt1.x = pt2.x;
                        pt3.x = pt2.x;
                    }
                    if (pt1.y < 0) {
                        pt1.y = pt3.y;
                        pt2.y = pt3.y;
                    }

                    dst_img.iloc(i, j, 0) = offset_y2 * offset_x2 * src_img.loc(pt1, 0) +
                                            offset_y1 * offset_x2 * src_img.loc(pt2, 0) +
                                            offset_y2 * offset_x1 * src_img.loc(pt3, 0) +
                                            offset_y1 * offset_x1 * src_img.loc(pt4, 0);
                    if (dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = offset_y2 * offset_x2 * src_img.loc(pt1, 1) +
                                                offset_y1 * offset_x2 * src_img.loc(pt2, 1) +
                                                offset_y2 * offset_x1 * src_img.loc(pt3, 1) +
                                                offset_y1 * offset_x1 * src_img.loc(pt4, 1);
                        dst_img.iloc(i, j, 2) = offset_y2 * offset_x2 * src_img.loc(pt1, 2) +
                                                offset_y1 * offset_x2 * src_img.loc(pt2, 2) +
                                                offset_y2 * offset_x1 * src_img.loc(pt3, 2) +
                                                offset_y1 * offset_x1 * src_img.loc(pt4, 2);
                    }
                }
                else {
                    int nearest_x = int(round(pos_x));
                    int nearest_y = int(round(pos_y));
                    dst_img.iloc(i, j, 0) = src_img.loc(nearest_y, nearest_x, 0);
                    if(dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = src_img.loc(nearest_y, nearest_x, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(nearest_y, nearest_x, 2);
                    }
                }

            }
        }
        return dst_img;
    }

    Img getRoi(const Img& src_img, point_pair_2d p1, point_pair_2d p2) {
        if(p1.x < 0 || p2.x < 0 || p1.y < 0 || p2.y < 0 ||
           p1.x >= src_img.width || p2.x >= src_img.width || p1.y >= src_img.height || p2.y >= src_img.height)
            throw CV_runtime_error(INDEX_OVERFLOW, "Index < 0 or overflow");
        int w = abs(p2.x-p1.x);
        int h = abs(p2.y-p1.y);
        if(w == 0 || h == 0)
            throw CV_runtime_error(INDEX_EQZ, "Roi w or h < 0");
        Img dst_img(w, h, src_img.color_bit|src_img.color_space);
        for(int i=0; i<h; i++) { // per row: y
            for(int j=0; j<w; j++) { // per col: x
                dst_img.iloc(i, j, 0) = src_img.loc(p1.y+i, p1.x+j, 0);
                if(dst_img.color_bit == COLOR_8UC3) {
                    dst_img.iloc(i, j, 1) = src_img.loc(p1.y+i, p1.x+j, 1);
                    dst_img.iloc(i, j, 2) = src_img.loc(p1.y+i, p1.x+j, 2);
                }
            }
        }
        return dst_img;
    }

    Img translationImg(const Img& src_img, int offset_x, int offset_y, pt_3d fill_color) {
        if(abs(offset_x) >= src_img.width || abs(offset_y) >= src_img.height) {
            throw CV_runtime_error(INDEX_EQZ, "Translation offset = 0");
        }
        Img dst_img(src_img.width, src_img.height, src_img.color_bit|src_img.color_space);
        Eigen::Matrix3d trans_mat;
        trans_mat << 1, 0, offset_x, 0, 1, offset_y, 0, 0, 1;

        for(int i=0; i<dst_img.height; i++) { // per row: y
            for(int j=0; j<dst_img.width; j++) { // per col: x
                Eigen::MatrixXd pixel_origin_pos(3, 1), pixel_pos(3, 1);
                pixel_origin_pos << j, i, 1;
                pixel_pos = trans_mat * pixel_origin_pos;
                int pixel_pos_x = pixel_pos(0, 0);
                int pixel_pos_y = pixel_pos(1, 0);
                if(pixel_pos_x > 0 && pixel_pos_x < dst_img.width && pixel_pos_y > 0 && pixel_pos_y < dst_img.height) {
                    dst_img.iloc(i, j, 0) = src_img.loc(pixel_pos_y, pixel_pos_x, 0);
                    if(dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = src_img.loc(pixel_pos_y, pixel_pos_x, 1);
                        dst_img.iloc(i, j, 2) = src_img.loc(pixel_pos_y, pixel_pos_x, 2);
                    }
                }
                else {
                    dst_img.iloc(i, j, 0) = fill_color.x;
                    if(dst_img.color_bit == COLOR_8UC3) {
                        dst_img.iloc(i, j, 1) = fill_color.y;
                        dst_img.iloc(i, j, 2) = fill_color.y;
                    }
                }
            }
        }
        return dst_img;
    }

    Img removeColor(const Img& src_img) {
        if(src_img.color_bit == COLOR_8UC1)
            return src_img;
        Img dst_img(src_img.width, src_img.height, COLOR_8UC1|COLOR_GRAY);
        for(int i=0; i<dst_img.height; i++) { // per row: y
            for(int j=0; j<dst_img.width; j++) { // per col: x
                long gray = (src_img.loc(i, j, 2)*19595 + src_img.loc(i, j, 1)*38469 + src_img.loc(i, j, 0)*7472);
                dst_img.iloc(i, j, 0) = gray>>16;
            }
        }
        return dst_img;

    }

} // BmpCV