#ifndef SPACE_SCENARIO_H
#define SPACE_SCENARIO_H

#include <engine.hpp>
#include <map>

class Ship;

class SpaceScenario : public GameObject{
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
        void    handleNetwork( uint16_t miliseconds_timeout = 0);
        void    frameUpdate();
        void    addOtherShip( ENetPeer* peer );
        void    removeOtherShip( ENetPeer* peer );
        void    updateFromPack( ENetPeer* peer , ENetPacket* packet );
};


#endif