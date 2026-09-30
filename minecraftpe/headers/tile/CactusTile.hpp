#pragma once
#include <tile/Tile.hpp>
#include <entity/Entity.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

struct CactusTile : Tile{
	TextureUVCoordinateSet field_80, field_98, field_B0;

	CactusTile(int32_t id) :
			Tile(id, Material::cactus) {
		TextureAtlasTextureItem* ti = this->getTextureItem("cactus");
		this->field_80 = *ti->getUV(0);
		this->field_98 = *ti->getUV(1);
		this->field_B0 = *ti->getUV(2);
		this->setTicking(1);
	}

	virtual ~CactusTile() {
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 13;
	}
	virtual TextureUVCoordinateSet* getTexture(int32_t a2) {
		if (a2 == 1) return &this->field_80;

		if (a2) return &this->field_98;

		return &this->field_B0;
	}
	virtual AABB* getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
		this->aabb.minX = x + 0.0625f;
		this->aabb.minY = y;
		this->aabb.minZ = z + 0.0625f;
		this->aabb.maxX = (x + 1) - 0.0625f;
		this->aabb.maxY = (y + 1) - 0.0625f;
		this->aabb.maxZ = (z + 1) - 0.0625f;
		return &this->aabb;
	}
	virtual AABB getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
		return AABB { (float) (x) + 0.0625f, (float) (y), (float) (z) + 0.0625f, (float) ((x + 1)) - 0.0625f, (float) (y) + 1.0f, (float) ((z + 1)) - 0.0625f };
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		if (Tile::mayPlace(level, x, y, z)) {
			return this->canSurvive(level, x, y, z);
		}
		return 0;
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random* a6) {
		int32_t aboveY = y + 1;
		if (level->isEmptyTile(x, y + 1, z)) {
			int32_t i;
			for (i = 1; level->getTile(x, y - i, z) == this->blockID; ++i) {
			}
			if (i <= 2) {
				int32_t meta = level->getData(x, y, z);
				int32_t za;
				if (meta <= 9) za = meta + 1;
				else {
					level->setTile(x, aboveY, z, this->blockID, 3);
					za = 0;
				}
				level->setData(x, y, z, za, 4);
			}
		}
	}
	virtual void neighborChanged(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
		if (!this->canSurvive(a2, a3, a4, a5)) {
			this->spawnResources(a2, a3, a4, a5, a2->getData(a3, a4, a5), 1.0);
			a2->setTile(a3, a4, a5, 0, 3);
		}
	}
	virtual int32_t getRenderLayer() {
		if (this->goodGraphics) return 3;

		return 1;
	}
	virtual void entityInside(Level* level, int32_t x, int32_t y, int32_t z, Entity* ent) {
		ent->hurt(0, 1);
	}
	virtual bool_t canSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
		if (level->getMaterial(x - 1, y, z)->isSolid()) return 0;

		if (level->getMaterial(x + 1, y, z)->isSolid()) return 0;

		if (level->getMaterial(x, y, z - 1)->isSolid()) return 0;

		if (level->getMaterial(x, y, z + 1)->isSolid()) return 0;

		int32_t bid = level->getTile(x, y - 1, z);
		return bid == Tile::cactus->blockID || bid == Tile::sand->blockID;
	}
};
