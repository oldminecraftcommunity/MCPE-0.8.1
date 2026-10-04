#pragma once
#include <level/gen/ChunkSource.hpp>
#include <level/Level.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/storage/chunk/ChunkStorage.hpp>

struct ChunkStorage;
struct LevelChunk;
struct Level;

static bool_t sub_D66664FE(int a1, int a2) {
	return a1 >= 0 && a2 >= 0 && a1 <= 15 && a2 <= 15;
}

struct ChunkCache: ChunkSource
{
	int8_t field_4, field_5, field_6, field_7;
	int32_t lastChunkX, lastChunkZ;
	LevelChunk* emptyChunk;
	ChunkSource* generatorSource;
	ChunkStorage* chunkStorage;
	LevelChunk* chunks[256];
	Level* level;
	LevelChunk* lastChunk;

	virtual ~ChunkCache() {
		if (this->generatorSource) {
			delete this->generatorSource;
		}
		if (this->emptyChunk) {
			delete this->emptyChunk;
		}
		for (int32_t i = 0; i != 256; ++i) {
			LevelChunk* lc = this->chunks[i];
			if (lc) {
				lc->deleteBlockData();
				lc = this->chunks[i];
				if (lc) {
					delete lc;
				}
			}
		}
	}
	virtual bool_t hasChunk(int32_t x, int32_t z) {
		LevelChunk* result; // r0
		if (!sub_D66664FE(x, z) || x == this->lastChunkX && z == this->lastChunkZ && this->lastChunk) {
			return 1;
		}
		result = this->chunks[16 * (z & 0xF) + (x & 0xF)];
		if (!result) {
			return 0;
		}
		return result == this->emptyChunk || result->isAt(x, z);
	}
	virtual LevelChunk* getChunk(int32_t x, int32_t z) {
		LevelChunk* result; // r0
		int32_t v7; // r9
		LevelChunk* v9; // r0
		LevelChunk* v10; // r7
		ChunkStorage* chunkStorage; // r0
		ChunkStorage* v12; // r0
		LevelChunk* emptyChunk; // r7
		ChunkSource* generatorSource; // r0
		LevelChunk* v16; // r0
		if (x != this->lastChunkX || z != this->lastChunkZ || (result = this->lastChunk) == 0) {
			if (!sub_D66664FE(x, z)) {
				return this->emptyChunk;
			}
			v7 = (x & 0xF) + 16 * (z & 0xF);
			if (this->hasChunk(x, z)) {
				goto LABEL_48;
			}
			v9 = this->chunks[v7];
			if (v9) {
				v9->unload();
				v10 = this->chunks[v7];
				if (!this->chunkStorage) {
					v10->field_250 = this->level->getTime();
					this->chunkStorage->save(this->level, v10);
				}
				chunkStorage = this->chunkStorage;
				if (chunkStorage) {
					chunkStorage->saveEntities(this->level, this->chunks[v7]);
				}
			}
			v12 = this->chunkStorage;
			if (v12 && (uint32_t) (x) <= 0xF && z >= 0 && z <= 15) {
				emptyChunk = (LevelChunk*) (v12->load(this->level, x, z));
				if (!emptyChunk) {
					goto LABEL_19;
				}
				emptyChunk->field_250 = this->level->getTime();
			} else {
				emptyChunk = this->emptyChunk;
				if (!emptyChunk) {
					LABEL_19: generatorSource = this->generatorSource;
					if (generatorSource) {
						emptyChunk = (LevelChunk*) (generatorSource->getChunk(x, z));
					} else {
						emptyChunk = this->emptyChunk;
					}
				}
			}
			this->chunks[v7] = emptyChunk; // this->chunks[v7]
			emptyChunk->lightLava();
			v16 = this->chunks[v7];
			if (v16) {
				v16->load();
			}
			if (!this->chunks[v7]->decorated && this->hasChunk(x + 1, z + 1) && this->hasChunk(x, z + 1) && this->hasChunk(x + 1, z)) {
				this->postProcess(this, x, z);
			}
			if (this->hasChunk(x - 1, z) && !this->getChunk(x - 1, z)->decorated && this->hasChunk(x - 1, z + 1) && this->hasChunk(x, z + 1) && this->hasChunk(x - 1, z)) {
				this->postProcess(this, x - 1, z);
			}
			if (this->hasChunk(x, z - 1) && !this->getChunk(x, z - 1)->decorated && this->hasChunk(x + 1, z - 1) && this->hasChunk(x, z - 1) && this->hasChunk(x + 1, z)) {
				this->postProcess(this, x, z - 1);
			}
			if (this->hasChunk(x - 1, z - 1) && !this->getChunk(x - 1, z - 1)->decorated && this->hasChunk(x - 1, z - 1) && this->hasChunk(x, z - 1) && this->hasChunk(x - 1, z)) {
				this->postProcess(this, x - 1, z - 1);
			}
			LABEL_48: this->lastChunkX = x;
			this->lastChunkZ = z;
			result = this->chunks[v7];
			this->lastChunk = result;
		}
		return result;
	}
	virtual LevelChunk* create(int32_t x, int32_t z) {
		return this->getChunk(x, z);
	}
	virtual void postProcess(ChunkSource* a2, int32_t x, int32_t z) {
		LevelChunk* v8; // r0
		LevelChunk* v9; // r5
		Level* level; // r2
		bool_t isClientMaybe; // r9
		if (sub_D66664FE(x, z)) {
			v8 = this->getChunk(x, z);
			v9 = v8;
			if (!v8->decorated) {
				v8->decorated = 1;
				if (this->generatorSource) {
					level = this->level;
					isClientMaybe = level->isClient;
					level->isClient = 0;
					this->generatorSource->postProcess(a2, x, z);
					v9->clearUpdateMap();
					this->level->isClient = isClientMaybe;
				}
			}
		}
	}
	virtual bool_t tick() {
		if (this->chunkStorage) {
			this->chunkStorage->tick();
		}
		return this->generatorSource->tick();
	}
	virtual bool_t shouldSave() {
		return 1;
	}
	virtual void saveAll(bool_t a2) {
		if (this->chunkStorage) {
			std::vector<LevelChunk*> v8;
			for (int32_t z = 0; z != 16; ++z) {
				for (int32_t x = 0; x != 16; ++x) {
					LevelChunk* chunk = this->level->getChunk(x, z);
					if (!a2 || chunk->shouldSave(0)) {
						v8.push_back(chunk);
					}
				}
			}
			this->chunkStorage->saveAll(this->level, v8);
		}
	}
	virtual std::vector<Biome::MobSpawnerData> getMobsAt(const MobCategory& a3, int32_t a4, int32_t a5, int32_t a6) {
		return this->generatorSource->getMobsAt(a3, a4, a5, a6);
	}
	virtual std::string gatherStats() {
		return "ChunkCache: 1024";
	}
};
