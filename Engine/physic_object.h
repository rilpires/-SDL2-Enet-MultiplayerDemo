#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include <SDL.h>
#include "spriteobject.h"

class PhysicObject : public SpriteObject {
    enum SHAPE { RECTANGLE , CIRCLE };
    
    protected:
        Vector2     velocity;
    public:
        PhysicObject();

        void        updatePhysics();

        Vector2     getVelocity();
        void        setVelocity(Vector2 v);
};

#endif