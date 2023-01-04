#include "gui.h"
#include "error.h"

namespace BmpCV {
    HANDLE pipe_write;
    HANDLE pipe_read;
    void pipeInit() {
        SECURITY_ATTRIBUTES attributes;
        attributes.bInheritHandle = TRUE;
        attributes.lpSecurityDescriptor = NULL;
        attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
        if(!CreatePipe(&pipe_read, &pipe_write, &attributes, 0)) {
            throw CV_runtime_error(PIPE_OPEN_ERROR, "Cannot open pipe");
        }
    }

    bool processSpawn() {
        PROCESS_INFORMATION proc_info;
        STARTUPINFO start_info;
        memset(&start_info, 0, sizeof(STARTUPINFO));
        start_info.cb = sizeof(STARTUPINFO);
        start_info.wShowWindow = SW_SHOW;
        start_info.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
        start_info.hStdInput = pipe_read;
        start_info.hStdOutput = pipe_write;
        start_info.hStdError = HANDLE(STD_ERROR_HANDLE);
        LPCSTR gui_path = _T("C:\\Users\\13087\\Desktop\\DIP\\BmpCV\\Qt_GUI\\pack1\\Qt_GUI.exe");
        if(!CreateProcess(gui_path, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &start_info, &proc_info)) {
            CloseHandle(pipe_read);
            CloseHandle(pipe_write);
            return false;
        }
        CloseHandle(proc_info.hProcess);
        CloseHandle(proc_info.hThread);
        std::cout << "task spawn success" << std::endl;
        return true;
    }

//    void setMemoryMap(uchar* data, long length) {
//        HANDLE map_handle;
//        LPCTSTR buf;
//        map_handle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 0xFFFF, map_name);
//        if(map_handle == NULL) {
//            throw CV_runtime_error(MAP_CREATE_ERROR, "Cannot create memory map");
//        }
//        buf = (LPTSTR) MapViewOfFile(map_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0xFFFF);
//        if(buf == NULL) {
//            CloseHandle(map_handle);
//            throw CV_runtime_error(MAP_CREATE_ERROR, "Cannot map view of file");
//        }
//        CopyMemory((PVOID)buf, data, length);
//
//    }

    bool dataSend(uchar* data, long length) {
        DWORD data_write;
        return WriteFile(pipe_write, (LPCTSTR)data, length, &data_write, NULL);
    }

    void createWindow() {
        pipeInit();
        processSpawn();
    }

    void imgShow(const Img& src_img) {
        char img_head[20] = {};
        sprintf(img_head, "%d,%d,%d", src_img.width, src_img.height, src_img.color_bit);
        dataSend(reinterpret_cast<uchar *>(img_head), 20);
//        std::cout << src_img.pixel_count << std::endl;
        dataSend(src_img.data, src_img.pixel_count);
    }

} // BmpCV