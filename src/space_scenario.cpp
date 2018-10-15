#include "space_scenario.h"
#include "ship.h"

SpaceScenario::SpaceScenario(){
    player_ship = new Ship();
    addChild( player_ship );

    network = Network();

    using namespace std;

    string answer = "";
    while( answer != "S" && answer != "s" && answer != "C" && answer != "c" ){
        cout << "Server(S) or Client(C)??" << endl;
        cin >> answer;
    }
    if( answer == "S" || answer == "s" ){
        //I'm a host
        network.setSocketPort(8010);

    }else{
        //I'm a client
        network.setSocketPort(8011);
        cout << "Server IP: " << endl;
        cin >> answer;
        network.connectWith( answer.c_str() , 8010 );
        handleNetwork();
    }

}

void    SpaceScenario::frameUpdate(){
    handlePlayerInput();
    handleNetwork();
}


void    SpaceScenario::handlePlayerInput(){
    if( Input::isKeyPressed(SDLK_LEFT) ){
        player_ship->setRotation( player_ship->getRotation() - 0.05 );
    } else
    if( Input::isKeyPressed(SDLK_RIGHT) ){
        player_ship->setRotation( player_ship->getRotation() + 0.05 );
    }
    if( Input::isKeyPressed(SDLK_UP) ){
        player_ship->setVelocity( player_ship->getVelocity() + Vector2(0,-0.3).rotatedByRad( player_ship->getRotation() ) );
    }
    if( Input::isKeyPressed(SDLK_DOWN) ){
        player_ship->setVelocity( player_ship->getVelocity() + Vector2(0,0.1).rotatedByRad( player_ship->getRotation() ) );
    }
    player_ship->setVelocity( player_ship->getVelocity() * 0.97 );
}

void SpaceScenario::handleNetwork( ){
    using namespace std;
    ENetEvent event;
    while( network.pollEvents(&event) ){
        if( event.type == ENET_EVENT_TYPE_CONNECT ){
            // someone joined!
            addOtherShip( event.peer );
            cout << "Someone joined!" << endl;
        }else
        if( event.type == ENET_EVENT_TYPE_DISCONNECT ){
            // someone disconnected
            removeOtherShip( event.peer );
            cout << "Someone disconnected!" << endl;
        }else
        if( event.type == ENET_EVENT_TYPE_RECEIVE ){
            //received a packet
            updateFromPack( event.peer , event.packet );
            enet_packet_destroy( event.packet );
        }else
        if( event.type == ENET_EVENT_TYPE_NONE ){
            //nothing to do here!
        }
    }

    ship_packet p;
    p.posx = player_ship->getPosition().x;
    p.posy = player_ship->getPosition().y;
    p.rot = player_ship->getRotation();
    network.sendPacket( (void*)&p , sizeof(p) , 0 , true );
     
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




