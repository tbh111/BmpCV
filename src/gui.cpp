#include "gui.h"
#include "error.h"

namespace BmpCV {
    HANDLE child_pipe_write;
    HANDLE child_pipe_read;
    HANDLE parent_pipe_write;
    HANDLE parent_pipe_read;

    void pipeInit() {
        SECURITY_ATTRIBUTES attributes;
        attributes.bInheritHandle = TRUE;
        attributes.lpSecurityDescriptor = NULL;
        attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
        if(!CreatePipe(&parent_pipe_read, &child_pipe_write, &attributes, 0)) {
            throw CV_runtime_error(PIPE_OPEN_ERROR, "Cannot open pipe");
        }
        if(!CreatePipe(&child_pipe_read, &parent_pipe_write, &attributes, 0)) {
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
        start_info.hStdInput = child_pipe_read;
        start_info.hStdOutput = child_pipe_write;
        start_info.hStdError = HANDLE(STD_ERROR_HANDLE);

//        LPCSTR gui_path = _T("C:\\Users\\13087\\Desktop\\DIP\\BmpCV\\Qt_GUI\\pack1\\Qt_GUI.exe");
        LPTSTR setting_path = new char[256];
        LPTSTR gui_path = new char[256];
        strcpy(setting_path, _T("..\\..\\setting.ini"));
        UINT length = GetPrivateProfileString("GUI_EXE_PATH", "PATH", NULL, gui_path, 256, setting_path);
        if(length <= 0)
            throw CV_runtime_error(FILE_OPEN_ERROR, "GUI path error");
        if(!CreateProcess(gui_path, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &start_info, &proc_info)) {
            CloseHandle(child_pipe_read);
            CloseHandle(child_pipe_write);
            return false;
        }
//        WaitForSingleObject(proc_info.hProcess, INFINITE);
        CloseHandle(proc_info.hProcess);
        CloseHandle(proc_info.hThread);
        std::cout << "task spawn success" << std::endl;
        return true;
    }

    bool dataSend(uchar* data, long length) {
        DWORD data_write;
        return WriteFile(parent_pipe_write, (LPCTSTR)data, length, &data_write, NULL);
    }

    void createWindow() {
        pipeInit();
        if(!processSpawn()) {
            throw CV_runtime_error(FILE_OPEN_ERROR, "Can't create GUI process, check setting.ini");
        }
    }

    void imgShow(const Img& src_img) {
        char img_head[20] = {};
        sprintf(img_head, "%d,%d,%d", src_img.width, src_img.height, src_img.color_bit);
        dataSend(reinterpret_cast<uchar*>(img_head), 20);
        dataSend(src_img.data, src_img.pixel_count);
        while(detectProcess() && process_running_flag) // block at image show GUI until window closed
        {
            processGUI(src_img); // process function called by GUI button
        }
    }

    void processGUI(const Img& src_img) {
        const int inst_length = 9;
        TCHAR inst[inst_length] = {0};
        DWORD data_read;
        memset(inst, 0, inst_length);

        char op_code = 0;
        uchar param1[4] = {0};
        uchar param2[4] = {0};
        uint32_t param1_int = 0;
        uint32_t param2_int = 0;

        if(ReadFile(parent_pipe_read, inst, inst_length, &data_read, NULL)) {
            op_code = inst[0];
            for(int i=0; i<4; i++) {
                param1[i] = inst[i+1];
                param2[i] = inst[i+5];
            }
//            std::cout << int(op_code) << " " << int(param1[0]) << " " << int(param1[1]) << " " << int(param1[2]) << " " << int(param1[3]) << std::endl;
            param1_int = param1[0] + (param1[1] << 8) + (param1[2] << 16) + (param1[3] << 24);
            param2_int = param2[0] + (param2[1] << 8) + (param2[2] << 16) + (param2[3] << 24);
            std::cout << int(op_code) << " " << param1_int << " " << param2_int << std::endl;

            char img_head[20] = {};
            switch (op_code) {
                case 0x01: // FLIP_V
                {
                    Img dst_img = flipImg(src_img, FLIP_V);
                    sprintf(img_head, "%d,%d,%d", dst_img.width, dst_img.height, dst_img.color_bit);
                    dataSend(reinterpret_cast<uchar*>(img_head), 20);
                    dataSend(dst_img.data, dst_img.pixel_count);
                    break;
                }
                case 0x02: // FLIP_H
                {
                    Img dst_img = flipImg(src_img, FLIP_H);
                    sprintf(img_head, "%d,%d,%d", dst_img.width, dst_img.height, dst_img.color_bit);
                    dataSend(reinterpret_cast<uchar*>(img_head), 20);
                    dataSend(dst_img.data, dst_img.pixel_count);
                    break;
                }
                case 0x03: // RESIZE
                {
                    Img dst_img = resizeImg(src_img, static_cast<double>(param1_int)/10);
                    sprintf(img_head, "%d,%d,%d", dst_img.width, dst_img.height, dst_img.color_bit);
                    dataSend(reinterpret_cast<uchar*>(img_head), 20);
                    dataSend(dst_img.data, dst_img.pixel_count);
                    break;
                }
                case 0x04: // ROTATE
                {
                    Img dst_img = rotateImg(src_img, static_cast<int>(param1_int)-180, INTER_BILINEAR);
                    sprintf(img_head, "%d,%d,%d", dst_img.width, dst_img.height, dst_img.color_bit);
                    dataSend(reinterpret_cast<uchar*>(img_head), 20);
                    dataSend(dst_img.data, dst_img.pixel_count);
                    break;
                }
                case 0x05: // CUT
                    break;
                case 0x06: // RECALL
                {
                    sprintf(img_head, "%d,%d,%d", src_img.width, src_img.height, src_img.color_bit);
                    dataSend(reinterpret_cast<uchar*>(img_head), 20);
                    dataSend(src_img.data, src_img.pixel_count);
                    break;
                }
                case 0x09: // CLOSE
                {
                    process_running_flag = false;
                    std::cout << "GUI window closed" << std::endl;
                    break;
                }
                default:
                    break;
            }
        }
    }


} // BmpCV

static bool detectProcess() {
    PROCESSENTRY32 pe;
    DWORD id = 0;
    HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    pe.dwSize = sizeof(PROCESSENTRY32);
    TCHAR process[] = _T("Qt_GUI.EXE");
    if(Process32First(snap_shot, &pe)) {
        do {
            if(lstrcmpi(process, pe.szExeFile) == 0) {
                return true;
            }
        } while(Process32Next(snap_shot, &pe));
    }
    CloseHandle(snap_shot);
    return false;
}