#include "physic_server.h"

PhysicServer* PhysicServer::current_server = NULL;

PhysicServer::PhysicServer(){
    all_physic_objects = std::vector<PhysicObject*>();
}
void        PhysicServer::new_physic_object( PhysicObject* obj ){
    all_physic_objects.push_back( obj );
}
void        PhysicServer::exit_physic_object( PhysicObject* obj ){
    for( auto it = all_physic_objects.begin() ; it != all_physic_objects.end() ; it++ ){
        if( *it == obj ){
            all_physic_objects.erase( it );
            break;
        }
    }
}
void        PhysicServer::updatePhysics(){
    for( auto it = all_physic_objects.begin() ; it != all_physic_objects.end() ; it++ ){
        (*it)->setPosition( (*it)->getPosition() + (*it)->getVelocity() );
    }
}

void PhysicServer::setCurrentPhysicServer( PhysicServer* server ){
    current_server = server;
}

PhysicServer* PhysicServer::getCurrentPhysicServer( ){
    return current_server;
}

