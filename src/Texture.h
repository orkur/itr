#include <SDL2/SDL.h> 
#include <string>
#pragma once
#include "globals.h"

class Texture
{
 public:
  static SDL_Texture* loadTexture( std::string path );
};
