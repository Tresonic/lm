#include "tui/tui.h"

int main() {
  // box widget with {0x,0y} {100%x, 100%y} size
  tui::box main_box({{0, 0}, {100, 100}});
  main_box.setTitle("github.com/jmicjm/TUI");
  main_box.setTitlePosition(tui::POSITION::END);

  // text widget with {0x,0y} {50%x, 50%y} size
  tui::text text({{0, 0}, {50, 50}});
  //{0x,0y} {0%x,0%y} offset, origin{x,y} at center
  text.setPositionInfo(
      {{0, 0}, {0, 0}, {tui::POSITION::CENTER, tui::POSITION::CENTER}});
  tui::symbol_string str;
  for (char i = 33; i < 127; i++) {
    str.push_back(i);
  }
  str << tui::COLOR::GREEN << "\ncolored text " << tui::COLOR::YELLOW
      << u8"zażółć gęślą jaźń " << tui::ATTRIBUTE::UNDERSCORE
      << tui::COLOR::CYAN << "underlined text";
  str += u8"\nｆｕｌｌｗｉｄｔｈ-> 全屏宽度 全角 전체 넓이";
  str +=
      "\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris sed "
      "libero nisi. "
      "Etiam pellentesque ornare consequat. Sed congue nunc sit amet arcu "
      "tempor rhoncus. "
      "Nulla mattis erat justo. Nulla semper lorem quis massa laoreet "
      "venenatis. "
      "Mauris quis purus ut nulla finibus pharetra. Nulla non bibendum ipsum. "
      "Vivamus sem lorem, tincidunt sed efficitur fermentum, porttitor sit "
      "amet sem.";
  text.setText(str);
  // activated widget will handle user input, in full example
  // activation/deactivation is handled by tui::navigation_group
  text.activate();

  tui::init();

  while (!tui::input::isKeyPressed(tui::input::KEY::ESC)) {
    tui::output::clear(); // clears buffer and resizes it to terminal size

    tui::output::draw(main_box); // copies widget to buffer
    tui::output::draw(text);

    tui::output::display(); // displays buffer content
  }

  return 0;
}
