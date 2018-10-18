#include "server.hpp"
#include <iostream>

SpaceServer::SpaceServer(std::string ip_address ){
    using namespace std;
    if ( enet_initialize() ){
		//std::cout << "Couldn't initialize enet" << std::endl;
    }
    if( ip_address == "" )
        address.host = ENET_HOST_ANY;
    else 
        enet_address_set_host( &address , ip_address.c_str() );
    address.port = 8011;
    
    host = enet_host_create( &address , 
                            32 , // Maximum number of clients
                            2 , // Number of channels
                            0 , // incoming bandwidth
                            0 ); // outgoing bandwidth

    ENetEvent event;
    
    while( true ){
        while( enet_host_service(host , &event , 1000.0 / 60.0 ) > 0 ){
            switch( event.type ){
                case ENET_EVENT_TYPE_CONNECT:
                    char ip_address[256];
                    enet_address_get_host_ip( &(event.peer->address) , ip_address , 256 );
                    cout << "someone joined:" << std::endl;
                    cout << "host_ip: " << ip_address << endl;
                    addNewPeer( event.peer );
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    std::cout << event.peer->address.host << " disconnected" << std::endl;
                    removePeer( event.peer );
                    break;
                case ENET_EVENT_TYPE_RECEIVE:
                    enet_packet_destroy( event.packet );
                    break;
                case ENET_EVENT_TYPE_NONE:
                    break;
            }
        }
    }

}

void SpaceServer::addNewPeer( ENetPeer* peer ){
    peers.push_back( peer );

    ENetAddress address;
    address.port = peer->address.port;
    char ip_address[256];
    enet_address_get_host_ip( &(peer->address) , ip_address , 256 );
    enet_address_set_host( &address , ip_address );
    
    ENetPacket* packet = enet_packet_create( (void*)&address , sizeof(ENetAddress) , ENET_PACKET_FLAG_RELIABLE );
    for( auto it = peers.begin() ; it != peers.end() ; it ++) if( *it != peer ){
        enet_peer_send( *it , 0 , packet );
    }
}
void SpaceServer::removePeer( ENetPeer* peer ){
	for (auto it = peers.begin(); it != peers.end(); it++) {
		if (*it == peer) {
			peers.erase(it);
			return;
		}
	}
}

int main() {
	SpaceServer* space_server = new SpaceServer();
}














