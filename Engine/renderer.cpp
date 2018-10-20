#include "path_finder.hpp"
#include "renderer.hpp"

SDL_Renderer*                                Renderer::sdl_renderer = NULL;
std::map<std::string,SDL_Surface*>           Renderer::loaded_surfaces;

Renderer::Renderer( SDL_Window* sdl_window , SDL_Renderer* rend ){
    if( sdl_renderer != NULL ){
        std::cout << "Already has a renderer!" << std::endl;
    }
    sdl_renderer = rend;
    window = sdl_window;
}

SDL_Surface*      Renderer::getSurface( const char* resource_path ){
    return loaded_surfaces[std::string( resource_path ) ];
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
            Vector2 texture_offset = (*it2)->texture_center;
            Vector2 scale = (*it2)->scale;

            src_rect.x = 0;
            src_rect.y = 0;
            src_rect.w = tex_size.x;
            src_rect.h = tex_size.y;

            dst_rect.x = SCREEN_WIDTH * 0.5 + global_pos.x - texture_offset.x * abs(scale.x) ;
            dst_rect.y = SCREEN_HEIGHT * 0.5 + global_pos.y - texture_offset.y * abs(scale.y);
            dst_rect.w = tex_size.x * abs(scale.x);
            dst_rect.h = tex_size.y * abs(scale.y);

            point.x = texture_offset.x * abs(scale.x);
            point.y = texture_offset.y * abs(scale.y);
            
            SDL_RenderCopyEx( sdl_renderer , (*it2)->getTexture() , &src_rect , &dst_rect ,  (*it2)->getGlobalRotation()*( 180.0/M_PI ) , &point , SDL_FLIP_NONE );
        }
    }
    SDL_RenderPresent( sdl_renderer );
}


void     Renderer::loadSurface( const char* resource_path ){
	std::string name(resource_path);
    SDL_Surface* s;
    if( name.find(".jpg") != std::string::npos ){
		std::cout << "Loading jpg images are not supported" << name << std::endl;
        return;
    }else{
        s = IMG_Load( getResPath(resource_path).c_str() ); 
    }
    SDL_SetSurfaceBlendMode( s , SDL_BLENDMODE_BLEND );
    loaded_surfaces[ std::string(resource_path) ] = s;
}

SDL_Texture*     Renderer::textureFromTTF( std::string text , SDL_Color color , TTF_Font* font ){
    SDL_Surface* surf = TTF_RenderText_Blended( font , text.c_str() , color );
    SDL_Texture* ret = SDL_CreateTextureFromSurface( sdl_renderer , surf ); 
    SDL_FreeSurface(surf);
    return ret;
}








