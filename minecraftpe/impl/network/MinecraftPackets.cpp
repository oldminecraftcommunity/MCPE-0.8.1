#include <network/MinecraftPackets.hpp>
#include <network/packet/LoginPacket.hpp>
#include <network/packet/LoginStatusPacket.hpp>
#include <network/packet/ReadyPacket.hpp>
#include <network/packet/MessagePacket.hpp>
#include <network/packet/SetTimePacket.hpp>
#include <network/packet/StartGamePacket.hpp>
#include <network/packet/AddMobPacket.hpp>
#include <network/packet/AddPlayerPacket.hpp>
#include <network/packet/RemovePlayerPacket.hpp>
#include <network/packet/AddEntityPacket.hpp>
#include <network/packet/RemoveEntityPacket.hpp>
#include <network/packet/AddItemEntityPacket.hpp>
#include <network/packet/TakeItemEntityPacket.hpp>
#include <network/packet/MoveEntityPacket.hpp>
#include <network/packet/MoveEntityPacket_PosRot.hpp>
#include <network/packet/RotateHeadPacket.hpp>
#include <network/packet/MovePlayerPacket.hpp>
#include <network/packet/PlaceBlockPacket.hpp>
#include <network/packet/RemoveBlockPacket.hpp>
#include <network/packet/UpdateBlockPacket.hpp>
#include <network/packet/AddPaintingPacket.hpp>
#include <network/packet/ExplodePacket.hpp>
#include <network/packet/LevelEventPacket.hpp>
#include <network/packet/TileEventPacket.hpp>
#include <network/packet/EntityEventPacket.hpp>
#include <network/packet/RequestChunkPacket.hpp>
#include <network/packet/ChunkDataPacket.hpp>
#include <network/packet/PlayerEquipmentPacket.hpp>
#include <network/packet/PlayerArmorEquipmentPacket.hpp>
#include <network/packet/InteractPacket.hpp>
#include <network/packet/UseItemPacket.hpp>
#include <network/packet/PlayerActionPacket.hpp>
#include <network/packet/HurtArmorPacket.hpp>
#include <network/packet/SetEntityDataPacket.hpp>
#include <network/packet/SetEntityMotionPacket.hpp>
#include <network/packet/SetEntityLinkPacket.hpp>
#include <network/packet/SetHealthPacket.hpp>
#include <network/packet/SetSpawnPositionPacket.hpp>
#include <network/packet/AnimatePacket.hpp>
#include <network/packet/RespawnPacket.hpp>
#include <network/packet/SendInventoryPacket.hpp>
#include <network/packet/DropItemPacket.hpp>
#include <network/packet/ContainerOpenPacket.hpp>
#include <network/packet/ContainerClosePacket.hpp>
#include <network/packet/ContainerSetSlotPacket.hpp>
#include <network/packet/ContainerSetDataPacket.hpp>
#include <network/packet/ContainerSetContentPacket.hpp>
#include <network/packet/ContainerAckPacket.hpp>
#include <network/packet/ChatPacket.hpp>
#include <network/packet/AdventureSettingsPacket.hpp>
#include <network/packet/EntityDataPacket.hpp>
#include <network/packet/PlayerInputPacket.hpp>

