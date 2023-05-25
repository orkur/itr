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
    void goLeft();
    void goRight();
    void select();
private:
    std::string currentLabel;
    bool labelContains(const std::string &query);
    void openOptions(const std::vector<std::string> &labels);
    void prepareMenu(std::vector<std::string> labels);
    void refreshGfxMenu();
    int getResIndex();
    int m_resIndex;
    int highlightIndex;
    const std::vector<std::string> menuLabels = {"Start game", "Load replay", "Instructions", "Options", "Exit"};
    const std::vector<std::string> optionLabels = {"Game options", "GFX options", "Sound options", "Controls", "Go back"};
    std::vector<std::string> gfxLabels;
    const std::vector<std::string> resolutionLabels = {"640x480", "800x600", "1280x720", "1920x1080"};
    std::string isFullscreenLabel;
    std::string resolutionLabel;
    std::string currentResLabel;
    bool m_labelContains;
    // std::vector<MenuItem> items(menuLabels.size());
};
extern MainMenu menu;
//extern MenuItem item;
