//#include "files.hpp"
//#include "tui/tui.h"
#include "dirlist.hpp"
#include "tui.h"

int main()
{
    // box widget with {0x,0y} {100%x, 100%y} size
    //tui::box main_box({ { 0, 0 }, { 100, 100 } });
    //main_box.setTitle("lm");
    //main_box.setTitlePosition(tui::POSITION::END);

    //tui::list eList { { { 0, 0 }, { 50, 100 } } };
    ////eList.setAppearance({ list_appearance, list_appearance });
    //eList.key_down = 'j';
    //eList.key_up = 'k';

    //std::vector<tui::list_entry> exampleList;
    //exampleList.push_back({ "asdf", tui::CHECK_STATE::NOT_CHECKED });
    //exampleList.push_back({ "asdf", tui::CHECK_STATE::NOT_CHECKED });
    //exampleList.push_back({ "asdf", tui::CHECK_STATE::NOT_CHECKED });
    //for (size_t i = 0; i < 100; i++)
    //exampleList.push_back({ "bsda" + std::to_string(i), tui::CHECK_STATE::NOT_CHECKED });

    //eList.setEntries(exampleList);
    //eList.displayScroll(true);
    //eList.setPositionInfo(
    //{ { 0, 0 }, { 0, 0 }, { tui::POSITION::BEGIN, tui::POSITION::CENTER } });
    //// activated widget will handle user input, in full example
    //// activation/deactivation is handled by tui::navigation_group
    //eList.activate();

    Dirlist d;
    //Dirlist d2;
    tui::init();

    while (!tui::input::isKeyPressed('q')) {
        tui::output::clear(); // clears buffer and resizes it to terminal size

        // tui::output::draw(main_box); // copies widget to buffer
        //tui::output::draw(eList);
        // tui::output::draw(text);

        d.draw();

        tui::output::display(); // displays buffer content
    }

    return 0;
}
