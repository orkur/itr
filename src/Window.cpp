#include <iostream>
#include <SDL2/SDL.h>
#include "globals.h"
#include "Window.h"

bool Window::isFullscreen()
{
    bool m_isFullscreen;
    Uint32 windowFlags = SDL_GetWindowFlags(window);
    // we don't need to check SDL_WINDOW_FULLSCREEN (without _DESKTOP) flag because
    // app shouldn't run in real fullscreen
    if ((windowFlags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) {
	m_isFullscreen = true;
    }
    else {
	m_isFullscreen = false;
    }
    return m_isFullscreen;
}
void Window::changeFullscreen()
{
    if(isFullscreen()) {
	SDL_SetWindowFullscreen(window, 0); // set windowed mode
    }
    else {
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // set fullscreen mode
    }
}
void Window::changeRes(const int &w, const int &h)
{
    win_width = w;
    win_height = h;
    if(isFullscreen())
    {
	SDL_DisplayMode oldMode;
	// get old display mode to overwrite it
        SDL_GetCurrentDisplayMode(0, &oldMode);
	SDL_DisplayMode newMode = {oldMode.format, win_width, win_height, oldMode.refresh_rate};
        SDL_SetWindowDisplayMode(window, &newMode);
    }
    else {
	SDL_SetWindowSize(window, w, h);
    }
}
std::string Window::resolutionLabel()
{
    // int m_currentWidth = SDL_GetWindowSurface(window)->w;
    // int m_currentHeight = SDL_GetWindowSurface(window)->h;
    int m_currentWidth;
    int m_currentHeight;
    SDL_GetWindowSize(window, &m_currentWidth, &m_currentHeight);
    std::string m_resolutionString = std::to_string(m_currentWidth) + "x" + std::to_string(m_currentHeight);
    return m_resolutionString;
}
