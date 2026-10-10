#include <network/NetEventCallback.hpp>
#include <network/packet/RespawnPacket.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>



Player* NetEventCallback::findPlayer(Level* a2, const RakNet::RakNetGUID* a3) {
	for(int32_t i = 0; i < a2->players.size(); ++i) {
		if(a2->players[i]->rakNetGUID == *a3) {
			return a2->players[i];
		}
	}
	return 0;
}
Player* NetEventCallback::findPlayer(Level* a2, int32_t a3) {
	Entity* e = a2->getEntity(a3);
	if(e) {
		if(!e->isPlayer()) {
			e->getEntityTypeId();
			return 0;
		}
		return (Player*)e;
	}
	return 0;
}
Player* NetEventCallback::findPlayer(Level* a2, int32_t a3, const RakNet::RakNetGUID* a4) {
	Player* res;
	if(a3 == -1 || (res = this->findPlayer(a2, a3)) == 0) {
		if(a4) {
			return this->findPlayer(a2, a4);
		} else {
			return 0;
		}
	}
	return res;
}

void NetEventCallback::handle(Level* a2, const RakNet::RakNetGUID& a3, struct RespawnPacket* a4) {
	Entity* e = this->findPlayer(a2, a4->eid, 0);
	if(e) {
		e->moveTo(a4->x, a4->y, a4->z, e->yaw, e->pitch);
		e->reset();
		e->resetPos(1);
	}
}
void NetEventCallback::onPlayerVerified(const RestCallTagData& a2){
}
void NetEventCallback::onPlayerVerifiedFailed(const RestCallTagData&) {
}