Packet* MinecraftPackets::createPacket(int32_t pid) {
	switch(pid) {
		case PID_LOGIN_PACKET:
			return new LoginPacket();
		case PID_LOGIN_STATUS_PACKET:
			return new LoginStatusPacket();
		case PID_READY_PACKET:
			return new ReadyPacket(0);
		case PID_MESSAGE_PACKET:
			return new MessagePacket();
		case PID_SET_TIME_PACKET:
			return new SetTimePacket();
		case PID_START_GAME_PACKET:
			return new StartGamePacket();
		case PID_ADD_MOB_PACKET:
			return new AddMobPacket();
		case PID_ADD_PLAYER_PACKET:
			return new AddPlayerPacket();
		case PID_REMOVE_PLAYER_PACKET:
			return new RemovePlayerPacket();
		case PID_ADD_ENTITY_PACKET:
			return new AddEntityPacket();
		case PID_REMOVE_ENTITY_PACKET:
			return new RemoveEntityPacket();
		case PID_ADD_ITEM_ENTITY_PACKET:
			return new AddItemEntityPacket();
		case PID_TAKE_ITEM_ENTITY_PACKET:
			return new TakeItemEntityPacket();
		case PID_MOVE_ENTITY_PACKET:
			return new MoveEntityPacket(0);
		case PID_MOVE_ENTITY_POSROT_PACKET:
			return new MoveEntityPacket_PosRot();
		case PID_ROTATE_HEAD_PACKET:
			return new RotateHeadPacket();
		case PID_MOVE_PLAYER_PACKET:
			return new MovePlayerPacket();
		case PID_PLACE_BLOCK_PACKET:
			return new PlaceBlockPacket();
		case PID_REMOVE_BLOCK_PACKET:
			return new RemoveBlockPacket();
		case PID_UPDATE_BLOCK_PACKET:
			return new UpdateBlockPacket();
		case PID_ADD_PAINTING_PACKET:
			return new AddPaintingPacket();
		case PID_EXPLODE_PACKET:
			return new ExplodePacket();
		case PID_LEVEL_EVENT_PACKET:
			return new LevelEventPacket();
		case PID_TILE_EVENT_PACKET:
			return new TileEventPacket();
		case PID_ENTITY_EVENT_PACKET:
			return new EntityEventPacket();
		case PID_REQUEST_CHUNK_PACKET:
			return new RequestChunkPacket();
		case PID_CHUNK_DATA_PACKET:
			return new ChunkDataPacket();
		case PID_PLAYER_EQUIPMENT_PACKET:
			return new PlayerEquipmentPacket();
		case PID_PLAYER_ARMOR_EQUIPMENT_PACKET:
			return new PlayerArmorEquipmentPacket();
		case PID_INTERACT_PACKET:
			return new InteractPacket();
		case PID_USE_ITEM_PACKET:
			return new UseItemPacket();
		case PID_PLAYER_ACTION_PACKET:
			return new PlayerActionPacket();
		case PID_HURT_ARMOR_PACKET:
			return new HurtArmorPacket();
		case PID_SET_ENTITY_DATA_PACKET:
			return new SetEntityDataPacket();
		case PID_SET_ENTITY_MOTION_PACKET:
			return new SetEntityMotionPacket();
		case PID_SET_ENTITY_LINK_PACKET:
			return new SetEntityLinkPacket();
		case PID_SET_HEALTH_PACKET:
			return new SetHealthPacket();
		case PID_SET_SPAWN_POSITION_PACKET:
			return new SetSpawnPositionPacket();
		case PID_ANIMATE_PACKET:
			return new AnimatePacket();
		case PID_RESPAWN_PACKET:
			return new RespawnPacket();
		case PID_SEND_INVENTORY_PACKET:
			return new SendInventoryPacket();
		case PID_DROP_ITEM_PACKET:
			return new DropItemPacket();
		case PID_CONTAINER_OPEN_PACKET:
			return new ContainerOpenPacket();
		case PID_CONTAINER_CLOSE_PACKET:
			return new ContainerClosePacket();
		case PID_CONTAINER_SET_SLOT_PACKET:
			return new ContainerSetSlotPacket();
		case PID_CONTAINER_SET_DATA_PACKET:
			return new ContainerSetDataPacket();
		case PID_CONTAINER_SET_CONTENT_PACKET:
			return new ContainerSetContentPacket();
		case PID_CONTAINER_ACK_PACKET:
			return new ContainerAckPacket();
		case PID_CHAT_PACKET:
			return new ChatPacket();
		case PID_ADVENTURE_SETTINGS_PACKET:
			return new AdventureSettingsPacket();
		case PID_ENTITY_DATA_PACKET:
			return new EntityDataPacket();
		case PID_PLAYER_INPUT_PACKET:
			return new PlayerInputPacket();
		default:
			return 0;
	}
}
