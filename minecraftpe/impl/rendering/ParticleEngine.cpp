#include <rendering/ParticleEngine.hpp>
#include <entity/particles/Particle.hpp>
#include <entity/particles/BubbleParticle.hpp>
#include <entity/particles/CritParticle2.hpp>
#include <entity/particles/SmokeParticle.hpp>
#include <entity/particles/ExplodeParticle.hpp>
#include <entity/particles/FlameParticle.hpp>
#include <entity/particles/LavaParticle.hpp>
#include <entity/particles/RedDustParticle.hpp>
#include <entity/particles/BreakingItemParticle.hpp>
#include <entity/particles/MobFlameParticle.hpp>
#include <entity/particles/TerrainParticle.hpp>
#include <entity/particles/HeartParticle.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
#include <item/Item.hpp>
#include <math/Mth.hpp>
#include <unigl.hpp>
#include <entity/Mob.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>
#include <sstream>

ParticleEngine::ParticleEngine(Level* a2, Textures* a3) : level(a2), textures(a3){
	a3->loadTexture("particles.png", 1, 0);
}
Particle* ParticleEngine::_get(ParticleType a2) {
	if(this->particlesToReuse[a2].empty()) return 0;
	Particle* p = this->particlesToReuse[a2].top();
	this->particlesToReuse[a2].pop();
	return p;
}
void ParticleEngine::_release(Particle* a2) {
	std::stack<Particle*>* deq = &this->particlesToReuse[a2->type];
	deq->push(a2);
}
void ParticleEngine::clear() {
	for(auto& p: this->string2ParticleVec) {
		for(int32_t i = 0; i < p.second.size(); ++i) {
			delete p.second[i];
		}
		p.second.clear();
	}
	for(auto& pd: this->particlesToReuse) {
		while(!pd.empty()) {
			Particle* p = pd.top();
			if(p) delete p;
			pd.pop();
		}
	}
}
std::string ParticleEngine::countParticles() { //TODO check return type
	std::stringstream ss;
	int32_t v5 = 0;
	for(auto& p: this->string2ParticleVec) {
		v5 += p.second.size();
	}
	ss << v5;
	return ss.str();
}
void ParticleEngine::crack(int32_t x, int32_t y, int32_t z, int32_t a5) {
	int id = this->level->getTile(x, y, z);
	if(id) {
		int data = this->level->getData(x, y, z);
		Tile* tile = Tile::tiles[id];
		float xx = x + (this->random.nextFloat() * (tile->maxX - tile->minX - 0.2f)) + 0.1f + tile->minX;
		float yy = y + (this->random.nextFloat() * (tile->maxY - tile->minY - 0.2f)) + 0.1f + tile->minY;
		float zz = z + (this->random.nextFloat() * (tile->maxZ - tile->minZ - 0.2f)) + 0.1f + tile->minZ;
		switch(a5) {
			case 0:
				yy = (y + tile->minY) - 0.1f;
				break;
			case 1:
				yy = (y + tile->maxY) + 0.1f;
				break;
			case 2:
				zz = (z + tile->minZ) - 0.1f;
				break;
			case 3:
				zz = (z + tile->maxZ) + 0.1f;
				break;
			case 4:
				xx = (x + tile->minX) - 0.1f;
				break;
			case 5:
				xx = (x + tile->maxX) + 0.1f;
				break;
			default:
				break;
		}
		Particle* pt = this->instance(PT_TERRAIN, xx, yy, zz, 0.0, 0.0, 0.0, tile->blockID | (data << 16));
		pt->setPower(0.2)->scale(0.6f);
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
	int id = this->level->getTile(x, y, z);
	if(id) {
		int meta = this->level->getData(x, y, z);
		Tile* tile = Tile::tiles[id];
		for(int xo = 0; xo != 3; ++xo) {
			for(int yo = 1; yo != 3; ++yo) {
				for(int zo = 0; zo != 3; ++zo) {
					float xx = x + ((xo + 0.5f) / 3.0f);
					float yy = y + ((yo + 0.5f) / 3.0f);
					float zz = z + ((zo + 0.5f) / 3.0f);
					this->instance(PT_TERRAIN, xx, yy, zz, ((xx - x) - 0.5f) * 2, ((yy - y) - 0.5f) * 2, ((zz - z) - 0.5f) * 2, (meta << 16) | tile->blockID);
				}
			}
		}
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
		this->string2ParticleVec[v16->textureAtlas].push_back(v16);
	}
	return v16;
}
void ParticleEngine::render(Entity* a2, float a3) {
	Particle::playerViewDir = ((Mob*)a2)->getViewVector(a3);

	float v8 = Mth::cos((Mth::PI * a2->yaw) / 180.0f);
	float v9 = Mth::sin((Mth::PI * a2->yaw) / 180.0f);

	float v11 = -v9 * Mth::sin((Mth::PI * a2->pitch) / 180.0f);
	float v12 = v8 * Mth::sin((Mth::PI * a2->pitch) / 180.0f);
	float v14 = Mth::cos((Mth::PI * a2->pitch) / 180.0f);

	Particle::xOff = a2->prevPosX + (a2->posX - a2->prevPosX) * a3;
	Particle::yOff = a2->prevPosY + (a2->posY - a2->prevPosY) * a3;
	Particle::zOff = a2->prevPosZ + (a2->posZ - a2->prevPosZ) * a3;
	glEnable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	for(auto& p: this->string2ParticleVec) {
		if(!p.second.empty()) {
			this->textures->loadAndBindTexture(p.first);
			Tesselator::instance.begin(p.second.size() & 0xFFFFFFFC); //TODO ????
			for(int32_t i = 0; i < p.second.size(); ++i) {
				Particle* v19 = p.second[i];
				v19->render(Tesselator::instance, a3, v8, v14, v9, v11, v12);
			}
			Tesselator::instance.draw(1);
		}
	}
	glEnable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
}
void ParticleEngine::setLevel(Level* a2) {
	this->level = a2;
	this->clear();
}
void ParticleEngine::tick() {
	for(auto&& p: this->string2ParticleVec) {
		uint32_t sz = p.second.size();
		for(uint32_t i = 0; i < sz; ++i) {
			Particle* prt = p.second[i];
			prt->tick();
			if(prt->isDead) {
				p.second.erase(p.second.begin()+i);
				--i;
				--sz;
				this->_release(prt);
			}
		}
	}
}
ParticleEngine::~ParticleEngine() {
	this->clear();
}
