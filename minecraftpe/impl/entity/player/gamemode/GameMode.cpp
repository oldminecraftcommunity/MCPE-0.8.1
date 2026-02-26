#include <entity/player/gamemode/GameMode.hpp>
#include <Minecraft.hpp>
#include <rendering/LevelRenderer.hpp>
#include <entity/LocalPlayer.hpp>
#include <level/Level.hpp>
#include <level/dimension/Dimension.hpp>
#include <item/Item.hpp>
#include <network/packet/UseItemPacket.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/PlayerActionPacket.hpp>
#include <tile/Tile.hpp>
#include <rendering/ParticleEngine.hpp>
#include <sound/SoundEngine.hpp>
#include <tile/material/Material.hpp>
#include <network/packet/RemoveBlockPacket.hpp>
#include <inventory/Inventory.hpp>

GameMode::GameMode(Minecraft* a2) {
	this->minecraft = a2;
	this->field_4 = 0;
	this->field_8 = 0;
	this->field_C = 0;
	this->delay = 0;
}

GameMode::~GameMode() {
}
void GameMode::initLevel(Level*) {
}
void GameMode::startDestroyBlock(int32_t x, int32_t y, int32_t z, int32_t a5) {
	if(!this->minecraft->player->getCarriedItem() || Item::bow != this->minecraft->player->getCarriedItem()->itemClass || !Item::bow) {
		this->destroyBlock(x, y, z, a5);
	}
}
bool_t GameMode::destroyBlock(int32_t x, int32_t y, int32_t z, int32_t side) {
	Level* level; // r5
	Tile* tile; // r11
	bool_t v11; // r10
	Minecraft* minecraft; // r0
	int32_t meta; // [sp+14h] [bp-4Ch]

	level = this->minecraft->level;
	tile = Tile::tiles[level->getTile(x, y, z)];
	if(!tile) {
		return 0;
	}
	if(level->adventureSettings.allowInteract && tile != Tile::leaves && tile->material != Material::plant) {
		return 0;
	}
	this->minecraft->particleEngine->destroy(x, y, z);
	meta = level->getData(x, y, z);
	tile->playerWillDestroy(level, x, y, z, meta, this->minecraft->player);
	v11 = level->setTile(x, y, z, 0, 3);
	if(!v11) {
		return 0;
	}
	this->minecraft->soundEngine->play(tile->soundType->field_8, (float)x + 0.5, (float)y + 0.5, (float)z + 0.5, (float)(tile->soundType->field_0 + 1.0) * 0.5, tile->soundType->field_4 * 0.8);
	tile->destroy(level, x, y, z, meta);
	minecraft = this->minecraft;
	if(minecraft->options.destroyVibration) {
		minecraft->platform()->vibrate(24);
	}
	if(this->minecraft->isOnline()) {
		RemoveBlockPacket v18(this->minecraft->player->entityId, x, y, z);
		this->minecraft->rakNetInstance->send(v18);
	}
	return v11;
}
void GameMode::stopDestroyBlock() {
}
void GameMode::tick() {
	this->field_4 = this->field_8;
}
void GameMode::render(float a2) {
	float v2; // s14
	float v3; // s15

	v2 = this->field_8;
	if(v2 > 0.0) {
		v3 = this->field_4 + (float)((float)(v2 - this->field_4) * a2);
		this->minecraft->gui.field_10 = v3;
		this->minecraft->levelRenderer->field_14 = v3;
	} else {
		this->minecraft->gui.field_10 = 0.0;
		this->minecraft->levelRenderer->field_14 = 0.0;
	}
}
float GameMode::getPickRange() {
	return 5.0;
}
bool_t GameMode::useItem(Player* a2, Level* a3, ItemInstance* a4) {
	int32_t count;	  // r9
	ItemInstance* v9; // r8

	count = a4->count;
	v9 = a4->use(a3, a2);
	if(a3->isClientMaybe) {
		UseItemPacket useItem(a2->entityId, (int32_t)(float)(a2->field_174.x * 32768.0), (int32_t)(float)(a2->field_174.y * 32768.0), (int32_t)(float)(a2->field_174.z * 32768.0), 255, a4->getId(), a4->getAuxValue());
		this->minecraft->rakNetInstance->send(useItem);
	}
	return v9 != a4 || v9->count != count;
}
bool_t GameMode::useItemOn(Player* player, Level* level, ItemInstance* a4, int32_t x, int32_t y, int32_t z, int32_t face, const Vec3& a9) {
	float faceX = a9.x - (float)x;
	float faceY = a9.y - (float)y;
	float faceZ = a9.z - (float)z;
	ItemInstance* sel = player->inventory->getSelected();
	if(level->isClientMaybe) {
		UseItemPacket v24(player, x, y, z, face, faceX, faceY, faceZ, sel);
		this->minecraft->rakNetInstance->send(v24);
	}
	int32_t bid = level->getTile(x, y, z);
	if(bid == Tile::invisible_bedrock->blockID) return 0;
	if(bid > 0 && Tile::tiles[bid]->use(level, x, y, z, player)) return 1;
	if(!ItemInstance::isItem(sel)) return 0;
	if(!this->isCreativeType()) return sel->useOn(player, level, x, y, z, face, faceX, faceY, faceZ);
	int32_t aux = sel->getAuxValue();
	int32_t count = sel->count;
	bool_t v19 = sel->useOn(player, level, x, y, z, face, faceX, faceY, faceZ);
	sel->setAuxValue(aux);
	sel->count = count;
	return v19;
}
Player* GameMode::createPlayer(Level* a2) {
	return new LocalPlayer(this->minecraft, a2, this->minecraft->user, a2->dimensionPtr->id, this->isCreativeType());
}
void GameMode::initPlayer(Player* a2) {
	this->initAbilities(a2->abilities);
}
void GameMode::adjustPlayer(Player*) {
}
bool_t GameMode::canHurtPlayer() {
	return 0;
}
void GameMode::interact(Player* a2, Entity* a3) {
	a2->interact(a3);
}
void GameMode::attack(Player* a2, Entity* a3) {
	if((!this->minecraft->level->adventureSettings.enablePVPMaybe || !a3->isPlayer()) && (!this->minecraft->level->adventureSettings.enablePVEMaybe || !a3->isMob())) {
		a2->attack(a3);
	}
}
bool_t GameMode::handleInventoryMouseClick(int32_t, int32_t, int32_t, Player*) {
	return 0;
}
void GameMode::handleCloseInventory(int32_t, Player*) {
}
bool_t GameMode::isCreativeType() {
	return 0;
}
bool_t GameMode::isSurvivalType() {
	return 0;
}
void GameMode::initAbilities(Abilities&) {
}
void GameMode::releaseUsingItem(Player* a2) {
	if(this->minecraft->level->isClientMaybe) {
		PlayerActionPacket pk(a2->entityId, 0, 0, 0, 0, 5);
		this->minecraft->rakNetInstance->send(pk);
	}
	a2->releaseUsingItem();
}
