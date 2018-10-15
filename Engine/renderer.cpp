#include "renderer.h"

#include "path_finder.h"
#include "SDL_params.h"


SDL_Renderer* Renderer::sdl_renderer = NULL;
std::map<int,SpriteObject*> Renderer::active_objects;


void   Renderer::new_active_object( SpriteObject* obj ){
    active_objects.insert( std::pair<int,SpriteObject*>( obj->getId() , obj ) );    
}
void   Renderer::exit_active_object( SpriteObject* obj ){
    active_objects.erase( obj->getId() );
}

SDL_Texture*     Renderer::loadTexture( const char* resource_path ){
    SDL_Texture* tex = IMG_LoadTexture( sdl_renderer , getResPath( resource_path ).c_str() );
    SDL_SetTextureBlendMode( tex , SDL_BLENDMODE_BLEND );
    return tex; 
}

SDL_Texture*     Renderer::textureFromTTF( std::string text , SDL_Color color , TTF_Font* font ){
    SDL_Surface* surf = TTF_RenderText_Blended( font , text.c_str() , color );
    SDL_Texture* ret = SDL_CreateTextureFromSurface( sdl_renderer , surf ); 
    SDL_FreeSurface(surf);
    return ret;
}

void Renderer::setSDLRenderer( SDL_Renderer* r ){
    sdl_renderer = r;
}

void Renderer::drawEverything(){
    SDL_RenderClear( sdl_renderer );
    for( auto it = active_objects.begin() ; it != active_objects.end() ; it++ ){
        if( it->second->isInsideTree() ){
            SDL_Rect src_rect;
            SDL_Rect dst_rect;
            SDL_Point point;

            Vector2 tex_size = it->second->getSize();
            Vector2 global_pos = it->second->getGlobalPosition();
            Vector2 texture_offset = it->second->getTextureCenter();

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
            
            SDL_RenderCopyEx( sdl_renderer , it->second->getTexture() , &src_rect , &dst_rect ,  it->second->getRotation()*( 180.0/M_PI ) , &point , SDL_FLIP_NONE );
        }
    }
    SDL_RenderPresent( sdl_renderer );
}