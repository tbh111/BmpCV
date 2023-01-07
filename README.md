# BmpCV

BmpCV：使用C++编写的BMP图像处理库

### 开发环境

CLion 2022.3, MinGW w64 9.0, Eigen 3.4.0, Qt 5.15.2

### 库模块

bmp：BMP图像的读取和保存

```C++
Img(); // 图像类
uchar Img::loc(int row, int col, int channel) const; // 访问图像中像素
uchar Img::loc(pt_2d pt, int channel) const; // 访问图像中像素
uchar& Img::iloc(int row, int col, int channel); // 访问/修改图像中像素
Img readImg(const std::string& filename); // 读取图像
void writeImg(const Img& src_img, const std::string& filename); // 保存图像
```

gui：BMP图像的显示

```C++
void createWindow(); // 创建窗口
void imgShow(const Img& src_img); // 显示图像
```

img_proc：BMP图像的基本变换

```C++
Img rotateImg(const Img& src_img, double angle, int flag); // 旋转
Img flipImg(const Img& src_img, int flag); // 水平/垂直镜像
Img resizeImg(const Img& src_img, int size_x, int size_y, int flag); // 缩放
Img resizeImg(const Img& src_img, double ratio); // 缩放
Img getRoi(const Img& src_img, point_pair_2d p1, point_pair_2d p2); // 剪切
Img translationImg(const Img& src_img, int offset_x, int offset_y, pt_3d fill_color); // 平移
Img removeColor(const Img& src_img); // 去色
```

Qt_GUI：gui模块调用的前端GUI界面，调用路径在setting.ini中设置
