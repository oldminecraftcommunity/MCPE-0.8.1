#pragma once
#include <_types.h>

struct Vec3{
	float x, y, z;
	static Vec3 ZERO;
	static Vec3 ONE;

	static Vec3 UNIT_X;
	static Vec3 NEG_UNIT_X;

	static Vec3 UNIT_Y;
	static Vec3 NEG_UNIT_Y;

	static Vec3 UNIT_Z;
	static Vec3 NEG_UNIT_Z;

	Vec3();
	Vec3(float, float, float);
	float distanceTo(const Vec3&);
	float distanceToSqr(const Vec3&) const;
	bool_t clipX(const Vec3&, float, Vec3&) const;
	bool_t clipY(const Vec3&, float, Vec3&) const;
	bool_t clipZ(const Vec3&, float, Vec3&) const;
	void yRot(float);
	Vec3 normalized(void);
	void xRot(float);
};
