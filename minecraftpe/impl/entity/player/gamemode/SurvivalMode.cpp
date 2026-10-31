#include <entity/player/gamemode/SurvivalMode.hpp>
#include <entity/player/Abilities.hpp>
#include <Minecraft.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
#include <entity/LocalPlayer.hpp>
#include <item/Item.hpp>
#include <sound/SoundEngine.hpp>
#include <inventory/Inventory.hpp>


SurvivalMode::SurvivalMode(Minecraft* a2)
	: GameMode(a2) {
	this->xCurrent = -1;
	this->yCurrent = -1;
	this->zCurrent = -1;
}

void SurvivalMode::startDestroyBlock(int32_t x, int32_t y, int32_t z, int32_t side) {
	if(!this->minecraft->player->getCarriedItem() || Item::bow != this->minecraft->player->getCarriedItem()->itemClass || !Item::bow) {
		int id = this->minecraft->level->getTile(x, y, z);
		if(id > 0) {
			if(this->field_8 == 0.0f) {
				Tile::tiles[id]->attack(this->minecraft->level, x, y, z, (Player*)this->minecraft->player);
			}
			if(Tile::tiles[id]->getDestroyProgress(this->minecraft->player) >= 1.0f) {
				this->destroyBlock(x, y, z, side);
			}
		}
	}
}
bool_t SurvivalMode::destroyBlock(int32_t x, int32_t y, int32_t z, int32_t side) {
	int32_t id;		   // r8
	int32_t meta;	   // r10
	int32_t v11;	   // r9
	bool_t canDestroy; // r11
	ItemInstance* sel; // r0
	ItemInstance* v16; // [sp+14h] [bp-44h]

	id = this->minecraft->level->getTile(x, y, z);
	meta = this->minecraft->level->getData(x, y, z);
	v11 = GameMode::destroyBlock(x, y, z, side);
	canDestroy = this->minecraft->player->canDestroy(Tile::tiles[id]);
	sel = this->minecraft->player->inventory->getSelected();
	v16 = sel;
	if(sel) {
		sel->mineBlock(id, x, y, z, this->minecraft->player);
		if(!v16->count) {
			this->minecraft->player->inventory->clearSlot(this->minecraft->player->inventory->selectedSlot);
		}
	}
	if(v11) {
		if(canDestroy) {
			ItemInstance v17(id, 1, meta); //TODO not usde???
			Tile::tiles[id]->playerDestroy(this->minecraft->level, (Player*)this->minecraft->player, x, y, z, meta);
		}
	}
	return v11;
}
void SurvivalMode::continueDestroyBlock(int32_t x, int32_t y, int32_t z, int32_t a5) {

	if(this->delay <= 0) {
		if(x == this->xCurrent && y == this->yCurrent && z == this->zCurrent) {
			int id = this->minecraft->level->getTile(x, y, z);
			if(id) {
				Tile* v11 = Tile::tiles[id];
				float v12 = v11->getDestroyProgress(this->minecraft->player);
				this->field_C += 1;
				this->field_8 += v12;
				if((this->field_C & 3) == 1) {
					this->minecraft->soundEngine->play(v11->soundType->soundName, x + 0.5f, y + 0.5f, z + 0.5f, (v11->soundType->field_0 + 1.0f) * 0.125f, v11->soundType->field_4 * 0.5f);
				}
				if(this->field_8 >= 1.0f) {
					this->destroyBlock(x, y, z, a5);
					this->field_8 = 0.0;
					this->field_4 = 0.0;
					this->field_C = 0;
					this->delay = 5;
				}
			}
		} else {
			this->xCurrent = x;
			this->field_8 = 0;
			this->field_4 = 0;
			this->yCurrent = y;
			this->field_C = 0;
			this->zCurrent = z;
		}
	} else {
		this->delay -= 1;
	}
}
void SurvivalMode::stopDestroyBlock() {
	this->field_8 = 0;
	this->delay = 0;
}
void SurvivalMode::initAbilities(Abilities& a2){
	a2.flying = 0;
	a2.mayfly = 0;
	a2.instabuild = 0;
	a2.invulnerable = 0;
}
