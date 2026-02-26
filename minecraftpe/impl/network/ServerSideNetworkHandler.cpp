#include <network/ServerSideNetworkHandler.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <entity/ServerPlayer.hpp>
#include <entity/player/gamemode/GameMode.hpp>
#include <inventory/Inventory.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <network/IRakNetInstance.hpp>
#include <network/packet/AnimatePacket.hpp>
#include <network/packet/ChunkDataPacket.hpp>
#include <network/packet/ContainerClosePacket.hpp>
#include <network/packet/ContainerSetContentPacket.hpp>
#include <network/packet/ContainerSetSlotPacket.hpp>
#include <network/packet/DropItemPacket.hpp>
#include <network/packet/EntityDataPacket.hpp>
#include <network/packet/EntityEventPacket.hpp>
#include <network/packet/InteractPacket.hpp>
#include <network/packet/LevelEventPacket.hpp>
#include <network/packet/LoginPacket.hpp>
#include <network/packet/LoginStatusPacket.hpp>
#include <network/packet/MessagePacket.hpp>
#include <network/packet/MovePlayerPacket.hpp>
#include <network/packet/PlayerActionPacket.hpp>
#include <network/packet/PlayerArmorEquipmentPacket.hpp>
#include <network/packet/PlayerEquipmentPacket.hpp>
#include <network/packet/PlayerInputPacket.hpp>
#include <network/packet/ReadyPacket.hpp>
#include <network/packet/RemoveBlockPacket.hpp>
#include <network/packet/RemoveEntityPacket.hpp>
#include <network/packet/RemovePlayerPacket.hpp>
#include <network/packet/RequestChunkPacket.hpp>
#include <network/packet/RespawnPacket.hpp>
#include <network/packet/SetEntityLinkPacket.hpp>
#include <network/packet/SetHealthPacket.hpp>
#include <network/packet/TileEventPacket.hpp>
#include <network/packet/UseItemPacket.hpp>
#include <tile/Tile.hpp>
#include <tile/entity/TileEntity.hpp>
#include <network/packet/AddItemEntityPacket.hpp>
#include <network/packet/AddPaintingPacket.hpp>
#include <entity/FallingTile.hpp>
#include <network/packet/AddEntityPacket.hpp>
#include <network/packet/AddMobPacket.hpp>
#include <network/packet/UpdateBlockPacket.hpp>
#include <network/RakNetInstance.hpp>
#include <network/mco/RestRequestJob.hpp>
#include <network/packet/StartGamePacket.hpp>
#include <network/packet/SetTimePacket.hpp>
#include <sstream>
#include <level/storage/LevelStorage.hpp>
#include <gui/Screen.hpp>
#include <level/Level.hpp>
#include <network/mco/RestCallTagData.hpp>
#include <network/packet/AddPlayerPacket.hpp>

