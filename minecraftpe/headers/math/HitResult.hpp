#pragma once
#include <_types.h>
#include <math/Vec3.hpp>

struct Entity;

struct HitResult{
	int32_t hitType;
	int32_t field_4;
	int32_t field_8;
	int32_t field_C;
	int32_t field_10;
	Vec3 hitVec;
	Entity* entity;
	char_t field_24;
	char field_25, field_26, field_27;

	HitResult(Entity*);
	HitResult(const HitResult&);
	HitResult(int32_t, int32_t, int32_t, int32_t, const Vec3&);
	HitResult(void);
	float distanceTo(Entity* entity);
};
