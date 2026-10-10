#include <level/Explosion.hpp>
#include <entity/Entity.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <math/Vec3.hpp>
#include <tile/Tile.hpp>

Explosion::Explosion(Level* a2, Entity* a3, float a4, float a5, float a6, float a7) {
	this->x = a4;
	this->y = a5;
	this->field_28 = 0;
	this->z = a6;
	this->field_2C = 0;
	this->radius = a7;
	this->field_28 = 0;
	this->setFire = 0;
	this->entity = a3;
	this->level = a2;
}
void Explosion::explode() {
	int v1 = this->radius;
	for(int xx = 0; xx != 16; ++xx) {
		for(int yy = 0; yy != 16; ++yy) {
			for(int zz = 0; zz != 16; ++zz) {
				if(xx == 0 || xx == 15 || yy == 0 || yy == 15 || zz == 0 || zz == 15) {
					float v3 = (yy / 15.0f) * 2 - 1.0f;
					float v4 = (xx / 15.0f) * 2 - 1.0f;
					float v5 = (zz / 15.0f) * 2 - 1.0f;
					float v6 = sqrt((v3 * v3) + (v4 * v4) + (v5 * v5));
					float v7 = v4 / v6;
					float v8 = v3 / v6;
					float v9 = v5 / v6;
					float v10 = this->radius;
					float f = this->level->random.nextFloat();
					float xc = this->x;
					float yc = this->y;
					float zc = this->z;
					for(float i = v10 * (float)((float)(f * 0.6f) + 0.7f); i > 0.0f; i = i - 0.225f) {
						int x = Mth::floor(xc);
						int y = Mth::floor(yc);
						int z = Mth::floor(zc);
						int tile = this->level->getTile(x, y, z);
						if(tile <= 0 || (i = i - ((Tile::tiles[tile]->getExplosionResistance(this->entity) + 0.3f) * 0.3f), i > 0.0f)) {
							this->affectedTiles.insert({x, y, z});
						}
						xc += v7 * 0.3f;
						yc += v8 * 0.3f;
						zc += v9 * 0.3f;
					}
				}
			}
		}
	}
	float rad = this->radius + this->radius;
	this->radius = rad;
	int minX = Mth::floor((float)(this->x - rad) - 1.0f);
	int maxX = Mth::floor((float)(this->x + rad) + 1.0f);
	int minY = Mth::floor((float)(this->y - rad) - 1.0f);
	int maxY = Mth::floor((float)(this->y + rad) + 1.0f);
	int minZ = Mth::floor((float)(this->z - rad) - 1.0f);
	int maxZ = Mth::floor((float)(this->z + rad) + 1.0f);

	std::vector<Entity*>* ents = this->level->getEntities(this->entity, AABB{(float)minX, (float)minY, (float)minZ, (float)maxX, (float)maxY, (float)maxZ});
	Vec3 v77(this->x, this->y, this->z);
	for(int v52 = 0; v52 < ents->size(); ++v52) {
		Entity* e = (*ents)[v52];
		float v59 = e->distanceTo(this->x, this->y, this->z) / this->radius;
		if(v59 <= 1.0f) {
			float dx = e->posX - this->x;
			float dy = e->posY - this->y;
			float dz = e->posZ - this->z;
			float dist = (dx * dx) + (dy * dy) + (dz * dz);
			float v64 = Mth::rsqrt(dist);
			//int s = 0x5F3759DF - (*((int*)&dist) >> 1);
			//*(float*)&s*(float)(1.5f - (float)((float)((float)(dist * 0.5f) * *(float*)&s) * *(float*)&s));
			float v65 = (float)(1.0f - v59) * this->level->getSeenPercent(v77, e->boundingBox);
			e->hurt(this->entity, (int)(((v65 + (v65 * v65)) * 0.5f * 8.0f * this->radius) + 1.0f));
			e->motionX += (dx * v64) * v65;
			e->motionY += (dy * v64) * v65;
			e->motionZ += (dz * v64) * v65;
		}
	}

	this->radius = v1;
	if(this->setFire) {
		for(auto&& k: this->affectedTiles) {
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
	this->level->playSound(this->x, this->y, this->z, "random.explode", 4.0f, (float)((float)((float)(this->level->random.nextFloat() - this->level->random.nextFloat()) * 0.2f) + 1.0f) * 0.7f);
	int32_t v38 = 0;
	for(auto p: this->affectedTiles) {
		int32_t id = this->level->getTile(p.x, p.y, p.z);
		if((v38 & 7) == 0) {
			float v13 = (float)p.x + this->level->random.nextFloat();
			float v14 = (float)p.y + this->level->random.nextFloat();
			float v18 = (float)p.z + this->level->random.nextFloat();
			float v16 = v14 - this->y;
			float v17 = v13 - this->x;
			float v19 = v18 - this->z;
			float v20 = sqrt((float)((float)((float)(v16 * v16) + (float)(v17 * v17)) + (float)(v19 * v19)));
			float v21 = 1.0f / v20;
			float v22 = v17 * v21;
			float v23 = v16 * v21;
			float v24 = v19 * v21;
			float v25 = this->radius / v21;
			float v27 = (float)(0.5f / (float)(v25 + 0.1f)) * (float)((float)(this->level->random.nextFloat() * this->level->random.nextFloat()) + 0.3f);
			float v28 = v22 * v27;
			float v29 = v23 * v27;
			float v30 = v24 * v27;
			this->level->addParticle(PT_EXPLODE, (float)(v13 + this->x) * 0.5f, (float)(v14 + this->y) * 0.5f, (float)(v18 + this->z) * 0.5f, v28, v29, v30, 0);
			this->level->addParticle(PT_SMOKE, v13, v14, v18, v28, v29, v30, 0);
		}
		if(id) {
			if(!this->level->isClient) {
				if(this->level->getLevelData()->getGameType() != 1) {
					Tile::tiles[id]->spawnResources(this->level, p.x, p.y, p.z, this->level->getData(p.x, p.y, p.z), 0.3f);
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
