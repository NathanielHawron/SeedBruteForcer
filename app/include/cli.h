#pragma once

#include <cstdint>
#include <any>
#include <string>
#include <iostream>
#include <unordered_map>


#ifdef DEBUG
    #define PRINT_DEBUG(message) std::cout << "[DEBUG]: " << message << std::endl;
    #define GL_CALL(f, fname) GLClearError(fname);f;GLLogCall(fname);
    #define RUN_DEBUG(x) x;
#else
    #define PRINT_DEBUG(message)
    #define GL_CALL(f, fname) f;
    #define RUN_DEBUG(x)
#endif
#define INFO(message) if(true){std::cout << "[Info]: " << message << std::endl;}
#define WARN(message) if(true){std::cout << "[Warning]: " << message << std::endl;}
#define PRINT_ERROR(message) std::cout << "[Error]: " << message << std::endl;

namespace cli{
    enum class ARG_TYPE:uint8_t{
        BOOL,
        INT8,
        //INT16,
        //INT32,
        //INT64,
        //UINT8,
        UINT16,
        //UINt32,
        //UINT64,
        STRING
    };
    void parseArgs(int argc, char *argv[], std::unordered_map<std::string, std::pair<ARG_TYPE, std::any>> &res);
}