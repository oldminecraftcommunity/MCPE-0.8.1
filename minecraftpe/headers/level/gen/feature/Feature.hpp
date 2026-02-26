#pragma once
#include <_types.h>

struct Level;
struct Random;

struct Feature{
	bool_t update;
	byte a, b, c;

	Feature(bool_t);
	void placeBlock(Level*, int32_t, int32_t, int32_t, int32_t);
	void placeBlock(Level*, int32_t, int32_t, int32_t, int32_t, int32_t);

	virtual ~Feature();
	virtual bool_t place(Level*, Random*, int32_t, int32_t, int32_t) = 0;
	virtual void init(float, float, float);
};
