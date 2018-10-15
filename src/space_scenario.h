#ifndef SPACE_SCENARIO_H
#define SPACE_SCENARIO_H

#include <engine.h>
#include <map>

class Ship;

class SpaceScenario : public SpriteObject{
    struct ship_packet{
        float posx;
        float posy;
        float rot;
    };

    private:
        Network                     network;
        Ship*                       player_ship;
        std::map<ENetPeer*,Ship*>   other_ships;
    public:
        SpaceScenario();
        
        void    handlePlayerInput();
        void    handleNetwork(  );
        void    frameUpdate();
        void    addOtherShip( ENetPeer* peer );
        void    removeOtherShip( ENetPeer* peer );
        void    updateFromPack( ENetPeer* peer , ENetPacket* packet );
};


#endif