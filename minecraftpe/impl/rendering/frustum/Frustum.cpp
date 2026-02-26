#include <rendering/frustum/Frustum.hpp>
#include <GL/gl.h>
Frustum Frustum::frustum;

void Frustum::calculateFrustum(void) {
	float* proj; // r5
	float* modl; // r6
	float* v4;	 // r8
	float v5;	 // s8
	float v6;	 // s15
	float v7;	 // s11
	float v8;	 // s25
	float v9;	 // s12
	float v10;	 // s24
	float v11;	 // s13
	float v12;	 // s23
	float v13;	 // s9
	float v14;	 // s22
	float v15;	 // s6
	float v16;	 // s21
	float v17;	 // s20
	float v18;	 // s19
	float v19;	 // s7
	float v20;	 // s18
	float v21;	 // s17
	float v22;	 // s1
	float v23;	 // s14
	float v24;	 // s3
	float v25;	 // s4
	float v26;	 // s8
	float v27;	 // s2
	float v28;	 // s10
	float v29;	 // s5
	float v30;	 // s12
	float v31;	 // s11
	float v32;	 // s13
	float v33;	 // s10
	float v34;	 // s16
	float v35;	 // s12
	float v36;	 // s0
	float v37;	 // s2
	float v38;	 // s13
	float v39;	 // s5
	float v40;	 // s12
	float v41;	 // s0
	float v42;	 // s16
	float v43;	 // s2
	float v44;	 // s5
	float v45;	 // s14
	float v46;	 // s15

	proj = this->proj;
	modl = this->modl;
	v4 = &this->clip[3];
	glGetFloatv(0xBA7u, this->proj);
	glGetFloatv(0xBA6u, modl);
	v5 = this->modl[1];
	v6 = this->proj[4];
	v7 = *modl;
	v8 = *proj;
	v9 = this->modl[2];
	v10 = this->proj[8];
	v11 = this->modl[3];
	v12 = this->proj[12];
	v13 = (float)((float)((float)(v5 * v6) + (float)(*modl * *proj)) + (float)(v9 * v10)) + (float)(v11 * v12);
	this->clip[0] = v13;
	v14 = this->proj[1];
	v15 = this->proj[5];
	v16 = this->proj[9];
	v17 = this->proj[13];
	this->clip[1] = (float)((float)((float)(v5 * v15) + (float)(v7 * v14)) + (float)(v9 * v16)) + (float)(v11 * v17);
	v18 = this->proj[2];
	v19 = this->proj[6];
	v20 = this->proj[10];
	v21 = this->proj[14];
	this->clip[2] = (float)((float)((float)(v5 * v19) + (float)(v7 * v18)) + (float)(v9 * v20)) + (float)(v11 * v21);
	v22 = this->proj[3];
	v23 = this->proj[7];
	v24 = this->proj[11];
	v25 = this->proj[15];
	v26 = (float)((float)((float)(v5 * v23) + (float)(v7 * v22)) + (float)(v9 * v24)) + (float)(v11 * v25);
	*v4 = v26;
	v27 = this->modl[4];
	v28 = this->modl[5];
	v29 = this->modl[6];
	v30 = this->modl[7];
	v31 = (float)((float)((float)(v28 * v6) + (float)(v27 * v8)) + (float)(v29 * v10)) + (float)(v30 * v12);
	this->clip[4] = v31;
	this->clip[5] = (float)((float)((float)(v28 * v15) + (float)(v27 * v14)) + (float)(v29 * v16)) + (float)(v30 * v17);
	v32 = v28 * v19;
	v33 = (float)((float)((float)(v28 * v23) + (float)(v27 * v22)) + (float)(v29 * v24)) + (float)(v30 * v25);
	this->clip[6] = (float)((float)(v32 + (float)(v27 * v18)) + (float)(v29 * v20)) + (float)(v30 * v21);
	this->clip[7] = v33;
	v34 = this->modl[8];
	v35 = this->modl[9];
	v36 = this->modl[10];
	v37 = this->modl[11];
	v38 = (float)((float)((float)(v35 * v6) + (float)(v34 * v8)) + (float)(v36 * v10)) + (float)(v37 * v12);
	this->clip[8] = v38;
	this->clip[9] = (float)((float)((float)(v35 * v15) + (float)(v34 * v14)) + (float)(v36 * v16)) + (float)(v37 * v17);
	v39 = v35 * v19;
	v40 = (float)((float)((float)(v35 * v23) + (float)(v34 * v22)) + (float)(v36 * v24)) + (float)(v37 * v25);
	this->clip[10] = (float)((float)(v39 + (float)(v34 * v18)) + (float)(v36 * v20)) + (float)(v37 * v21);
	this->clip[11] = v40;
	v41 = this->modl[12];
	v42 = this->modl[13];
	v43 = this->modl[14];
	v44 = this->modl[15];
	v45 = (float)((float)((float)(v42 * v23) + (float)(v41 * v22)) + (float)(v43 * v24)) + (float)(v44 * v25);
	v46 = (float)((float)((float)(v42 * v6) + (float)(v41 * v8)) + (float)(v43 * v10)) + (float)(v44 * v12);
	this->clip[12] = v46;
	this->clip[13] = (float)((float)((float)(v42 * v15) + (float)(v41 * v14)) + (float)(v43 * v16)) + (float)(v44 * v17);
	this->clip[14] = (float)((float)((float)(v42 * v19) + (float)(v41 * v18)) + (float)(v43 * v20)) + (float)(v44 * v21);
	this->clip[15] = v45;
	this->planes[0][0] = v26 - v13;
	this->planes[0][1] = v33 - v31;
	this->planes[0][2] = v40 - v38;
	this->planes[0][3] = v45 - v46;
	this->normalizePlane(this->planes, 0);
	this->planes[1][0] = *v4 + this->clip[0];
	this->planes[1][1] = this->clip[7] + this->clip[4];
	this->planes[1][2] = this->clip[11] + this->clip[8];
	this->planes[1][3] = this->clip[15] + this->clip[12];
	this->normalizePlane(this->planes, 1);
	this->planes[2][0] = *v4 + this->clip[1];
	this->planes[2][1] = this->clip[7] + this->clip[5];
	this->planes[2][2] = this->clip[11] + this->clip[9];
	this->planes[2][3] = this->clip[15] + this->clip[13];
	this->normalizePlane(this->planes, 2);
	this->planes[3][0] = *v4 - this->clip[1];
	this->planes[3][1] = this->clip[7] - this->clip[5];
	this->planes[3][2] = this->clip[11] - this->clip[9];
	this->planes[3][3] = this->clip[15] - this->clip[13];
	this->normalizePlane(this->planes, 3);
	this->planes[4][0] = *v4 - this->clip[2];
	this->planes[4][1] = this->clip[7] - this->clip[6];
	this->planes[4][2] = this->clip[11] - this->clip[10];
	this->planes[4][3] = this->clip[15] - this->clip[14];
	this->normalizePlane(this->planes, 4);
	this->planes[5][0] = *v4 + this->clip[2];
	this->planes[5][1] = this->clip[7] + this->clip[6];
	this->planes[5][2] = this->clip[11] + this->clip[10];
	this->planes[5][3] = this->clip[15] + this->clip[14];
	this->normalizePlane(this->planes, 5);
}
void Frustum::normalizePlane(float (*a2)[16], int32_t a3) {
	float* v3 = a2[a3];
	float v4;  // s13
	float v5;  // s14
	float v6;  // r1
	float v7;  // s10
	float v8;  // s11
	float v9;  // s12
	float v10; // s14

	v4 = v3[1];
	v5 = v3[2];
	v6 = (float)((float)(v4 * v4) + (float)(*v3 * *v3)) + (float)(v5 * v5);
	*((int32_t*)&v7) = 0x5F3759DF - (*((int32_t*)&v6) >> 1); //TODO replace with sqrt if needed
	v8 = 1.5 - (float)((float)((float)(v6 * 0.5) * v7) * v7);
	v9 = *v3 * (float)(v7 * v8);
	v3[2] = v5 * (float)(v7 * v8);
	v10 = v3[3];
	*v3 = v9;
	v3[1] = v4 * (float)(v7 * v8);
	v3[3] = v10 * (float)(v7 * v8);
}
