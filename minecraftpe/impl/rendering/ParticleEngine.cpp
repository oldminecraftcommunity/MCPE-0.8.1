#include <rendering/ParticleEngine.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
#include <entity/particles/Particle.hpp>
#include <entity/particles/BubbleParticle.hpp>
#include <entity/particles/CritParticle2.hpp>
#include <entity/particles/SmokeParticle.hpp>
#include <entity/particles/ExplodeParticle.hpp>
#include <entity/particles/FlameParticle.hpp>
#include <entity/particles/LavaParticle.hpp>
#include <entity/particles/RedDustParticle.hpp>
#include <entity/particles/BreakingItemParticle.hpp>
#include <item/Item.hpp>
#include <entity/particles/MobFlameParticle.hpp>
#include <entity/particles/HeartParticle.hpp>
#include <entity/particles/TerrainParticle.hpp>
#include <math/Mth.hpp>
#include <GL/gl.h>
#include <entity/Mob.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>
#include <algorithm>

ParticleEngine::ParticleEngine(Level* a2, Textures* a3) {
	this->level = a2;
	this->textures = a3;
	a3->loadTexture("particles.png", 1, 0);
}
Particle* ParticleEngine::_get(ParticleType a2) {
	if(this->particles[a2].empty()) return 0;
	Particle* p = this->particles[a2].back();
	this->particles[a2].pop_back();
	return p;
}
void ParticleEngine::_release(Particle* a2) {
	 //TODO check
	auto&& p = std::find(this->particles[a2->type].begin(), this->particles[a2->type].end(), a2);
	if(p != this->particles[a2->type].end()) {
		this->particles[a2->type].erase(p);
	}
}
void ParticleEngine::clear() {
	for(auto& p: this->string2ParticleVec) {
		for(int32_t i = 0; i < p.second.size(); ++i) {
			delete p.second[i];
		}
		p.second.clear();
	}
	for(auto& pd: this->particles) {
		while(!pd.empty()) {
			Particle* p = pd.back();
			if(p) delete p;
			pd.pop_back();
		}
	}
}
std::string ParticleEngine::countParticles() { //TODO check return type
	int32_t v5 = 0;
	for(auto& p: this->string2ParticleVec) {
		v5 += p.second.size();
	}
	return std::to_string(v5);
}
void ParticleEngine::crack(int32_t x, int32_t y, int32_t z, int32_t a5) {
	int32_t v9; // r6
	int32_t v10; // r0
	float v11; // s19
	Tile* v12; // r4
	int32_t v13; // r11
	float v14; // s18
	float v15; // s21
	float v16; // s17
	float v17; // s20
	float f; // r0
	float minZ; // s13
	float maxZ; // s12
	float v21; // s14
	Particle* v22; // r0

	v9 = this->level->getTile(x, y, z);
	if(v9) {
		v10 = this->level->getData(x, y, z);
		v11 = (float)x;
		v12 = Tile::tiles[v9];
		v13 = v10;
		v14 = (float)((float)((float)x + (float)(this->random.nextFloat() * (float)((float)(v12->maxX - v12->minX) - 0.2))) + 0.1) + v12->minX;
		v15 = (float)y;
		v16 = (float)((float)((float)y + (float)(this->random.nextFloat() * (float)((float)(v12->maxY - v12->minY) - 0.2))) + 0.1) + v12->minY;
		v17 = (float)z;
		f = this->random.nextFloat();
		minZ = v12->minZ;
		maxZ = v12->maxZ;
		v21 = (float)((float)((float)z + (float)(f * (float)((float)(maxZ - minZ) - 0.2))) + 0.1) + minZ;
		switch(a5) {
			case 0:
				v16 = (float)(v15 + v12->minY) - 0.1;
				break;
			case 1:
				v16 = (float)(v15 + v12->maxY) + 0.1;
				break;
			case 2:
				v21 = (float)(v17 + minZ) - 0.1;
				break;
			case 3:
				v21 = (float)(v17 + maxZ) + 0.1;
				break;
			case 4:
				v14 = (float)(v11 + v12->minX) - 0.1;
				break;
			case 5:
				v14 = (float)(v11 + v12->maxX) + 0.1;
				break;
			default:
				break;
		}
		v22 = this->instance(PT_TERRAIN, v14, v16, v21, 0.0, 0.0, 0.0, v12->blockID | (v13 << 16));
		v22->setPower(0.2)->scale(0.6);
	}
}
Particle* ParticleEngine::create(ParticleType a2) {
	switch(a2) {
		case PT_BUBBLE:
			return new BubbleParticle(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_CRIT:
			return new CritParticle2(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_SMOKE:
			return new SmokeParticle(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_EXPLODE:
			return new ExplodeParticle(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_FLAME:
			return new FlameParticle(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_LAVA:
			return new LavaParticle(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_RED_DUST:
			return new RedDustParticle(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_BREAKING_ITEM_1:
			return new BreakingItemParticle(this->level, a2, Particle::PARTICLE_ATLAS, 0);
		case PT_BREAKING_ITEM_2:
			return new BreakingItemParticle(this->level, a2, Particle::PARTICLE_ATLAS, Item::snowBall);
		case PT_MOB_FLAME:
			return new MobFlameParticle(this->level, a2, MobFlameParticle::FLAME_ATLAS);
		case PT_HEART:
			return new HeartParticle(this->level, a2, Particle::PARTICLE_ATLAS);
		case PT_TERRAIN:
			return new TerrainParticle(this->level, a2, Particle::TERRAIN_ATLAS);
		default:
			return 0;
	}
}
void ParticleEngine::destroy(int32_t x, int32_t y, int32_t z) {
	int32_t id; // r5
	int32_t meta; // r0
	Tile* v10; // r11
	int32_t v11; // r5
	int32_t v12; // r8
	float v13; // s13
	int32_t v14; // r6
	int32_t v15; // r4
	float v16; // s14
	float v17; // s21
	float v18; // s18
	float v19; // s19

	id = this->level->getTile(x, y, z);
	if(id) {
		meta = this->level->getData(x, y, z);
		v10 = Tile::tiles[id];
		v11 = 0;
		v12 = meta << 16;
		do {
			v15 = 1;
			v19 = (float)y;
			do {
				v14 = 0;
				do {
					v13 = (float)v14++;
					v18 = (float)z;
					v17 = (float)x + (float)((float)((float)v11 + 0.5) / 3.0);
					v16 = (float)((float)(v19 + (float)((float)((float)v15 + 0.5) / 3.0)) - v19) - 0.5;
					this->instance(PT_TERRAIN, v17, v19 + (float)((float)((float)v15 + 0.5) / 3.0), v18 + (float)((float)(v13 + 0.5) / 3.0), (float)((float)(v17 - (float)x) - 0.5) + (float)((float)(v17 - (float)x) - 0.5), v16 + v16, (float)((float)((float)(v18 + (float)((float)(v13 + 0.5) / 3.0)) - v18) - 0.5) + (float)((float)((float)(v18 + (float)((float)(v13 + 0.5) / 3.0)) - v18) - 0.5), v12 | v10->blockID);
				} while(v14 != 3);
				++v15;
			} while(v15 != 3);
			++v11;
		} while(v11 != 3);
	}
}
Particle* ParticleEngine::instance(ParticleType a2, float a3, float a4, float a5, float a6, float a7, float a8, int32_t a9) {
	Particle* v16; // [sp+14h] [bp-1Ch] BYREF

	v16 = this->_get(a2);
	if(!v16) {
		v16 = this->create(a2);
	}
	if(v16) {
		v16->_init(a3, a4, a5, a6, a7, a8, a9);
		this->string2ParticleVec[v16->textureAtlas].emplace_back(v16);
	}
	return v16;
}
void ParticleEngine::render(Entity* a2, float a3) {
	float yaw; // s11
	float v7; // s11
	float v8; // s17
	float v9; // s18
	float v10; // s14
	float v11; // s13
	float posY; // s14
	float v14; // r9
	float v15; // s15
	float posZ; // s14

	Vec3 v21 = ((Mob*)a2)->getViewVector(a3);
	yaw = a2->yaw;
	Particle::playerViewDir = v21;
	v7 = (float)((float)(3.1416 * yaw) / 180.0);
	v8 = Mth::cos(v7);
	v9 = Mth::sin(v7);
	v10 = (float)((float)(3.1416 * a2->pitch) / 180.0);
	v11 = Mth::sin(v10);
	posY = a2->posY;
	v14 = Mth::cos(v10);
	Particle::xOff = a2->prevPosX + (float)((float)(a2->posX - a2->prevPosX) * a3);
	v15 = a2->prevPosY + (float)((float)(posY - a2->prevPosY) * a3);
	posZ = a2->posZ;
	Particle::yOff = v15;
	Particle::zOff = a2->prevPosZ + (float)((float)(posZ - a2->prevPosZ) * a3);
	glEnable(0xBC0u);
	glDisable(0xBE2u);
	for(auto& p: this->string2ParticleVec) {
		if(!p.second.empty()) {
			this->textures->loadAndBindTexture(p.first);
			Tesselator::instance.begin(p.second.size() & 0xFFFFFFFC); //TODO ????
			for(int32_t i = 0; i < p.second.size(); ++i) {
				Particle* v19 = p.second[i];
				v19->render(Tesselator::instance, a3, v8, v14, v9, -(float)(v9 * v11), v8 * v11);
			}
			Tesselator::instance.draw(1);
		}
	}
	glEnable(0xBE2u);
	glDisable(0xBC0u);
}
void ParticleEngine::setLevel(Level* a2) {
	this->level = a2;
	this->clear();
}
void ParticleEngine::tick() {
	for(auto& p: this->string2ParticleVec) {
		for(int32_t i = 0; i < p.second.size(); ++i) {
			Particle* prt = p.second[i];
			prt->tick();
			if(prt->isDead) {
				p.second.erase(p.second.begin() + i);
				--i;
				this->_release(prt);
			}
		}
	}
}
ParticleEngine::~ParticleEngine() {
	this->clear();
}
