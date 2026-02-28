#include <level/MobSpawner.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <entity/MobCategory.hpp>
#include <tile/material/Material.hpp>
#include <entity/AgableMob.hpp>
#include <entity/Player.hpp>
#include <perf/Stopwatch.hpp>
#include <entity/MobFactory.hpp>


std::map<ChunkPos, bool> MobSpawner::chunksToPoll;

bool MobSpawner::addMob(Level* level, Mob* entity, float x, float y, float z, float yaw, float pitch, bool_t force) {
	entity->moveTo(x, y, z, yaw, pitch);
	if(force || entity->canSpawn()) {
		level->addEntity(entity);
		MobSpawner::finalizeMobSettings(entity, level, x, y, z);
		return 1;
	}
	return 0;
}
void MobSpawner::finalizeMobSettings(Mob* a1, Level* a2, float a3, float a4, float a5) {
	a1->finalizeMobSpawn();
	MobSpawner::makeBabyMob(a1, 0.5);
}
Pos MobSpawner::getRandomPosWithin(Level* a2, int32_t startChunkX, int32_t startChunkZ) {
	return {startChunkX + (int32_t)(a2->random.genrand_int32() & 0xf), (int32_t)(a2->random.genrand_int32() & 0x7f), startChunkZ + (int32_t)(a2->random.genrand_int32() & 0xf)};
}
bool_t MobSpawner::isSpawnPositionOk(const MobCategory& a1, Level* level, int32_t x, int32_t y, int32_t z){
	if(a1.material == Material::water) {
		if(!level->getMaterial(x, y, z)->isLiquid()) {
			return 0;
		}
	} else {
		if(!level->isSolidBlockingTile(x, y - 1, z)) {
			return 0;
		}
		if(level->isSolidBlockingTile(x, y, z)) {
			return 0;
		}
		if(level->getMaterial(x, y, z)->isLiquid()) {
			return 0;
		}
	}
	return !level->isSolidBlockingTile(x, y + 1, z);
}
void MobSpawner::makeBabyMob(Mob* a1, float chance) {
	static Random randomInstance2(0x5DEEA8F);
	if(a1->getCreatureBaseType() == 2) {
		if(randomInstance2.nextFloat() < chance) {
			((AgableMob*)a1)->setAge(-24000);
		}
	}
}
void MobSpawner::postProcessSpawnMobs(Level* a2, Biome* a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, Random* a8){
	std::vector<Biome::MobSpawnerData> v61 = *a3->getMobs(MobCategory::creature); //TODO check
	if(!v61.empty()) {
		while(1) {
			float v26 = a8->nextFloat();
			if(v26 >= a3->getCreatureProbability()) {
				break;
			}

			int totalrarity = 0;
			for(auto&& msd: v61) {
				totalrarity += msd.rarity;
			}

			int v30 = a2->random.genrand_int32() % totalrarity;
			Biome::MobSpawnerData* data;
			for(auto&& i: v61) {
				v30 -= i.rarity;
				if(v30 < 0) {
					data = &i;
					goto LABEL_15;
				}
			}
			data = 0;
LABEL_15:
			int min = data->min;
			int v33 = data->max + 1 - min;
			int v60 = min + a8->genrand_int32() % v33;
			int v58 = a4 + a8->genrand_int32() % a6;
			int v34 = 0;
			int v35 = v58;
			int v59 = a8->genrand_int32() % a7 + a5;
			int v50 = v59;
LABEL_34:
			int v55 = v34;
			if(v34 < v60) {
				int v56 = 4;
				while(1) {
					int top = a2->getTopSolidBlock(v35, v50);
					bool v43;
					if(MobSpawner::isSpawnPositionOk(MobCategory::creature, a2, v35, top, v50)) {
						Mob* mob = MobFactory::CreateMob(data->mobtype, a2);
						if(!mob) {
							if(!--v56) {
								v34 = v55 + 1;
								goto LABEL_34;
							}
							continue;
							//goto LABEL_24;
						}
						mob->moveTo((float)v35 + 0.5, (float)top, (float)v50 + 0.5, a8->nextFloat() * 360.0, 0.0);
						a2->addEntity(mob);
						v43 = 1;
						MobSpawner::finalizeMobSettings(mob, a2, (float)v35 + 0.5, (float)top, (float)v50 + 0.5);
					}
					else
					{
						v43 = 0;
					}

					v35 += a8->genrand_int32() % 5u - a8->genrand_int32() % 5;
					v50 += a8->genrand_int32() % 5u - a8->genrand_int32() % 5;
					int v44 = a4 + a6;
					int v45 = a5 + a6;
					while ( v35 < a4 || v35 >= v44 || v50 < a5 || v50 >= v45 )
					{
						int v54 = v45;
						int v53 = v44;
						int v46 = v58 + a8->genrand_int32() % 5;
						v35 = v46 - a8->genrand_int32() % 5;
						int v47 = v59 + a8->genrand_int32() % 5;
						int v48 = a8->genrand_int32() % 5;
						v45 = v54;
						v44 = v53;
						v50 = v47 - v48;
					}
					if ( v43 )
					{
LABEL_33:
						v34 = v55 + 1;
						goto LABEL_34;
					}
					if ( !--v56 )
					{
						goto LABEL_33;
					}
				}
			}
		}
	}


}

