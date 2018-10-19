#ifndef SPACE_SCENARIO_H
#define SPACE_SCENARIO_H

#include <engine.hpp>
#include <map>

class Ship;

class SpaceScenario : public GameObject{
    struct ship_packet{
		Vector2	position;
		bool	has_shot;
		uint8_t	current_life;
		float	rot;
		ship_packet() { position = Vector2(), has_shot = false, current_life = 1; rot = 0; }
    };

    private:
        Network                     network;
        Ship*                       player_ship;
        std::map<ENetPeer*,Ship*>   other_ships;
		ship_packet					next_packet_to_send;
    public:
        SpaceScenario();
        
        void    handlePlayerInput();
        void    handleNetwork( uint16_t miliseconds_timeout = 0);
        void    _frameUpdate();
        void    addOtherShip( ENetPeer* peer );
        void    removeOtherShip( ENetPeer* peer );
        void    updateFromPack( ENetPeer* peer , ENetPacket* packet );
};


#endif