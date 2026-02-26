#pragma once
#include <_types.h>
struct LightLayer;
struct Level;
struct LightUpdate
{
	const LightLayer* layer;
	int32_t minX, minY, minZ;
	int32_t maxX, maxY, maxZ;

	LightUpdate(const LightLayer&, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	LightUpdate(const LightUpdate&);
	LightUpdate(const LightUpdate*);
	bool_t expandToContain(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	LightUpdate& operator=(const LightUpdate*);
	void update(Level*);
};
