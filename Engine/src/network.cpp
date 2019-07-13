#include <network.hpp>


#include <iostream>

Network::Network( ){
    host = NULL;
	enet_initialize();
}

void            Network::setSocketPort( uint16_t port ){
    if( host ) enet_host_destroy(host);
    my_adress.host = ENET_HOST_ANY;
    my_adress.port = port;
    host = enet_host_create(    &my_adress , 
                                8 /*number of connections*/, 
                                2 /*number of channels*/, 
                                0 /*outgoing bandwith*/ , 
                                0 /*incoming bandwidth*/ ); 
}
void            Network::connectWith(ENetAddress* other_address) {
	ENetPeer* peer = enet_host_connect(host, other_address, 2 /* channel count */, 0 /* any data */);
	if (peer == NULL) {
		std::cout << "peer == NULL" << std::endl;
	}
}
void            Network::connectWith(const char* _ip, uint16_t port) {
	ENetAddress other_address;
	enet_address_set_host(&other_address, _ip);
	other_address.port = port;
	connectWith(&other_address);
}

int      Network::pollEvents( ENetEvent* ev, uint16_t miliseconds_timeout){
    int ret = enet_host_service( host , ev , miliseconds_timeout ); 
    if( ret < 0 ){
        return -1;
    }else 
    if( ret == 0 ){
        return 0;
    }
    // Event occurred:
    if( ev->type == ENET_EVENT_TYPE_CONNECT ){
        connected_peers.push_back( ev->peer );
    } else 
    if( ev->type == ENET_EVENT_TYPE_DISCONNECT ) {
        for( auto it = connected_peers.begin() ; it != connected_peers.end() ; it++ )
        if( *it == ev->peer ){
            connected_peers.erase( it );
            break;
        }
    }
    return 1;
}

void            Network::sendPacket( void* data , size_t data_size , enet_uint8 channel , bool reliable ){
    using namespace std;
    ENetPacket* packet;
    if(reliable){
        packet = enet_packet_create(data , data_size , ENET_PACKET_FLAG_RELIABLE );
    }else{
        packet = enet_packet_create(data , data_size , 0 );
    }

    for( auto it = connected_peers.begin() ; it != connected_peers.end() ; it ++ ){
        enet_peer_send( *it , channel , packet );
    }
}
