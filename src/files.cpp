#include "files.hpp"
#include <tgmath.h>
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

fs::path currentDir;

std::vector<fs::path> hiddenDirs;
std::vector<fs::path> hiddenFiles;
std::vector<fs::path> dirs;
std::vector<fs::path> files;

void TEST_outputFolderContent(fs::path path)
{
    /* src: https://www.cppstories.com/2019/04/dir-iterate/ */
    for (const auto &entry : fs::directory_iterator(path)) {
        const auto filenameStr = entry.path().filename().string();
        ;
        if (entry.is_directory()) {
            std::cout << "dir:  " << filenameStr << '\n';
        } else if (entry.is_regular_file()) {
            std::cout << "file: " << filenameStr << '\n';
        } else
            std::cout << "??    " << filenameStr << '\n';
    }
}

bool isHidden(auto entry)
{
    if (OS == 0) { /* Unix */
        if (entry.path().filename().string()[0] == '.') {
            return true;
        } else {
            return false;
        }
    } else if (OS == 1) { /* Windows */
        /* TODO */
        return false;
    }
}

void renewVectors(fs::path dirPath)
{
    hiddenDirs.clear();
    hiddenFiles.clear();
    dirs.clear();
    files.clear();
    
    for (const auto &entry : fs::directory_iterator(dirPath)) {
        if (isHidden(entry)) {
            if (entry.is_directory()) {
                hiddenDirs.push_back(entry);
            } else if (entry.is_regular_file()) {
                hiddenFiles.push_back(entry);
            }
        } else {
            if (entry.is_directory()) {
                dirs.push_back(entry);
            } else if (entry.is_regular_file()) {
                files.push_back(entry);
            }
        }
    }
}

/*
 * normal cd with tests and Error outputs
 */
void changeDir(std::string newPath)
{
    if (!fs::exists(newPath)) {
        /* TODO: output ERROR to gui/tui */
        std::cout << "ERROR Folder doesn't exist!\n";
        return;
    }
    //if (fs::current_path(newPath)) { /* Doesn't return error */ /* Doesn't return error */
    if (cd(newPath.c_str())) {
        /* TODO: output ERROR to gui/tiu */
        std::cout << "ERROR IN changeDir\n";
    }
}

std::string getPerms(fs::path entry)
{ /* source: https://en.cppreference.com/w/cpp/filesystem/perms */
    fs::perms p = fs::status(entry.string()).permissions();
    std::string ret = "----------";
    int i = 0;
    ret[i++] = (fs::is_directory(fs::status(entry.string())) ? 'd' : '.');
    ret[i++] = ((p & fs::perms::owner_read) != fs::perms::none ? 'r' : '-');
    ret[i++] = ((p & fs::perms::owner_write) != fs::perms::none ? 'w' : '-');
    ret[i++] = ((p & fs::perms::owner_exec) != fs::perms::none ? 'x' : '-');
    ret[i++] = ((p & fs::perms::group_read) != fs::perms::none ? 'r' : '-');
    ret[i++] = ((p & fs::perms::group_write) != fs::perms::none ? 'w' : '-');
    ret[i++] = ((p & fs::perms::group_exec) != fs::perms::none ? 'x' : '-');
    ret[i++] = ((p & fs::perms::others_read) != fs::perms::none ? 'r' : '-');
    ret[i++] = ((p & fs::perms::others_write) != fs::perms::none ? 'w' : '-');
    ret[i++] = ((p & fs::perms::others_exec) != fs::perms::none ? 'x' : '-');
    return ret;
}

std::string toHumanReadableSize(long size) /* TODO: type to actual size type */
{
    long ret;
    char chr;
    if (int(size / pow(10, 24))) {
        ret = size / pow(10, 24);
        chr = 'Y';
    } else if (int(size / pow(10, 21))) {
        ret = size / pow(10, 21);
        chr = 'Z';
    } else if (int(size / pow(10, 18))) {
        ret = size / pow(10, 18);
        chr = 'E';
    } else if (int(size / pow(10, 15))) {
        ret = size / pow(10, 15);
        chr = 'P';
    } else if (int(size / pow(10, 12))) {
        ret = size / pow(10, 12);
        chr = 'T';
    } else if (int(size / pow(10, 9))) {
        ret = size / pow(10, 9);
        chr = 'G';
    } else if (int(size / pow(10, 6))) {
        ret = size / pow(10, 6);
        chr = 'M';
    } else if (int(size / pow(10, 3))) {
        ret = size / pow(10, 3);
        chr = 'K';
    } else {
        ret = size;
    }

    return std::to_string(ret) + chr;
}

std::string getSize(fs::path entry)
{
    return (fs::is_directory(fs::status(entry.string())) ? "DIR" : toHumanReadableSize(fs::file_size(entry)));
}

void remove(fs::path entry)
{
    /* TODO: move question to tui */
    std::cout << "Are you sure you want to delete the file/folder and all its subfolders?";
    char chr;
    std::cin >> chr;
    if (chr != 'y' && chr != 'Y')
        return;
    if (!fs::remove_all(entry)) {
        /* TODO: move to tui */
        std::cout << "Permissions Failed!\n";
    }
}

void copy(fs::path from, fs::path to)
{
    fs::copy(from, to);
}

void copyList(std::vector<fs::path> from, fs::path to)
{
    for (long unsigned i = 0; i < from.size(); i++) {
        fs::copy(from.at(i), to);
    }
}

void move(fs::path from, fs::path to)
{
    fs::rename(from, to);
}

void moveList(std::vector<fs::path> from, fs::path to)
{
    for (long unsigned i = 0; i < from.size(); i++) {
        fs::rename(from.at(i), to);
    }
}

void TODO_openFile(fs::path filePath)
{
    /* https://stackoverflow.com/questions/38124415/using-a-filesystempath-how-do-you-open-a-file-in-a-cross-platform-way */
    //std::ifstream fileStream(filePath.string().c_str(), std::ios::binary);
}

void TEST_printVec(auto v)
{
    for (long unsigned i = 0; i < v.size(); i++) {
        std::cout << getPerms(v.at(i)) << " " << v.at(i).filename().string() << " " << getSize(v.at(i)) << "\n"; // get filename
    }
}

void TEST_printallVecs()
{
    std::cout << "Hidden Dirs:\n";
    TEST_printVec(hiddenDirs);
    std::cout << "Normal Dirs:\n";
    TEST_printVec(dirs);
    std::cout << "Hidden Files:\n";
    TEST_printVec(hiddenFiles);
    std::cout << "Normal Fies:\n";
    TEST_printVec(files);
}

int main()
{
    renewVectors(fs::path("/home/jakob/Documents"));

    TEST_printallVecs();   

    changeDir("/home/jakob/repos/own/");

    char buf[4096];
    std::cout << cwd(buf, sizeof(buf));

    std::cout << fs::current_path() << "\n";
    return 0;
}
