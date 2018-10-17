#include <enet/enet.h>
#include <string>
#include <vector>


class SpaceServer {
public:
	enum PACKET_TYPE { PACKET_TYPE_NEW_PEER };

private:
	ENetAddress                         address;
	ENetHost*                           host;
	std::vector< ENetPeer* >			peers;
public:
	SpaceServer(std::string ip_address = "");

	void    addNewPeer(ENetPeer* peer);
	void    removePeer(ENetPeer* peer);

	void    start();

};