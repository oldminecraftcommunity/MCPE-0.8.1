#pragma once
#include <_types.h>

struct Vec3;
struct HitResult;

struct AABB{
	float minX, minY, minZ, maxX, maxY, maxZ;

	//TODO missing constructor
	HitResult clip(const Vec3&, const Vec3&);
	AABB expand(float, float, float);
	float clipXCollide(const AABB&, float);
	float clipYCollide(const AABB&, float);
	float clipZCollide(const AABB&, float);
	void move(float, float, float);
	AABB merge(const AABB&);
};
