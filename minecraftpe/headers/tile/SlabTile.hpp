#pragma once
#include <tile/Tile.hpp>

struct SlabTile : Tile{
	bool_t isFull;
	char field_7D, field_7E, field_7F;

	SlabTile(int32_t, const std::string&, bool_t, const struct Material*);
	bool_t isBottomSlab(LevelSource*, int32_t, int32_t, int32_t);

	virtual ~SlabTile();
	virtual int32_t getTileType();
	virtual bool_t isCubeShaped();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual void updateDefaultShape();
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual void addAABBs(Level*, int32_t, int32_t, int32_t, const AABB*, std::vector<AABB>&);
	virtual bool_t isSolidRender();
	virtual int32_t getResourceCount(Random*);
	virtual int32_t getPlacementDataValue(Level*, int32_t, int32_t, int32_t, int32_t, float, float, float, Mob*, int32_t);
};
