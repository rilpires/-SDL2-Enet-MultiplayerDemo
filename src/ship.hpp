#ifndef SHIP_H
#define SHIP_H

#include <engine.hpp>

class Ship : public PhysicObject {
    private:
    public:
        Ship( bool otherplayer_ship = false );
        virtual void    frameUpdate();
        SpriteObject*   getShipSpriteObject();
};

#endif