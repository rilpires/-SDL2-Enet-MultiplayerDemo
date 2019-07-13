#include <spriteobject.hpp>
#include <initial_scene.hpp>


SpriteObject::SpriteObject( SDL_Surface* surf ) : TransformObject( GAMEOBJECT_TYPE_RENDER ) {
    surface = surf;

    //all constructors must have:
    tex = NULL;
    createTextureFromImage( surface );
    monocolor=false;
    z_index = 0;
    setModulate( 255 , 255 , 255 , 255 );
    texture_center = Vector2( surface->w , surface->h )*0.5;
    scale = Vector2(1,1);
}
SpriteObject::SpriteObject( const char* path ) : TransformObject( GAMEOBJECT_TYPE_RENDER ) {
    surface = Renderer::getSurface(path);
    
    //all constructors must have:
    tex = NULL;
    createTextureFromImage( surface );
    monocolor=false;
    z_index = 0;
    setModulate( 255 , 255 , 255 , 255 );
    texture_center = Vector2( surface->w , surface->h )*0.5;
    scale = Vector2(1,1);
}
SpriteObject::SpriteObject( Vector2 filled_rect , uint32_t border , uint8_t r , uint8_t g , uint8_t b , uint8_t a ) :
        TransformObject( GAMEOBJECT_TYPE_RENDER ) {    
    surface = SDL_CreateRGBSurfaceWithFormat(0,filled_rect.x,filled_rect.y,32,SDL_PIXELFORMAT_RGBA32);
    SDL_Rect rect; rect.x = 0 ; rect.y = 0 ; rect.w = filled_rect.x ; rect.h = filled_rect.y;
    
    SDL_FillRect( surface , &rect , SDL_MapRGBA(surface->format,r,g,b,a) );
    if( border != 0 ){
        SDL_Rect inside_rect = rect;
        inside_rect.x += border; inside_rect.y += border;
        inside_rect.w -= 2*border; inside_rect.h -= 2*border;
        SDL_FillRect( surface , &inside_rect , SDL_MapRGBA(surface->format,r,g,b,0) );
    }

    //all constructors must have:
    tex = NULL;
    createTextureFromImage( surface );
    monocolor=false;
    z_index = 0;
    setModulate( 255 , 255 , 255 , 255 );
    texture_center = Vector2( surface->w , surface->h )*0.5;
    scale = Vector2(1,1);
}

SpriteObject::~SpriteObject(){
    if (tex != NULL )
        SDL_DestroyTexture(tex);
}

void            SpriteObject::createTextureFromImage( SDL_Surface* surf ){
    SDL_DestroyTexture(tex);
    SDL_Renderer* sdl_renderer = Renderer::getSDLRenderer();
    SDL_Rect rect;
    rect.x=0;rect.y=0;rect.w=surf->w;rect.h=surf->h;
    SDL_Texture* old_target = SDL_GetRenderTarget( sdl_renderer );
    tex = SDL_CreateTexture( sdl_renderer , surf->format->format , SDL_TEXTUREACCESS_TARGET , surf->w , surf->h );
    SDL_SetTextureBlendMode( tex , SDL_BLENDMODE_BLEND );
    SDL_SetRenderTarget( sdl_renderer , tex );
    SDL_Texture* t = SDL_CreateTextureFromSurface( sdl_renderer , surf );
    SDL_SetRenderDrawColor( sdl_renderer , 0 , 0 , 0 , 0 );
    SDL_RenderDrawRect(sdl_renderer,&rect);
    SDL_SetTextureBlendMode( t , SDL_BLENDMODE_BLEND );
    SDL_RenderCopy( sdl_renderer , t , &rect , &rect );
    SDL_DestroyTexture( t );
    SDL_SetTextureColorMod( tex , modulate.r , modulate.g , modulate . b );
    SDL_SetTextureAlphaMod( tex , modulate.a );
    SDL_SetRenderTarget( sdl_renderer , old_target );
}
void            SpriteObject::createTextureFromImage( const char* resource_path ){
    createTextureFromImage( Renderer::getSurface( resource_path ) );
}
void    SpriteObject::setMonocolor( bool val ){
    if( tex == NULL || monocolor == val ) return;
    monocolor = val;
    if(monocolor){
        SDL_Renderer* sdl_renderer = Renderer::getSDLRenderer();
        SDL_Texture* old_target = SDL_GetRenderTarget( sdl_renderer );
        Vector2 size = getSize();
        SDL_Rect rect;
        rect.x=0;rect.y=0;rect.w=size.x;rect.h=size.y;
        SDL_SetRenderTarget( sdl_renderer , tex );
        SDL_Surface* s = SDL_CreateRGBSurfaceWithFormat( 0 , size.x , size.y , 32 , SDL_PIXELFORMAT_RGBA32 );
        SDL_FillRect( s , &rect , SDL_MapRGBA(s->format,255,255,255,255) );
        SDL_Texture* t = SDL_CreateTextureFromSurface(sdl_renderer,s);
        SDL_SetTextureBlendMode(t,SDL_BLENDMODE_ADD);
        SDL_RenderCopy( sdl_renderer , t , &rect , &rect );
        SDL_FreeSurface( s );
        SDL_DestroyTexture( t );
        SDL_SetTextureColorMod( tex , modulate.r , modulate.g , modulate . b );
        SDL_SetTextureAlphaMod( tex , modulate.a );
        SDL_SetRenderTarget( sdl_renderer , old_target );
    }else{
        createTextureFromImage( surface );
    }
}    
const Vector2 SpriteObject::getSize() const{
    if(tex==NULL)return Vector2(0,0);
    int w,h;
    SDL_QueryTexture( getTexture() , NULL , NULL , &w , &h );
    return Vector2( (float)w , (float)h );
}


Renderer* SpriteObject::getRenderer() const {
    GameObject* root = getParent();
    while( root != NULL )
        root = root->getParent();
    return ((InitialScene*)root)->getRenderer();
}

void    SpriteObject::setModulate( uint8_t r , uint8_t g , uint8_t b , uint8_t a ){
    modulate.r = r ; modulate.g = g; modulate.b = b; modulate.a = a;
    if( tex != NULL ){
        SDL_SetTextureColorMod( tex , r , g , b );
        SDL_SetTextureAlphaMod( tex , a );   
    }
}


