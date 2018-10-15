#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "structs.h"
#include <map>
#include "spriteobject.h"


class Renderer{

    private:
        static std::map<int,SpriteObject*>  active_objects;
        static SDL_Renderer*                sdl_renderer;
    public:
        static void             drawEverything();
        static void             new_active_object( SpriteObject* obj );
        static void             exit_active_object( SpriteObject* obj );
        static void             setSDLRenderer( SDL_Renderer* r );
        static SDL_Texture*     loadTexture( const char* resource_path );
        static SDL_Texture*     textureFromTTF( std::string text , SDL_Color color , TTF_Font* font );
};



#endif