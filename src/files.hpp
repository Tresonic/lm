#pragma once
#define FILES_HPP

#ifdef __unix__
    #define OS 0
    #include "unistd.h"
    #define cwd getcwd
    #define cd chdir
#elif _WIN32
    #define OS 1
    #include <direct.h>
    #define cwd _getcwd
    #define cd _chdir
#endif
