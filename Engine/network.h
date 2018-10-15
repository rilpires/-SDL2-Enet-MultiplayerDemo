#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <enet/enet.h>
#include <string>

class Network {
    private:
        ENetAddress             my_adress;
        ENetHost*               host;
        std::vector<ENetPeer*>  connected_peers;
    public:
        Network( );
        void            setSocketPort( uint16_t port );
        void            connectWith( const char* _ip , uint16_t port );
        int             pollEvents( ENetEvent* ev );
        void            sendPacket( void* data , size_t data_size , uint8_t channel , bool reliable = true );
};

#endif