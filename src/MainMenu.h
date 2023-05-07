#include <vector>
#include <string>
#include <SDL2/SDL_ttf.h>
//#include "globals.h"
#include "MenuItem.h"

class MainMenu
{
 public:
  explicit MainMenu();
  int renderBackground();
  int renderText(TTF_Font* font);
  const std::vector<std::string> menuLabels = {"Start game", "Load replay", "Instructions", "Options", "Exit"};
  std::vector<MenuItem> items;
  void goUp();
  void goDown();
 private:
  int highlightIndex;
  // std::vector<MenuItem> items(menuLabels.size());
};
extern MainMenu menu;
//extern MenuItem item;
