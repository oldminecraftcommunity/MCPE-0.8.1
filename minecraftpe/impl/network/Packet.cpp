#include <_types.h>
#include <network/Packet.hpp>
#include <ReliabilityLayer.h>

Packet::~Packet() {
}
Packet::Packet(){
	this->packetPriorityMaybe = PacketPriority::HIGH_PRIORITY; //1
	this->packetReliabilityMaybe = PacketReliability::RELIABLE; //2
}
