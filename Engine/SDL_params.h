#ifndef SDL_PARAMS_H
#define SDL_PARAMS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern bool sdl_quit;

extern SDL_Window* sdl_window;
extern TTF_Font* default_font;

bool _init_sdl_params();


#endif