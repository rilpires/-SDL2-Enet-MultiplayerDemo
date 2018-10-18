#include "physic_server.hpp"


PhysicServer::PhysicServer(){
}


#include <iostream>
void        PhysicServer::updateEverything( std::vector<PhysicObject*>& all_physic_objects )
{
    for( auto it = all_physic_objects.begin() ; it != all_physic_objects.end() ; it ++ ){
        Vector2 velocity = (*it)->getVelocity();
        Vector2 position = (*it)->getPosition();
        (*it)->setPosition( position + velocity );
    }
}