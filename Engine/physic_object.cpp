#include "physic_object.h"
#include <engine.h>

PhysicObject::PhysicObject() : SpriteObject( NULL ) {
    velocity = Vector2(0,0);
    PhysicServer::getCurrentPhysicServer()->new_physic_object( this );
}

void  PhysicObject::updatePhysics(){
    position += velocity;
}


Vector2     PhysicObject::getVelocity(){
    return velocity;
}

void        PhysicObject::setVelocity(Vector2 v){
    velocity = v;
}