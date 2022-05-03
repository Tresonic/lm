#include <iostream>

#include "ftxui/linux/component/component.hpp"
#include "ftxui/linux/component/component_options.hpp"
#include "ftxui/linux/component/screen_interactive.hpp"
#include "ftxui/linux/component/captured_mouse.hpp"
#include "ftxui/linux/dom/elements.hpp"

using namespace ftxui;

int selected = 0;

std::vector<std::string> fileMenuEntries = {
    "abc",
    "def",
};

class FileMenu : public Menu {
public:
  FileMenu() {};
  std::vector<int> itemcolors;
  std::function<void()> on_mark = []() {};
  std::function<void()> on_back = []() {};
  std::function<void()> on_enter = []() {};

  bool OnEvent(Event event) override {
    if(event == Event::Special("l")) {
  Element Render() {
  std::vector<Element> elements;
  bool is_focused = Focused();
  for (size_t i = 0; i < fileMenuEntries.size(); ++i) {
    auto style = (selected != int(i))
                     ? normal_style
                     : is_focused ? focused_style : selected_style;
    auto focused = (selected != int(i)) ? nothing : is_focused ? focus : ftxui::select;
    auto icon = (selected != int(i)) ? L"  " : L"> ";
    if(itemcolors.size() == fileMenuEntries.size() && itemcolors[i] == 1) {
      elements.push_back(text(icon + fileMenuEntries[i]) | color(Color::GreenLight) | style | focused);
    } else if(itemcolors.size() == fileMenuEntries.size() && itemcolors[i] == 2) {
      elements.push_back(text(icon + fileMenuEntries[i]) | bgcolor(Color::YellowLight) | style | focused);
    } else if(itemcolors.size() == fileMenuEntries.size() && itemcolors[i] == 3) {
      elements.push_back(text(icon + fileMenuEntries[i]) | bgcolor(Color::YellowLight) | color(Color::GreenLight) | style | focused);
    } else {
      elements.push_back(text(icon + fileMenuEntries[i]) | style | focused);
    }
  }
  return vbox(std::move(elements));
      elements.push_back(text(icon + entries[i]) | bgcolor(Color::YellowLight) | style | focused);
    } else if(itemcolors.size() == entries.size() && itemcolors[i] == 3) {
      elements.push_back(text(icon + entries[i]) | bgcolor(Color::YellowLight) | color(Color::GreenLight) | style | focused);
    } else {
      elements.push_back(text(icon + entries[i]) | style | focused);
    }
  }
  return vbox(std::move(elements));
}


};

int init()
{
    auto screen = ScreenInteractive::TerminalOutput();

    MenuOption fileMenuOptions;
    //fileMenuOptions.on_enter = screen.ExitLoopClosure();
    fileMenuOptions.on_enter = [&] {
        fileMenuEntries.push_back("NEW");
    };
    auto fileMenu = FileMenu(&fileMenuEntries, &selected, &fileMenuOptions);

    screen.Loop(fileMenu);
}
