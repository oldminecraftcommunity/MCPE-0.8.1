#pragma once
#include <tile/Tile.hpp>

struct ThinFenceTile : Tile{
	TextureUVCoordinateSet field_80;
	bool_t field_98;
	byte field_99, field_9A, field_9B;

	ThinFenceTile(int32_t, const std::string&, const std::string&, const struct Material*, bool_t);
	bool_t attachsTo(int32_t);

	virtual ~ThinFenceTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual void updateDefaultShape();
	virtual bool_t shouldRenderFace(LevelSource*, int32_t, int32_t, int32_t, int32_t);
	virtual void addAABBs(Level*, int32_t, int32_t, int32_t, const AABB*, std::vector<AABB>&);
	virtual bool_t isSolidRender();
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getRenderLayer();

};
