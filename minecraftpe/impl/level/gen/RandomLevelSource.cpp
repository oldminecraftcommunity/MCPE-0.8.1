#include <level/gen/RandomLevelSource.hpp>
#include <level/BiomeSource.hpp>
#include <level/Level.hpp>
#include <level/MobSpawner.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/gen/feature/CactusFeature.hpp>
#include <level/gen/feature/ClayFeature.hpp>
#include <level/gen/feature/FlowerFeature.hpp>
#include <level/gen/feature/OreFeature.hpp>
#include <level/gen/feature/ReedsFeature.hpp>
#include <level/gen/feature/SpringFeature.hpp>
#include <math.h>
#include <tile/HeavyTile.hpp>
#include <tile/material/Material.hpp>
#include <utils.h>

RandomLevelSource::RandomLevelSource(struct Level* a2, int32_t a3, int32_t a4, bool a5) //long, int, bool
	: random(a3),
	octave16noise_1(&this->random, 16)
	, octave16noise_2(&this->random, 16)
	, octave8noise_1(&this->random, 8)
	, octave4noise_1(&this->random, 4)
	, octave4noise_2(&this->random, 4)
	, octave10noise_1(&this->random, 10)
	, octave16noise_3(&this->random, 16)
	, treeNoise(&this->random, 8) {
	this->field_4 = 0;

	this->level = a2;
	this->field_72CC = a5;
	this->interpolationNoises = 0;
	this->upperInterpolationNoises = 0;
	this->lowerInterpolationNoises = 0;
	this->biomeNoises = 0;
	this->depthNoises = 0;
	this->field_7EE8 = 0;
	this->field_7EEC = 0;
	for(int32_t v8 = 0; v8 != 32; ++v8) {
		for(int32_t i = 0; i != 32; ++i) {
			this->field_9E0[v8 * 32 + i] = 0;
		}
	}
	this->field_72D0 = new float[1024];
	Random v12 = this->random;
	printf("random.get : %d\n", v12.genrand_int32() >> 1);
}
void RandomLevelSource::buildSurfaces(int32_t a2, int32_t a3, uint8_t* a4, struct Biome** a5) {
	float v5;			 // s17
	float v8;			 // s16
	int32_t v9;			 // r12
	float v10;			 // s17
	int32_t v11;		 // r6
	int32_t v12;		 // r4
	float f;			 // r0
	float v14;			 // s18
	float v15;			 // s17
	float f1;			 // r0
	float v17;			 // s22
	float v18;			 // s18
	float f2;			 // r0
	int32_t fillerBlock; // r7
	int32_t topBlock;	 // r3
	uint8_t* v22;		 // r9
	int32_t v23;		 // r1
	int32_t blockID_low; // r1
	int8_t v25;			 // r0
	int32_t v26;		 // r11
	int32_t v27;		 // [sp+20h] [bp-68h]
	int32_t v28;		 // [sp+20h] [bp-68h]
	int32_t v29;		 // [sp+24h] [bp-64h]
	float* v30;			 // [sp+28h] [bp-60h]
	Biome* v31;			 // [sp+2Ch] [bp-5Ch]
	int32_t v32;		 // [sp+30h] [bp-58h]
	int32_t v33;		 // [sp+34h] [bp-54h]
	Biome** v34;		 // [sp+38h] [bp-50h]

	v5 = (float)(16 * a2);
	v8 = (float)(16 * a3);
	this->octave4noise_1.getRegion(this->field_72D4, v5, v8, 0.0, 16, 16, 1, 0.03125, 0.03125, 1.0);
	this->octave4noise_1.getRegion(this->field_76D4, v5, 109.01, v8, 16, 1, 16, 0.03125, 1.0, 0.03125);
	this->octave4noise_2.getRegion(this->field_7AD4, v5, v8, 0.0, 16, 16, 1, 0.0625, 0.0625, 0.0625);

	//taken from Minecraft013Server(which took it from some b1.4 mod+changes from 0.1.3)
	//arm version produced weird results
	//x86 version inlined random calls so the function is mess
	for(int blockX = 0; blockX < 16; ++blockX) {
		for(int blockZ = 0; blockZ < 16; ++blockZ) {
			Biome* biome = a5[blockX + (blockZ * 16)];
			bool z = this->field_72D4[blockX + (blockZ * 16)] + (this->random.nextFloat() * 0.2f) > 0.0f;
			bool z2 = this->field_76D4[blockX + (blockZ * 16)] + (this->random.nextFloat() * 0.2f) > 3.0f;
			int nextFloat = (int)((this->field_7AD4[blockX + (blockZ * 16)] / 3.0f) + 3.0f + (this->random.nextFloat() * 0.25f));
			int i = -1;
			int b = biome->topBlock;
			int b2 = biome->fillerBlock;
			for(int blockY = 127; blockY >= 0; --blockY) {
				int index = (blockZ * 16 + blockX) * 128 + blockY;
				if((this->random.genrand_int32() % 5) >= blockY) {
					a4[index] = Tile::unbreakable->blockID;
				} else {
					int b3 = a4[index];
					if(b3 == 0) {
						i = -1;
					} else if(b3 == Tile::rock->blockID) {
						if(i == -1) {
							if(nextFloat > 0) {
								if(blockY >= 60 && blockY <= 65) {
									b = biome->topBlock;
									b2 = biome->fillerBlock;
									if(z2) {
										b = 0;
										b2 = Tile::gravel->blockID;
									}
									if(z) {
										b = Tile::sand->blockID;
										b2 = Tile::sand->blockID;
									}
								}

							} else {
								b = 0;
								b2 = Tile::rock->blockID;
							}

							if (blockY < 64 && b == 0) {
								b = Tile::calmWater->blockID;
							}
							i = nextFloat;
							if (blockY >= 63) {
								a4[index] = b;
							} else {
								a4[index] = b2;
							}
						} else if (i > 0) {
							--i;
							a4[index] = b2;
							if (i == 0 && b2 == Tile::sand->blockID) {
								i = (this->random.genrand_int32() % 4);
								b2 = Tile::sandStone->blockID;
							}
						}

					}
				}
			}
		}
	}
}
void RandomLevelSource::calcWaterDepths(struct ChunkSource* a2, int32_t a3, int32_t a4) {
	Level* level;  // r4
	int32_t x;	   // r9
	int32_t z;	   // r10
	int32_t y;	   // r5
	int32_t v8;	   // r6
	int32_t v9;	   // r3
	int32_t v10;   // r0
	int32_t i;	   // r7
	int32_t v12;   // r8
	int32_t v13;   // r2
	int32_t v14;   // [sp+8h] [bp-58h]
	int32_t v15;   // [sp+Ch] [bp-54h]
	int32_t v16;   // [sp+10h] [bp-50h]
	int32_t v17;   // [sp+14h] [bp-4Ch]
	int32_t v18;   // [sp+18h] [bp-48h]
	int32_t xsub2; // [sp+1Ch] [bp-44h]
	uint32_t v20;  // [sp+20h] [bp-40h]
	int32_t v21;   // [sp+2Ch] [bp-34h]
	uint32_t v22;  // [sp+30h] [bp-30h]

	level = this->level;
	x = 16 * a3 + 8;
	v21 = 16 * a4;
	v17 = 16;
	do {
		z = v21;
		v15 = 0;
		xsub2 = x - 2;
		y = level->getSeaLevel();
		do {
			v8 = z + 7;
			if(level->getHeightmap(x - 1, z + 7) <= 0 && (level->getHeightmap(xsub2, z + 7) > 0 || level->getHeightmap(x, z + 7) > 0 || level->getHeightmap(x - 1, z + 6) > 0 || level->getHeightmap(x - 1, z + 8) > 0) && (level->getTile(xsub2, y, z + 7) == Tile::calmWater->blockID && level->getData(xsub2, y, z + 7) <= 6 || level->getTile(x, y, z + 7) == Tile::calmWater->blockID && level->getData(x, y, z + 7) <= 6 || level->getTile(x - 1, y, z + 6) == Tile::calmWater->blockID && level->getData(x - 1, y, z + 6) <= 6 || level->getTile(x - 1, y, z + 8) == Tile::calmWater->blockID && level->getData(x - 1, y, z + 8) <= 6)) {
				for(i = -5; i != 6; ++i) {
					v14 = -5;
					v22 = abs(i); //abs32(i);
					v18 = x - 1 + i;
					do {
						v9 = v14;
						if(v14 < 0) {
							v9 = -v14;
						}
						v20 = v22 + v9;
						if((int32_t)(v22 + v9) <= 5) {
							v16 = v8 + v14;
							if(level->getTile(v18, y, v8 + v14) == Tile::calmWater->blockID) {
								v10 = level->getData(v18, y, v16);
								if(v10 <= 6 && v10 < (int32_t)(6 - v20)) {
									level->setData(v18, y, v16, 6 - v20, 4);
								}
							}
						}
						++v14;
					} while(v14 != 6);
				}
				v12 = 0;
				level->setTileAndDataNoUpdate(x - 1, y, z + 7, Tile::calmWater->blockID, 7);
				while(v12 < y) {
					v13 = v12++;
					level->setTileAndDataNoUpdate(x - 1, v13, z + 7, Tile::calmWater->blockID, 8);
				}
			}
			++z;
			++v15;
		} while(v15 != 16);
		++x;
		--v17;
	} while(v17);
}
float* RandomLevelSource::getHeights(float* heights, int32_t chunkX, int32_t chunkY, int32_t chunkZ, int32_t scaleX, int32_t scaleY, int32_t scaleZ) {
	float* rainfallNoises;	  // r11
	float* temperatureNoises; // r10
	float v14;				  // s17
	int32_t v15;			  // r0
	int32_t v16;			  // r3
	int32_t v17;			  // r9
	int32_t v18;			  // r10
	int32_t v19;			  // r0
	int32_t v20;			  // r11
	int32_t i;				  // r12
	float v22;				  // s8
	int32_t v23;			  // r1
	float v24;				  // s11
	float v25;				  // s15
	float v26;				  // s14
	float v27;				  // s14
	float v28;				  // s14
	int32_t v29;			  // r1
	int32_t v30;			  // r2
	float v31;				  // s15
	float v32;				  // s14
	float v33;				  // s11
	float v34;				  // s7
	float v35;				  // s8
	float v36;				  // s11
	float* v37;				  // r4
	int32_t v39;			  // [sp+24h] [bp-6Ch]
	int32_t v40;			  // [sp+28h] [bp-68h]
	float* v42;				  // [sp+3Ch] [bp-54h]
	float* v43;				  // [sp+48h] [bp-48h]

	rainfallNoises = this->level->getBiomeSource()->rainfallNoises;
	temperatureNoises = this->level->getBiomeSource()->temperatureNoises;
	this->biomeNoises = this->octave10noise_1.getRegion(this->biomeNoises, chunkX, chunkZ, scaleX, scaleZ, 1.121, 1.121, 0.5);
	v14 = (float)chunkY;
	this->depthNoises = this->octave16noise_3.getRegion(this->depthNoises, chunkX, chunkZ, scaleX, scaleZ, 200.0, 200.0, 0.5);
	this->interpolationNoises = this->octave8noise_1.getRegion(this->interpolationNoises, (float)chunkX, v14, (float)chunkZ, scaleX, scaleY, scaleZ, 8.5552, 4.2776, 8.5552);
	this->upperInterpolationNoises = this->octave16noise_1.getRegion(this->upperInterpolationNoises, (float)chunkX, v14, (float)chunkZ, scaleX, scaleY, scaleZ, 684.41, 684.41, 684.41);
	this->lowerInterpolationNoises = this->octave16noise_2.getRegion(this->lowerInterpolationNoises, (float)chunkX, v14, (float)chunkZ, scaleX, scaleY, scaleZ, 684.41, 684.41, 684.41);
	v40 = scaleY & ~(scaleY >> 31);
	v15 = 17 * (16 / scaleX / 2);
	v16 = 0;
	v17 = 0;
	v39 = 0;
	v42 = &rainfallNoises[v15];
	v43 = &temperatureNoises[v15];
	v18 = 0;
	while(v17 < scaleX) {
		v19 = 0;
		v20 = v18;
		for(i = 0; i < scaleZ; ++i) {
			v22 = 1.0 - (float)(v43[v16 + v19] * v42[v16 + v19]);
			v23 = i + v39;
			v24 = this->depthNoises[v23] / 8000.0;
			v25 = (float)((float)(this->biomeNoises[v23] + 256.0) * 0.0019531) * (float)(1.0 - (float)((float)(v22 * v22) * (float)(v22 * v22)));
			if(v25 > 1.0) {
				v25 = 1.0;
			}
			if(v24 < 0.0) {
				v24 = -(float)(v24 * 0.3);
			}
			v26 = (float)(v24 * 3.0) - 2.0;
			if(v26 >= 0.0) {
				if(v26 > 1.0) {
					v26 = 1.0;
				}
				v28 = v26 * 0.125;
				if(v25 < 0.0) {
					v25 = 0.0;
				}
			} else {
				v27 = v26 * 0.5;
				if(v27 < -1.0) {
					v27 = -1.0;
				}
				v25 = 0.0;
				v28 = (float)(v27 / 1.4) * 0.5;
			}
			v29 = v20;
			v30 = 0;
			v31 = v25 + 0.5;
			v32 = (float)((float)((float)(v28 * (float)scaleY) * 0.0625) * 4.0) + (float)((float)scaleY * 0.5);
			while(v30 < scaleY) {
				v33 = (float)((float)((float)v30 - v32) * 12.0) / v31;
				v34 = (float)((float)(this->interpolationNoises[v29] / 10.0) + 1.0) * 0.5;
				if(v33 < 0.0) {
					v33 = v33 * 4.0;
				}
				v35 = this->upperInterpolationNoises[v29] * 0.0019531;
				if(v34 >= 0.0) {
					if(v34 > 1.0) {
						v35 = this->lowerInterpolationNoises[v29] * 0.0019531;
					} else {
						v35 = v35 + (float)((float)((float)(this->lowerInterpolationNoises[v29] * 0.0019531) - v35) * v34);
					}
				}
				v36 = v35 - v33;
				if(scaleY - 3 <= v30) {
					v36 = (float)((float)((float)(4 - scaleY + v30) / 3.0) * -10.0) + (float)(v36 * (float)(1.0 - (float)((float)(4 - scaleY + v30) / 3.0)));
				}
				++v30;
				v37 = &heights[v29++];
				*v37 = v36;
			}
			v20 += v40;
			v19 += /*4 **/ (16 / scaleX);
		}
		++v17;
		v18 += (scaleZ & ~(scaleZ >> 31)) * v40;
		v16 += ((16 / scaleX) << 6) / 4;
		v39 += scaleZ & ~(scaleZ >> 31);
	}
	return heights;
}

