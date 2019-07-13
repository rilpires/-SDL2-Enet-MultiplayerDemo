#include <bullet.hpp>

Bullet::Bullet( Ship* ship ) : PhysicObject() {
    lifetime_in_frames = 0;
    setShapeCircle( 5 );
    SpriteObject* sprite = new SpriteObject( "bullet.png" );
    sprite->setZindex(-1);
    sprite->name = "bullet sprite";
    name = "bullet";
    addChild( sprite );
    if( ship->getMaskBit(0) ){
        setMaskBit(1,true);
    }else{
        setMaskBit(0,true);
	}
    velocity = Vector2(0,-7).rotatedByRad( ship->getShipSpriteObject()->rotation );
    ship->getParent()->addChild( this );
    setGlobalPosition( ship->getGlobalPosition() );
}

void Bullet::_frameUpdate(){
    lifetime_in_frames ++;
    if ( lifetime_in_frames > 50 ){
        queueDelete();
    }
}

void Bullet::_collidesWith( PhysicObject* other ){
    if( other->name.find("Ship") != std::string::npos ){
        static_cast<Ship*>(other)->takeHit();
        lifetime_in_frames = 999;
    }
}
