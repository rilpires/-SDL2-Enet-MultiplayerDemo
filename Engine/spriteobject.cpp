#include "spriteobject.h"
#include "renderer.h"



SpriteObject::SpriteObject( SDL_Texture* _tex ) : GameObject() {
    setTexture( _tex );
    Renderer::new_active_object( this );
}

SpriteObject::~SpriteObject( ){
    Renderer::exit_active_object( this );
}

SDL_Texture*    SpriteObject::getTexture() const {
    return tex;
}
void            SpriteObject::setTexture( SDL_Texture* _tex ){
    tex = _tex;
    if( tex ){
        int w,h;
        SDL_QueryTexture( tex , NULL , NULL , &w , &h );
        texture_center = Vector2( w*0.5 , h*0.5 );
    }else{
        texture_center = Vector2(0,0);
    }
}
Vector2         SpriteObject::getPosition(){
    return position;
}
void         SpriteObject::setPosition( Vector2 v ){
    position = v;
}
float           SpriteObject::getRotation(){
    return rotation;
}
void            SpriteObject::setRotation( float v ){
    rotation = v;
}
Vector2         SpriteObject::getGlobalPosition(){
    Vector2 ret = position;
    GameObject* current_parent = getParent();
    while( current_parent != NULL ){
        ret += current_parent->getPosition();
        current_parent = current_parent->getParent();
    }
    return ret;
}

Vector2 SpriteObject::getTextureCenter(){
    return texture_center;
}    

void    SpriteObject::setTextureCenter( Vector2 val){
    texture_center = val;
}
    
const Vector2 SpriteObject::getSize() const{
    int w,h;
    SDL_QueryTexture( getTexture() , NULL , NULL , &w , &h );
    return Vector2( w , h );
}