void RandomLevelSource::prepareHeights(int32_t a2, int32_t a3, uint8_t* a4, void* a5, float* a6) {
	//XXX either ida(and ghidra) makes some terrible mistakes when decompiling arm stuff or it uses slightly different array filling algo
	//XXX uses x86 version
	float* heights;	  // ecx
	float* v7;		  // edx
	float* v8;		  // eax
	float* v9;		  // ebp
	float v10;		  // xmm3_4
	int v11;		  // eax
	float v12;		  // xmm2_4
	int v13;		  // ecx
	float v14;		  // xmm0_4
	uint8_t* v15;	  // ecx
	float v16;		  // xmm1_4
	int v17;		  // edx
	int v18;		  // esi
	int v19;		  // eax
	int v20;		  // eax
	uint8_t* v21;	  // ecx
	float v22;		  // xmm1_4
	int v23;		  // edx
	int v24;		  // eax
	uint8_t* v25;	  // ecx
	float v26;		  // xmm1_4
	int v27;		  // edx
	int v29;		  // eax
	int v30;		  // [esp+28h] [ebp-74h]
	int v31;		  // [esp+2Ch] [ebp-70h]
	float v32;		  // [esp+34h] [ebp-68h]
	float v33;		  // [esp+38h] [ebp-64h]
	int v34;		  // [esp+3Ch] [ebp-60h]
	float v35;		  // [esp+40h] [ebp-5Ch]
	float v36;		  // [esp+44h] [ebp-58h]
	int v37;		  // [esp+48h] [ebp-54h]
	float v38;		  // [esp+4Ch] [ebp-50h]
	float v39;		  // [esp+50h] [ebp-4Ch]
	float v40;		  // [esp+54h] [ebp-48h]
	float v41;		  // [esp+58h] [ebp-44h]
	float* v42;		  // [esp+5Ch] [ebp-40h]
	unsigned int v43; // [esp+64h] [ebp-38h]
	int v44;		  // [esp+68h] [ebp-34h]
	int v45;		  // [esp+6Ch] [ebp-30h]
	int v46;		  // [esp+78h] [ebp-24h]

	this->field_72D0 = heights = this->getHeights(this->field_72D0, 4 * a2, 0, 4 * a3, 5, 17, 5);
	v34 = 0;
	while(2) {
		v44 = 85 * v34;
		v45 = 85 * v34 + 340;
		v42 = a6;
		v46 = 0;
		while(2) {
			v43 = 0;
			while(2) {
				v7 = &heights[(v44 + v43) / 4];
				v37 = 0;
				v32 = *v7;
				v33 = heights[(v44 + v43 + 68) / 4];
				v8 = &heights[v43 / 4 + v45 / 4];
				v35 = *v8;
				v36 = heights[(v45 + v43 + 68)/4];
				v31 = 2 * v43;
				v38 = 0.125 * (float)(v7[1] - *v7);
				v39 = 0.125 * (float)(v7[18] - v33);
				v40 = 0.125 * (float)(v8[1] - *v8);
				v41 = 0.125 * (float)(v8[18] - v36);
				do {
					v9 = v42;
					v10 = v33;
					v11 = 0;
					v12 = v32;
					do {
						v13 = (v46 << 7) | v31 | ((v11 + v34) << 11);
						v14 = (float)(v10 - v12) * 0.25;
						if(v31 > 63) {
							v15 = &a4[v13];
							v16 = v12;
							v17 = 0;
							v18 = v11;
							do {
								v19 = 0;
								if(v16 > 0.0) v19 = Tile::rock->blockID;
								++v17;
								*v15 = v19;
								v15 += 128;
								v16 = v16 + v14;
							} while(v17 != 4);
LABEL_11:
							v20 = v18;
							goto LABEL_12;
						}
						if(v31 == 63) {
							v25 = &a4[v13];
							v26 = v12;
							v27 = 0;
							v18 = v11;
							do {
								if(v9[v27] >= 0.5) {
									v29 = Tile::calmWater->blockID;
								} else {
									v29 = Tile::ice->blockID;
								}
								if(v26 > 0.0) v29 = Tile::rock->blockID;
								++v27;
								*v25 = v29;
								v25 += 128;
								v26 = v26 + v14;
							} while(v27 != 4);
							goto LABEL_11;
						}
						v21 = &a4[v13];
						v22 = v12;
						v23 = 0;
						v30 = v11;
						do {
							v24 = Tile::calmWater->blockID;
							if(v22 > 0.0) v24 = Tile::rock->blockID;
							++v23;
							*v21 = v24;
							v21 += 128;
							v22 = v22 + v14;
						} while(v23 != 4);
						v20 = v30;
LABEL_12:
						v11 = v20 + 1;
						v9 += 16;
						v12 = v12 + (float)((float)(v35 - v32) * 0.25);
						v10 = v10 + (float)((float)(v36 - v33) * 0.25);
					} while(v11 != 4);
					++v37;
					++v31;
					v32 = v32 + v38;
					v33 = v33 + v39;
					v35 = v35 + v40;
					v36 = v36 + v41;
				} while(v37 != 8);
				v43 += 4;
				if(v43 != 64) {
					heights = this->field_72D0;
					continue;
				}
				break;
			}
			v46 += 4;
			v42 += 4;
			if(v46 != 16) {
				v45 += 68;
				v44 += 68;
				heights = this->field_72D0;
				continue;
			}
			break;
		}
		v34 += 4;
		a6 += 64;
		if(v34 != 16) {
			heights = this->field_72D0;
			continue;
		}
		break;
	}
}

