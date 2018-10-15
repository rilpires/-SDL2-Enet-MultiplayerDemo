#include "ship.h"

Ship::Ship( bool otherplayer_ship ) : PhysicObject() {
    if( otherplayer_ship ){
        setTexture( Renderer::loadTexture("other_player_ship.png") );
    }else{
        setTexture( Renderer::loadTexture("player_ship.png") );
    }
}

void Ship::frameUpdate(){
    while( position.x < -SCREEN_WIDTH*0.5 - 50 ){
        position.x += SCREEN_WIDTH + 100;
    }while( position.x > SCREEN_WIDTH*0.5 + 50 ){
        position.x -= SCREEN_WIDTH + 100;
    }while( position.y < -SCREEN_HEIGHT*0.5 - 50 ){
        position.y += SCREEN_HEIGHT + 100;
    }while( position.y > SCREEN_HEIGHT*0.5 + 50 ){
        position.y -= SCREEN_HEIGHT + 100;
    }
}
