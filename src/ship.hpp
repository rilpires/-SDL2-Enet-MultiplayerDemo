#ifndef SHIP_H
#define SHIP_H

#include <engine.hpp>

class Ship : public PhysicObject {
    private:
        int life;
    public:
        Ship( bool otherplayer_ship = false );
        virtual void    _frameUpdate();
        SpriteObject*   getShipSpriteObject();
        void takeHit();
};


#endif