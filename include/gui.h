#ifndef BMPCV_GUI_H
#define BMPCV_GUI_H

#include <windows.h>
#include <tchar.h>
#include <direct.h>
#include <tlhelp32.h>
#include "bmp.h"
#include "img_proc.h"
typedef unsigned char uchar;

namespace BmpCV {

    void pipeInit();
    bool processSpawn();
    bool dataSend(uchar* data, long length);
    void createWindow();
    void imgShow(const Img& src_img);
    void processGUI(const Img& src_img);

} // TbhCV
    static bool detectProcess();
    static bool process_running_flag = true;
#endif //BMPCV_GUI_H
