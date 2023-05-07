#include "Texture.h"
#include <iostream>
#include <SDL2/SDL_image.h> 

// Texture::Texture()
// {
// }
SDL_Texture* Texture::loadTexture(std::string path )
{
    SDL_Texture* newTex;
    SDL_Surface* surface;
    // if image has bmp extension we don't want to use sdl_image
    if (path.find("bmp") != std::string::npos)
	surface = SDL_LoadBMP(path.c_str());
    else
        surface = IMG_Load(path.c_str());
    if (surface == NULL ){
	std::cout << "Error importing image: " << IMG_GetError() << std::endl;
	return NULL;
    }
    newTex = SDL_CreateTextureFromSurface(renderer, surface );
    if (newTex == NULL ){
	std::cout << "Error converting image: " << IMG_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return newTex;
}
