#ifndef PHYSIC_SERVER_H
#define PHYSIC_SERVER_H

#include "physic_object.h"
#include <vector>

class PhysicServer{
    private:
        static PhysicServer*    current_server;
        std::vector<PhysicObject*> all_physic_objects;
    public:
        PhysicServer();
        static void             setCurrentPhysicServer( PhysicServer* server );
        static PhysicServer*    getCurrentPhysicServer( );
        void                    new_physic_object( PhysicObject* obj );
        void                    exit_physic_object( PhysicObject* obj );
        void                    updatePhysics();
};

#endif