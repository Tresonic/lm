#pragma once
#define FILES_HPP

#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

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

bool isHidden(auto);

void renewVectors(fs::path);

void changeDir(std::string);

std::string getPerms(fs::path);

std::string toHumanReadableSize(fs::path);

std::string getSize(fs::path);

void remove(fs::path);

void copy(fs::path, fs::path);

void copyList(std::vector<fs::path>, fs::path);

void move(fs::path, fs::path);

void moveList(std::vector<fs::path>, fs::path);
