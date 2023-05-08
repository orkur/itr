#include <iostream>
//#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "globals.h"
#include "MainMenu.h"

using namespace std;

int win_width = 640;
int win_height = 480;
bool isRunning = true;
SDL_Renderer *renderer = nullptr;
SDL_Window *window = nullptr;
SDL_DisplayMode displayMode;
TTF_Font *font = nullptr;
MainMenu menu;

void closeApp()
{
    //SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
int loadFont(string path, int size)
{
    font = TTF_OpenFont(path.c_str(), size);
    if (font == NULL){
	cout << "Font loading failed:" << TTF_GetError() << endl;
	return 1;
    }
    return 0;
}
// main loop
void loop()
{
    SDL_Event e;
    menu.renderBackground();
    // TODO: move to separate function
    loadFont("FreeMono.ttf", 22);
    menu.renderText(font);
    while(isRunning) {
	while(SDL_PollEvent(&e) != 0){
	    // handle app exit. Stop repeating loop if exit requested
	    if(e.type == SDL_QUIT){
		isRunning = false;
	    }
	    else if(e.type == SDL_KEYUP){
		SDL_Scancode code = e.key.keysym.scancode;
		if(code == SDL_SCANCODE_DOWN){
		    menu.goDown();
		    cout << "down" << endl;
		}
		else if(code == SDL_SCANCODE_UP){
		    menu.goUp();
		    cout << "up" << endl;
		}
		else if(code == SDL_SCANCODE_RETURN){
		    menu.select();
		    cout << "enter pressed" << endl;
		}
	    }
	}
    }
}
// init sdl libraries
void initLibs()
{
    SDL_Init(SDL_INIT_VIDEO); // We need only video so far
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
}
int main()
{
    initLibs();
    SDL_GetCurrentDisplayMode(0, &displayMode);
    win_width = displayMode.w;
    win_height = displayMode.h;
    // TODO: check do we need newer opengl context version
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // get rid of deprecated features
    window = SDL_CreateWindow (
			       "itr", // NOTE: remember to change this title if we'll decide to change project name
			       SDL_WINDOWPOS_CENTERED, // x
			       SDL_WINDOWPOS_CENTERED, // y, we need centered window so far
			       win_width, // window width. TODO: change to screen width
			       win_height, // window height. TODO: change to screen height
			       // SDL_WINDOW_OPENGL | // we want opengl to use video card
			       SDL_WINDOW_FULLSCREEN_DESKTOP | // game should launch at fullscreen
			       NULL // to make commenting fullscreen flag easier
			       );
    if (window == NULL) {
	cout << "Could not create window. Error:\n" << SDL_GetError();
    }
    // TODO: make sure we don't need opengl context
    renderer = SDL_CreateRenderer (
				   window,
				   -1,
				   SDL_RENDERER_ACCELERATED
				   );
    if (renderer == NULL) {
	cout << "Could not create renderer. Error:\n" << SDL_GetError() << endl;
    }
    // context = SDL_GL_CreateContext(window);
    // // Set some color to see if opengl works
    // glClearColor(1.f, 0.f, 1.f, 0.f);
    // GLenum error = glGetError();
    // //    glViewport(0, 0, 100, 100);
    loop();
    // cout << error;
    // cout << "Vendor:" << glGetString(GL_VENDOR) << endl;
    closeApp();
    return 0;
}
