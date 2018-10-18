#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "transformobject.hpp"
#include "structs.hpp"

class PhysicObject : public TransformObject {
    enum SHAPE { RECTANGLE , CIRCLE };
    
    protected:
        Vector2     velocity;
    public:
        PhysicObject();

        Vector2     getVelocity();
        void        setVelocity(Vector2 v);
};

#endif