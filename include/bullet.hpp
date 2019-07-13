#ifndef BULLET_H
#define BULLET_H

#include <engine.hpp>
#include "ship.hpp"

class Bullet : public PhysicObject {
    public:
        unsigned int lifetime_in_frames;
        Bullet( Ship* ship );
        void    _frameUpdate();
        void    _collidesWith(PhysicObject* other);
};



#endif
