#include "SDL_params.h"
#include <iostream>
#include "renderer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool sdl_quit = false;

SDL_Window* sdl_window;

bool _init_sdl_params(){
    
    sdl_window = SDL_CreateWindow("SpaceShooterVS" , 100 , 100 , SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_SHOWN );
    
    SDL_Renderer* sdl_renderer = SDL_CreateRenderer( sdl_window , -1 , SDL_RENDERER_ACCELERATED  );
    Renderer::setSDLRenderer( sdl_renderer );

    if( sdl_window && sdl_renderer )
        return true;
    else
        return false;
}
