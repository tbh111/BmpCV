#ifndef BMPCV_GUI_H
#define BMPCV_GUI_H

#include <windows.h>
#include <tchar.h>
#include <direct.h>
#include "bmp.h"
typedef unsigned char uchar;

namespace BmpCV {

    void pipeInit();
    bool processSpawn();
    void setMemoryMap();
    bool dataSend(uchar* data, long length);
    void createWindow();
    void imgShow(const Img& src_img);
    // static DWORD WINAPI pipe_thread(LPVOID lp);

} // TbhCV

#endif //BMPCV_GUI_H
