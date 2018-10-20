#include "ship.hpp"

Ship::Ship( bool otherplayer_ship ) : PhysicObject() {
    setShapeCircle( 15 );
    
    //Setting up life bar
    SpriteObject* bar_borders = new SpriteObject( Vector2(50,5) , 1 ); 
    bar_sprite = new SpriteObject( Vector2(50,5) , 0 );
    bar_sprite->position = Vector2(-25,0);
    bar_sprite->texture_center = Vector2(0,2.5);
    bar_borders->addChild( bar_sprite );
    bar_borders->position.y -= 20;
    
    //Specific to which player
    if( otherplayer_ship ){
        ship_sprite = new SpriteObject( "other_player_ship.png" ) ;
        addChild( ship_sprite );
        name = "OtherPlayerShip";
		ship_sprite->name = "Sprite";
		setMaskBit(1, true);
        bar_borders->setRGB(155,55,55);
        bar_sprite->setRGB(255,55,55);
    }else{
        ship_sprite = new SpriteObject( "player_ship.png" ) ;
        addChild( ship_sprite );
        name = "PlayerShip";
        ship_sprite->name = "Sprite";
        setMaskBit(0,true);
        bar_borders->setRGB(55,155,55);
        bar_sprite->setRGB(55,255,55);
    }
    addChild( bar_borders );
    setLife(max_life);
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
    getShipSpriteObject()->setMonocolor(false);
}

void    Ship::setLife(int new_val){
    life = new_val;
    bar_sprite->scale.x = life / (float)max_life;
}
void Ship::takeHit(){
    life --;
    getShipSpriteObject()->setMonocolor(true);
    if( life <= 0 ){
		life = max_life;
		setPosition(Vector2(0,0));
		getShipSpriteObject()->setRotation(0);
		//queueDelete();
    }
    setLife( life );
}

