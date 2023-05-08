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
    std::vector<MenuItem> items;
    void goUp();
    void goDown();
    void select();
private:
    int highlightIndex;
    void openOptions();
    void prepareMenu(std::vector<std::string> labels);
    const std::vector<std::string> menuLabels = {"Start game", "Load replay", "Instructions", "Options", "Exit"};
    const std::vector<std::string> optionLabels = {"Game options", "GFX options", "Sound options", "Controls", "Go back"};
    // std::vector<MenuItem> items(menuLabels.size());
};
extern MainMenu menu;
//extern MenuItem item;
