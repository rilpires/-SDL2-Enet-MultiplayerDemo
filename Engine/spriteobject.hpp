#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "transformobject.hpp"
#include <SDL.h>


class Renderer;
class SpriteObject : public TransformObject{
    private:
    protected:
        SDL_Surface*        surface;
        SDL_Texture*        tex;
        int                 z_index;
        bool                monocolor;
        SDL_Color           modulate;
    public:
        Vector2         texture_center;
        Vector2         scale;

        SpriteObject( const char* path );
        SpriteObject( SDL_Surface* surf = NULL );
        SpriteObject( Vector2 filled_rect , uint32_t border_0_is_filled = 0 , uint8_t r = 255 , uint8_t g = 255 , uint8_t b = 255 , uint8_t a = 255 );
        ~SpriteObject();
        
        SDL_Texture*    getTexture() const {return tex;};
        void            createTextureFromImage( SDL_Surface* surf );
        void            createTextureFromImage( const char* resource_name );
        int             getZindex() const ;
        void            setZindex( int new_val );
        const Vector2   getSize() const ;
        Renderer*       getRenderer() const ;
        bool            isMonocolor() const { return monocolor; }
        void            setMonocolor( bool val );
        SDL_Color       getModulate() const {return modulate;}
        void            setModulate( uint8_t r , uint8_t g , uint8_t b , uint8_t a );
        void            setAlpha( uint8_t a )  {setModulate(modulate.r,modulate.g,modulate.b,a);}
        void            setRGB( uint8_t r , uint8_t g , uint8_t b){setModulate(r,g,b,modulate.a);}
};


inline int             SpriteObject::getZindex() const{
    return z_index;
}
inline void            SpriteObject::setZindex( int new_val ){
    z_index = new_val;
}



#endif