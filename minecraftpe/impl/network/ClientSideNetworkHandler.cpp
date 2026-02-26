#include <network/ClientSideNetworkHandler.hpp>
#include <Minecraft.hpp>
#include <entity/Arrow.hpp>
#include <entity/EntityFactory.hpp>
#include <entity/FallingTile.hpp>
#include <entity/ItemEntity.hpp>
#include <entity/LocalPlayer.hpp>
#include <entity/MobFactory.hpp>
#include <entity/Painting.hpp>
#include <entity/RemotePlayer.hpp>
#include <entity/player/User.hpp>
#include <entity/player/gamemode/GameMode.hpp>
#include <gui/screens/DisconnectionScreen.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <level/Explosion.hpp>
#include <level/LevelSettings.hpp>
#include <level/MultiPlayerLevel.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/dimension/Dimension.hpp>
#include <level/gen/ChunkSource.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <math/Mth.hpp>
#include <network/IRakNetInstance.hpp>
#include <network/RakNetInstance.hpp>
#include <network/SBufferedBlockUpdate.hpp>
#include <network/mco/MojangConnector.hpp>
#include <network/packet/AddEntityPacket.hpp>
#include <network/packet/AddItemEntityPacket.hpp>
#include <network/packet/AddMobPacket.hpp>
#include <network/packet/AddPaintingPacket.hpp>
#include <network/packet/AddPlayerPacket.hpp>
#include <network/packet/AdventureSettingsPacket.hpp>
#include <network/packet/AnimatePacket.hpp>
#include <network/packet/ChatPacket.hpp>
#include <network/packet/ChunkDataPacket.hpp>
#include <network/packet/ContainerOpenPacket.hpp>
#include <network/packet/ContainerSetContentPacket.hpp>
#include <network/packet/ContainerSetDataPacket.hpp>
#include <network/packet/ContainerSetSlotPacket.hpp>
#include <network/packet/DropItemPacket.hpp>
#include <network/packet/EntityDataPacket.hpp>
#include <network/packet/EntityEventPacket.hpp>
#include <network/packet/ExplodePacket.hpp>
#include <network/packet/HurtArmorPacket.hpp>
#include <network/packet/InteractPacket.hpp>
#include <network/packet/LevelEventPacket.hpp>
#include <network/packet/LoginPacket.hpp>
#include <network/packet/LoginStatusPacket.hpp>
#include <network/packet/MessagePacket.hpp>
#include <network/packet/MoveEntityPacket.hpp>
#include <network/packet/MovePlayerPacket.hpp>
#include <network/packet/PlayerArmorEquipmentPacket.hpp>
#include <network/packet/PlayerEquipmentPacket.hpp>
#include <network/packet/ReadyPacket.hpp>
#include <network/packet/RemoveEntityPacket.hpp>
#include <network/packet/RemovePlayerPacket.hpp>
#include <network/packet/RequestChunkPacket.hpp>
#include <network/packet/RespawnPacket.hpp>
#include <network/packet/RotateHeadPacket.hpp>
#include <network/packet/SetEntityDataPacket.hpp>
#include <network/packet/SetEntityLinkPacket.hpp>
#include <network/packet/SetEntityMotionPacket.hpp>
#include <network/packet/SetHealthPacket.hpp>
#include <network/packet/SetSpawnPositionPacket.hpp>
#include <network/packet/SetTimePacket.hpp>
#include <network/packet/StartGamePacket.hpp>
#include <network/packet/TakeItemEntityPacket.hpp>
#include <network/packet/TileEventPacket.hpp>
#include <network/packet/UpdateBlockPacket.hpp>
#include <stdlib.h>
#include <tile/Tile.hpp>
#include <tile/entity/FurnaceTileEntity.hpp>
#include <tile/entity/TileEntity.hpp>
#include <util/_ChunkSorter.hpp>

ClientSideNetworkHandler::ClientSideNetworkHandler(Minecraft* a2, IRakNetInstance* a3) {
	this->minecraft = a2;
	this->level = 0;
	this->field_C = a3;
	this->loadedChunks = 0;
	this->field_38 = 0;
	this->requestedChunksMaybe = 0;
	this->_isRealmsServer = 0;
	this->field_10 = a3->getPeer();
}
bool_t ClientSideNetworkHandler::areAllChunksLoaded() {
	return this->loadedChunks > 255;
}

