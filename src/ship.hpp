#ifndef SHIP_H
#define SHIP_H

#include <engine.hpp>

class Ship : public PhysicObject {
    private:
        const   int     max_life = 5;
        int             life;
        SpriteObject*   ship_sprite;
        SpriteObject*   bar_sprite;
    public:
        Ship( bool otherplayer_ship = false );
        
        virtual void        _frameUpdate();
        SpriteObject*       getShipSpriteObject(){return ship_sprite;}
		int		            getCurrentLife() const { return life; }
        void	            takeHit();
        void                setLife(int new_val);
        int                 getCurrentLife(){return life;}
};


#endif