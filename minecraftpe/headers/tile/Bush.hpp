#pragma once
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>

struct Bush : Tile{

	Bush(int32_t a2, const std::string& a3, Material* mat) :
			Tile(a2, a3, mat) {
		this->setTicking(1);
		this->setShape(0.3, 0, 0.3, 0.7, 0.6, 0.7);
	}
	Bush(int32_t a2, const std::string& a3) :
			Bush(a2, a3, Material::plant) {
	}
	bool_t checkAlive(Level* level, int32_t x, int32_t y, int32_t z) {
		if(this->canSurvive(level, x, y, z)) return 1;
		this->spawnResources(level, x, y, z, level->getData(x, y, z));
		return level->setTile(x, y, z, 0, 3);
	}
	virtual ~Bush() {
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 1;
	}
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t) {
		return 0;
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t) {
		return this->mayPlaceOn(level->getTile(x, y - 1, z));
	}
	virtual void tick(Level* a2, int32_t a3, int32_t a4, int32_t a5, Random*) {
		this->checkAlive(a2, a3, a4, a5);
	}
	virtual void neighborChanged(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9) {
		Tile::neighborChanged(a2, a3, a4, a5, a6, a7, a8, a9);
		this->checkAlive(a2, a3, a4, a5);
	}
	virtual int32_t getRenderLayer() {
		return 1;
	}
	virtual bool_t canSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
		if(level->getRawBrightness(x, y, z) <= 7 || !level->canSeeSky(x, y, z)) return 0;

		return this->mayPlaceOn(level->getTile(x, y - 1, z));
	}
	virtual bool_t mayPlaceOn(int32_t a2) {
		return a2 == Tile::grass->blockID || a2 == Tile::dirt->blockID || a2 == Tile::farmland->blockID;
	}
};
