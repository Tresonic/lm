#pragma once

#include <string>
#include <vector>

//#include "tui/tui.h"

#include "files.hpp"
#include "tui.h"

enum class SORT_MODE {
    NAME,
    SIZE,
};

static SORT_MODE SortMode;
static bool SortDesc;

static bool sortEntries(DirectoryEntry d1, DirectoryEntry d2);

class Dirlist {
public:
    Dirlist(const std::string& path);

    void update(const std::string& path);
    void draw();

private:
    std::string mBasePath;
    std::vector<DirectoryEntry> mDirEntries;

    tui::list mList;
    std::vector<tui::list_entry> mListEntries;
};
