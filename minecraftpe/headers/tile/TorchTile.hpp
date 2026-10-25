#pragma once
#include <tile/Tile.hpp>
#include <level/Level.hpp>
#include <math/HitResult.hpp>

struct TorchTile : Tile{
	bool_t isConnection(Level* level, int32_t x, int32_t y, int32_t z) {
		if (level->isSolidBlockingTile(x, y, z)) {
			return 1;
		}
		int id = level->getTile(x, y, z);
		return id == Tile::fence->blockID || id == Tile::glass->blockID || id == Tile::cobbleWall->blockID;
	}
	bool_t checkCanSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t v10; // r0
		if (this->mayPlace(level, x, y, z)) {
			return 1;
		}
		if (level->getTile(x, y, z) == this->blockID) {
			v10 = level->getData(x, y, z);
			this->spawnResources(level, x, y, z, v10);
			level->setTile(x, y, z, 0, 3);
		}
		return 0;
	}

	TorchTile(int32_t id, const std::string& s, Material* m) :
			Tile(id, s, m) {
		this->setTicking(1);
	}
	virtual ~TorchTile() {
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 2;
	}
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		return level->isSolidBlockingTile(x - 1, y, z) || level->isSolidBlockingTile(x + 1, y, z) || level->isSolidBlockingTile(x, y, z - 1) || level->isSolidBlockingTile(x, y, z + 1) || this->isConnection(level, x, y - 1, z);
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random*) {
		if (!level->getData(x, y, z)) {
			this->onPlace(level, x, y, z);
		}
	}
	virtual void animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random* r) {
		int meta = level->getData(x, y, z);
		float yy = y + 0.7f;
		float xx = x + 0.5f;
		float zz = z + 0.5f;

		if(meta == 1) {
			level->addParticle(PT_SMOKE, xx - 0.27f, yy + 0.22f, zz, 0, 0, 0, 0);
			level->addParticle(PT_FLAME, xx - 0.27f, yy + 0.22f, zz, 0, 0, 0, 0);
		} else if(meta == 2) {
			level->addParticle(PT_SMOKE, xx + 0.27f, yy + 0.22f, zz, 0, 0, 0, 0);
			level->addParticle(PT_FLAME, xx + 0.27f, yy + 0.22f, zz, 0, 0, 0, 0);
		} else if(meta == 3) {
			level->addParticle(PT_SMOKE, xx, yy + 0.22f, zz - 0.27f, 0, 0, 0, 0);
			level->addParticle(PT_FLAME, xx, yy + 0.22f, zz - 0.27f, 0, 0, 0, 0);
		} else if(meta == 4) {
			level->addParticle(PT_SMOKE, xx, yy + 0.22f, zz + 0.27f, 0, 0, 0, 0);
			level->addParticle(PT_FLAME, xx, yy + 0.22f, zz + 0.27f, 0, 0, 0, 0);
		}else{
			level->addParticle(PT_SMOKE, xx, yy, zz, 0, 0, 0, 0);
			level->addParticle(PT_FLAME, xx, yy, zz, 0, 0, 0, 0);
		}


	}
	virtual void neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
		int32_t data; // r9
		bool_t v14; // r8
		int32_t v16; // r0
		if (this->checkCanSurvive(level, x, y, z)) {
			data = level->getData(x, y, z);
			if (level->isSolidBlockingTile(x - 1, y, z)) {
				v14 = 0;
			} else {
				v14 = data == 1;
			}
			if (!level->isSolidBlockingTile(x + 1, y, z) && data == 2) {
				v14 = 1;
			}
			if (!level->isSolidBlockingTile(x, y, z - 1) && data == 3) {
				v14 = 1;
			}
			if (!level->isSolidBlockingTile(x, y, z + 1) && data == 4) {
				v14 = 1;
			}
			if (!this->isConnection(level, x, y - 1, z) && data == 5 || v14) {
				v16 = level->getData(x, y, z);
				this->spawnResources(level, x, y, z, v16);
				level->setTile(x, y, z, 0, 3);
			}
		}
	}
	virtual void onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		if (level->getData(x, y, z) == 0) {
			if (level->isSolidBlockingTile(x - 1, y, z)) {
				level->setData(x, y, z, 1, 2);
			}else if (level->isSolidBlockingTile(x + 1, y, z)) {
				level->setData(x, y, z, 2, 2);
			} else if (level->isSolidBlockingTile(x, y, z - 1)) {
				level->setData(x, y, z, 3, 2);
			}else if (level->isSolidBlockingTile(x, y, z + 1)) {
				level->setData(x, y, z, 4, 2);
			}else if (this->isConnection(level, x, y - 1, z)) {
				level->setData(x, y, z, 5, 2);
			}
		}
		this->checkCanSurvive(level, x, y, z);
	}
	virtual HitResult clip(Level* level, int32_t x, int32_t y, int32_t z, const Vec3& a7, const Vec3& a8) {
		int v14 = level->getData(x, y, z) & 7;


		if(v14 == 1) this->setShape(0.0f, 0.2f, 0.35f, 0.3f, 0.8f, 0.65f);
		else if(v14 == 2) this->setShape(0.7f, 0.2f, 0.35f, 1.0f, 0.8f, 0.65f);
		else if(v14 == 3) this->setShape(0.35f, 0.2f, 0.0f, 0.65f, 0.8f, 0.3f);
		else if(v14 == 4) this->setShape(0.35f, 0.2f, 0.7f, 0.65f, 0.8f, 1.0f);
		else this->setShape(0.4f, 0.0f, 0.4f, 0.6f, 0.6f, 0.6f);

		return Tile::clip(level, x, y, z, a7, a8);
	}
	virtual int32_t getRenderLayer() {
		return 0;
	}
	virtual int32_t getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float, float, float, Mob*, int32_t a11) {
		if(a6 == 1 && this->isConnection(level, x, y - 1, z)) return 5;
		if(a6 == 2 && level->isSolidBlockingTile(x, y, z + 1)) return 4;
		if(a6 == 3 && level->isSolidBlockingTile(x, y, z - 1)) return 3;
		if(a6 == 4 && level->isSolidBlockingTile(x + 1, y, z)) return 2;
		if(a6 == 5 && level->isSolidBlockingTile(x - 1, y, z)) return 1;

		return a11;
	}
};
