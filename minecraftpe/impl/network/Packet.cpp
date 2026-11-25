#include <_types.h>
#include <network/Packet.hpp>
#include <ReliabilityLayer.h>

Packet::Packet(){
	this->packetPriority = PacketPriority::HIGH_PRIORITY; //1
	this->packetReliability = PacketReliability::RELIABLE; //2
}
