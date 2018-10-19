#include "physic_object.hpp"


PhysicObject::PhysicObject() : TransformObject( GAMEOBJECT_TYPE_PHYSIC ) {
    mask = 0;
    velocity = Vector2(0,0);
    shape_offset = Vector2(0,0);
}
PhysicObject::~PhysicObject(){
    exitedTree();
}

bool                PhysicObject::checkIfCollidesWith( PhysicObject* other ){
    if( ( mask & other->mask ) == 0 ){
        return false;
    }
    else if( shape_type == other->shape_type ){
        if( shape_type == SHAPE_TYPE_RECTANGLE ){
            Rect2 rect1( getGlobalPosition() + shape_offset - shape.rect.extents*0.5 , shape.rect.extents );
            Rect2 rect2( other->getGlobalPosition() + other->shape_offset - other->shape.rect.extents*0.5 , other->shape.rect.extents );
            return rect1.collidesWith(rect2);
        }else
        if( shape_type == SHAPE_TYPE_CIRCLE ){
            return ( other->getGlobalPosition() + other->shape_offset - getGlobalPosition() - shape_offset ).length() < shape.circle.radius + other->shape.circle.radius;
        }
    }
    else{
        // Some serious math shit here
        return false;
    }
	return false;
}

void                PhysicObject::setMaskBit(uint8_t bit_0_7 , bool val){
    if( val ){
        mask = mask | (int)pow(2,bit_0_7);
    }
    else{
        mask = mask & ( -1 - (int)pow(2,bit_0_7) );
    }
}


void                    PhysicObject::enteredTree(){
    colliding_bodies.clear();
}
void                    PhysicObject::exitedTree(){
    for( auto it = colliding_bodies.rbegin() ; it != colliding_bodies.rend() ; ++it ){
        it->second->colliding_bodies.erase( getId() );
    }
}