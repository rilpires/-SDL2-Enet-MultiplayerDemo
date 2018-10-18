#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "transformobject.hpp"
#include <SDL.h>


class Renderer;
class SpriteObject : public TransformObject{
    private:
    protected:
        SDL_Texture*        tex;
        Vector2             texture_center;
        int                 z_index;
    public:
        SpriteObject( const char* path );
        SpriteObject( SDL_Texture* _tex = NULL );
        
        SDL_Texture*    getTexture() const;
        void            setTexture( SDL_Texture* _tex );
        int             getZindex() const ;
        void            setZindex( int new_val );
        Vector2         getTextureCenter();
        void            setTextureCenter( Vector2 val);
        const Vector2   getSize() const ;
        Renderer*       getRenderer() const ;
};


inline int             SpriteObject::getZindex() const{
    return z_index;
}
inline void            SpriteObject::setZindex( int new_val ){
    z_index = new_val;
}



#endif