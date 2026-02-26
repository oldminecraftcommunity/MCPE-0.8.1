#include <level/gen/feature/LargeCaveFeature.hpp>
#include <math.h>
#include <tile/Tile.hpp>

LargeCaveFeature::~LargeCaveFeature() {
}
void LargeCaveFeature::addFeature(Level* level, int32_t a3, int32_t a4, int32_t a5, int32_t a6, uint8_t* blocks, int32_t a8) {
	Random* p_random; // r4
	int32_t v12;	  // r10
	int32_t v13;	  // r8
	int32_t v14;	  // r6
	int32_t v15;	  // r8
	int32_t v16;	  // r11
	int32_t i;		  // r6
	float v18;		  // s21
	int32_t v19;	  // r10
	float v20;		  // s20
	int32_t v21;	  // s14
	float f;		  // r0
	int32_t v23;	  // r12
	int32_t v24;	  // r5
	float v25;		  // s15
	float v26;		  // s25
	float v27;		  // s18
	float v28;		  // r0
	int32_t v29;	  // [sp+28h] [bp-60h]
	int32_t v30;	  // [sp+2Ch] [bp-5Ch]

	p_random = &this->random;
	v12 = this->random.genrand_int32();
	v13 = p_random->genrand_int32();
	v14 = p_random->genrand_int32();
	if(p_random->genrand_int32() % 0xF) {
		v15 = 0;
	} else {
		v15 = v14 % (v13 % (v12 % 0x28u + 1) + 1);
	}
	v16 = 16 * a4;
	v30 = 16 * a3;
	for(i = 0; i < v15; ++i) {
		v18 = (float)(int32_t)(v30 + (p_random->genrand_int32() & 0xF));
		v19 = p_random->genrand_int32();
		v20 = (float)(int32_t)(p_random->genrand_int32() % (v19 % 0x78u + 8));
		v21 = (p_random->genrand_int32() & 0xF) + v16;
		if(p_random->genrand_int32() << 30) {
			v23 = 1;
		} else {
			f = p_random->nextFloat();
			LargeCaveFeature::addTunnel(a5, a6, blocks, v18, v20, (float)v21, (float)(f * 6.0) + 1.0, 0.0, 0.0, -1, -1, 0.5);
			v23 = (p_random->genrand_int32() & 3) + 1;
		}
		v24 = 0;
		do {
			v29 = v23;
			++v24;
			v25 = p_random->nextFloat() * 3.1416;
			v26 = p_random->nextFloat();
			v27 = p_random->nextFloat();
			v28 = p_random->nextFloat();
			LargeCaveFeature::addTunnel(a5, a6, blocks, v18, v20, (float)v21, (float)(v27 + v27) + v28, v25 + v25, (float)((float)(v26 - 0.5) + (float)(v26 - 0.5)) * 0.125, 0, 0, 1.0);
			v23 = v29;
		} while(v24 < v29);
	}
}
void LargeCaveFeature::addTunnel(int32_t a2, int32_t a3, uint8_t* blocks, float a5, float a6, float a7, float a8, float a9, float a10, int32_t a11, int32_t a12, float a13) {
	int32_t v17;   // r9
	int32_t v19;   // r8
	int32_t v20;   // r10
	int32_t v21;   // r6
	uint32_t v22;  // r0
	float v23;	   // s27
	float v24;	   // s28
	int32_t range; // r5
	float v26;	   // s26
	float v27;	   // s23
	float v28;	   // s16
	double v29;	   // d6
	double v30;	   // d8
	float v31;	   // s15
	float v32;	   // r2
	float v33;	   // s16
	float v34;	   // s16
	float v35;	   // s16
	float v36;	   // s16
	float v37;	   // s16
	float v38;	   // r0
	float v39;	   // s25
	float v40;	   // r0
	float v41;	   // s16
	float v42;	   // s15
	int32_t v43;   // r5
	int32_t v44;   // r5
	int32_t v45;   // r8
	double v46;	   // r0
	int32_t v47;   // r8
	int32_t v48;   // r11
	double v49;	   // r0
	int32_t v50;   // r7
	double v51;	   // r0
	int32_t v52;   // r6
	double v53;	   // r0
	int32_t v54;   // r12
	double v55;	   // d6
	int32_t v56;   // r1
	int32_t v57;   // r0
	int32_t v58;   // r3
	int32_t v59;   // r7
	bool_t v60;	   // r7
	uint32_t v61;  // r3
	int32_t v62;   // r2
	int32_t v63;   // r0
	uint8_t* v64;  // r2
	float v65;	   // s8
	float v66;	   // s6
	float v67;	   // s6
	int32_t v68;   // r3
	int32_t v69;   // r7
	uint8_t* v70;  // r1
	float v71;	   // s11
	int32_t v72;   // r8
	int32_t v73;   // [sp+2Ch] [bp-A9Ch]
	int32_t v74;   // [sp+38h] [bp-A90h]
	int32_t v75;   // [sp+44h] [bp-A84h]
	double v76;	   // [sp+50h] [bp-A78h]
	int32_t v77;   // [sp+50h] [bp-A78h]
	int32_t v82;   // [sp+6Ch] [bp-A5Ch]
	int32_t v83;   // [sp+70h] [bp-A58h]
	int32_t v84;   // [sp+74h] [bp-A54h]
	uint32_t v85;  // [sp+80h] [bp-A48h]
	uint32_t v86;  // [sp+84h] [bp-A44h]

	v17 = a12;
	v83 = 16 * a2;
	v19 = 16 * a3;
	v20 = a11;
	v21 = 16 * a2 + 8;
	v84 = 16 * a3;
	v22 = this->random.genrand_int32();
	v23 = (float)v21;
	v24 = (float)(v19 + 8);
	Random random(v22 >> 1); // [sp+90h] [bp-A38h] BYREF
	if(a12 <= 0) {
		range = this->range;
		v17 = 16 * (range - 1) - random.genrand_int32() % (16 * (range - 1) / 4);
	}
	if(a11 == -1) {
		v82 = 1;
		v20 = v17 / 2;
	} else {
		v82 = 0;
	}
	v26 = 0.0;
	v27 = 0.0;
	v85 = random.genrand_int32() % (v17 / 2) + v17 / 4;
	v86 = random.genrand_int32() % 6;
	while(v20 < v17) {
		v76 = sin((float)((float)((float)v20 * 3.1416) / (float)v17));
		v28 = cos(a10);
		v29 = sin(a10);
		v30 = v28;
		a5 = a5 + cos(a9) * v30;
		v31 = v29;
		a6 = a6 + v31;
		a7 = a7 + sin(a9) * v30;
		if(v86) {
			v32 = 0.7;
		} else {
			v32 = 0.92;
		}
		a9 = a9 + (float)(v27 * 0.1);
		a10 = (float)(a10 * v32) + (float)(v26 * 0.1);
		v33 = random.nextFloat();
		v34 = v33 - random.nextFloat();
		v35 = v34 * random.nextFloat();
		v26 = (float)(v26 * 0.9) + (float)(v35 + v35);
		v36 = random.nextFloat();
		v37 = v36 - random.nextFloat();
		v27 = (float)(v27 * 0.75) + (float)((float)(v37 * random.nextFloat()) * 4.0);
		if(v82) {
			goto LABEL_73;
		}
		if(v20 == v85 && a8 > 1.0) {
			v38 = random.nextFloat();
			v39 = a10 / 3.0;
			this->addTunnel(a2, a3, blocks, a5, a6, a7, (float)(v38 * 0.5) + 0.5, a9 - (float)(3.1416 * 0.5), v39, v20, v17, 1.0);
			v40 = random.nextFloat();
			this->addTunnel(a2, a3, blocks, a5, a6, a7, (float)(v40 * 0.5) + 0.5, a9 + (float)(3.1416 * 0.5), v39, v20, v17, 1.0);
			return;
		}
		if(random.genrand_int32() << 30) {
LABEL_73:
			if((float)((float)((float)((float)(a7 - v24) * (float)(a7 - v24)) + (float)((float)(a5 - v23) * (float)(a5 - v23))) - (float)((float)(v17 - v20) * (float)(v17 - v20))) > (float)((float)((float)(a8 + 2.0) + 16.0) * (float)((float)(a8 + 2.0) + 16.0))) {
				return;
			}
			v41 = v76 * a8 + 1.5;
			v42 = v41 + v41;
			if(a5 >= (float)((float)(v23 - 16.0) - (float)(v41 + v41)) && a7 >= (float)((float)(v24 - 16.0) - v42) && a5 <= (float)((float)(v23 + 16.0) + v42) && a7 <= (float)((float)(v24 + 16.0) + v42)) {
				v43 = (int32_t)floor((float)(a5 - v41)) - 16 * a2;
				v44 = (v43 - 1) & ~((v43 - 1) >> 31);
				v45 = (int32_t)floor((float)(a5 + v41)) - 16 * a2;
				v46 = floor((float)(a6 - (float)(v41 * a13)));
				v47 = v45 + 1;
				if(v47 >= 16) {
					v47 = 16;
				}
				v48 = (int32_t)v46 - 1;
				v49 = floor((float)(a6 + (float)(v41 * a13)));
				if(v48 < 1) {
					v48 = 1;
				}
				v50 = (int32_t)v49 + 1;
				v51 = floor((float)(a7 - v41));
				if(v50 >= 120) {
					v50 = 120;
				}
				v52 = (int32_t)v51 - 16 * a3;
				v53 = floor((float)(a7 + v41));
				v77 = v47;
				v74 = v50;
				v54 = (v52 - 1) & ~((v52 - 1) >> 31);
				v55 = v53;
				v56 = v44;
				v57 = 16 * v44;
				v58 = (int32_t)v55 - 16 * a3 + 1;
				if(v58 >= 16) {
					v58 = 16;
				}
				v75 = v58;
				v73 = v48 - 1;
				while(v56 < v47) {
					v62 = (v52 - 1) & ~((v52 - 1) >> 31);
					while(v62 < v75) {
						v61 = v74 + 1;
						while((int32_t)v61 >= v73) {
							if(v61 > 0x7F) {
								v60 = 0;
							} else {
								v59 = blocks[128 * (v62 + v57) + v61];
								v60 = v59 == Tile::water->blockID || v59 == Tile::calmWater->blockID;
								if(v61 != v73 && v56 != v44 && v56 != v47 - 1 && v62 != v54 && v62 != v75 - 1) {
									v61 = v48;
								}
							}
							--v61;
							if(v60) {
								goto LABEL_43;
							}
						}
						v60 = 0;
LABEL_43:
						++v62;
						if(v60) {
							goto LABEL_48;
						}
					}
					v60 = 0;
LABEL_48:
					++v56;
					v57 += 16;
					if(v60) {
						goto LABEL_15;
					}
				}
				while(v44 < v77) {
					v63 = (v52 - 1) & ~((v52 - 1) >> 31);
					v64 = &blocks[128 * (v54 + 16 * v44)];
					v65 = (float)((float)((float)(v44 + v83) + 0.5) - a5) / v41;
					while(v63 < v75) {
						v66 = (float)((float)((float)(v84 + v63) + 0.5) - a7) / v41;
						v67 = v66 * v66;
						if((float)((float)(v65 * v65) + v67) < 1.0) {
							v68 = v74 - 1;
							v69 = 0;
							v70 = &v64[v74 - 1];
							while(v68 >= v48) {
								v71 = (float)((float)((float)v68 + 0.5) - a6) / (float)(v41 * a13);
								if(v71 > -0.7 && (float)((float)((float)(v65 * v65) + (float)(v71 * v71)) + v67) < 1.0) {
									v72 = v70[1];
									if(v72 == Tile::grass->blockID) {
										v69 = 1;
									}
									if(v72 == Tile::rock->blockID || v72 == Tile::dirt->blockID || v72 == Tile::grass->blockID) {
										if(v68 > 9) {
											v70[1] = 0;
											if(v69) {
												if(v64[v68] == Tile::dirt->blockID) {
													v64[v68] = Tile::grass->blockID;
												}
											}
										} else {
											v70[1] = Tile::lava->blockID;
										}
									}
								}
								--v68;
								--v70;
							}
						}
						++v63;
						v64 += 128;
					}
					++v44;
				}
				if(v82) {
					return;
				}
			}
		}
LABEL_15:
		++v20;
	}
}
