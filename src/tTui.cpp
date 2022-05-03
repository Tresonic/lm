#include "files.hpp"
#include "tui.hpp"
#include <iostream>

//if (OS == 0) {
#include "ftxui/linux/dom/elements.hpp"
#include "ftxui/linux/screen/screen.hpp"
#include "ftxui/linux/screen/string.hpp"
//} else if (OS == 1) {
//#include "ftxui/win/dom/elements.hpp"
//#include "ftxui/win/screen/screen.hpp"
//#include "ftxui/win/screen/string.hpp"
//}

int main(void)
{
    using namespace ftxui;

    auto boxTitle = [&] {
        auto content = vbox({
            hbox({ text(getCurrentDir()) | color(Color::Blue), text(getCurrentFile()) | color(Color::White)}),
        });
        return window(text(L" Summary "), content);
    };

    auto boxMain = [&] {
        auto content = vbox({
            vbox({ text(L"- done:   "), text(L"3") | bold }) | color(Color::Green),
        });
        return window(text(L" Summary "), content);
    };

    auto boxInfo = [&] {
        auto content = vbox({
            vbox({ text(getCurrentPerms())}) | color(Color::BlueLight),
            vbox({ text(getCurrentInfo())}) | color(Color::White),
        });
        return window(content);
    };

    auto boxInput = [&] {
        auto content = vbox({
        });
        return window(content);
    };

    auto document = //
        vbox({
            boxTitle() | flex,
            boxMain() | flex,
            boxInfo() | flex,
            boxInput() | flex
        });

    // Limit the size of the document to 80 char.
    //document = document | size(WIDTH, LESS_THAN, 80);

    auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
    Render(screen, document);

    std::cout << screen.ToString() << std::endl;

    return EXIT_SUCCESS;
}
