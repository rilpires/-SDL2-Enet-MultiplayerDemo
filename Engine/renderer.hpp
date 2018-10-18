#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include "spriteobject.hpp"


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Renderer{
    private:
        SDL_Window*                                         window;
        SDL_Renderer*                                       sdl_renderer;
        static std::map<std::string,SDL_Texture*>           loaded_textures;           
    
    public:

        Renderer( SDL_Window* sdl_window , SDL_Renderer* sdl_rend );
        void                    drawEverything( std::map< int , std::vector < SpriteObject* > > all_objects );

        static SDL_Texture*     getTexture( std::string path );
        void                    loadTexture( const char* resource_path );
        SDL_Texture*            textureFromTTF( std::string text , SDL_Color color , TTF_Font* font );
};






#endif