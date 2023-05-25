#include <iostream>
#include "MainMenu.h"
#include "Texture.h"
#include "Window.h"

MainMenu::MainMenu()
{
    gfxLabels = {"Eye Candy:", "Fullscreen: " + isFullscreenLabel, "Resolution:", "Back"};
    prepareMenu(menuLabels);
}
void MainMenu::prepareMenu(std::vector<std::string> labels)
{
    items.resize(labels.size());
    // assign labels to menu items
    for (int i = 0; i < labels.size(); i++){
	items.at(i).setLabel(labels.at(i));
	// remove highlight from previous menu if exists
	items.at(i).setHighlight(false);
    }
    // highlight first item by default
    items.at(0).setHighlight(true);
    highlightIndex = 0;
}
void MainMenu::refreshGfxMenu()
{
    isFullscreenLabel = Window::isFullscreen() ? "Yes" : "No"; 
    gfxLabels.at(1) = "Fullscreen: " + isFullscreenLabel;
    resolutionLabel = Window::resolutionLabel();
    gfxLabels.at(2) = "Resolution: " + resolutionLabel;
    openOptions(gfxLabels);
    getResIndex();
}
void MainMenu::goUp()
{
    items.at(highlightIndex).setHighlight(false);
    if(highlightIndex > 0)
    {
	highlightIndex--;
    }
    else {
	highlightIndex = items.size() - 1;
    }
    items.at(highlightIndex).setHighlight(true);
    currentLabel = items.at(highlightIndex).label();
    renderText(font);
}
void MainMenu::goDown()
{
    items.at(highlightIndex).setHighlight(false);
    if (highlightIndex < items.size() - 1)
    {
	highlightIndex++;
    }
    else {
	highlightIndex = 0;
    }
    items.at(highlightIndex).setHighlight(true);
    currentLabel = items.at(highlightIndex).label();
    renderText(font);
}
void MainMenu::goLeft()
{
    if(labelContains("Resolution"))
    {
    if(m_resIndex > 0 ) {
	m_resIndex--;
    }
    resolutionLabel = resolutionLabels.at(m_resIndex);
    items.at(highlightIndex).setLabel("Resolution: " + resolutionLabel);
    currentLabel = gfxLabels.at(2);
    SDL_RenderClear(renderer);
    renderText(font);
    }
}
void MainMenu::goRight()
{
    if(labelContains("Resolution"))
    {
    if(m_resIndex < (resolutionLabels.size() - 1)) {
	m_resIndex++;
    }
    resolutionLabel = resolutionLabels.at(m_resIndex);
    items.at(highlightIndex).setLabel("Resolution: " + resolutionLabel);
    currentLabel = gfxLabels.at(2);
    SDL_RenderClear(renderer);
    renderText(font);
    }
}
int MainMenu::getResIndex()
{
    for(int i = 0; i < resolutionLabels.size(); i++)
    {
	currentResLabel = resolutionLabels.at(i);
	if( currentResLabel == Window::resolutionLabel())
	{
	    m_resIndex = i;
	}
    }
    return m_resIndex;
}
void MainMenu::select()
{
    // TODO: make string and position-independent menu item functions
    // (chodzi o to zeby jak zmienimy podpis danej opcji w menu albo przeniesiemy ja do innej 
    // pozycji ta opcja dalej robila to samo)
    currentLabel = items.at(highlightIndex).label();
    // open options if player selected options from main menu or if back from submenu has been requested
    if(currentLabel == "Exit") // exit
    {
	isRunning = false;
    }
    else if(currentLabel == "Options" || currentLabel == "Back")
    {
	openOptions(optionLabels);
    }
    else if(currentLabel == "Go back")
    {
	openOptions(menuLabels);
    }
    else if(currentLabel == "GFX options")
    {
	refreshGfxMenu();
    }
    else if(labelContains("Fullscreen"))
    {
	Window::changeFullscreen();
	// replace Fullscreen value
	isFullscreenLabel = Window::isFullscreen() ? "Yes" : "No"; 
	gfxLabels.at(1) = "Fullscreen: " + isFullscreenLabel;
	// redraw menu
	openOptions(gfxLabels);
    }
    else if(labelContains("Resolution"))
    {
	std::string widthString;
	std::string heightString;
	int newWidth;
	int newHeight;
	for(int i = 0; i < resolutionLabel.size(); i++) {
	    // get width and height from resolution string
	    if(resolutionLabel.at(i) == 'x') {
		widthString = resolutionLabel.substr(0, i);
		heightString = resolutionLabel.substr(i + 1, resolutionLabel.size());
		//convert to int
		newWidth = stoi(widthString);
		newHeight = stoi(heightString);
	    }
	}
	Window::changeRes(newWidth, newHeight);
        // resolutionLabel = Window::resolutionLabel();
	// gfxLabels.at(2) = "Resolution: " + resolutionLabel;
	// openOptions(gfxLabels);
    }
}
bool MainMenu::labelContains(const std::string &query)
{
    m_labelContains = currentLabel.find(query) != std::string::npos;
    return m_labelContains;
}
void MainMenu::openOptions(const std::vector<std::string> &labels)
{
    prepareMenu(labels);
    SDL_RenderClear(renderer);
    renderText(font);
}
int MainMenu::renderBackground()
{
    // screen update
    // glClear(GL_COLOR_BUFFER_BIT);
    SDL_Texture *background;
    background = Texture::loadTexture("background.bmp");
    if(background == NULL) {
	return 1;
    }
    //clear our main screen
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode( background, SDL_BLENDMODE_BLEND); // blend text with background
    // render background texture
    SDL_RenderCopy(renderer, background, NULL, NULL);
    // update to show rendered screen
    //    SDL_RenderPresent(renderer);
    // background = SDL_CreateTexture(context)
    // SDL_GL_SwapWindow(window);
    return 0;
}
int MainMenu::renderText(TTF_Font* font)
{
    SDL_RenderClear(renderer);
    renderBackground();
    SDL_Surface* text;
    SDL_Color color = {255, 255, 255};
    SDL_Color highlightColor = {255, 0, 0};
    for (int i = 0; i < items.size(); i++)
    {
	MenuItem currentItem = items.at(i);
	SDL_Color itemColor;
	// check if current item is highlighted. If true use highlight color
	currentItem.highlighted() ? (itemColor = highlightColor) : (itemColor = color);
	text = TTF_RenderText_Blended( font, currentItem.label().c_str(), itemColor);
	if (text == NULL) {
	    std::cout << "Unable to render text: " << TTF_GetError() << std::endl;
	    return 1;
	}
	SDL_Texture* textTex;
	textTex = SDL_CreateTextureFromSurface(renderer, text);
	if (textTex == NULL) {
	    std::cout << "Texture creation failed: " << SDL_GetError() << std::endl;
	    return 1;
	}
	SDL_Rect textImg = {
	    (win_width / 5), // x
	    ((win_height / 5) + i*(text ->h)), // y
	    text->w, // width
	    text->h // height
	};
	SDL_SetTextureBlendMode( textTex, SDL_BLENDMODE_BLEND); // blend text with background
	SDL_RenderCopy(renderer, textTex, NULL, &textImg);
    }
    SDL_RenderPresent(renderer);
    return 0;
}
