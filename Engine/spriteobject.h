#ifndef SPRITE_OBJECT_H
#define SPRITE_OBJECT_H

#include "gameobject.h"
#include <SDL.h>

class SpriteObject : public GameObject{
    protected:
        SDL_Texture* tex;
        Vector2 position;
        float rotation;
        Vector2 texture_center;
    public:
        SpriteObject( SDL_Texture* _tex = NULL );
        ~SpriteObject();
        
        SDL_Texture*    getTexture() const;
        void            setTexture( SDL_Texture* _tex );
        Vector2         getPosition();
        void            setPosition( Vector2 v );
        float           getRotation();
        void            setRotation( float v );
        Vector2         getGlobalPosition();
        Vector2         getTextureCenter();
        void            setTextureCenter( Vector2 val);
        const Vector2   getSize() const;
};

#endif