static _ChunkSorter _ihatecppstdevenmore;
static int32_t _ihatecppstd(const void* a, const void* b) {
	const IntPair* aa = (const IntPair*)a;
	const IntPair* bb = (const IntPair*)b;
	bool_t res = _ihatecppstdevenmore(*aa, *bb);
	if(aa->x == bb->x && aa->y == bb->y) return 0;
	if(res) return 1;
	return -1;
}

void ClientSideNetworkHandler::arrangeRequestChunkOrder() {
	this->clearChunksLoaded();
	int cx, cz;
	if(this->minecraft && this->minecraft->player != 0) {
		cx = Mth::floor(this->minecraft->player->posX * 0.0625) /*inlined*/;
		cz = Mth::floor(this->minecraft->player->posZ * 0.0625) /*inlined*/;
	} else {
		cz = 8;
		cx = 8;
	}

	//TODO uses std::sort(or something else) but it doesnt want to compile (no match for 'operator+'(operand type is 'IntPair'))

	_ihatecppstdevenmore = _ChunkSorter{cx, cz};
	qsort(this->field_40, 256, sizeof(*this->field_40), _ihatecppstd);
}
void ClientSideNetworkHandler::clearChunksLoaded() {
	int32_t v1;					  // r3
	ClientSideNetworkHandler* v2; // r2

	v1 = 0;
	v2 = this;
	for(v1 = 0; v1 != 256; ++v1) {
		this->field_40[v1].x = v1 >> 4;
		this->field_40[v1].y = v1 & 0xf;
		this->chunksLoadedMaybe[v1] = 0;
	}
}
bool_t ClientSideNetworkHandler::isChunkLoaded(int32_t a2, int32_t a3) {
	return (uint32_t)a2 > 0xF || a3 < 0 || a3 > 15 || this->chunksLoadedMaybe[16 * a2 + a3];
}
bool_t ClientSideNetworkHandler::isRealmsServer() {
	return this->_isRealmsServer;
}
void ClientSideNetworkHandler::requestNextChunk() {
	int32_t requestedChunksMaybe; // r3
	IntPair* v3;				  // r2
	int32_t x;					  // r7
	int32_t y;					  // r6
	IRakNetInstance* v6;		  // r0

	requestedChunksMaybe = this->requestedChunksMaybe;
	if(requestedChunksMaybe <= 255) {
		v3 = &this->field_40[requestedChunksMaybe];
		x = v3->x;
		y = v3->y;
		RequestChunkPacket v7(x, y);
		this->field_C->send(v7);
		++this->requestedChunksMaybe;
		++this->loadedChunks;
	}
}
void ClientSideNetworkHandler::setRealmsServer() {
	this->_isRealmsServer = 1;
}

void ClientSideNetworkHandler::levelGenerated(Level* a2) {
	int v4;					// r1
	LevelStorageSource* ls; // r7
	LevelData* LevelData;	// r0

	this->level = (MultiPlayerLevel*)a2;
	v4 = this->field_38;
	if(v4) {
		a2->setTime(v4);
	}
	if(this->_isRealmsServer) {
		if(this->minecraft->getLevelSource()) {
			this->minecraft->getLevelSource()->storeToCache(a2->getLevelData(), LevelStorageSource::TempLevelId);
		}
	}
	ReadyPacket v9(1);
	this->field_C->send(v9);
	this->arrangeRequestChunkOrder();
	this->requestNextChunk();
}
ClientSideNetworkHandler::~ClientSideNetworkHandler() {
}
void ClientSideNetworkHandler::onConnect(const RakNet::RakNetGUID& a2) {
	a2.ToString();
	this->field_10->GetMyGUID().ToString();
	this->field_18 = a2;
	this->clearChunksLoaded();
	LoginPacket v10(this->minecraft->user->username, this->minecraft->field_C5C, *this->minecraft->mojangConnector->getJoinMCOPayload());
	this->field_C->send(v10);
}
void ClientSideNetworkHandler::onUnableToConnect() {
	this->minecraft->setScreen(new DisconnectionScreen("Unable to connect to world."));
}

