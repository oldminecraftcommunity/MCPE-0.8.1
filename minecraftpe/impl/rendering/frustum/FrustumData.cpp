#include <rendering/frustum/FrustumData.hpp>

bool_t FrustumData::cubeInFrustum(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	int32_t v9; // r3
	float v10;	// s8
	float v11;	// s12
	float v12;	// s11
	float v13;	// s14
	float v14;	// s15
	float v15;	// s13
	float v16;	// s9
	float v17;	// s8
	float v18;	// s10
	float v19;	// s12
	float v20;	// s11
	float v21;	// s12
	float v22;	// s14

	for(v9 = 0; v9 != 5; ++v9) {
		v10 = this->planes[v9][0];
		v11 = this->planes[v9][1];
		v12 = v10 * minX;
		v13 = this->planes[v9][2];
		v14 = this->planes[v9][3];
		v15 = v13 * minZ;
		v16 = (float)(v10 * minX) + (float)(v11 * minY);
		if((float)((float)(v16 + (float)(v13 * minZ)) + v14) <= 0.0) {
			v17 = v10 * maxX;
			v18 = v17 + (float)(v11 * minY);
			if((float)((float)(v18 + v15) + v14) <= 0.0) {
				v19 = v11 * maxY;
				v20 = v12 + v19;
				if((float)((float)(v20 + v15) + v14) <= 0.0) {
					v21 = v17 + v19;
					if((float)((float)(v21 + v15) + v14) <= 0.0) {
						v22 = v13 * maxZ;
						if((float)((float)(v16 + v22) + v14) <= 0.0 && (float)((float)(v18 + v22) + v14) <= 0.0 && (float)((float)(v20 + v22) + v14) <= 0.0 && (float)((float)(v21 + v22) + v14) <= 0.0) {
							return 0;
						}
					}
				}
			}
		}
	}
	return 1;
}
