#include "spriteobject.hpp"
#include "initial_scene.hpp"


SpriteObject::SpriteObject( SDL_Texture* _tex ) : TransformObject( GAMEOBJECT_TYPE_RENDER ) {
    setTexture( _tex );
    z_index = 0;
}
SpriteObject::SpriteObject( const char* path ) : TransformObject( GAMEOBJECT_TYPE_RENDER ) {
    setTexture( Renderer::getTexture(path) );
    z_index = 0;
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

Vector2 SpriteObject::getTextureCenter(){
    return texture_center;
}    

void    SpriteObject::setTextureCenter( Vector2 val){
    texture_center = val;
}
    
const Vector2 SpriteObject::getSize() const{
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




