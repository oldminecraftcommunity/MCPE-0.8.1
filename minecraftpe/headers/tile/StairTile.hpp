#pragma once
#include <tile/Tile.hpp>
#include <level/Level.hpp>

struct StairTile : Tile{
	Tile* block;
	int8_t field_84;
	int32_t field_88, meta;
	static const  int DEAD_SPACES[8][2];
	StairTile(int32_t a2, Tile* a3, int32_t a4) :
			Tile(a2, a3->material) {
		this->block = a3;
		this->meta = a4;
		this->field_84 = 0;
		this->field_88 = 0;
		this->setDestroyTime(a3->blockHardness);
		this->setExplodeable(a3->blockResistance / 3.0);
		this->setSoundType(*a3->soundType);
		this->setLightBlock(255);
		this->field_5C = a3->field_5C;
	}
	static bool_t isLockAttached(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
		int32_t v9; // r0
		v9 = level->getTile(x, y, z);
		return StairTile::isStairs(v9) && level->getData(x, y, z) == a6;
	}
	static bool_t isStairs(int32_t id) {
		return id > 0 && Tile::tiles[id]->getRenderShape() == 10;
	}
	void setBaseShape(LevelSource* level, int32_t x, int32_t y, int32_t z) {
		int32_t v6; // r0
		v6 = level->getData(x, y, z); //lobyte = ...
		if ((v6 & 4) != 0) {
			this->setShape(0.0, 0.5, 0.0, 1.0, 1.0, 1.0);
		} else {
			this->setShape(0.0, 0.0, 0.0, 1.0, 0.5, 1.0);
		}
	}
	bool_t setInnerPieceShape(LevelSource*, int32_t, int32_t, int32_t);
	bool_t setStepShape(LevelSource*, int32_t, int32_t, int32_t);

	virtual ~StairTile() {
	}
	virtual int32_t getTileType() {
		return 1;
	}
	virtual bool_t isCubeShaped() {
		return 0;
	}
	virtual int32_t getRenderShape() {
		return 10;
	}
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t) {
		int v5; // r1
		if (this->field_84) {
			v5 = this->field_88;
			this->setShape((float) ((v5 % 2)) * 0.5, (float) ((v5 / 2 % 2)) * 0.5, (float) ((v5 / 4 % 2)) * 0.5, (float) (((float) ((v5 % 2)) * 0.5)) + 0.5, (float) (((float) ((v5 / 2 % 2)) * 0.5)) + 0.5, (float) (((float) ((v5 / 4 % 2)) * 0.5)) + 0.5);
		} else {
			this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
		}
	}
	virtual void addLights(Level* level, int32_t x, int32_t y, int32_t z) {
		this->block->addLights(level, x, y, z);
	}
	virtual float getBrightness(LevelSource* level, int32_t x, int32_t y, int32_t z) {
		return this->block->getBrightness(level, x, y, z);
	}
	const virtual TextureUVCoordinateSet* getTexture(int32_t a2) {
		return this->block->getTexture(a2, this->meta);
	}
	const virtual TextureUVCoordinateSet* getTexture(int32_t a2, int32_t) {
		return this->block->getTexture(a2, this->meta);
	}
	const virtual TextureUVCoordinateSet* getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t a6) {
		return this->block->getTexture(a6, this->meta);
	}
	virtual void addAABBs(Level* level, int32_t x, int32_t y, int32_t z, const AABB* aabb, std::vector<AABB>& vec) {
		bool_t v11; // r11
		this->setBaseShape(level, x, y, z);
		Tile::addAABBs(level, x, y, z, aabb, vec);
		v11 = this->setStepShape(level, x, y, z);
		Tile::addAABBs(level, x, y, z, aabb, vec);
		if (v11) {
			if (this->setInnerPieceShape(level, x, y, z)) {
				Tile::addAABBs(level, x, y, z, aabb, vec);
			}
		}
		this->setShape(0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
	}
	virtual AABB getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
		return this->block->getTileAABB(level, x, y, z);
	}
	virtual bool_t isSolidRender() {
		return 0;
	}
	virtual bool_t mayPick() {
		return this->block->mayPick();
	}
	virtual bool_t mayPick(int32_t a2, bool_t a3) {
		return this->block->mayPick(a2, a3);
	}
	virtual bool_t mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t) {
		return this->block->mayPlace(level, x, y, z);
	}
	virtual int32_t getTickDelay() {
		return this->block->getTickDelay();
	}
	virtual void tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
		return this->block->tick(level, x, y, z, rng);
	}
	virtual void animateTick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
		return this->block->animateTick(level, x, y, z, rng);
	}
	virtual void destroy(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
		return this->block->destroy(level, x, y, z, a6);
	}
	virtual void onPlace(Level* level, int32_t x, int32_t y, int32_t z) {
		this->neighborChanged(level, x, y, z, x, y, z, 0);
		return this->block->onPlace(level, x, y, z);
	}
	virtual void onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
		return this->block->onRemove(level, x, y, z);
	}
	virtual int32_t getResourceCount(Random* rng) {
		return this->block->getResourceCount(rng);
	}
	virtual float getExplosionResistance(Entity* e) {
		return this->block->getExplosionResistance(e);
	}
	virtual HitResult clip(Level*, int32_t, int32_t, int32_t, const Vec3&, const Vec3&);
	virtual void wasExploded(Level* level, int32_t x, int32_t y, int32_t z) {
		this->block->wasExploded(level, x, y, z);
	}
	virtual int32_t getRenderLayer() {
		return this->block->getRenderLayer();
	}
	virtual bool_t use(Level* level, int32_t x, int32_t y, int32_t z, Player* p) {
		return this->block->use(level, x, y, z, p);
	}
	virtual void stepOn(Level* a2, int32_t x, int32_t y, int32_t z, Entity* e) {
		this->block->stepOn(a2, x, y, z, e);
	}
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
	virtual void prepareRender(Level* level, int32_t x, int32_t y, int32_t z) {
		this->block->prepareRender(level, x, y, z);
	}
	virtual void attack(Level* level, int32_t x, int32_t y, int32_t z, Player* p) {
		this->block->attack(level, x, y, z, p);
	}
	virtual void handleEntityInside(Level* level, int32_t x, int32_t y, int32_t z, Entity* e, Vec3& v) {
		this->block->handleEntityInside(level, x, y, z, e, v);
	}
};
