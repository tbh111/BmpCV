#ifndef BMPCV_ERROR_H
#define BMPCV_ERROR_H
#include <iostream>
#include <exception>
namespace BmpCV {
    enum ERROR_CODE {
        FILE_OPEN_ERROR = 0,
        BAD_IMAGE_INFO = 1,
        PIPE_OPEN_ERROR = 2,
        MAP_CREATE_ERROR = 3,
        INDEX_OVERFLOW = 4,
        INDEX_EQZ = 5,
        RATIO_EQZ = 6};

    class CV_runtime_error : public std::runtime_error {
    public:
        CV_runtime_error(int error_code) : std::runtime_error(""), code(error_code) {}
        CV_runtime_error(int error_code, const std::string& error_info) : std::runtime_error(error_info), code(error_code) {}
    private:
        int code = 0;
    };
}

#endif //BMPCV_ERROR_H