ServerSideNetworkHandler::ServerSideNetworkHandler(Minecraft* a2, IRakNetInstance* a3) {
	this->minecraft = a2;
	this->level = 0;
	this->field_30 = 0;
	this->raknetInstance = a3;
	this->allowIncomingConnections(0);
	this->rakPeer = a3->getPeer();
}
void ServerSideNetworkHandler::allowIncomingConnections(bool_t a2) {
	if(a2) {
		this->raknetInstance->announceServer(this->minecraft->options.username);
	} else {
		this->raknetInstance->announceServer("");
	}
	this->field_34 = a2;
}
ServerPlayer* ServerSideNetworkHandler::createNewPlayer(const RakNet::RakNetGUID& a2, LoginPacket* a3) {
	Player* pp = this->findPendingPlayer(a2);
	if(!pp) {
		ServerPlayer* v7 = new ServerPlayer(this->minecraft, this->level);
		v7->rakNetGUID = a2;
		v7->username = a3->username.C_String();
		v7->field_CA8 = a3->clientId;
		std::stringstream v15;
		v15 << a3->clientId;
		v7->field_CA4 = v15.str();
		this->level->getLevelStorage()->load(v7);
		this->minecraft->gameMode->initAbilities(v7->abilities);
		this->players.emplace_back(v7);
		while(v7->posY < 129) {
			v7->setPos(v7->posX, v7->posY, v7->posZ);
			if(this->level->getCubes(v7, v7->boundingBox, 0)->empty()) break;
			v7->posY += 1;
		}
		v7->moveTo(v7->posX, v7->posY - v7->ridingHeight, v7->posZ, v7->yaw, v7->pitch);
		this->level->getCubes(v7, v7->boundingBox, 0);
		return v7;
	}
	return (ServerPlayer*) pp;
}
void ServerSideNetworkHandler::displayGameMessage(const std::string& a2, const std::string& a3) {
	this->minecraft->gui.addMessage(a2, a3, 200);
	MessagePacket pk(a3, a2);
	this->raknetInstance->send(pk);
}
Player* ServerSideNetworkHandler::findPendingPlayer(const RakNet::RakNetGUID& a2) {
	for(int32_t i = 0; i < this->players.size(); ++i) {
		if(this->players[i]->rakNetGUID == a2) {
			return this->players[i];
		}
	}
	return 0;
}
Player* ServerSideNetworkHandler::getPlayer(const RakNet::RakNetGUID& a2) {
	for(int32_t i = 0; i < this->level->playersMaybe.size(); ++i) {
		if(a2 == this->level->playersMaybe[i]->rakNetGUID) {
			return this->level->playersMaybe[i];
		}
	}
	return 0;
}
int32_t ServerSideNetworkHandler::numberOfConnections() {
	return this->rakPeer->NumberOfConnections();
}
void ServerSideNetworkHandler::onReady_ClientGeneration(const RakNet::RakNetGUID& a2) {
	Player* p = this->popPendingPlayer(a2);
	if(p) {
		RakNet::BitStream stream;
		SetTimePacket(this->level->getTime(), (uint32_t)this->level->levelData.stopTime >> 31).write(&stream);
		this->rakPeer->Send(&stream, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);

		for(int32_t v8 = 0; v8 < this->level->playersMaybe.size(); ++v8) {
			Player* v9 = this->level->playersMaybe[v8];
			stream.Reset();
			AddPlayerPacket(v9).write(&stream);
			this->rakPeer->Send(&stream, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);
			if(v9->getArmorTypeHash()) {
				stream.Reset();
				PlayerArmorEquipmentPacket(v9).write(&stream);
				this->rakPeer->Send(&stream, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);
			}
		}

		this->level->addEntity(p);
		this->minecraft->gui.addMessage("server", p->username + " joined the game", 200);
		for(int32_t v21 = 0; v21 < this->level->entities.size(); ++v21) {
			Packet* v22 = this->getAddPacketFromEntity(this->level->entities[v21]);
			if(v22) {
				stream.Reset();
				v22->write(&stream);
				this->rakPeer->Send(&stream, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);
				delete v22;
			}
		}

		stream.Reset();
		ContainerSetContentPacket a3(0, p->inventory->getSlotCopies(), 9);
		for(int v26 = 0; v26 < p->inventory->getLinkedSlotsCount(); ++v26) {
			a3.field_1C.emplace_back(p->inventory->getLinkedSlot(v26));
		}
		a3.write(&stream);
		this->rakPeer->Send(&stream, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);
		std::vector<ItemInstance> v61(4);
		for(int32_t i = 0; i != 4; ++i) {
			ItemInstance* v31 = p->getArmor(i);
			v61[i] = v31 ? ItemInstance(*v31) : ItemInstance();
		}
		stream.Reset();
		ContainerSetContentPacket(120, v61, 0).write(&stream);
		this->rakPeer->Send(&stream, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);

		for(auto e: this->level->entities) {
			if(e->isRiding()) {
				SetEntityLinkPacket pk(0, e->entityId, e->ridingAt ? e->ridingAt->entityId : 0);
				this->raknetInstance->send(pk);
			}
		}

		stream.Reset();
		AddPlayerPacket(p).write(&stream);
		this->rakPeer->Send(&stream, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 1, 0);
	}
}
void ServerSideNetworkHandler::onReady_RequestedChunks(const RakNet::RakNetGUID& a2) {
	RakNet::BitStream v11;
	for(int32_t i = 0; i < this->level->tileEntities.size(); ++i) {
		Packet* v5 = this->level->tileEntities[i]->getUpdatePacket();
		if(v5) {
			v11.Reset();
			v5->write(&v11);
			this->rakPeer->Send(&v11, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);
			delete v5;
		}
	}
}
Player* ServerSideNetworkHandler::popPendingPlayer(const RakNet::RakNetGUID& a2) {
	if(this->level) {
		for(int i = 0; i < this->players.size(); ++i) {
			Player* v4 = this->players[i];
			if(v4->rakNetGUID == a2) {
				this->players.erase(this->players.begin() + i);
				return v4;
			}
		}
	}
	return 0;
}
void ServerSideNetworkHandler::redistributePacket(Packet* a2, const RakNet::RakNetGUID& a3) {
	RakNet::BitStream v11;
	a2->write(&v11);
	this->rakPeer->Send(&v11, a2->packetPriorityMaybe, a2->packetReliabilityMaybe, 0, RakNet::AddressOrGUID(a3), 1, 0);
}
void ServerSideNetworkHandler::sendLoginMessageLocal(int32_t a2, const RakNet::RakNetGUID& a3, LoginPacket* a4) {
	RakNet::BitStream v13;
	LoginStatusPacket v11(a2);
	v11.write(&v13);
	this->rakPeer->Send(&v13, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a3), 0, 0);

	if(a2 == 0) {
		this->sendWorldSeed(this->createNewPlayer(a3, a4), a3);
	}
}
void ServerSideNetworkHandler::sendLoginMessageMCO(int32_t, const RakNet::RakNetGUID&, LoginPacket*) {
	printf("ServerSideNetworkHandler::sendLoginMessageMCO - not implemented\n"); //TODO implement
	//unused?
}
void ServerSideNetworkHandler::sendWorldSeed(Player* a2, const RakNet::RakNetGUID& a3) {
	RakNet::BitStream v24;
	StartGamePacket v22(this->level->getSeed(), this->level->getLevelData()->getGeneratorVersion(), this->minecraft->isCreativeMode(), a2->entityId, a2->posX, a2->posY - a2->ridingHeight, a2->posZ);
	v22.write(&v24);
	this->rakPeer->Send(&v24, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a3), 0, 0);
	v24.Reset();
	SetTimePacket v23(this->level->getTime(), this->level->levelData.stopTime >> 31);
	v23.write(&v24);
	this->rakPeer->Send(&v24, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a3), 0, 0);
}

