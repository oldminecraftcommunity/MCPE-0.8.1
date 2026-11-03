#pragma once
#include <_types.h>
#include <entity/PathfinderMob.hpp>
#include <math/Vec3.hpp>
#include <math/Mth.hpp>

struct Vec3;
struct PathfinderMob;
struct RandomPos
{
	static bool_t generateRandomPos(Vec3& res, PathfinderMob* mob, int32_t a3, int32_t a4, Vec3* a5) {
		float best = -99999.0f;
		Random* p_random = &mob->random;
		int rz = 0;
		int ry = 0;
		int rx = 0;
		bool found = 0;
		int v31 = 2 * a3;
		int v33 = 2 * a4;
		for(int v12 = 0; v12 < 10; ++v12) {
			int v15 = p_random->nextInt(v31 - a3);
			int v28 = p_random->nextInt(v33 - a4);
			int v16 = p_random->nextInt(v31 - a3);
			if(!a5 || ((v15 * a5->x) + (v16 * a5->z)) >= 0) {
				int v18 = Mth::floor(mob->posX);
				int v22 = Mth::floor(mob->posY);
				int v24 = Mth::floor(mob->posZ);
				int v21 = v18 + v15;
				int v30 = v22 + v28;
				int v25 = v16 + v24;
				float v = mob->getWalkTargetValue(v21, v30, v25);
				if(v > best) {
					found = 1;
					best = v;

					rz = v25;
					ry = v30;
					rx = v21;
				}
			}
		}

		if(!found) return 0;

		res.x = rx;
		res.y = ry;
		res.z = rz;
		return 1;
	}
};
