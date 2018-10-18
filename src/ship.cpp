#include "ship.hpp"

Ship::Ship( bool otherplayer_ship ) : PhysicObject() {
    if( otherplayer_ship ){
        SpriteObject* sprite = new SpriteObject( "other_player_ship.png" ) ;
        addChild( sprite );
    }else{
        SpriteObject* sprite = new SpriteObject( "player_ship.png" ) ;
        addChild( sprite );
        setName("PlayerShipPhysic");
        sprite->setName("Sprite");
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

SpriteObject* Ship::getShipSpriteObject(){
    return (SpriteObject*)getChild("Sprite");
}