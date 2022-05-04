#pragma once
#define FILES_HPP

#include <filesystem>
#include <vector>

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

struct DirectoryEntry {
    std::string mName;
    bool mDir;
    bool mHidden;
    long mSize;
};

std::vector<DirectoryEntry> getDirEntries(const std::string& path);
bool isHidden(const fs::directory_entry&);

void renewVectors(std::string);

void changeDir(std::string);

std::string getPerms(std::string);

std::string toHumanReadableSize(std::string);

std::string getSize(std::string);

void remove(std::string);

void copy(std::string, std::string);

void copyList(std::vector<std::string>, std::string);

void move(std::string, std::string);

void moveList(std::vector<std::string>, std::string);
