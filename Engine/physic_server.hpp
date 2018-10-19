#ifndef PHYSIC_SERVER_H
#define PHYSIC_SERVER_H

#include "physic_object.hpp"
#include <vector>

class PhysicServer{
        Rect2                   getLimits(std::vector<PhysicObject*>& all_physic_objects);
    public:
        PhysicServer();
        void                    updateEverything( std::vector<PhysicObject*>& all_physic_objects );
};

#endif