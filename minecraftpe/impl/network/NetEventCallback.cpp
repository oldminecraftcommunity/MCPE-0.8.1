#include <network/NetEventCallback.hpp>
#include <network/packet/RespawnPacket.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>



Player* NetEventCallback::findPlayer(Level* a2, const RakNet::RakNetGUID* a3) {
	for(int32_t i = 0; i < a2->playersMaybe.size(); ++i) {
		if(a2->playersMaybe[i]->rakNetGUID == *a3) {
			return a2->playersMaybe[i];
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

void NetEventCallback::levelGenerated(Level*) {
}
NetEventCallback::~NetEventCallback() {
}
void NetEventCallback::onConnect(const RakNet::RakNetGUID&) {
}
void NetEventCallback::onUnableToConnect(void) {
}
void NetEventCallback::onNewClient(const RakNet::RakNetGUID&) {
	return;
}
void NetEventCallback::onDisconnect(const RakNet::RakNetGUID&) {
}
bool_t NetEventCallback::allowIncomingPacketId(const RakNet::RakNetGUID&, int32_t) {
	return 0;
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct LoginPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ReadyPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct LoginStatusPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct SetTimePacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct MessagePacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct StartGamePacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct AddItemEntityPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct AddPaintingPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct TakeItemEntityPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct AddEntityPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct AddMobPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct AddPlayerPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct RemovePlayerPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct RemoveEntityPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct MoveEntityPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct RotateHeadPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct MovePlayerPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct PlaceBlockPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct RemoveBlockPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct UpdateBlockPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ExplodePacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct LevelEventPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct TileEventPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct EntityEventPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct RequestChunkPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ChunkDataPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct PlayerEquipmentPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct PlayerArmorEquipmentPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct SetEntityDataPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct SetEntityMotionPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct SetHealthPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct SetEntityLinkPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct SetSpawnPositionPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct InteractPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct UseItemPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct PlayerActionPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct HurtArmorPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct SendInventoryPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct DropItemPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ContainerOpenPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ContainerClosePacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ContainerAckPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ContainerSetDataPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ContainerSetSlotPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ContainerSetContentPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct ChatPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct AdventureSettingsPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct AnimatePacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct EntityDataPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct PlayerInputPacket*) {
}
void NetEventCallback::handle(const RakNet::RakNetGUID&, struct RespawnPacket*) {
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

