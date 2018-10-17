#include "space_scenario.h"
#include "ship.h"
#include "../Server/server.h"

SpaceScenario::SpaceScenario() {
	using namespace std;
	player_ship = new Ship();
	addChild(player_ship);

	network = Network();
	network.setSocketPort(8010);

	string answer = "";
	cout << "Enter server ip" << endl;
	cin >> answer;
	network.connectWith(answer.c_str(), 8011);

	ENetEvent event;
	if ( network.pollEvents(&event , 5000) > 0){
		if (event.type == ENET_EVENT_TYPE_CONNECT) {
            cout << "Joined server: " << event.peer->address.host << ":" << event.peer->address.port << endl;
		}
	}
}

void    SpaceScenario::frameUpdate(){
    handlePlayerInput();
    handleNetwork();
}


void    SpaceScenario::handlePlayerInput(){
    if( Input::isKeyPressed( SDL_SCANCODE_LEFT ) ){
        player_ship->setRotation( player_ship->getRotation() - 0.05 );
    }
    if( Input::isKeyPressed( SDL_SCANCODE_RIGHT) ){
        player_ship->setRotation( player_ship->getRotation() + 0.05 );
    }
    if( Input::isKeyPressed(SDL_SCANCODE_UP ) ){
        player_ship->setVelocity( player_ship->getVelocity() + Vector2(0,-0.3).rotatedByRad( player_ship->getRotation() ) );
    }
    if( Input::isKeyPressed(SDL_SCANCODE_DOWN ) ){
        player_ship->setVelocity( player_ship->getVelocity() + Vector2(0,0.1).rotatedByRad( player_ship->getRotation() ) );
    }
    player_ship->setVelocity( player_ship->getVelocity() * 0.97 );
}

void SpaceScenario::handleNetwork( uint16_t miliseconds_timeout){
    using namespace std;
    ENetEvent event;
    while( network.pollEvents(&event , miliseconds_timeout ) ){
        if( event.type == ENET_EVENT_TYPE_CONNECT ){
            // someone joined!
            addOtherShip( event.peer );
            cout << "Someone joined!" << endl;
        }else
        if( event.type == ENET_EVENT_TYPE_DISCONNECT ){
            // someone disconnected
            if( event.channelID == 0 ){
                cout << "Server went nuts" << endl;
            }else if( event.channelID == 1 ){
                removeOtherShip( event.peer );
                cout << "Someone disconnected!" << endl;
            }
        }else
        if( event.type == ENET_EVENT_TYPE_RECEIVE ){
            //received a packet
			if (event.channelID == 0) {
				//Received from server
				ENetAddress* address = (ENetAddress*)event.packet->data;
                cout << " trying to connect with peers...." << endl;
				network.connectWith( address );
			}else if (event.channelID == 1) {
				//Received from peer(player)
				updateFromPack(event.peer, event.packet);
			}
			enet_packet_destroy(event.packet);
        }else
        if( event.type == ENET_EVENT_TYPE_NONE ){
            //nothing to do here!
        }
    }

    ship_packet p;
    p.posx = player_ship->getPosition().x;
    p.posy = player_ship->getPosition().y;
    p.rot = player_ship->getRotation();
    network.sendPacket( (void*)&p , sizeof(p) , 1 , true );
     
}

void    SpaceScenario::addOtherShip( ENetPeer* peer ){
    Ship* new_ship = new Ship(true);
    other_ships[peer] = new_ship;
    addChild( new_ship );
}
void    SpaceScenario::removeOtherShip( ENetPeer* peer ){
    Ship* ship = other_ships[peer];
    other_ships.erase( peer );
    ship->exitTree();
}
void    SpaceScenario::updateFromPack( ENetPeer* peer , ENetPacket* packet ){
    Ship* ship = other_ships[ peer ];
    ship_packet* p = (ship_packet*)(packet->data);
    ship->setPosition( Vector2(p->posx,p->posy) );
    ship->setRotation( p->rot );
}




