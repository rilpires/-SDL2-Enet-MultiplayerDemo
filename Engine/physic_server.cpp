#include "physic_server.hpp"


PhysicServer::PhysicServer() {
}

void        PhysicServer::updateEverything( std::vector<PhysicObject*>& all_physic_objects )
{
    for( auto it = all_physic_objects.begin() ; it != all_physic_objects.end() ; it ++ ){
        Vector2 velocity = (*it)->velocity;
        Vector2 position = (*it)->getPosition();
        (*it)->setPosition( position + velocity );
    }

    //Dumb N^2 collision checking
    for( auto it = all_physic_objects.begin() ; it != all_physic_objects.end() ; it ++ )
    for( auto it2 = it + 1 ; it2 != all_physic_objects.end() ; it2 ++ ){
        
        PhysicObject* obj1 = *it;
        PhysicObject* obj2 = *it2;
        
        if( obj1->checkIfCollidesWith(obj2) ){
            if( obj1->colliding_bodies.find(obj2->getId()) == obj1->colliding_bodies.end() ){
                obj1->_collidesWith(obj2);
                obj2->_collidesWith(obj1);
            }
            obj1->colliding_bodies[obj2->getId()] = obj2;
            obj2->colliding_bodies[obj1->getId()] = obj1;
        }else if( obj1->colliding_bodies.find(obj2->getId()) != obj1->colliding_bodies.end()  ) {
            obj1->colliding_bodies.erase( obj2->getId() );
            obj2->colliding_bodies.erase( obj1->getId() );
        }

    }
    
    

}

Rect2       PhysicServer::getLimits(std::vector<PhysicObject*>& all_physic_objects){
    
    Rect2 ret;
    if( all_physic_objects.size() == 0 ){
        ret.x = 0;
        ret.y = 0;
        ret.w = 0;
        ret.h = 0;
    }
    else{
        PhysicObject* obj = all_physic_objects[0];
        ret.x = obj->getGlobalPosition().x;
        ret.y = obj->getGlobalPosition().x;
        ret.w = 1;
        ret.h = 1;
        for( auto it = all_physic_objects.begin() ; it != all_physic_objects.end() ; it ++ ){
            float x = (*it)->getGlobalPosition().x;
            float y = (*it)->getGlobalPosition().y;
            if( x > ret.x + ret.w )
                ret.w = x - ret.x;
            if( y > ret.y + ret.h )
                ret.h = y - ret.h;
            if( x < ret.x )
                ret.x = x;
            if( y < ret.y )
                ret.y = y;
        }
    }
    return ret;
}


