#pragma once
#include <tile/Tile.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <entity/ItemEntity.hpp>
#include <level/LightLayer.hpp>

struct TopSnowTile : Tile{
	TopSnowTile(int32_t id, const std::string& name, Material* mat) :
			Tile(id, name, mat) {
		this->setShape(0, 0, 0, 1, 0.125, 1);
		this->setTicking(1);
		this->replaceable = 1;
		this->field_5C = 255;
	}
	bool_t checkCanSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t v10; // r0
		if (this->mayPlace(level, x, y, z)) return 1;

		v10 = level->getData(x, y, z);
		this->spawnResources(level, x, y, z, v10);
		level->setTile(x, y, z, 0, 3);
		return 0;
	}


	virtual ~TopSnowTile() {
	}
	virtual int32_t getTileType() {
		return 4;
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual bool_t shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t face) {
		Material* mat; // r0
		mat = level->getMaterial(x, y, z);
		if (face == 1) {
			return 1;
		}
		if (mat == this->material) {
			return 0;
		}
		return Tile::shouldRenderFace(level, x, y, z, face);
	}
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		int32_t yb; // r6
		int32_t id; // r0
		Material* mat; // r0
		yb = y - 1;
		id = level->getTile(x, y - 1, z);
		if (!id || !Tile::tiles[id]->isSolidRender()) {
			return 0;
		}
		mat = level->getMaterial(x, yb, z);
		return mat->blocksMotion();
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random* random) {
		int32_t v11; // r0
		if (level->getBrightness(LightLayer::Block, x, y, z) > 11) {
			v11 = level->getData(x, y, z);
			this->spawnResources(level, x, y, z, v11);
			level->setTile(x, y, z, 0, 3);
		}
	}
	virtual void neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t, int32_t, int32_t, int32_t) {
		this->checkCanSurvive(level, x, y, z);
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Item::snowBall->itemID;
	}
	virtual int32_t getResourceCount(Random*) {
		return 0;
	}
	virtual float getThickness() {
		return 0.13;
	}
	virtual void playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t a7) {
		Random* p_random; // r6
		int32_t itemID; // r9
		float f; // s18
		float f1; // s17
		float f2; // s16
		ItemEntity* v15; // r6
		if (!level->isClient) {
			p_random = &level->random;
			itemID = Item::snowBall->itemID;
			f = p_random->nextFloat();
			f1 = p_random->nextFloat();
			f2 = p_random->nextFloat();
			v15 = new ItemEntity(level, (float) (x) + (float) (((float) ((f * 0.7)) + 0.15)), (float) (y) + (float) (((float) ((f1 * 0.7)) + 0.15)), (float) (z) + (float) (((float) ((f2 * 0.7)) + 0.15)), ItemInstance(itemID, 1, 0));
			v15->delayBeforePickup = 10;
			level->addEntity(v15);
			level->setTile(x, y, z, 0, 3);
		}
	}

};
