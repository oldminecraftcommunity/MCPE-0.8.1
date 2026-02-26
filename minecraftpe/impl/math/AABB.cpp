#include <math/AABB.hpp>
#include <math/HitResult.hpp>
#include <math/Vec3.hpp>

HitResult AABB::clip(const Vec3& a3, const Vec3& a4) {
	bool_t v7;	// r9
	bool_t v8;	// r8
	bool_t v9;	// r7
	bool_t v10; // r6
	bool_t v11; // r0
	bool_t v12; // r12
	bool_t v13; // r11
	float v14;	// s16
	Vec3* v15;	// r4
	float v16;	// s16
	float v17;	// s16
	float v18;	// s16
	float v19;	// s16
	int v20;	// r3
	bool_t v21; // [sp+Ch] [bp-94h]
	Vec3 v23;	// [sp+28h] [bp-78h] BYREF
	Vec3 v24;	// [sp+34h] [bp-6Ch] BYREF
	Vec3 v25;	// [sp+40h] [bp-60h] BYREF
	Vec3 v26;	// [sp+4Ch] [bp-54h] BYREF
	Vec3 v27;	// [sp+58h] [bp-48h] BYREF
	Vec3 v28;	// [sp+64h] [bp-3Ch] BYREF

	v21 = a3.clipX(a4, this->minX, v23);
	v7 = a3.clipX(a4, this->maxX, v24);
	v8 = a3.clipY(a4, this->minY, v25);
	v9 = a3.clipY(a4, this->maxY, v26);
	v10 = a3.clipZ(a4, this->minZ, v27);
	v11 = a3.clipZ(a4, this->maxZ, v28);
	v12 = v21;
	v13 = v11;
	if(v21) {
		v12 = v23.y >= this->minY && v23.y <= this->maxY && v23.z >= this->minZ && v23.z <= this->maxZ;
	}
	if(v7) {
		v7 = v24.y >= this->minY && v24.y <= this->maxY && v24.z >= this->minZ && v24.z <= this->maxZ;
	}
	if(v8) {
		v8 = v25.x >= this->minX && v25.x <= this->maxX && v25.z >= this->minZ && v25.z <= this->maxZ;
	}
	if(v9) {
		v9 = v26.x >= this->minX && v26.x <= this->maxX && v26.z >= this->minZ && v26.z <= this->maxZ;
	}
	if(v10) {
		v10 = v27.x >= this->minX && v27.x <= this->maxX && v27.y >= this->minY && v27.y <= this->maxY;
	}
	if(v11) {
		v13 = v28.x >= this->minX && v28.x <= this->maxX && v28.y >= this->minY && v28.y <= this->maxY;
	}
	if(v12) {
		if(!v7 || (v14 = a3.distanceToSqr(v24), v14 >= a3.distanceToSqr(v23))) {
			v15 = &v23;
			if(!v8) {
LABEL_99:
				if(!v9) {
					if(!v10) {
						goto LABEL_81;
					}
					if(!v15) {
						goto LABEL_83;
					}
					goto LABEL_50;
				}
LABEL_45:
				v17 = a3.distanceToSqr(v26);
				if(v17 >= a3.distanceToSqr(*v15)) {
					goto LABEL_101;
				}
LABEL_79:
				if(!v10) {
					v15 = &v26;
					if(!v13) {
						goto LABEL_54;
					}
					goto LABEL_53;
				}
				v15 = &v26;
				goto LABEL_50;
			}
			goto LABEL_42;
		}
	} else if(!v7) {
		if(!v8) {
			if(!v9) {
				if(!v10) {
					v15 = 0;
					goto LABEL_81;
				}
				goto LABEL_83;
			}
			goto LABEL_79;
		}
		goto LABEL_75;
	}
	if(!v8) {
		v15 = &v24;
		if(!v9) {
LABEL_101:
			if(!v10) {
LABEL_81:
				if(!v13) {
					goto LABEL_85;
				}
				if(!v15) {
LABEL_58:
					v15 = &v28;
LABEL_59:
					if(v15 == &v26) {
						v20 = 1;
						goto LABEL_69;
					}
					if(v15 == &v27) {
						v20 = 2;
						goto LABEL_69;
					}
					v20 = -1;
LABEL_63:
					if(v15 == &v28) {
						v20 = 3;
					}
					goto LABEL_69;
				}
LABEL_53:
				v19 = a3.distanceToSqr(v28);
				if(v19 >= a3.distanceToSqr(*v15)) {
LABEL_54:
					if(v15 == &v23) {
						v20 = 4;
						goto LABEL_63;
					}
					if(v15 == &v24) {
						v20 = 5;
						goto LABEL_69;
					}
					goto LABEL_56;
				}
				goto LABEL_58;
			}
LABEL_50:
			v18 = a3.distanceToSqr(v27);
			if(v18 >= a3.distanceToSqr(*v15)) {
				goto LABEL_103;
			}
LABEL_83:
			v15 = &v27;
			if(!v13) {
LABEL_56:
				if(v15 == &v25) {
					v20 = 0;
LABEL_69:
					return HitResult(0, 0, 0, v20, *v15);
				}
				goto LABEL_59;
			}
			goto LABEL_53;
		}
		goto LABEL_45;
	}
	v15 = &v24;
LABEL_42:
	v16 = a3.distanceToSqr(v25);
	if(v16 >= a3.distanceToSqr(*v15)) {
		goto LABEL_99;
	}
LABEL_75:
	if(v9) {
		v15 = &v25;
		goto LABEL_45;
	}
	v15 = &v25;
	if(v10) {
		goto LABEL_50;
	}
LABEL_103:
	if(v13) {
		goto LABEL_53;
	}
LABEL_85:
	if(v15) {
		goto LABEL_54;
	}
	return HitResult();
}

