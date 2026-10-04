#include <level/Explosion.hpp>
#include <entity/Entity.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <math/Vec3.hpp>
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
void Explosion::explode() {
	int v1 = this->field_C;
	for(int xx = 0; xx != 16; ++xx) {
		for(int yy = 0; yy != 16; ++yy) {
			for(int zz = 0; zz != 16; ++zz) {
				if(!xx || xx == 15 || !yy || yy == 15 || !zz || zz == 15) {
					float v3 = (float)((float)((float)yy / 15.0) + (float)((float)yy / 15.0)) - 1.0;
					float v4 = (float)((float)((float)xx / 15.0) + (float)((float)xx / 15.0)) - 1.0;
					float v5 = (float)((float)((float)zz / 15.0) + (float)((float)zz / 15.0)) - 1.0;
					float v6 = sqrt((float)((float)((float)(v3 * v3) + (float)(v4 * v4)) + (float)(v5 * v5)));
					float v7 = v4 / v6;
					float v8 = v3 / v6;
					float v9 = v5 / v6;
					float v10 = this->field_C;
					float f = this->level->random.nextFloat();
					float v12 = this->field_0;
					float v13 = this->field_4;
					float v14 = this->field_8;
					for(float i = v10 * (float)((float)(f * 0.6) + 0.7); i > 0.0; i = i - 0.225) {
						int x = Mth::floor(v12);
						int y = Mth::floor(v13);
						int z = Mth::floor(v14);
						int tile = this->level->getTile(x, y, z);
						if(tile <= 0 || (i = i - (float)((float)(Tile::tiles[tile]->getExplosionResistance(this->entity) + 0.3) * 0.3), i > 0.0)) {
							this->field_10.insert({x, y, z});
						}
						v12 = v12 + (float)(v7 * 0.3);
						v13 = v13 + (float)(v8 * 0.3);
						v14 = v14 + (float)(v9 * 0.3);
					}
				}
			}
		}
	}
	float v37 = this->field_C + this->field_C;
	float v38 = this->field_0;
	this->field_C = v37;
	int v39 = Mth::floor((float)(v38 - v37) - 1.0);
	int v40 = Mth::floor((float)(v38 + v37) + 1.0);
	float v41 = this->field_4;
	int v42 = v40;
	int v43 = Mth::floor((float)(v41 - v37) - 1.0);
	int v44 = Mth::floor((float)(v41 + v37) + 1.0);
	float v45 = this->field_8;
	int v46 = v44;
	int v47 = Mth::floor((float)(v45 - v37) - 1.0);
	int v48 = Mth::floor((float)(v45 + v37) + 1.0);

	std::vector<Entity*>* ents = this->level->getEntities(this->entity, AABB{(float)v39, (float)v43, (float)v47, (float)v42, (float)v46, (float)v48});
	Vec3 v77(this->field_0, this->field_4, this->field_8);
	for(int v52 = 0; v52 < ents->size(); ++v52) {
		Entity* e = (*ents)[v52];
		float v59 = e->distanceTo(this->field_0, this->field_4, this->field_8) / this->field_C;
		if(v59 <= 1.0) {
			float v60 = e->posX - this->field_0;
			float v61 = e->posY - this->field_4;
			float v62 = e->posZ - this->field_8;
			float v63 = (float)((float)(v61 * v61) + (float)(v60 * v60)) + (float)(v62 * v62);
			int s = 0x5F3759DF - (*((int*)&v63) >> 1);
			float v64 = *(float*)&s * (float)(1.5 - (float)((float)((float)(v63 * 0.5) * *(float*)&s) * *(float*)&s));
			float v65 = (float)(1.0 - v59) * this->level->getSeenPercent(v77, e->boundingBox);
			e->hurt(this->entity, (int)(float)((float)((float)((float)((float)(v65 + (float)(v65 * v65)) * 0.5) * 8.0) * this->field_C) + 1.0));
			e->motionX += (float)((float)(v60 * v64) * v65);
			e->motionY += (float)((float)(v61 * v64) * v65);
			e->motionZ += (float)((float)(v62 * v64) * v65);
		}
	}

	this->field_C = v1;
	if(this->field_30) {
		for(auto&& k: this->field_10) {
			int v68 = k.x;
			int v69 = k.y;
			int v70 = k.z;
			int v71 = this->level->getTile(v68, v69, v70);
			int v72 = this->level->getTile(v68, v69 - 1, v70);
			if(!v71 && Tile::solid[v72] && !(this->random.genrand_int32() % 3)) {
				this->level->setTileNoUpdate(v68, v69, v70, Tile::fire->blockID);
			}
		}
	}
}
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
			if(!this->level->isClient) {
				if(this->level->getLevelData()->getGameType() != 1) {
					Tile::tiles[id]->spawnResources(this->level, p.x, p.y, p.z, this->level->getData(p.x, p.y, p.z), 0.3);
				}
			}
			if(this->level->setTileNoUpdate(p.x, p.y, p.z, 0)) {
				this->level->updateNeighborsAt(p.x, p.y, p.z, 0);
			}
			this->level->setTileDirty(p.x, p.y, p.z);
			if(!this->level->isClient) {
				Tile::tiles[id]->wasExploded(this->level, p.x, p.y, p.z);
			}
		}
		++v38;
	}
}
