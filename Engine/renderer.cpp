#include "path_finder.hpp"
#include "renderer.hpp"

std::map<std::string,SDL_Texture*>           Renderer::loaded_textures;

Renderer::Renderer( SDL_Window* sdl_window , SDL_Renderer* rend ){
    sdl_renderer = rend;
    window = sdl_window;
}

SDL_Texture*      Renderer::getTexture( std::string path ){
    return loaded_textures[ path ];
}

void Renderer::drawEverything( std::map< int , std::vector < SpriteObject* > > all_objects ){
    using namespace std;
    SDL_RenderClear( sdl_renderer );
    for( auto it = all_objects.begin() ; it != all_objects.end() ; it++ ){
        for( auto it2 = (it->second).begin() ; it2 != (it->second).end() ; it2++ ){
            SDL_Rect src_rect;
            SDL_Rect dst_rect;
            SDL_Point point;

            Vector2 tex_size = (*it2)->getSize();
            Vector2 global_pos = (*it2)->getGlobalPosition();
            Vector2 texture_offset = (*it2)->getTextureCenter();

            src_rect.x = 0;
            src_rect.y = 0;
            src_rect.w = (int)tex_size.x;
            src_rect.h = (int)tex_size.y;

            dst_rect.x = SCREEN_WIDTH * 0.5 + global_pos.x - texture_offset.x;
            dst_rect.y = SCREEN_HEIGHT * 0.5 + global_pos.y - texture_offset.y;
            dst_rect.w = (int)tex_size.x;
            dst_rect.h = (int)tex_size.y;

            point.x = (int)texture_offset.x;
            point.y = (int)texture_offset.y;
            
            SDL_RenderCopyEx( sdl_renderer , (*it2)->getTexture() , &src_rect , &dst_rect ,  (*it2)->getGlobalRotation()*( 180.0/M_PI ) , &point , SDL_FLIP_NONE );
        }
    }
    SDL_RenderPresent( sdl_renderer );
}


void     Renderer::loadTexture( const char* resource_path ){
    SDL_Texture* tex = IMG_LoadTexture( sdl_renderer , getResPath( resource_path ).c_str() );
    SDL_SetTextureBlendMode( tex , SDL_BLENDMODE_BLEND );
    loaded_textures[ std::string(resource_path) ] = tex; 
}

SDL_Texture*     Renderer::textureFromTTF( std::string text , SDL_Color color , TTF_Font* font ){
    SDL_Surface* surf = TTF_RenderText_Blended( font , text.c_str() , color );
    SDL_Texture* ret = SDL_CreateTextureFromSurface( sdl_renderer , surf ); 
    SDL_FreeSurface(surf);
    return ret;
}








