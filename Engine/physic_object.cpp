#include "physic_object.hpp"

PhysicObject::PhysicObject() : TransformObject( GAMEOBJECT_TYPE_PHYSIC ) {
    velocity = Vector2(0,0);
}


Vector2     PhysicObject::getVelocity(){
    return velocity;
}

void        PhysicObject::setVelocity(Vector2 v){
    velocity = v;
}