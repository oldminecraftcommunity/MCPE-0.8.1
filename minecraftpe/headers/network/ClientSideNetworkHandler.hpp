#pragma once
#include <network/NetEventCallback.hpp>
#include <RakPeer.h>
#include <util/IntPair.hpp>
#include <vector>

struct MultiPlayerLevel;
struct Minecraft;
struct IRakNetInstance;
struct SBufferedBlockUpdate;
struct ClientSideNetworkHandler: NetEventCallback
{
	Minecraft* minecraft;
	MultiPlayerLevel* level;
	IRakNetInstance* field_C;
	RakNet::RakPeer* field_10;
	int8_t field_14, field_15, field_16, field_17;
	RakNet::RakNetGUID field_18;
	int8_t field_24, field_25, field_26, field_27;
	std::vector<SBufferedBlockUpdate> field_28;
	int32_t loadedChunks;
	int32_t field_38;
	int32_t requestedChunksMaybe;
	IntPair field_40[256];
	bool_t chunksLoadedMaybe[256];
	bool_t _isRealmsServer;
	int8_t field_941, field_942, field_943, field_944, field_945, field_946, field_947;

	ClientSideNetworkHandler(Minecraft*, IRakNetInstance*);
	bool_t areAllChunksLoaded();
	void arrangeRequestChunkOrder();
	void clearChunksLoaded();
	bool_t isChunkLoaded(int32_t, int32_t);
	bool_t isRealmsServer();
	void requestNextChunk();
	void setRealmsServer();

	virtual void levelGenerated(Level*);
	virtual ~ClientSideNetworkHandler();
	virtual void onConnect(const RakNet::RakNetGUID&);
	virtual void onUnableToConnect();
	virtual void onDisconnect(const RakNet::RakNetGUID&);
	virtual void handle(const RakNet::RakNetGUID&, struct LoginStatusPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetTimePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct MessagePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct StartGamePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AddItemEntityPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AddPaintingPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct TakeItemEntityPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AddEntityPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AddMobPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AddPlayerPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct RemovePlayerPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct RemoveEntityPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct MoveEntityPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct RotateHeadPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct MovePlayerPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct UpdateBlockPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ExplodePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct LevelEventPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct TileEventPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct EntityEventPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ChunkDataPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct PlayerEquipmentPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct PlayerArmorEquipmentPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetEntityDataPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetEntityMotionPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetHealthPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetEntityLinkPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct SetSpawnPositionPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct InteractPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct HurtArmorPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerOpenPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerClosePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerSetDataPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerSetSlotPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ContainerSetContentPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct ChatPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AdventureSettingsPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct AnimatePacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct EntityDataPacket*);
	virtual void handle(const RakNet::RakNetGUID&, struct RespawnPacket*);

};
