#ifndef SHIP_H
#define SHIP_H

#include <engine.h>

class Ship : public PhysicObject {
    private:
    public:
        Ship( bool otherplayer_ship = false );

        virtual void    frameUpdate();
};

#endif