RandomLevelSource::~RandomLevelSource() {
	if(this->field_72D0) {
		delete[] this->field_72D0;
	}
	if(this->interpolationNoises) {
		delete[] this->interpolationNoises;
	}

	if(this->upperInterpolationNoises) {
		delete[] this->upperInterpolationNoises;
	}

	if(this->lowerInterpolationNoises) {
		delete[] this->lowerInterpolationNoises;
	}

	if(this->biomeNoises) {
		delete[] this->biomeNoises;
	}

	if(this->depthNoises) {
		delete[] this->depthNoises;
	}

	if(this->field_7EE8) {
		delete[] this->field_7EE8;
	}

	if(this->field_7EEC) {
		delete[] this->field_7EEC;
	}
}
bool_t RandomLevelSource::hasChunk(int32_t x, int32_t z) {
	return 1;
}
struct LevelChunk* RandomLevelSource::getChunk(int32_t chunkX, int32_t chunkZ) {
	uint32_t v5;		// r10
	int32_t v6;			// r2
	int32_t v9;			// r10
	LevelChunk* chunk;	// r6
	uint8_t* chunkData; // r8
	Biome** v16;		// r10

	v5 = chunkZ & 0x7FFF | ((chunkX & 0x7FFF) << 16) | chunkX & 0x80000000;
	if(chunkZ >= 0) {
		v6 = 0;
	} else {
		v6 = 0x8000;
	}
	v9 = v5 | v6;
	auto&& p = this->field_19E0.find(v9);
	if(p != this->field_19E0.end()) {
		return p->second;
	}

