#include "ship.hpp"

Ship::Ship( bool otherplayer_ship ) : PhysicObject() {
    setShapeCircle( 15 );
    life = 15;
    if( otherplayer_ship ){
        SpriteObject* sprite = new SpriteObject( "other_player_ship.png" ) ;
        addChild( sprite );
        name = "OtherPlayerShip";
		sprite->name = "Sprite";
		setMaskBit(1, true);
    }else{
        SpriteObject* sprite = new SpriteObject( "player_ship.png" ) ;
        addChild( sprite );
        name = "PlayerShip";
        sprite->name = "Sprite";
        setMaskBit(0,true);
    }
}

void Ship::_frameUpdate(){
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


void Ship::takeHit(){
    life --;
    if( life <= 0 ){
		queueDelete();
    }
}