void ClientSideNetworkHandler::onDisconnect(const RakNet::RakNetGUID& a2) {
	if(this->level) {
		this->level->isClientMaybe = 0;
		int v5 = this->level->playersMaybe.size() - 1;
		while(v5 >= 0) {
			Player* v7 = this->level->playersMaybe[v5];
			if(v7 != this->minecraft->player) {
				v7->field_108 = 1;
				this->level->removeEntity(v7);
			}
			--v5;
		}
	}

	if(this->level) {
		this->minecraft->setScreen(new DisconnectionScreen("You have been disconnected"));
		this->minecraft->setLeaveGame();
	} else {
		this->minecraft->gui.addMessage("error", "Disconnected from server", 2400);
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct LoginStatusPacket* a3) {
	if(a3->status) {
		if(a3->status == 1) {
			this->minecraft->setScreen(new DisconnectionScreen("Could not connect: Outdated client!"));
		}
		if(a3->status == 2) {
			this->minecraft->setScreen(new DisconnectionScreen("Could not connect: Outdated server!"));
		}

	} else {
		this->field_C->setIsLoggedIn(1);
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct SetTimePacket* a3) {
	if(this->level) {
		this->level->setTime(a3->timeValue);
		this->level->setDayCycleActive(a3->stopTime);
	} else {
		this->field_38 = a3->timeValue;
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct MessagePacket* a3) {
	this->minecraft->gui.addMessage(a3->source.C_String(), a3->message.C_String(), 200);
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct StartGamePacket* pk) {
	LevelStorageSource* levelSource; // r4
	LevelStorage* v6;				 // r4
	MultiPlayerLevel* v8;			 // r8
	LocalPlayer* player;			 // r7
	Minecraft* minecraft;			 // r4

	levelSource = this->minecraft->getLevelSource();
	levelSource->deleteLevel(LevelStorageSource::TempLevelId);
	if(this->_isRealmsServer) {
		LevelData v14;
		v14.setGeneratorVersion(pk->genver);
		v14.setSeed(pk->seed);
		levelSource->loadFromCache(&v14, LevelStorageSource::TempLevelId);
	}
	v6 = levelSource->selectLevel(LevelStorageSource::TempLevelId, 1);
	v8 = new MultiPlayerLevel(v6, "temp", LevelSettings{pk->seed, pk->gamemode != 0}, 1, pk->genver, 0);
	player = new LocalPlayer(this->minecraft, (Level*)v8, this->minecraft->user, v8->dimensionPtr->id, pk->gamemode == 1);

	player->rakNetGUID = this->field_10->GetMyGUID();
	player->entityId = pk->eid;
	player->inventoryMenu.setListener(player);
	player->moveTo(pk->x, pk->y, pk->z, player->yaw, player->pitch);
	minecraft = this->minecraft;
	minecraft->setLevel(v8, "ClientSideNetworkHandler -> setLevel", player);
	this->minecraft->setIsCreativeMode(pk->gamemode == 1);
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct AddItemEntityPacket* a3) {
	if(this->level) {
		ItemEntity* e = new ItemEntity(this->level, a3->x, a3->y, a3->z, ItemInstance(a3->itemID, a3->count, a3->itemMeta));
		e->motionX = (float)a3->motionX * 0.0078125;
		e->motionY = (float)a3->motionY * 0.0078125;
		e->motionZ = (float)a3->motionZ * 0.0078125;
		this->level->putEntity(a3->eid, e);
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct AddPaintingPacket* a3) {
	if(this->level) {
		this->level->putEntity(a3->eid, new Painting(this->level, a3->x, a3->y, a3->z, a3->direction, a3->title));
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct TakeItemEntityPacket* pk) {
	if(this->level) {
		Entity* e = this->level->getEntity(pk->target);
		if(e) {
			ItemInstance v15;
			if(e->isItemEntity()) {
				v15 = ((ItemEntity*)e)->itemInstance;
			} else if(e->getEntityTypeId() == 80) {
				v15 = ItemInstance(Item::arrow);
			}

			if(!v15.isNull()) {
				if(this->minecraft->player->entityId == pk->eid && !this->minecraft->player->inventory->add(&v15)) {
					DropItemPacket a3(pk->eid, 0, v15);
					this->minecraft->rakNetInstance->send(a3);
				}
				this->level->playSound(e, "random.pop", 0.2, 2.0);
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct AddEntityPacket* pk) {
	if(this->level) {
		Entity* e = EntityFactory::CreateEntity(pk->type, this->level);
		if(e) {
			e->entityId = pk->eid;
			e->setPos(pk->x, pk->y, pk->z);
			if(pk->type == 66) {
				int32_t v9 = -pk->did;
				((FallingTile*)e)->blockID = (uint8_t)v9;
				((FallingTile*)e)->blockMetaMaybe = v9 >> 16;
			} else if(pk->type != 80) {
LABEL_10:
				if(pk->did > 0) {
					e->lerpMotion(pk->motionX, pk->motionY, pk->motionZ);
				}
				this->level->putEntity(pk->eid, e);
			}
			//XXX ???
			Entity* ee = this->level->getEntity(pk->did);
			if(ee && ee->isMob()) {
				((Arrow*)e)->shooterEID = ee->entityId;
			}
			goto LABEL_10;
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct AddMobPacket* a3) {
	Level* level; // r1
	int32_t type; // r0
	Mob* mob;	  // r0
	int32_t v11;  // r2

	level = this->level;
	if(level) {
		type = a3->type;
		if(type) {
			mob = MobFactory::CreateMob(type, level);
			if(mob) {
				mob->entityId = a3->eid;
				mob->moveTo(a3->x, a3->y, a3->z, a3->pitch, a3->yaw);
				mob->field_130 = a3->pitch;
				mob->headYaw = a3->pitch;
				mob->getEntityData()->assignValues(&a3->readData);
				this->level->addEntity(mob);
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct AddPlayerPacket* pk) {
	if(this->level) {
		Player* p = new RemotePlayer(this->level, this->minecraft->isCreativeMode());
		this->minecraft->gameMode->initAbilities(p->abilities);
		p->entityId = pk->eid;
		this->level->addEntity(p);
		p->moveTo(pk->x, pk->y, pk->z, pk->yaw, pk->pitch);
		p->username = pk->username.C_String();
		p->rakNetGUID = pk->clientId;
		p->getEntityData()->assignValues(&pk->field_40);
		if(pk->itemId) {
			ItemInstance v10(pk->itemId, 1, pk->itemAuxValue);
			p->inventory->replaceSlot(9, &v10);
		} else {
			p->inventory->clearSlot(9);
		}
		p->inventory->moveToSelectedSlot(9);
		this->minecraft->gui.addMessage("server", std::string(pk->username.C_String()) + " joined the game", 200);
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct RemovePlayerPacket* a3) {
	if(this->level) {
		if(!(a2 == this->minecraft->player->rakNetGUID)) {
			Player* p = this->findPlayer(this->level, a3->eid, &a3->clientId);
			if(p) {
				p->field_108 = 1;
				this->level->removeEntity(p);
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct RemoveEntityPacket* a3) {
	if(this->level) {
		Entity* e = this->level->getEntity(a3->eid);
		if(e) {
			e->isPlayer();
			this->level->removeEntity(e);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct MoveEntityPacket* a3) {
	Entity* ent; // r0
	float pitch; // r3
	float yaw;	 // r2

	if(this->level) {
		ent = this->level->getEntity(a3->eid);
		if(ent) {
			if(a3->hasrot) {
				pitch = a3->pitch;
				yaw = a3->yaw;
			} else {
				pitch = ent->pitch;
				yaw = ent->yaw;
			}
			ent->lerpTo(a3->posX, a3->posY, a3->posZ, yaw, pitch, 3);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct RotateHeadPacket* a3) {
	if(this->level) {
		Mob* m = this->level->getMob(a3->eid);
		if(m) {
			m->setYHeadRot((float)((float)a3->headYaw * 360.0) * 0.0039062);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct MovePlayerPacket* a3) {
	if(this->level) {
		Mob* mob = this->level->getMob(a3->eid);
		if(mob) {
			mob->lerpTo(a3->x, a3->y, a3->z, a3->yaw, a3->pitch, 3);
			mob->headYaw = a3->bodyYaw;
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct UpdateBlockPacket* a3) {
	if(this->level) {
		int x = a3->x;
		int z = a3->z;
		if(this->isChunkLoaded(x >> 4, z >> 4)) {
			int y = (uint8_t)a3->y;
			this->level->setTileAndData(x, y, z, Tile::transformToValidBlockId(a3->id, x, y, z), a3->meta, 3);
		} else {
			this->field_28.emplace_back(SBufferedBlockUpdate{x, z, a3->y, a3->id, a3->meta, 1});
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct ExplodePacket* a3) {
	if(this->level) {
		Explosion v5(this->level, 0, a3->x, a3->y, a3->z, a3->radius);
		v5.field_10.insert(a3->positions.begin(), a3->positions.end());
		v5.finalizeExplosion();
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct LevelEventPacket* a3) {
	if(this->level) {
		if(a3->evid == 9800) {
			this->minecraft->player->setAllPlayersSleeping();
		} else {
			this->minecraft->level->levelEvent(0, a3->evid, a3->x, a3->y, a3->z, a3->data);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct TileEventPacket* a3) {
	if(this->level) {
		this->minecraft->level->tileEvent(a3->x, a3->y, a3->z, a3->case1, a3->case2);
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct EntityEventPacket* a3) {
	if(this->level) {
		Entity* e = this->level->getEntity(a3->eid);
		if(e) {
			e->handleEntityEvent(a3->event);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct ChunkDataPacket* a3) {
	if(this->level) {
		LevelChunk* v7 = this->level->getChunkSource()->create(a3->xPos, a3->zPos);
		if(v7) {
			if(!v7->isEmpty()) {
				int v29 = 16;
				int v30 = 0;
				int v39 = 0;
				int v31 = 0;
				int v44 = 16 * a3->xPos;
				int v38 = 128;
				int v37 = 0;
				int v36 = 0;
				int v45 = 16 * a3->zPos;
				int v35 = 16;
				do {
					int v9 = 0;
					unsigned char v46 = 0;
					a3->stream.Read<unsigned char>(v46);
					if(v46) {
						int v10 = v30 >> 4;
						int v34 = v30 & 0xF;
						do {
							if((((int)v46 >> v9) & 1) != 0) {
								int v11 = 16 * v9;
								int v32 = v10;
								char dest[0x10];
								a3->stream.Read(dest, 0x10u);
								char v48[0x8];
								int v12 = 0;
								a3->stream.Read(v48, 8u);
								v10 = v32;
								int x = v44 + v34;
								int z = v45 + v32;
								do {
									int v13 = v12 + v11;
									int v14 = (uint8_t)dest[v12++];
									int v33 = v10;
									int v41 = v13;
									int valid = Tile::transformToValidBlockId(v14, x, v13, z);
									this->level->setTileNoUpdate(x, v41, z, valid);
									v10 = v33;
								} while(v12 != 16);

								for(int i = 0; i < 8; ++i) { //TODO inlined into 2int assign?
									v7->tileMeta.data[((v11 + (((v30 & 0xF) << 11) | (v30 >> 4 << 7))) >> 1) + i] = v48[i];
								}
							}
							int v18 = v38;
							int v19 = 16 << v9;
							int v20 = (16 << v9) + 14;
							if(v38 >= 16 << v9) {
								v18 = 16 << v9;
							}
							++v9;
							if(v20 >= v39) {
								v39 = v19 + 15;
							}
							v38 = v18;
						} while(v9 != 8);
						int v21 = v35;
						v31 = 1;
						if(v29 >= v10) {
							v29 = v10;
						}
						int v22 = v36;
						if(v35 >= v34) {
							v21 = v30 & 0xF;
						}
						if(v36 < v34) {
							v22 = v30 & 0xF;
						}
						v35 = v21;
						v36 = v22;
						if(v10 > v37) {
							v37 = v10;
						}
					}
					++v30;
				} while(v30 != 256);

				if(v31) {
					this->level->setTilesDirty(16 * a3->xPos + v35, v38, 16 * a3->zPos + v29, 16 * a3->xPos + v36, v39, 16 * a3->zPos + v37);
				}

				v7->unsaved = 0;
				this->chunksLoadedMaybe[16 * a3->xPos + a3->zPos] = 1;
				if(this->areAllChunksLoaded()) {
					ReadyPacket v47(2);
					this->field_C->send(v47);
					for(uint32_t v23 = 0; v23 < this->field_28.size(); ++v23) {
						SBufferedBlockUpdate* v25 = &this->field_28[v23];
						int v26 = Tile::transformToValidBlockId(v25->id, v25->x, v25->y, v25->z);
						if(v25->field_B) {
							this->level->setTileAndData(v25->x, v25->y, v25->z, v26, v25->meta, 3);
						} else {
							this->level->setTile(v25->x, v25->y, v25->z, v26, 3);
						}
					}
					this->field_28.clear();
				} else {
					this->requestNextChunk();
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct PlayerEquipmentPacket* a3) {
	if(this->level) {
		Entity* ent = this->level->getEntity(a3->eid);
		if(ent) {
			if(ent->isPlayer()) {
				Player* v7 = (Player*)ent;
				if(v7->rakNetGUID == this->field_10->GetMyGUID()) {
					puts("Attempted to modify local player's inventory");
				} else {
					if(a3->itemID) {
						ItemInstance v8(a3->itemID, 63, a3->itemMeta);
						v7->inventory->replaceSlot(9, &v8);
					} else {
						v7->inventory->clearSlot(9);
					}
					v7->inventory->moveToSelectedSlot(9);
				}
			}
		}
	}
}

static void _D663005E(Player* a1, int32_t id, int32_t slot) {
	if(id >= 0) {
		ItemInstance a3(id + 256, 1, 0);
		a1->setArmor(slot, &a3);
	} else {
		a1->setArmor(slot, 0);
	}
}

void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct PlayerArmorEquipmentPacket* a3) {
	if(this->level) {
		Entity* ent = level->getEntity(a3->eid);
		if(ent) {
			if(ent->isPlayer()) {
				Player* v7 = (Player*)ent;
				;
				if(v7->rakNetGUID == this->field_10->GetMyGUID()) {
					puts("Attempted to modify local player's armor visually");
				} else {
					_D663005E(v7, a3->headId, 0);
					_D663005E(v7, a3->chestId, 1u);
					_D663005E(v7, a3->legsId, 2u);
					_D663005E(v7, a3->bootsId, 3u);
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct SetEntityDataPacket* pk) {
	if(this->level) {
		Entity* e = this->level->getEntity(pk->entityId);
		if(e) {
			SynchedEntityData* v6 = e->getEntityData();
			if(v6) {
				v6->assignValues(&pk->data);
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct SetEntityMotionPacket* pk) {
	if(this->level) {
		Entity* e = this->level->getEntity(pk->eid);
		if(e) {
			e->lerpMotion(pk->speedX, pk->speedY, pk->speedZ);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct SetHealthPacket* pk) {
	if(this->level) {
		LocalPlayer* e = this->minecraft->player;
		if(e) {
			e->hurtTo(pk->health);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct SetEntityLinkPacket* pk) {
	if(this->level) {
		Entity* riderEntity = this->level->getEntity(pk->rider);
		Entity* ridingEntity = this->level->getEntity(pk->riding);
		if(!pk->typeMaybe) {
			Entity* rider = (Entity*)this->minecraft->player;
			if(pk->rider != rider->entityId) {
				if(!riderEntity) {
					return;
				}
				rider = riderEntity;
			}
			rider->ride(ridingEntity);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct SetSpawnPositionPacket* pk) {
	if(this->level) {
		if(this->minecraft) {
			if(this->minecraft->player) {
				if(this->level->inRange(pk->x, pk->y, pk->z)) {
					this->minecraft->player->setRespawnPosition({pk->x, pk->y, pk->z});
					this->level->getLevelData()->setSpawn(pk->x, pk->y, pk->z);
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct InteractPacket* a3) {
	Level* level; // r0
	Entity* ent;  // r4
	Entity* v7;	  // r0
	Entity* v8;	  // r7

	level = this->level;
	if(level) {
		ent = level->getEntity(a3->eid);
		v7 = this->level->getEntity(a3->type);
		v8 = v7;
		if(ent) {
			if(v7) {
				if(ent->isPlayer()) {
					if(a3->action == 2) {
						this->minecraft->gameMode->attack((Player*)ent, v8);
					}
					if(a3->action == 1) {
						this->minecraft->gameMode->interact((Player*)ent, v8);
					}
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct HurtArmorPacket* a3) {
	if(this->level) {
		if(this->minecraft->player) {
			this->minecraft->player->hurtArmor(a3->health);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ContainerOpenPacket* a3) {
	if(this->level) {
		if(this->minecraft) {
			if(this->minecraft->player) {
				if(a3->containerId == 2) {
					FurnaceTileEntity* v6 = new FurnaceTileEntity();
					v6->field_34 = 1;
					//XXX why v6 is not freed???
					this->minecraft->player->openFurnace(v6);
					if(this->minecraft->player->currentContainer) {
						this->minecraft->player->currentContainer->field_0 = (uint8_t)a3->field_C;
					}
				}
				if(a3->containerId == 0) {
					TileEntity* tile = this->level->getTileEntity(a3->x, a3->y, a3->z);
					if(tile) {
						if(TileEntity::isType(tile, 2)) {
							this->minecraft->player->openContainer((ChestTileEntity*)tile);
							if(this->minecraft->player->currentContainer) {
								this->minecraft->player->currentContainer->field_0 = (uint8_t)a3->field_C;
							}
						}
					}
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ContainerClosePacket* a3) {
	if(this->minecraft) {
		if(this->minecraft->player) {
			if(this->minecraft->player->currentContainer) {
				this->minecraft->player->closeContainer();
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ContainerSetDataPacket* a3) {
	LocalPlayer* player;				 // r3
	BaseContainerMenu* currentContainer; // r0

	player = this->minecraft->player;
	if(player) {
		currentContainer = player->currentContainer;
		if(currentContainer) {
			if(currentContainer->field_0 == (uint8_t)a3->field_10) {
				currentContainer->setData(a3->field_C, a3->field_E);
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct ContainerSetSlotPacket* a3) {
	if(this->minecraft->player) {
		if(this->minecraft->player->currentContainer) {
			if(this->minecraft->player->currentContainer->field_0 == (uint8_t)a3->field_D) {
				this->minecraft->player->currentContainer->setSlot(a3->field_E, &a3->field_10);
				if(this->minecraft->currentScreen) {
					this->minecraft->currentScreen->onInternetUpdate();
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ContainerSetContentPacket* a3) {
	if(this->minecraft) {
		if(this->minecraft->player) {
			if(a3->field_C) {
				int v7 = (uint8_t)a3->field_C;
				if(v7 == 120) {
					for(int i = 0; i < (a3->field_10.size() >= 4 ? 4 : a3->field_10.size()); ++i) {
						this->minecraft->player->setArmor(i, &a3->field_10[i]);
					}
				} else {
					if(this->minecraft->player->currentContainer) {
						if(this->minecraft->player->currentContainer->field_0 == v7) {
							for(int j = 0; j < a3->field_10.size(); ++a3) {
								this->minecraft->player->currentContainer->setSlot(j, &a3->field_10[j]);
							}
						}
					}
				}
			} else {
				this->minecraft->player->inventory->clearInventory(-1);
				int v9 = this->minecraft->player->inventory->getContainerSize();
				int v10 = a3->field_10.size();
				int v11 = v9 - 9;
				if(v11 < v10) v10 = v11;
				for(int v7 = 0; v7 != v10; ++v7) {
					if(!a3->field_10[v7].isNull()) {
						this->minecraft->player->inventoryMenu.setSlot(v7, &a3->field_10[v7]);
					}
				}

				for(int k = 0; k < a3->field_1C.size() && k < this->minecraft->player->inventory->getLinkedSlotsCount(); ++k) {
					this->minecraft->player->inventory->linkedSlots[k].field_0 = a3->field_1C[k];
					ItemInstance* v25 = this->minecraft->player->inventory->getItem(a3->field_1C[k]);
					this->minecraft->player->inventory->setItem(k, v25);
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ChatPacket* a3) {
	this->minecraft->gui.displayClientMessage(a3->message);
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct AdventureSettingsPacket* a3) {
	if(this->level) {
		this->level->adventureSettings.allowInteract = a3->flags & 1;
		this->level->adventureSettings.enablePVPMaybe = (a3->flags & 2) != 0;
		this->level->adventureSettings.enablePVEMaybe = (a3->flags & 4) != 0;
		this->level->adventureSettings.field_3 = (a3->flags & 8) != 0;
		this->level->adventureSettings.daylightCycle = ((a3->flags ^ 0x10) & 0x10) != 0;
		this->level->adventureSettings.field_5 = (a3->flags & 0x20) != 0;
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct AnimatePacket* a3) {
	if(this->level) {
		if(this->minecraft->player->entityId != a3->eid || a3->action != 1) {
			Entity* e = this->level->getEntity(a3->eid);
			if(e) {
				if(e->isPlayer()) {
					int32_t action = (uint8_t)a3->action;
					if(action == 1) {
						((Mob*)e)->swing();
					} else if(action == 3) {
						((Player*)e)->stopSleepInBed(0, 0, 0);
					}
				}
			}
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID&, struct EntityDataPacket* a3) {
	if(this->level) {
		TileEntity* te = this->level->getTileEntity(a3->x, a3->y, a3->z);
		if(te) {
			te->onUpdatePacket(&a3->data);
		}
	}
}
void ClientSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct RespawnPacket* a3) {
	if(this->level) {
		NetEventCallback::handle(level, a2, a3);
	}
}