	this->random.setSeed(132899541 * chunkZ + 341872712 * chunkX);
	chunkData = new uint8_t[0x8000u];
	chunk = new LevelChunk(this->level, chunkData, chunkX, chunkZ);
	this->field_19E0.insert({v9, chunk});

	v16 = this->level->getBiomeSource()->getBiomeBlock(16 * chunkX, 16 * chunkZ, 16, 16);
	this->prepareHeights(chunkX, chunkZ, chunkData, 0, this->level->getBiomeSource()->rainfallNoises);
	this->buildSurfaces(chunkX, chunkZ, chunkData, v16);
	chunk->recalcHeightmap();
	return chunk;
}

struct LevelChunk* RandomLevelSource::create(int32_t x, int32_t z) {
	return this->getChunk(x, z);
}
static double _D6E52C58 = 0;
void RandomLevelSource::postProcess(struct ChunkSource* a2, int32_t chunkX, int32_t chunkZ) {
	this->level->field_12 = 1;
	int32_t chunkXStart = 16 * chunkX;
	int32_t chunkZStart = 16 * chunkZ;
	HeavyTile::instaFall = 1;

	BiomeSource* bs = this->level->getBiomeSource();
	Biome* biomeAtChunk = bs->getBiome(chunkXStart + 16, chunkZStart + 16);
	this->random.setSeed(this->level->getSeed());
	int v11 = this->random.genrand_int32();
	int v12 = (2 * (this->random.genrand_int32() >> 2) + 1) * chunkZ;
	this->random.setSeed((v12 + (2 * (v11 >> 2) + 1) * chunkX) ^ this->level->getSeed());
	double timeS = getTimeS();
	Random* a8 = &this->random;
	for(int32_t v14 = 0; v14 < 10; ++v14) {
		int32_t v16 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v17 = a8->genrand_int32();
		int32_t v18 = chunkZStart + (a8->genrand_int32() & 0xF);
		ClayFeature f;
		f.place(this->level, a8, v16, v17 & 0x7F, v18);
	}
	for(int32_t v20 = 0; v20 < 20; ++v20) {
		int32_t v21 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v22 = a8->genrand_int32();
		int8_t v23 = a8->genrand_int32();
		int32_t z = chunkZStart + (v23 & 0xF);
		OreFeature f(Tile::dirt->blockID, 32);
		f.place(this->level, a8, v21, v22 & 0x7F, z);
	}
	for(int32_t v25 = 0; v25 < 10; ++v25) {
		int32_t v26 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v27 = a8->genrand_int32();
		int8_t v28 = a8->genrand_int32();
		int32_t v29 = chunkZStart + (v28 & 0xF);
		OreFeature f(Tile::gravel->blockID, 32);
		f.place(this->level, a8, v26, v27 & 0x7F, v29);
	}
	for(int v30 = 0; v30 < 20; ++v30) {
		int32_t v31 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v32 = a8->genrand_int32();
		int8_t v33 = a8->genrand_int32();
		int32_t v34 = chunkZStart + (v33 & 0xF);
		OreFeature f(Tile::coalOre->blockID, 16);
		f.place(this->level, a8, v31, v32 & 0x7F, v34);
	}
	for(int v36 = 0; v36 < 20; ++v36) {
		int32_t v37 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v38 = a8->genrand_int32();
		int8_t v39 = a8->genrand_int32();
		int32_t v40 = chunkZStart + (v39 & 0xF);
		OreFeature f(Tile::ironOre->blockID, 8);
		f.place(this->level, a8, v37, v38 & 0x3F, v40);
	}
	for(int v42 = 0; v42 < 2; ++v42) {
		int32_t v43 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v44 = a8->genrand_int32();
		int8_t v45 = a8->genrand_int32();
		int32_t v46 = chunkZStart + (v45 & 0xF);
		OreFeature f(Tile::goldOre->blockID, 8);
		f.place(this->level, a8, v43, v44 & 0x1F, v46);
	}
	for(int v48 = 0; v48 < 8; ++v48) {
		int32_t v49 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v50 = a8->genrand_int32();
		int8_t v51 = a8->genrand_int32();
		int32_t v52 = chunkZStart + (v51 & 0xF);
		OreFeature f(Tile::redStoneOre->blockID, 7);
		f.place(this->level, a8, v49, v50 & 0xF, v52);
	}
	{
		int32_t v54 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v55 = a8->genrand_int32();
		int8_t v56 = a8->genrand_int32();
		int32_t v57 = chunkZStart + (v56 & 0xF);
		OreFeature f(Tile::emeraldOre->blockID, 7);
		f.place(this->level, a8, v54, v55 & 0xF, v57);
	}
	{
		int32_t v59 = chunkXStart + (a8->genrand_int32() & 0xF);
		int8_t v60 = a8->genrand_int32();
		int32_t v61 = (v60 & 0xF) + (a8->genrand_int32() & 0xF);
		int8_t v62 = a8->genrand_int32();
		int32_t v63 = chunkZStart + (v62 & 0xF);
		OreFeature f(Tile::lapisOre->blockID, 6);
		f.place(this->level, a8, v59, v61, v63);
	}

	float v = this->treeNoise.getValue((float)chunkXStart * 0.5, (float)chunkZStart * 0.5);
	int v67 = (int)(float)((float)((float)((float)(a8->nextFloat() * 4.0) + (float)(v * 0.125)) + 4.0) / 3.0);
	int v68 = v67;
	int v69 = a8->genrand_int32() % 0xA;
	int32_t amountOfTrees = v69 == 0;
	if(biomeAtChunk == Biome::forest) {
		amountOfTrees += v67 + 2;
	}
	if(biomeAtChunk == Biome::rainForest) {
		amountOfTrees += v67 + 2;
	}
	if(biomeAtChunk == Biome::seasonalForest) {
		amountOfTrees += v67 + 1;
	}
	if(biomeAtChunk == Biome::taiga) {
		v68 = v67 + 1;
	}
	if(biomeAtChunk == Biome::taiga) {
		amountOfTrees += v68;
	}
	if(biomeAtChunk == Biome::desert) {
		amountOfTrees -= 20;
	}
	if(biomeAtChunk == Biome::tundra) {
		amountOfTrees -= 20;
	}
	if(biomeAtChunk == Biome::plains) {
		amountOfTrees -= 20;
	}
	for(int32_t v65 = 0; v65 < amountOfTrees; ++v65) {
		int32_t xx = chunkXStart + (a8->genrand_int32() & 0xF) + 8;
		int32_t zz = chunkZStart + (a8->genrand_int32() & 0xF) + 8;
		int32_t hm = this->level->getHeightmap(xx, zz);
		Feature* v74 = biomeAtChunk->getTreeFeature(a8);
		if(v74) {
			v74->init(1, 1, 1);
			v74->place(this->level, a8, xx, hm, zz);
			delete v74;
		}
	}
	for(int32_t v76 = 0; v76 < 2; ++v76) {
		int8_t v77 = a8->genrand_int32();
		int8_t v78 = a8->genrand_int32();
		int8_t v79 = a8->genrand_int32();
		FlowerFeature f(Tile::flower->blockID);
		f.place(this->level, a8, chunkXStart + (v77 & 0xF) + 8, v78 & 0x7F, chunkZStart + (v79 & 0xF) + 8);
	}
	if((a8->genrand_int32() & 1) == 0) {
		int8_t v80 = a8->genrand_int32();
		int8_t v81 = a8->genrand_int32();
		int8_t v82 = a8->genrand_int32();
		FlowerFeature f(Tile::rose->blockID);
		f.place(this->level, a8, chunkXStart + (v80 & 0xF) + 8, v81 & 0x7F, chunkZStart + (v82 & 0xF) + 8);
	}
	if((a8->genrand_int32() & 3) == 0) {
		int8_t v84 = a8->genrand_int32();
		int8_t v85 = a8->genrand_int32();
		int8_t v86 = a8->genrand_int32();
		FlowerFeature f(Tile::mushroom1->blockID);
		f.place(this->level, a8, chunkXStart + (v84 & 0xF) + 8, v85 & 0x7F, chunkZStart + (v86 & 0xF) + 8);
	}
	if((a8->genrand_int32() & 7) == 0) {
		int8_t v89 = a8->genrand_int32();
		int8_t v90 = a8->genrand_int32();
		int8_t v91 = a8->genrand_int32();
		FlowerFeature f(Tile::mushroom2->blockID);
		f.place(this->level, a8, chunkXStart + (v89 & 0xF) + 8, v90 & 0x7F, chunkZStart + (v91 & 0xF) + 8);
	}
	for(int32_t v95 = 0; v95 < 10; ++v95) {
		int8_t v96 = a8->genrand_int32();
		int8_t v97 = a8->genrand_int32();
		int8_t v98 = a8->genrand_int32();
		ReedsFeature f;
		f.place(this->level, a8, chunkXStart + (v96 & 0xF) + 8, v97 & 0x7F, chunkZStart + (v98 & 0xF) + 8);
	}
	int32_t cactiCnt;
	if(biomeAtChunk == Biome::desert) {
		cactiCnt = 5;
	} else {
		cactiCnt = 0;
	}
	for(int32_t v95 = 0; v95 < cactiCnt; ++v95) {
		int8_t v100 = a8->genrand_int32();
		int8_t v101 = a8->genrand_int32();
		int8_t v102 = a8->genrand_int32();
		CactusFeature f;
		f.place(this->level, a8, chunkXStart + (v100 & 0xF) + 8, v101 & 0x7F, chunkZStart + (v102 & 0xF) + 8);
	}
	for(int32_t v103 = 0; v103 < 50; ++v103) {
		int8_t v104 = a8->genrand_int32();
		int v137 = a8->genrand_int32();
		int v135 = a8->genrand_int32();
		int8_t v105 = a8->genrand_int32();
		SpringFeature f(Tile::water->blockID);
		f.place(this->level, a8, (v104 & 0xF) + chunkXStart + 8, v135 % (v137 % 0x78u + 8), chunkZStart + (v105 & 0xF) + 8);
	}
	for(int32_t v103 = 0; v103 < 20; ++v103) {
		int8_t v108 = a8->genrand_int32();
		int v138 = a8->genrand_int32();
		int v136 = a8->genrand_int32();
		int v109 = a8->genrand_int32();
		int8_t v110 = a8->genrand_int32();
		SpringFeature f(Tile::lava->blockID);
		f.place(this->level, a8, (v108 & 0xF) + chunkXStart + 8, v109 % (v136 % (v138 % 0x70u + 8) + 8), chunkZStart + (v110 & 0xF) + 8);
	}
	if(this->field_72CC) {
		MobSpawner::postProcessSpawnMobs(this->level, biomeAtChunk, chunkXStart + 8, chunkZStart + 8, 16, 16, a8);
	}

	int v113 = chunkXStart + 8;
	float* v114 = this->level->getBiomeSource()->getTemperatureBlock(chunkXStart + 8, chunkZStart + 8, 16, 16);
	while(chunkXStart + 23 >= v113) {
		int v119 = chunkZStart + 8;
		float* v142 = v114;
		while(chunkZStart + 23 >= v119) {
			int topy = this->level->getTopSolidBlock(v113, v119);
			float v116 = *v142++;
			int v117 = topy;
			if((float)(v116 - (float)((float)((float)(topy - 64) * 0.015625) * 0.3)) < 0.5 && (unsigned int)(topy - 1) <= 0x7E && this->level->isEmptyTile(v113, topy, v119)) {
				Material* v118 = this->level->getMaterial(v113, v117 - 1, v119);
				if(v118->blocksMotion()) {
					if(Material::ice != this->level->getMaterial(v113, v117 - 1, v119)) {
						this->level->setTile(v113, v117, v119, Tile::topSnow->blockID, 4);
					}
				}
			}
			++v119;
		}
		++v113;
		v114 += 16;
	}
	_D6E52C58 = _D6E52C58 + getTimeS() - timeS;
	HeavyTile::instaFall = 0;
	this->level->field_12 = 0;
}
bool_t RandomLevelSource::tick() {
	return 0;
}
bool_t RandomLevelSource::shouldSave() {
	return 1;
}
std::vector<Biome::MobSpawnerData> RandomLevelSource::getMobsAt(const struct MobCategory& a3, int32_t a4, int32_t a5, int32_t a6) {
	BiomeSource* bs = this->level->getBiomeSource();
	if(bs) {
		Biome* v10 = bs->getBiome(a4, a6);
		if(v10) {
			return std::vector<Biome::MobSpawnerData>(*v10->getMobs(a3));
		}
	}
	return std::vector<Biome::MobSpawnerData>();
}
std::string RandomLevelSource::gatherStats() {
	return "RandomLevelSource";
}