static int _D6E4E9EC;
bool_t MobSpawner::tick(Level* level, bool_t hostiles, bool_t animals) {
	if(hostiles || animals) {
		MobSpawner::chunksToPoll.clear();
		if(animals) {
			int v5 = 0;
			do {
				MobSpawner::chunksToPoll.insert({ChunkPos{v5 >> 4, (v5 & 0xf)}, 0});
				++v5;
			} while(v5 != 256);
			hostiles = 0;
		} else {
			if(++_D6E4E9EC >= level->playersMaybe.size()) {
				_D6E4E9EC = 0;
			}
			if(level->playersMaybe.size()) {
				Player* v9 = level->playersMaybe[_D6E4E9EC];
				float v10 = v9->posX * 0.0625;
				int v11 = (int)v10;
				float v12 = v9->posZ * 0.0625;
				if(v10 < (float)(int)v10) {
					--v11;
				}
				int v13 = (int)v12;
				if(v12 < (float)(int)v12) {
					--v13;
				}

				for(int i = -8; i != 9; ++i) {
					int v15 = -8;
					int v16 = v13 - 8;
					do {
						if((unsigned int)(i + v11) <= 0xF && v16 >= 0 && v16 <= 15) {
							MobSpawner::chunksToPoll.insert({{i + v11, v16}, 0});
						}
						++v15;
						++v16;
					} while(v15 != 9);
				}
			}
		}

		TilePos v48 = level->getSharedSpawnPos();
		int v17 = 0;
		int v38 = 0;
		int v39;
		int v44;
		int v34;
		int zz;
		int v45;
		int rarity;
		int v41;
		int v40;
		float v22, v23, v24;
		while(1) {
			if(v17 >= 3) {
				return v38;
			}
			const MobCategory* v18 = MobCategory::values[v17];
			if(v18->field_10) {
				if(!animals) {
					goto LABEL_58;
				}
			} else if(!hostiles) {
				goto LABEL_58;
			}
			if(level->countInstanceOfBaseType(v18->id) <= v18->maxCountInChunkMaybe) {
				int x, y, z;
LABEL_28:
				auto&& j = MobSpawner::chunksToPoll.begin();
				for(;; ++j) {
					if(j == MobSpawner::chunksToPoll.end()) {
						goto LABEL_58;
					}
					{
						Pos v49 = MobSpawner::getRandomPosWithin(level, 16 * j->first.x, 16 * j->first.z);
						x = v49.x;
						y = v49.y;
						z = v49.z;

						if(!level->isSolidBlockingTile(v49.x, v49.y, v49.z) && v18->material == level->getMaterial(x, y, z)) {
							break;
						}
					}
LABEL_56:;
				}
				v39 = 0;
				v44 = 3;
LABEL_55:
				v34 = x;
				zz = z;
				v45 = 4;
				rarity = -128;
				v41 = 0;
				v40 = 999;
				while(1) {
					v34 += (level->random.genrand_int32() % 6) - (level->random.genrand_int32() % 6);
					level->random.genrand_int32();
					level->random.genrand_int32();
					zz += (level->random.genrand_int32() % 6) - (level->random.genrand_int32() % 6);
					if(MobSpawner::isSpawnPositionOk(*v18, level, v34, y, zz)) {
						v22 = (float)v34 + 0.5;
						v23 = (float)zz + 0.5;
						v24 = (float)y;
						if(!level->getNearestPlayer(v22, (float)y, v23, 24.0) && (float)((float)((float)((float)(v24 - (float)v48.y) * (float)(v24 - (float)v48.y)) + (float)((float)(v22 - (float)v48.x) * (float)(v22 - (float)v48.x))) + (float)((float)(v23 - (float)v48.z) * (float)(v23 - (float)v48.z))) >= 576.0) {
							static Stopwatch _sw;
							_sw.start();
							int a2a;
							if(rarity < 0) {
								Biome::MobSpawnerData a1 = level->getRandomMobSpawnAt(*v18, v34, y, zz);
								rarity = a1.rarity;
								a2a = a1.mobtype;
								if(a1.rarity < 0 || v18 == &MobCategory::monster && level->countInstanceOfType(a1.mobtype) >= (int)(float)((float)((float)rarity * 1.5) * (float)v18->maxCountInChunkMaybe) / Biome::defaultTotalEnemyWeight) {
LABEL_54:
									if(!--v44) {
										goto LABEL_56;
									}
									goto LABEL_55;
								}
								int min = a1.min;
								int v33 = a1.max + 1 - a1.min;
								v40 = min + (level->random.genrand_int32() % v33);
							}
							Mob* mob = MobFactory::getStaticTestMob(a2a, level);
							if(mob) {
								mob->moveTo(v22, v24, v23, 0.0, 0.0);
								if(mob->canSpawn()) {
									Mob* v28 = MobFactory::CreateMob(a2a, level);
									if(v28) {
										float v29 = level->random.nextFloat();
										bool v30 = MobSpawner::addMob(level, v28, v22, v24, v23, v29 * 360.0, 0.0, 0);
										if(v30) {
											++v41;
											if(++v39 >= v28->getMaxSpawnClusterSize()) {
												goto LABEL_28;
											}
										} else {

											delete v28;
										}
										v38 += v39;
									}
								}
							}
						}
					}
					if ( !--v45 || v41 > v40 )
					{
						//goto LABEL_54;
						if(!--v44) {
							goto LABEL_56;
						}
						goto LABEL_55;
					}

				}

			}
LABEL_58:
			++v17;
		}
	}
	return 0;
}
