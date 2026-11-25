#pragma once
#include <math/Vec3.hpp>

struct Entity;

struct HitResult{
	int32_t hitType;
	int32_t x;
	int32_t y;
	int32_t z;
	int32_t face;
	Vec3 hitVec;
	Entity* entity;
	bool field_24;

	HitResult(Entity*);
	HitResult(const HitResult&);
	HitResult(int32_t, int32_t, int32_t, int32_t, const Vec3&);
	HitResult(void);
	float distanceTo(Entity* entity) const;
};
