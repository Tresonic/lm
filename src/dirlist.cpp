#include "dirlist.hpp"

const tui::list_appearance_a list_appearance { { "x", tui::COLOR::RED }, { "" }, { ">" } };

Dirlist::Dirlist(const std::string& path)
    : mBasePath { path }
    , mList { { { 0, 0 }, { 50, 100 } } }
{
    mList.setEntries(mListEntries);
    mList.setAppearance({ { list_appearance }, { list_appearance } });
    mList.key_down = 'j';
    mList.key_up = 'k';

    mList.setPositionInfo(
        { { 0, 0 }, { 0, 0 }, { tui::POSITION::BEGIN, tui::POSITION::CENTER } });
    mList.activate();

    update(path);
}

bool sortEntries(DirectoryEntry d1, DirectoryEntry d2)
{
    if (d1.mDir != d2.mDir)
        return d1.mDir;

    if (SortMode == SORT_MODE::NAME) {
        return d1.mName < d2.mName;
    }
}

void Dirlist::update(const std::string& path)
{
    mBasePath = path;
    mDirEntries.clear();
    mDirEntries = getDirEntries(mBasePath);

    std::sort(mDirEntries.begin(), mDirEntries.end(), sortEntries);

    mListEntries.clear();
    for (const auto& entry : mDirEntries) {
        mListEntries.push_back({ entry.mName, tui::CHECK_STATE::NOT_CHECKED });
    }
    mList.setEntries(mListEntries);
    mList.update();
}

void Dirlist::draw()
{
    tui::output::draw(mList);
}
