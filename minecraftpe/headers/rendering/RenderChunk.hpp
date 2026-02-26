#pragma once
#include <_types.h>
#include <rendering/MeshBuffer.hpp>
#include <math/AABB.hpp>

struct RenderChunk
{
	static int32_t updates;
	struct Level* level;
	int32_t xPos, yPos, zPos;
	int32_t xSize, ySize, zSize;
	bool_t skipLayer[4];
	int32_t blockX, blockY, blockZ;
	float field_2C;
	AABB frustumBB;
	int32_t field_48;
	bool_t isInFrustumMaybe;
	int8_t field_4D, field_4E, field_4F;
	int32_t field_50;
	int8_t touchedSky;
	int8_t field_55, field_56, field_57;
	MeshBuffer meshBuffers[4];
	struct Tesselator* tessellator;
	int32_t renderLists;
	bool_t built, dirty, skipRenderMaybe;
	int8_t field_103;

	RenderChunk(struct Level*, int32_t, int32_t, int32_t, int32_t, int32_t);
	float distanceToSqr(const struct Entity*);
	int32_t getAllLists(int32_t*, int32_t, int32_t);
	int32_t getList(int32_t);
	MeshBuffer* getRenderChunk(int32_t);
	bool_t isDirty();
	void rebuild(void);
	void renderBB(void);
	void reset(void);
	void resetUpdates(void);
	void setClean(void);
	void setDirty(void);
	void setPos(int32_t, int32_t, int32_t);
	float squishedDistanceToSqr(const struct Entity*);
	void translateToPos(void);
};
