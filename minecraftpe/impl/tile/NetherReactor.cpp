#include <tile/NetherReactor.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>
#include <level/NetherReactorPattern.hpp>
#include <tile/entity/NetherReactorTileEntity.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

NetherReactor::NetherReactor(int32_t id, const std::string& a3, const struct Material* a4)
	: EntityTile(id, a3, a4) {
	TextureAtlasTextureItem* texIt = this->getTextureItem("reactor_core_stage_x");
	this->field_80 = *texIt->getUV(0);
	this->field_98 = *texIt->getUV(1);
	this->field_B0 = *texIt->getUV(2);

}
bool_t NetherReactor::allPlayersCloseToReactor(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t xmin; // r6
	int32_t ymin; // r7
	int32_t xmax; // r2
	int32_t ymax; // r3

	xmin = x - 5;
	ymin = y - 1;
	xmax = x + 5;
	ymax = y + 1;
	for(auto& player: level->playersMaybe) {
		if(player->posX < xmin) return 0;
		if(player->posX > xmax) return 0;
		float v14 = player->posY - player->ridingHeight;
		if(v14 < ymin) return 0;
		if(v14 > ymax) return 0;
		if(player->posZ < (z - 5)) return 0;
		if(player->posZ > (z + 5)) return 0;
	}
	return 1;
}
bool_t NetherReactor::canSpawnStartNetherReactor(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	if(!this->allPlayersCloseToReactor(level, x, y, z)) {
		player->displayClientMessage("All players need to be close to the reactor.");
		return 0;
	}
	if(y > 100) {
		player->displayClientMessage("The nether reactor needs to be built lower down.");
		return 0;
	}

	if(y <= 1) {
		player->displayClientMessage("The nether reactor needs to be built higher up.");
		return 0;
	}
	return 1;
}
void NetherReactor::setPhase(Level* level, int32_t x, int32_t y, int32_t z, int32_t phase) {
	if(level->getData(x, y, z) != phase) {
		level->setData(x, y, z, phase, 2);
	}
}

NetherReactor::~NetherReactor() {
}
TextureUVCoordinateSet* NetherReactor::getTexture(int32_t a2, int32_t a3) {
	if(a3 == 1) return &this->field_98;
	if(a3 == 2) return &this->field_B0;
	return &this->field_80;
}
int32_t NetherReactor::getTileEntityType() {
	return 3;
}
bool_t NetherReactor::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	int32_t yy;					 // r6
	int32_t i;					 // r0
	int32_t v12;				 // r8
	int32_t v14;				 // r7
	bool_t result;				 // r0
	NetherReactorTileEntity* te; // r0
	int32_t v19;				 // [sp+14h] [bp-ACh]
	int32_t v20;				 // [sp+18h] [bp-A8h]

	if(level->levelData.getGameType()) {
		return 0;
	}

	yy = 0;
	NetherReactorPattern v22;
	do {
		v14 = 0;
		v20 = y - 1 + yy;
		do {
			v12 = -1;
			v19 = x - 1 + v14;
			for(i = level->getTile(v19, v20, z - 1);; i = level->getTile(v19, v20, v12 + z)) {
				if(i != v22.getTileAt(yy, v14, ++v12)) {
					player->displayClientMessage("Not the correct pattern!");
					return 0;
				}
				if(v12 == 2) {
					break;
				}
			}
			++v14;
		} while(v14 != 3);
		++yy;
	} while(yy != 3);

	if(this->canSpawnStartNetherReactor(level, x, y, z, player)) {
		player->displayClientMessage("Active!");
		te = (NetherReactorTileEntity*)level->getTileEntity(x, y, z);
		if(te) {
			if(te->type == 3) {
				te->lightItUp(x, y, z);
			}
		}
		return 1;
	}
	return 0;
}
