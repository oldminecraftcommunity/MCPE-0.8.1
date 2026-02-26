#pragma once
#include <network/NetEventCallback.hpp>
#include <level/LevelListener.hpp>
#include <RakPeer.h>
#include <memory>
#include <vector>

struct RestRequestJob;
struct Minecraft;
struct IRakNetInstance;
struct LoginPacket;
struct ServerPlayer;
struct Packet;
struct ServerSideNetworkHandler: NetEventCallback, LevelListener
{
	Minecraft* minecraft;
	Level* level;
	IRakNetInstance* raknetInstance;
	RakNet::RakPeer* rakPeer;
	std::vector<std::shared_ptr<RestRequestJob>> field_18;
	std::vector<Player*> players;
	int32_t field_30;
	bool_t field_34;
	int8_t field_35, field_36, field_37;

	ServerSideNetworkHandler(Minecraft*, IRakNetInstance*);
	void allowIncomingConnections(bool_t);
	ServerPlayer* createNewPlayer(const RakNet::RakNetGUID&, LoginPacket*);
	void displayGameMessage(const std::string&, const std::string&);
	Player* findPendingPlayer(const RakNet::RakNetGUID&);
	Player* getPlayer(const RakNet::RakNetGUID&);
	int32_t numberOfConnections();
	void onReady_ClientGeneration(const RakNet::RakNetGUID&);
	void onReady_RequestedChunks(const RakNet::RakNetGUID&);
	Player* popPendingPlayer(const RakNet::RakNetGUID&);
	void redistributePacket(Packet*, const RakNet::RakNetGUID&);
	void sendLoginMessageLocal(int32_t, const RakNet::RakNetGUID&, LoginPacket*);
	void sendLoginMessageMCO(int32_t, const RakNet::RakNetGUID&, LoginPacket*);
	void sendWorldSeed(Player*, const RakNet::RakNetGUID&);

	virtual void levelGenerated(Level*);
	virtual ~ServerSideNetworkHandler();
	virtual void onNewClient(const RakNet::RakNetGUID&);
	virtual void onDisconnect(const RakNet::RakNetGUID&);
	virtual bool_t allowIncomingPacketId(const RakNet::RakNetGUID&, int32_t);
	virtual void handle(const RakNet::RakNetGUID&, struct LoginPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ReadyPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct MessagePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct MovePlayerPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct RemoveBlockPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct EntityEventPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct RequestChunkPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct PlayerEquipmentPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct PlayerArmorEquipmentPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetHealthPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetEntityLinkPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct InteractPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct UseItemPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct PlayerActionPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct DropItemPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerClosePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerSetSlotPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerSetContentPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AnimatePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct EntityDataPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct PlayerInputPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct RespawnPacket*);
	virtual void onPlayerVerified(const RestCallTagData&);
	virtual void onPlayerVerifiedFailed(const RestCallTagData&);
	virtual void tileChanged(int32_t, int32_t, int32_t);
	virtual void tileBrightnessChanged(int32_t, int32_t, int32_t);
	virtual Packet* getAddPacketFromEntity(Entity*);
	virtual void entityAdded(Entity*);
	virtual void entityRemoved(Entity*);
	virtual void levelEvent(Player*, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void tileEvent(int32_t, int32_t, int32_t, int32_t, int32_t);
};
