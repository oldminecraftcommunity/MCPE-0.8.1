#include <level/Explosion.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <tile/Tile.hpp>

Explosion::Explosion(Level* a2, Entity* a3, float a4, float a5, float a6, float a7) {
	this->field_0 = a4;
	this->field_4 = a5;
	this->field_28 = 0;
	this->field_8 = a6;
	this->field_2C = 0;
	this->field_C = a7;
	this->field_28 = 0;
	this->field_30 = 0;
	this->entity = a3;
	this->level = a2;
}
void Explosion::explode()
#ifdef IMTOOLAZYTOFIX16ERRS
{
	printf("Explosion::explode - not implemented\n");
}
#endif
;
void Explosion::finalizeExplosion() {
	this->level->playSound(this->field_0, this->field_4, this->field_8, "random.explode", 4.0, (float)((float)((float)(this->level->random.nextFloat() - this->level->random.nextFloat()) * 0.2) + 1.0) * 0.7);
	int32_t v38 = 0;
	for(auto p: this->field_10) {
		int32_t id = this->level->getTile(p.x, p.y, p.z);
		if((v38 & 7) == 0) {
			float v13 = (float)p.x + this->level->random.nextFloat();
			float v14 = (float)p.y + this->level->random.nextFloat();
			float v18 = (float)p.z + this->level->random.nextFloat();
			float v16 = v14 - this->field_4;
			float v17 = v13 - this->field_0;
			float v19 = v18 - this->field_8;
			float v20 = sqrt((float)((float)((float)(v16 * v16) + (float)(v17 * v17)) + (float)(v19 * v19)));
			float v21 = 1.0 / v20;
			float v22 = v17 * v21;
			float v23 = v16 * v21;
			float v24 = v19 * v21;
			float v25 = this->field_C / v21;
			float v27 = (float)(0.5 / (float)(v25 + 0.1)) * (float)((float)(this->level->random.nextFloat() * this->level->random.nextFloat()) + 0.3);
			float v28 = v22 * v27;
			float v29 = v23 * v27;
			float v30 = v24 * v27;
			this->level->addParticle(PT_EXPLODE, (float)(v13 + this->field_0) * 0.5, (float)(v14 + this->field_4) * 0.5, (float)(v18 + this->field_8) * 0.5, v28, v29, v30, 0);
			this->level->addParticle(PT_SMOKE, v13, v14, v18, v28, v29, v30, 0);
		}
		if(id) {
			if(!this->level->isClientMaybe) {
				if(this->level->getLevelData()->getGameType() != 1) {
					Tile::tiles[id]->spawnResources(this->level, p.x, p.y, p.z, this->level->getData(p.x, p.y, p.z), 0.3);
				}
			}
			if(this->level->setTileNoUpdate(p.x, p.y, p.z, 0)) {
				this->level->updateNeighborsAt(p.x, p.y, p.z, 0);
			}
			this->level->setTileDirty(p.x, p.y, p.z);
			if(!this->level->isClientMaybe) {
				Tile::tiles[id]->wasExploded(this->level, p.x, p.y, p.z);
			}
		}
		++v38;
	}
}
