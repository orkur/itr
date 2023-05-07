#include <iostream>
#include "MainMenu.h"
#include "Texture.h"

MainMenu::MainMenu()
{
    MenuItem item;
    items.resize(menuLabels.size());
    // assign labels to menu items
    for (int i = 0; i < menuLabels.size(); i++){
	items.at(i).setLabel(menuLabels.at(i));
    }
    // highlight first item by default
    items.at(0).setHighlight(true);
    highlightIndex = 0;
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
    renderText(font);
}
void MainMenu::goDown()
{
    items.at(highlightIndex).setHighlight(false);
    if (highlightIndex < items.size() - 1)
    {
	highlightIndex++;
    }
    items.at(highlightIndex).setHighlight(true);
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