float AABB::clipXCollide(const AABB& a2, float a3) {
	float v3;	// s14
	float v4;	// s15
	float maxX; // s15
	float v6;	// s13

	v3 = a3;
	if(a2.maxY > this->minY && a2.minY < this->maxY && a2.maxZ > this->minZ && a2.minZ < this->maxZ) {
		if(a3 <= 0.0 || (maxX = a2.maxX, maxX > this->minX) || (v4 = this->minX - maxX, v4 >= a3)) {
			v4 = a3;
		}
		if(v4 < 0.0) {
			v6 = this->maxX;
			if(a2.minX >= v6 && (float)(v6 - a2.minX) > v4) {
				return v6 - a2.minX;
			}
		}
		return v4;
	}
	return v3;
}
float AABB::clipYCollide(const AABB& a2, float a3) {
	float v3;	// s14
	float v4;	// s15
	float maxY; // s15
	float minY; // s13
	float v7;	// s14
	float v8;	// s13
	float v9;	// s14

	v3 = a3;
	if(a2.maxX > this->minX && a2.minX < this->maxX && a2.maxZ > this->minZ && a2.minZ < this->maxZ) {
		if(a3 <= 0.0 || (maxY = a2.maxY, minY = this->minY, maxY > minY) || (v4 = minY - maxY, v4 >= a3)) {
			v4 = a3;
		}
		if(v4 < 0.0) {
			v7 = a2.minY;
			v8 = this->maxY;
			if(v7 >= v8) {
				v9 = v8 - v7;
				if(v9 > v4) {
					return v9;
				}
			}
		}
		return v4;
	}
	return v3;
}
float AABB::clipZCollide(const AABB& a2, float a3) {
	float v3;	// s14
	float v4;	// s15
	float maxZ; // s15
	float minZ; // s13
	float v7;	// s14
	float v8;	// s13
	float v9;	// s14

	v3 = a3;
	if(a2.maxX > this->minX && a2.minX < this->maxX && a2.maxY > this->minY && a2.minY < this->maxY) {
		if(a3 <= 0.0 || (maxZ = a2.maxZ, minZ = this->minZ, maxZ > minZ) || (v4 = minZ - maxZ, v4 >= a3)) {
			v4 = a3;
		}
		if(v4 < 0.0) {
			v7 = a2.minZ;
			v8 = this->maxZ;
			if(v7 >= v8) {
				v9 = v8 - v7;
				if(v9 > v4) {
					return v9;
				}
			}
		}
		return v4;
	}
	return v3;
}
AABB AABB::expand(float x, float y, float z) {
	AABB result;
	result = *this;
	if(x > 0) result.maxX += x;
	else if(x < 0) result.minX += x;

	if(y > 0) result.maxY += y;
	else if(y < 0) result.minY += y;

	if(z > 0) result.maxZ += z;
	else if(z < 0) result.minZ += z;

	return result;
}
void AABB::move(float x, float y, float z) {
	this->minX += x;
	this->minY += y;
	this->minZ += z;

	this->maxX += x;
	this->maxY += y;
	this->maxZ += z;
}

AABB AABB::merge(const AABB& bb) {
	AABB result;
	float minX, minY, minZ;
	float maxX, maxY, maxZ;

	if(bb.minX >= this->minX) minX = this->minX;
	else minX = bb.minX;

	if(bb.minY < this->minY) minY = bb.minY;
	else minY = this->minY;

	if(bb.minZ < this->minZ) minZ = bb.minZ;
	else minZ = this->minZ;

	if(this->maxX < bb.maxX) maxX = bb.maxX;
	else maxX = this->maxX;

	if(this->maxY < bb.maxY) maxY = bb.maxY;
	else maxY = this->maxY;

	if(this->maxX >= bb.maxZ) maxZ = this->maxZ;
	else maxZ = bb.maxZ;

	result.minX = minX;
	result.minY = minY;
	result.minZ = minZ;
	result.maxX = maxX;
	result.maxY = maxY;
	result.maxZ = maxZ;

	return result;
}