void ServerSideNetworkHandler::levelGenerated(Level* a2) {
	this->level = a2;
	if(this->minecraft->player) {
		this->minecraft->player->rakNetGUID = this->rakPeer->GetMyGUID();
	}
	a2->addListener(this);
	this->allowIncomingConnections(this->minecraft->options.serverVisible);
}
ServerSideNetworkHandler::~ServerSideNetworkHandler() {
	if(this->level) {
		this->level->removeListener(this);
	}
	for(int32_t i = 0; i < this->players.size(); ++i) {
		if(this->players[i]) {
			delete this->players[i];
		}
	}
	for(auto&& p: this->field_18) {
		if(p) {
			p->stop();
			p.reset(); //TODO check is this thing called
		}
	}
}
void ServerSideNetworkHandler::onNewClient(const RakNet::RakNetGUID& a2) {
	a2.ToString();
}
void ServerSideNetworkHandler::onDisconnect(const RakNet::RakNetGUID& a2) {
	if(this->level) {
		for(int i = 0; i < this->level->playersMaybe.size(); ++i) {
			Player* v6 = this->level->playersMaybe[i];
			if(v6->rakNetGUID == a2) {
				std::string v9 = v6->username + " disconnected from the game";
				this->displayGameMessage("server", v9);
				((ServerPlayer*)v6)->disconnect();
				this->level->getLevelStorage()->save(v6);
				this->level->removeEntity(v6);
				break;
			}
		}
		this->popPendingPlayer(a2);
	}
}
bool_t ServerSideNetworkHandler::allowIncomingPacketId(const RakNet::RakNetGUID& a2, int32_t a3) {
	if(!this->level) return 0;
	if(a3 > 56) {
		this->raknetInstance->getPeer()->CloseConnection(RakNet::AddressOrGUID(a2), 0);
		return 0;
	}
	if(a3 > 3 && !this->getPlayer(a2)) {
		this->raknetInstance->getPeer()->CloseConnection(RakNet::AddressOrGUID(a2), 0);
		return 0;
	}
	return 1;
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct LoginPacket* a3) {
	if(this->level) {
		if(this->field_34) {
			int32_t v4;
			if(a3->protocol1 <= 12) {
				v4 = 1;
			} else if(a3->protocol2 <= 14) {
				v4 = 0;
			} else {
				v4 = 2;
			}
			this->sendLoginMessageLocal(v4, a2, a3);
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ReadyPacket* a3) {
	if(this->level) {
		if(a3->status == 1) {
			this->onReady_ClientGeneration(a2);
		}
		if(a3->status == 2) {
			this->onReady_RequestedChunks(a2);
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct MessagePacket* a3) {
	this->displayGameMessage(a3->source.C_String(), a3->message.C_String());
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct MovePlayerPacket* a3) {
	if(this->level) {
		Player* player = this->getPlayer(a2);
		if(player) {
			if(player->ridingAt) {
				player->ridingAt->positionRider(0);
				float xx = player->posX;
				float yaw = a3->yaw;
				float yy = player->posY;
				float pitch = a3->pitch;
				float zz = player->posZ;
				player->tick();
				player->ySize = 0;
				player->moveTo(xx, yy, zz, yaw, pitch);
				player->headYaw = a3->bodyYaw;
				if(player->ridingAt) {
					player->ridingAt->positionRider(0);
				}
				this->level->tick(player);
			} else {
				float x = a3->x;
				if(x > 384.0) {
					x = 384.0;
				} else if(x <= -128.0) {
					x = -128.0;
				}
				a3->x = x;
				float z = a3->z;
				if(z > 384.0) {
					z = 384.0;
				} else if(z <= -128.0) {
					z = -128.0;
				}
				a3->z = z;
				float y = a3->y;
				if(y > 512.0) {
					y = 512.0;
				} else if(y <= -128.0) {
					y = -128.0;
				}
				a3->y = y;
				a3->yaw = fmodf(a3->yaw, 360.0);
				a3->pitch = fmodf(a3->pitch, 360.0);
				player->motionZ = 0.0;
				player->motionY = 0.0;
				player->motionX = 0.0;
				player->lerpTo(a3->x, a3->y, a3->z, a3->yaw, a3->pitch, 3);
				player->headYaw = a3->bodyYaw;
				player->checkTileCollisions();
			}
			this->redistributePacket(a3, a2);
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct RemoveBlockPacket* a3) {
	if(this->level) {
		Player* player = this->getPlayer(a2);
		if(player) {
			player->swing();
			int32_t x = a3->x;
			int32_t y = (uint8_t)a3->y;
			int32_t z = a3->z;
			int32_t v10 = this->level->getTile(x, y, z);
			int32_t v11 = this->level->getData(x, y, z);
			bool_t v14 = this->level->setTile(x, y, z, 0, 3);
			if(Tile::tiles[v10]) {
				if(v14) {
					this->level->playSound((float)x + 0.5, (float)y + 0.5, (float)z + 0.5, Tile::tiles[v10]->soundType->field_8, (float)(Tile::tiles[v10]->soundType->field_0 + 1.0) * 0.5, Tile::tiles[v10]->soundType->field_4 * 0.8);
					if(this->minecraft->gameMode->isSurvivalType()) {
						if(player->canDestroy(Tile::tiles[v10])) {
							Tile::tiles[v10]->playerDestroy(this->level, player, x, y, z, v11);
						}
					}
					Tile::tiles[v10]->playerWillDestroy(this->level, x, y, z, v11, player);
					Tile::tiles[v10]->destroy(this->level, x, y, z, v11);
				}
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct EntityEventPacket* a3) {
	if(this->level) {
		Entity* e = this->level->getEntity(a3->eid);
		if(e) {
			e->handleEntityEvent(a3->event);
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct RequestChunkPacket* a3) {
	if(this->level) {
		LevelChunk* chunk = this->level->getChunk(a3->x, a3->z);
		if(chunk) {
			int32_t chunkX = chunk->chunkX;
			int32_t chunkZ = chunk->chunkZ;
			ChunkDataPacket v16(chunkX, chunkZ, chunk);

			RakNet::BitStream v15;
			v16.write(&v15);
			this->rakPeer->Send(&v15, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2), 0, 0);
			for(auto&& p: *chunk->getTileEntityMap()) {
				Packet* pk = p.second->getUpdatePacket();
				if(pk) {
					v15.Reset();
					pk->write(&v15);
					this->raknetInstance->send(a2, pk);
				}
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct PlayerEquipmentPacket* a3) {
	if(this->level) {
		Player* p = this->getPlayer(a2);
		if(!(this->rakPeer->GetMyGUID() == p->rakNetGUID)) {
			ItemInstance v9(a3->itemID, 200, a3->itemMeta);
			if(p->abilities.instabuild) {
				p->inventory->replaceSlot(a3->slot, &v9);
			}
			ItemInstance* v7 = p->inventory->getItem(a3->slot);
			if(!v7 || !ItemInstance::isItem(v7)) {
				a3->itemMeta = 0;
				a3->itemID = 0;
			}
			int slot = a3->slot;
			if(slot >= 0 && a3->itemID) {
				p->inventory->moveToSelectedSlot(slot);
				p->inventory->selectSlot(a3->slot);
			} else {
				p->inventory->unlinkSlot(p->inventory->selectedSlot);
			}
			this->redistributePacket(a3, a2);
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct PlayerArmorEquipmentPacket* a3) {
	if(this->level) {
		Player* p = this->getPlayer(a2);
		if(p) {
			if(this->rakPeer->GetMyGUID() == p->rakNetGUID) {
				this->redistributePacket(a3, a2);
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct SetHealthPacket* a3) {
	if(this->level) {
		Player* p = this->getPlayer(a2);
		if(p) {
			if(p != this->minecraft->player) {
				int32_t health = a3->health;
				if(health < -31) {
					int32_t v7 = health + 64;
					if(v7 <= 0) {
						if(v7) {
							p->heal(-v7);
						}
					} else {
						p->hurt(0, v7);
					}
				}
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct SetEntityLinkPacket* a3) {
	if(this->level) {
		Entity* e = this->level->getEntity(a3->rider);
		Entity* v8 = this->level->getEntity(a3->riding);
		if(a3->typeMaybe == 0) {
			Entity* p = this->minecraft->player;
			if(!p || a3->rider != p->entityId) {
				if(!e) return;
				p = e;
			}
			p->ride(v8);
		}
		this->redistributePacket(a3, a2);
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct InteractPacket* a3) {
	if(this->level) {
		Entity* e = this->level->getEntity(a3->eid);
		Entity* v8 = this->level->getEntity(a3->type);
		if(e) {
			if(v8) {
				if(e->isPlayer()) {
					if(a3->action == 2) {
						((Player*)e)->swing();
						this->minecraft->gameMode->attack((Player*)e, v8);
					}
					if(a3->action == 1) {
						((Player*)e)->swing();
						this->minecraft->gameMode->interact((Player*)e, v8);
					}
					this->redistributePacket(a3, a2);
				}
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct UseItemPacket* packet) {
	if(this->level) {
		Player* v5 = this->getPlayer(a2);
		Player* player = v5;
		if(v5) {
			if(packet->item.isValid) {
				if(packet->face == 255) {
					int field_D8 = v5->field_D8;
					if(field_D8 - v5->field_CAC > 4) {
						v5->field_CAC = field_D8;
						player->field_174 = Vec3(packet->x * 0.000030518, packet->y * 0.000030518, packet->z * 0.000030518).normalized();

						this->minecraft->gameMode->useItem(player, this->level, &packet->item);
					}
				} else {
					int x = packet->x;
					int v19 = packet->y;
					int v20 = packet->z;
					Tile* v21 = Tile::tiles[this->level->getTile(x, v19, v20)];
					if(v21 != Tile::invisible_bedrock && (!v21 || !v21->use(this->level, x, v19, v20, player))) {
						float playerX = player->posX;
						float playerY = player->posY;
						float playerZ = player->posZ;
						player->setPos(packet->posX, packet->posY, packet->posZ);
						this->minecraft->gameMode->useItemOn(player, this->level, &packet->item, packet->x, packet->y, packet->z, packet->face, Vec3((float)packet->x + packet->faceX, packet->faceY + (float)packet->y, packet->faceZ + (float)packet->z));
						player->setPos(playerX, playerY, playerZ);
					}
				}
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct PlayerActionPacket* a3) {
	if(this->level) {
		Player* p = this->getPlayer(a2);
		if(p) {
			if(a3->action == 5) {
				this->minecraft->gameMode->releaseUsingItem(p);
			} else if(a3->action == 6) {
				p->stopSleepInBed(1, 1, 1);
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct DropItemPacket* a3) {
	if(this->level) {
		if(ItemInstance::isItem(&a3->itemInstance)) {
			Player* p = this->getPlayer(a2);
			if(p) {
				p->drop(&a3->itemInstance, a3->motionType ? 1 : 0);
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ContainerClosePacket* a3) {
	if(this->level) {
		Player* p = this->findPlayer(this->level, &a2);
		if(p) {
			if(p != this->minecraft->player) {
				((ServerPlayer*)p)->doCloseContainer();
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ContainerSetSlotPacket* a3) {
	if(this->level) {
		Player* player = this->findPlayer(this->level, &a2);
		if(player) {
			if(!ItemInstance::isItem(&a3->field_10)) {
				a3->field_10.setNull();
			}

			int32_t v8 = (uint8_t)a3->field_D;
			if(a3->field_D) {
				if(v8 == 120) {
					player->setArmor(a3->field_E, &a3->field_10);
				} else {
					if(player->currentContainer) {
						if(player->currentContainer->field_0 == v8) {
							if(player->currentContainer->containerID == 2) {
								player->currentContainer->setSlot(a3->field_E, &a3->field_10);
							}
							if(player->currentContainer->containerID == 0) {
								player->currentContainer->setSlot(a3->field_E, &a3->field_10);
								if(this->minecraft->currentScreen) {
									this->minecraft->currentScreen->onInternetUpdate();
								}
							}
						}
					}
				}
			} else {
				player->inventory->setItem(a3->field_E + 9, &a3->field_10);
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct ContainerSetContentPacket* a3) {
	if(this->level) {
		Player* p = this->findPlayer(this->level, &a2);
		if(p) {
			if(!a3->field_C) {
				int32_t v7 = 0;
				while(v7 < a3->field_1C.size() && v7 < p->inventory->getLinkedSlotsCount()) {
					p->inventory->linkedSlots[v7].field_0 = a3->field_1C[v7];
				}
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct AnimatePacket* a3) {
	if(this->level) {
		Player* player = this->getPlayer(a2);
		if(player) {
			if(player != this->minecraft->player) {
				a3->eid = player->entityId;
				if(a3->action == 1) {
					player->swing();
				}
				this->redistributePacket(a3, a2);
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct EntityDataPacket* a3) {
	if(this->level) {
		this->redistributePacket(a3, a2);
		TileEntity* te = this->level->getTileEntity(a3->x, a3->y, a3->z);
		if(te->isType(4)) {
			te->onUpdatePacket(&a3->data);
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct PlayerInputPacket* pk) {
	if(this->level) {
		Player* p = this->getPlayer(a2);
		if(p) {
			if(p != this->minecraft->player) {
				((ServerPlayer*)p)->setPlayerInput(pk->moveForward, pk->moveStrafe, pk->isJumping, pk->isSneaking);
			}
		}
	}
}
void ServerSideNetworkHandler::handle(const RakNet::RakNetGUID& a2, struct RespawnPacket* a3) {
	if(this->level) {
		this->handle(a2, a3);
		this->redistributePacket(a3, a2);
	}
}
void ServerSideNetworkHandler::onPlayerVerified(const RestCallTagData& a2) {
	RakNet::BitStream v16;
	Player* pp = this->findPendingPlayer(a2.guid_g);
	if(pp) {
		LoginStatusPacket v14(0);
		v14.write(&v16);
		this->rakPeer->Send(&v16, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2.guid_g), 0, 0);
		this->sendWorldSeed(pp, a2.guid_g);
	} else {
		LoginStatusPacket v14(4);
		v14.write(&v16);
		this->rakPeer->Send(&v16, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2.guid_g), 0, 0);
	}
}
void ServerSideNetworkHandler::onPlayerVerifiedFailed(const RestCallTagData& a2) {
	RakNet::BitStream v8;
	LoginStatusPacket v7(3);
	v7.write(&v8); //XXX non-virtual in mcpe081
	this->rakPeer->Send(&v8, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, RakNet::AddressOrGUID(a2.guid_g), 0, 0);
}

static RakNet::SystemAddress _d6e0a1f0; //TODO check is this thing initialized correctly
void ServerSideNetworkHandler::tileChanged(int32_t x, int32_t y, int32_t z) {
	int32_t id = this->level->getTile(x, y, z);
	int32_t meta = this->level->getData(x, y, z);

	UpdateBlockPacket v14(x, y, z, id, meta);
	RakNet::BitStream v17;
	v14.write(&v17);
	this->rakPeer->Send(&v17, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE_ORDERED, 0, _d6e0a1f0, 1, 0);
	if(Tile::isEntityTile[id]) {
		TileEntity* te = this->level->getTileEntity(x, y, z);
		if(te) {
			Packet* v11 = te->getUpdatePacket();
			if(v11) {
				this->level->rakNetInstance->send(v11);
			}
		}
	}
}
void ServerSideNetworkHandler::tileBrightnessChanged(int32_t, int32_t, int32_t) {
}
Packet* ServerSideNetworkHandler::getAddPacketFromEntity(Entity* a2) {
	if(!a2->isMob() || a2->isPlayer()) {
		if(a2->isPlayer()) {
			return 0;
		} else if(a2->isItemEntity()) {
			return new AddItemEntityPacket((ItemEntity*)a2);
		} else if(a2->isHangingEntity()) {
			return new AddPaintingPacket((Painting*)a2);
		} else {
			int32_t id = a2->getEntityTypeId();
			int32_t v5 = a2->getAuxData();
			if(id == 66) {
				v5 = -(((FallingTile*)a2)->blockID | (((FallingTile*)a2)->blockMetaMaybe << 16));
			}
			return new AddEntityPacket(a2, v5);
		}
	} else {
		return new AddMobPacket((Mob*)a2);
	}
}
void ServerSideNetworkHandler::entityAdded(Entity* a2) {
	Packet* v4 = this->getAddPacketFromEntity(a2);
	if(v4) {
		if(!a2->isMob() || a2->isPlayer()) {
			this->raknetInstance->send(v4);
		} else {
			this->redistributePacket(v4, this->rakPeer->GetMyGUID());
			delete v4;
		}
	}
}
void ServerSideNetworkHandler::entityRemoved(Entity* a2) {
	if(a2->isPlayer()) {
		RemovePlayerPacket v11(a2->entityId, ((Player*)a2)->rakNetGUID);
		this->redistributePacket(&v11, this->rakPeer->GetMyGUID());
	} else {
		RemoveEntityPacket v11(a2->entityId);
		this->redistributePacket(&v11, this->rakPeer->GetMyGUID());
	}
}
void ServerSideNetworkHandler::levelEvent(Player* a2, int32_t evid, int32_t x, int32_t y, int32_t z, int32_t data) {
	LevelEventPacket pk(evid, x, y, z, data);
	this->redistributePacket(&pk, a2 ? a2->rakNetGUID : this->rakPeer->GetMyGUID());
}
void ServerSideNetworkHandler::tileEvent(int32_t x, int32_t y, int32_t z, int32_t c1, int32_t c2) {
	TileEventPacket pk(x, y, z, c1, c2);
	this->raknetInstance->send(pk);
}
