#include <util/RandomPos.hpp>
#include <entity/PathfinderMob.hpp>
#include <math/Vec3.hpp>

bool_t RandomPos::generateRandomPos(Vec3& res, PathfinderMob* mob, int32_t a3, int32_t a4, Vec3* a5) {
	int32_t v5;		  // r5
	float v6;		  // s16
	Random* p_random; // r8
	int32_t v8;		  // s17
	int32_t v10;	  // s18
	int32_t v12;	  // r10
	int32_t v13;	  // r6
	int32_t v15;	  // r11
	int32_t v16;	  // r1
	float posX;		  // s15
	int32_t v18;	  // r2
	bool_t v19;		  // fnf
	float posY;		  // s15
	int32_t v21;	  // r2
	int32_t v22;	  // r11
	float posZ;		  // s15
	int32_t v24;	  // r3
	int32_t v25;	  // r11
	float v26;		  // r0
	uint32_t v28;	  // [sp+0h] [bp-50h]
	int32_t v29;	  // [sp+4h] [bp-4Ch]
	int32_t v30;	  // [sp+8h] [bp-48h]
	uint32_t v31;	  // [sp+Ch] [bp-44h]
	uint32_t v33;	  // [sp+14h] [bp-3Ch]

	v5 = 0;
	v6 = -99999.0;
	p_random = &mob->random;
	v8 = 0;
	v10 = 0;
	v12 = 10;
	v13 = 0;
	v31 = 2 * a3;
	v33 = 2 * a4;
	do {
		v15 = p_random->genrand_int32() % v31 - a3;
		v28 = p_random->genrand_int32();
		v16 = p_random->genrand_int32() % v31 - a3;
		if(!a5 || (float)((float)((float)v16 * a5->z) + (float)((float)v15 * a5->x)) >= 0.0) {
			posX = mob->posX;
			v18 = (int32_t)posX;
			v19 = posX < (float)(int32_t)posX;
			posY = mob->posY;
			if(v19) {
				--v18;
			}
			v21 = v18 + v15;
			v22 = (int32_t)posY;
			v29 = v21;
			if(posY < (float)(int32_t)posY) {
				--v22;
			}
			posZ = mob->posZ;
			v24 = (int32_t)posZ;
			if(posZ < (float)(int32_t)posZ) {
				--v24;
			}
			v30 = v22 + v28 % v33 - a4;
			v25 = v16 + v24;
			v26 = mob->getWalkTargetValue(v21, v30, v16 + v24);
			if(v26 > v6) {
				v6 = v26;
				v5 = v25;
				v13 = 1;
				v8 = v30;
				v10 = v29;
			}
		}
		--v12;
	} while(v12);
	if(!v13) {
		return 0;
	}

	res.x = (float)v10;
	res.y = (float)v8;
	res.z = (float)v5;
	return 1;
}
