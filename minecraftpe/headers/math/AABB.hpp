#pragma once
#include <_types.h>
#include <math/HitResult.hpp>
#include <math/Vec3.hpp>

struct Vec3;
struct HitResult;

struct AABB{
	float minX, minY, minZ, maxX, maxY, maxZ;
	//TODO missing constructor

	HitResult clip(const Vec3& a3, const Vec3& a4) {
		Vec3 minXvec(0, 0, 0);
		Vec3 maxXvec(0, 0, 0);
		Vec3 minYvec(0, 0, 0);
		Vec3 maxYvec(0, 0, 0);
		Vec3 minZvec(0, 0, 0);
		Vec3 maxZvec(0, 0, 0);

		bool minXclip = a3.clipX(a4, this->minX, minXvec);
		bool maxXclip = a3.clipX(a4, this->maxX, maxXvec);

		bool minYclip = a3.clipY(a4, this->minY, minYvec);
		bool maxYclip = a3.clipY(a4, this->maxY, maxYvec);

		bool minZclip = a3.clipZ(a4, this->minZ, minZvec);
		bool maxZclip = a3.clipZ(a4, this->maxZ, maxZvec);

		if(minXclip) {
			minXclip = minXvec.y >= this->minY && minXvec.y <= this->maxY && minXvec.z >= this->minZ && minXvec.z <= this->maxZ;
		}
		if(maxXclip) {
			maxXclip = maxXvec.y >= this->minY && maxXvec.y <= this->maxY && maxXvec.z >= this->minZ && maxXvec.z <= this->maxZ;
		}
		if(minYclip) {
			minYclip = minYvec.x >= this->minX && minYvec.x <= this->maxX && minYvec.z >= this->minZ && minYvec.z <= this->maxZ;
		}
		if(maxYclip) {
			maxYclip = maxYvec.x >= this->minX && maxYvec.x <= this->maxX && maxYvec.z >= this->minZ && maxYvec.z <= this->maxZ;
		}
		if(minZclip) {
			minZclip = minZvec.x >= this->minX && minZvec.x <= this->maxX && minZvec.y >= this->minY && minZvec.y <= this->maxY;
		}
		if(maxZclip) {
			maxZclip = maxZvec.x >= this->minX && maxZvec.x <= this->maxX && maxZvec.y >= this->minY && maxZvec.y <= this->maxY;
		}

		Vec3* vec3 = 0;
		if(minXclip) {
			vec3 = &minXvec;
		}
		if(maxXclip && (!vec3 || (a3.distanceToSqr(maxXvec) < a3.distanceToSqr(*vec3)))) {
			vec3 = &maxXvec;
		}

		if(minYclip && (!vec3 || (a3.distanceToSqr(minYvec) < a3.distanceToSqr(*vec3)))) {
			vec3 = &minYvec;
		}
		if(maxYclip && (!vec3 || (a3.distanceToSqr(maxYvec) < a3.distanceToSqr(*vec3)))) {
			vec3 = &maxYvec;
		}

		if(minZclip && (!vec3 || (a3.distanceToSqr(minZvec) < a3.distanceToSqr(*vec3)))) {
			vec3 = &minZvec;
		}
		if(maxZclip && (!vec3 || (a3.distanceToSqr(maxZvec) < a3.distanceToSqr(*vec3)))) {
			vec3 = &maxZvec;
		}

		if(!vec3) return HitResult();
		int side = -1;
		if(vec3 == &minXvec) side = 4;
		if(vec3 == &maxXvec) side = 5;
		if(vec3 == &minYvec) side = 0;
		if(vec3 == &maxYvec) side = 1;
		if(vec3 == &minZvec) side = 2;
		if(vec3 == &maxZvec) side = 3;
		return HitResult(0, 0, 0, side, *vec3);
	}

	AABB expand(float x, float y, float z) {
		float minX = this->minX;
		float minY = this->minY;
		float minZ = this->minZ;
		float maxX = this->maxX;
		float maxY = this->maxY;
		float maxZ = this->maxZ;

		if(x < 0) minX += x;
		if(x > 0) maxX += x;

		if(y < 0) minY += y;
		if(y > 0) maxY += y;

		if(z < 0) minZ += z;
		if(z > 0) maxZ += z;

		return AABB{minX, minY, minZ, maxX, maxY, maxZ};
	}
	float clipXCollide(const AABB& a2, float a3) const{
		if(a2.maxY <= this->minY || a2.minY >= this->maxY) return a3;
		if(a2.maxZ <= this->minZ || a2.minZ >= this->maxZ) return a3;

		if(a3 > 0 && a2.maxX <= this->minX) {
			float xd = this->minX - a2.maxX;
			if(xd < a3) a3 = xd;
		}
		if(a3 < 0 && a2.minX >= this->maxX) {
			float xd = this->maxX - a2.minX;
			if(xd > a3) a3 = xd;
		}
		return a3;
	}
	float clipYCollide(const AABB& a2, float a3) const{
		if(a2.maxX <= this->minX || a2.minX >= this->maxX) return a3;
		if(a2.maxZ <= this->minZ || a2.minZ >= this->maxZ) return a3;

		if(a3 > 0 && a2.maxY <= this->minY) {
			float yd = this->minY - a2.maxY;
			if(yd < a3) a3 = yd;
		}
		if(a3 < 0 && a2.minY >= this->maxY) {
			float yd = this->maxY - a2.minY;
			if(yd > a3) a3 = yd;
		}
		return a3;

	}
	float clipZCollide(const AABB& a2, float a3) const {
		if(a2.maxX <= this->minX || a2.minX >= this->maxX) return a3;
		if(a2.maxY <= this->minY || a2.minY >= this->maxY) return a3;

		if(a3 > 0 && a2.maxZ <= this->minZ) {
			float zd = this->minZ - a2.maxZ;
			if(zd < a3) a3 = zd;
		}
		if(a3 < 0 && a2.minZ >= this->maxZ) {
			float zd = this->maxZ - a2.minZ;
			if(zd > a3) a3 = zd;
		}
		return a3;
	}
	AABB* move(float x, float y, float z) {
		this->minX += x;
		this->minY += y;
		this->minZ += z;

		this->maxX += x;
		this->maxY += y;
		this->maxZ += z;
		return this;
	}
	AABB merge(const AABB& bb) const{
		float minX = bb.minX < this->minX ? bb.minX : this->minX;
		float minY = bb.minY < this->minY ? bb.minY : this->minY;
		float minZ = bb.minZ < this->minZ ? bb.minZ : this->minZ;
		float maxX = this->maxX < bb.maxX ? bb.maxX : this->maxX;
		float maxY = this->maxY < bb.maxY ? bb.maxY : this->maxY;
		float maxZ = this->maxZ < bb.maxZ ? bb.maxZ : this->maxZ;

		return AABB{minX, minY, minZ, maxX, maxY, maxZ};
	}

	//the method names was taken from b1.2, should always be inlined
	AABB grow(float x, float y, float z) {
		return AABB{this->minX - x, this->minY - y, this->minZ - z, this->maxX + x, this->maxY + y, this->maxZ + z};
	}
	AABB cloneMove(float x, float y, float z) {
		return AABB{this->minX + x, this->minY + y, this->minZ + z, this->maxX + x, this->maxY + y, this->maxZ + z};
	}
	bool contains(const Vec3& vec){
		return vec.x > this->minX && vec.x < this->maxX && vec.y > this->minY && vec.y < this->maxY && vec.z > this->minZ && vec.z < this->maxZ;
	}
};
