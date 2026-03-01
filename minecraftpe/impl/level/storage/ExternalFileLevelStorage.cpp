#include <level/storage/ExternalFileLevelStorage.hpp>
#include <GetTime.h>
#include <cpputils.hpp>
#include <level/Level.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <level/storage/RegionFile.hpp>
#include <level/storage/chunk/UnsavedLevelChunk.hpp>
#include <util/output/RakDataOutput.hpp>
#include <nbt/CompoundTag.hpp>
#include <entity/Player.hpp>
#include <level/storage/LevelStorageSource.hpp>
#include <level/LevelConverters.hpp>
#include <tile/Tile.hpp>
#include <util/Util.hpp>
#include <utils.h>
#include <util/input/RakDataInput.hpp>
#include <nbt/NbtIo.hpp>
#include <nbt/ListTag.hpp>
#include <tile/entity/TileEntity.hpp>
#include <entity/EntityFactory.hpp>

ExternalFileLevelStorage::ExternalFileLevelStorage(const std::string& a2, const std::string& a3)
	: field_8(a2),
	field_2C(),
	anotherDataFolder(a3) {
	this->dataFolder = a3 + "/players";
	this->field_28 = 3;
	this->levelData = 0;
	this->regionFile = 0;
	this->field_34 = -999999;
	this->field_1C = 0;
	this->level = 0;
	this->field_24 = 0;
	createFolderIfNotExists(this->anotherDataFolder.c_str());
	if(this->anotherDataFolder.find(LevelStorageSource::TempLevelId, 0) == -1) {
		createFolderIfNotExists(this->dataFolder.c_str());
	}
	std::string v11 = this->anotherDataFolder + "/" + "level.dat";
	std::string a1a = this->anotherDataFolder + "/" + "player.dat";
	this->levelData = new LevelData();
	if(ExternalFileLevelStorage::readLevelData(this->anotherDataFolder, *this->levelData)) {
		this->field_28 = this->levelData->getStorageVersion();
		ExternalFileLevelStorage::readPlayerData(a1a, *this->levelData);
	} else {
		if(this->levelData) {
			delete this->levelData;
		}
		this->levelData = 0;
	}
}
bool_t ExternalFileLevelStorage::readLevelData(const std::string& a1, LevelData& a2) {
	std::string filename = a1 + "/" + "level.dat";
	FILE* v4 = fopen(filename.c_str(), "rb");
	if(v4 || (filename = a1 + "/" + "level.dat_old", v4 = fopen(filename.c_str(), "rb")) != 0) {
		int ver = 0;
		int n = 0;
		unsigned char* v5;
		if(fread(&ver, sizeof(ver), 1u, v4) == 1 && fread(&n, sizeof(n), 1u, v4) == 1 && (int)n <= getRemainingFileSize(v4) && (int)n > 0) {
			v5 = new unsigned char[n];
			int v7 = fread(v5, 1, n, v4);
			if(v7 == n) {
				if(ver == 1) {
					RakNet::BitStream v16(v5, v7, 0);
					a2.v1_read(v16, ver);
					goto end;
				}
				if(ver > 1) {
					RakNet::BitStream v16(v5, v7, 0);
					RakDataInput v14;
					v14.stream = &v16;
					Tag* v8 = NbtIo::read(&v14);
					if(v8) {
						a2.getTagData((CompoundTag*)v8);
						v8->deleteChildren();
						delete v8;
					}
					goto end;
				}
			}
		} else {
			v5 = 0;
		}
end:
		fclose(v4);
		if(v5) {
			delete[] v5;
		}
		return 1;
	}
	return 0;
}
void ExternalFileLevelStorage::readPlayerData(const std::string& a1, LevelData& a2) {
	FILE* v3 = fopen(a1.c_str(), "rb");
	if(v3) {
		int size;
		int ptr;
		if(fread(&size, sizeof(size), 1, v3) == 1 && fread(&ptr, sizeof(ptr), 1, v3) && size == 1) {
			int v4 = fread(&a2, 1, sizeof(a2), v3);
			if(v4 == ptr) {
				float z = a2.playerData.z;
				if(a2.playerData.x < 0.5) {
					a2.playerData.x = 0.5;
				}
				bool v6 = a2.playerData.x == 255.5;
				bool v7 = a2.playerData.x < 255.5;
				if(z < 0.5) {
					a2.playerData.z = 0.5;
				}
				float v8 = a2.playerData.z;
				if(!v7 && !v6) {
					a2.playerData.x = 255.5;
				}
				float y = a2.playerData.y;
				if(v8 > 255.5) {
					a2.playerData.z = 255.5;
				}
				if(y < 0.0) {
					a2.playerData.y = 64.0;
				}
				a2.field_50 = size;
			}
		}
		fclose(v3);
	}
}
void ExternalFileLevelStorage::saveLevelData(const std::string& a1, LevelData& a2, std::vector<Player*>* a3) {
	std::string v5 = a1 + '/';
	std::string v6 = v5 + "level.dat_new";
	std::string old = v5 + "level.dat";
	std::string filename = v5 + "level.dat_old";
	a2.setStorageVersion(2);
	if(ExternalFileLevelStorage::writeLevelData(v6, a2, a3)) {
		remove(filename.c_str());
		if(exists(old.c_str())) {
			if(rename(old.c_str(), filename.c_str())) {
				return;
			}
			remove(old.c_str());
		}
		if(!rename(v6.c_str(), old.c_str())) {
			remove(v6.c_str());
		}
	}
}
void ExternalFileLevelStorage::savePendingUnsavedChunks(int32_t a2) {
	int v2 = a2;
	if(a2 < 0) {
		v2 = this->field_2C.size(); //loop in mcpe due to stlport implementation
	}
	for(int v5 = 0; ++v5 <= v2;) {
		if(this->field_2C.empty()) break;
		UnsavedLevelChunk* ulv = &this->field_2C.front();
		this->save(this->level, ulv->chunk); //TODO check
		this->field_2C.pop_front();
	}
}
bool_t ExternalFileLevelStorage::writeLevelData(const std::string& a1, LevelData& a2, const std::vector<Player*>* a3) {
	FILE* f = fopen(a1.c_str(), "wb");
	if(f) {
		RakNet::BitStream v14;
		if(a2.getStorageVersion() == 1) {
			a2.v1_write(v14);
		} else {
			RakDataOutput v13;
			v13.bitStream = &v14;
			Tag* tag;
			if(a3 && !a3->empty()) {
				tag = a2.createTag(*a3);
			} else {
				tag = a2.createTag();
			}

			if(tag) {
				Tag::writeNamedTag(tag, &v13);
			}
			tag->deleteChildren();
			delete tag;
		}
		int32_t sv = a2.getStorageVersion();
		fwrite(&sv, 4u, 1u, f);
		size_t sz = v14.GetNumberOfBytesUsed();
		fwrite(&sz, 4u, 1u, f);
		fwrite(v14.GetData(), 1u, sz, f);
		fclose(f);
		return 1;
	}
	return 0;
}

ExternalFileLevelStorage::~ExternalFileLevelStorage() {
	if(this->regionFile) {
		delete this->regionFile;
	}
	if(this->levelData) {
		delete this->levelData;
	}
}
LevelData* ExternalFileLevelStorage::prepareLevel(Level* a2) {
	this->level = a2;
	return this->levelData;
}
ChunkStorage* ExternalFileLevelStorage::createChunkStorage(Dimension*) {
	return this;
}
void ExternalFileLevelStorage::saveLevelData(LevelData& a2, std::vector<Player*>* a3) {
	ExternalFileLevelStorage::saveLevelData(this->anotherDataFolder, a2, a3);
}

static std::string sub_D6677960(std::string& a2, std::string& a3) {
	return a2 + "/" + Util::toLower(a3) + ".dat";
}

bool_t ExternalFileLevelStorage::load(Player* a2) {
	if(!a2) return 0;
	FILE* v4 = fopen(sub_D6677960(this->dataFolder, a2->field_CA4).c_str(), "rb");
	if(!v4) return 0;
	int sz, v11, n;
	fread(&sz, 1, sizeof(sz), v4);
	int rfs = getRemainingFileSize(v4);
	if(n > rfs || n <= 0) {
		return 0;
	} else {
		bool ret = 0;
		unsigned char* v6 = new unsigned char[n];
		fread(v6, 1, n, v4);
		RakNet::BitStream v15(v6, n, 0);
		RakDataInput input;
		input.stream = &v15;
		Tag* tag = NbtIo::read(&input);
		if(tag) {
			a2->load((CompoundTag*)tag);
			tag->deleteChildren();
			ret = 1;
			delete tag;
		} else {
			ret = 0;
		}
		if(v6) delete[] v6;
		return ret;
	}

}
static int _d6753BB8 = 0x524C50;
bool_t ExternalFileLevelStorage::save(Player* a2) {
	RakNet::BitStream v12;
	RakDataOutput v10;
	v10.bitStream = &v12;
	{
		CompoundTag v11;
		a2->saveWithoutId(&v11);
		Tag::writeNamedTag(&v11, &v10);
		v11.deleteChildren();
	}
	std::string newa = sub_D6677960(this->dataFolder, a2->field_CA4); //TODO check
	std::string v11 = newa + ".tmp";
	FILE* v5 = fopen(v11.c_str(), "wb");
	if(v5) {
		int size = 1;
		size_t n = v12.GetNumberOfBytesUsed();
		fwrite(&_d6753BB8, 1u, 4u, v5);
		fwrite(&size, 4u, 1u, v5);
		fwrite(&n, 4u, 1u, v5);
		fwrite(v12.GetData(), 1u, n, v5);
		fclose(v5);
		if(exists(newa.c_str())) {
			remove(newa.c_str());
		}
		rename(v11.c_str(), newa.c_str());
		return 1;
	}
	return 0;
}
void ExternalFileLevelStorage::closeAll() {
}
void ExternalFileLevelStorage::saveGame(Level* a2) {
	return this->saveEntities(a2, 0);
}
void ExternalFileLevelStorage::loadEntities(Level* a2, LevelChunk* a3) {
	this->field_34 = this->field_24;
	FILE* v4 = fopen((this->anotherDataFolder + "/entities.dat").c_str(), "rb");
	if(v4) {
		int v35;
		char dest[4];
		int n;
		fread(&v35, 1u, 4u, v4);
		fread(dest, 4u, 1u, v4);
		fread(&n, 4u, 1u, v4);
		int rem = getRemainingFileSize(v4);
		if(n <= rem && n > 0) {
			unsigned char* src = new unsigned char[n];
			fread(src, 1, n, v4);
			RakNet::BitStream v37(src, n, 0);
			RakDataInput v36;
			v36.stream = &v37;
			CompoundTag* v6 = (CompoundTag*)NbtIo::read(&v36);
			if(v6->contains("Entities", 9)) {
				ListTag* list = v6->getList("Entities");
				for(int v9 = 0; v9 < list->value.size(); ++v9) {
					CompoundTag* v10 = (CompoundTag*)list->value[v9];
					if(v10) {
						if(v10->getId() == 10) {
							Entity* e = EntityFactory::loadEntity(v10, a2);
							Entity* v16 = e;
							if(e) {
								a2->addEntity(e);
								CompoundTag* v11 = v10;
								//TODO check complex mountables
								for(auto&& i = v10->value.find(Entity::RIDING_TAG); i != v11->value.end(); i = v11->value.find(Entity::RIDING_TAG)) {
									CompoundTag* comp = v11->getCompound(Entity::RIDING_TAG);
									Entity* v14 = EntityFactory::loadEntity(comp, a2);
									if(v14) {
										a2->addEntity(v14);
										v16->ride(v14);
									}
									v16 = v14;
									v11 = v11->getCompound(Entity::RIDING_TAG);
								}
							}
						} else {
							v10->getId();
						}
					}
				}
			}

			if(v6->contains("TileEntities", 9)) {
				ListTag* v19 = v6->getList("TileEntities");
				for(int v18 = 0; v18 < v19->value.size(); ++v18) {
					CompoundTag* v20 = (CompoundTag*)v19->value[v18];
					if(v20) {
						if(v20->getId() == 10) {
							TileEntity* te = TileEntity::loadStatic(v20);
							if(te) {
								Tile* v21 = Tile::tiles[a2->getTile(te->posX, te->posY, te->posZ)];
								bool v23;
								if(v21) {
									v23 = !te->isType(v21->getTileEntityType());
								} else {
									v23 = 1;
								}
								LevelChunk* c = a2->getChunkAt(te->posX, te->posZ);
								if(!c || c->hasTileEntityAt(te) || v23) {
									delete te;
								} else {
									c->addTileEntity(te);
								}
							}
						} else {
							v20->getId();
						}
					}
				}
			}

			v6->deleteChildren();
			delete v6;
			if(src) delete[] src;
		}
		fclose(v4);
	}
}
LevelChunk* ExternalFileLevelStorage::load(Level* a2, int32_t a3, int32_t a4) {
	if(this->regionFile || (this->regionFile = new RegionFile(this->anotherDataFolder), this->regionFile->open())) {
		RegionFile* regionFile = this->regionFile;
		RakNet::BitStream* v22 = 0;
		if(regionFile->readChunk(a3, a4, &v22)) {
			v22->ResetReadPointer();
			char* v12 = new char[0x8000];
			v22->Read(v12, 0x8000);
			LevelChunk* v10 = new LevelChunk(a2, (uint8_t*)v12, a3, a4);
			v22->Read((char*)v10->tileMeta.data, 0x4000);
			if(this->field_28 > 0) {
				v22->Read((char*)v10->skyLight.data, 0x4000);
				v22->Read((char*)v10->blockLight.data, 0x4000);
			}
			v22->Read((char*) v10->updateMap, 0x100);
			if(v22->GetData()) delete[] v22->GetData(); //TODO is this actually needed?
			if(v22) {
				delete v22;
			}
			bool v15;
			if(this->field_28 == 1) {
				v15 = LevelConverters::v1_ClothIdToClothData(v10);
			} else {
				v15 = 0;
			}
			bool v17 = 0;
			for(int i = 0; i != 0x8000; ++i) {
				int v19 = v10->tiles[i];
				int valid = Tile::transformToValidBlockId(v19);
				if(v19 != valid) {
					v10->tiles[i] = valid;
				}
				if(v19 != valid) {
					v17 = 1;
				}
			}
			v10->recalcHeightmap();
			v10->unsaved = v17 | v15;
			v10->decorated = 1;
			v10->field_24B = 1;
			return v10;
		} else {
			return 0;
		}
	} else {
		if(this->regionFile) {
			delete this->regionFile;
		}
		this->regionFile = 0;
		return 0;
	}
}
void ExternalFileLevelStorage::save(Level* a2, LevelChunk* a3) {
	RegionFile* v5;
	if(this->regionFile || (v5 = new RegionFile(this->anotherDataFolder), this->regionFile = v5, v5->open())) {
		RakNet::BitStream v7;
		v7.Write((const char*)a3->tiles, 0x8000);
		v7.Write((const char*)a3->tileMeta.data, 0x4000);
		v7.Write((const char*)a3->skyLight.data, 0x4000);
		v7.Write((const char*)a3->blockLight.data, 0x4000);
		v7.Write((const char*)a3->updateMap, 0x100);
		this->regionFile->writeChunk(a3->chunkX, a3->chunkZ, v7);
	} else {
		if(this->regionFile) {
			delete this->regionFile;
		}
		this->regionFile = 0;
	}
}
void ExternalFileLevelStorage::saveEntities(Level* a2, LevelChunk* a3) {
	this->field_34 = this->field_24;
	ListTag* v6 = new ListTag();
	for(int v5 = 0; v5 < a2->entities.size(); ++v5) {
		Entity* v7 = a2->entities[v5];
		CompoundTag* v8 = new CompoundTag();
		if(v7->save(v8)) {
			v6->add(v8);
		} else if(v8) {
			delete v8;
		}
	}
	ListTag* v11 = new ListTag();
	for(int v5 = 0; v5 < a2->tileEntities.size(); ++v5) {
		TileEntity* v12 = a2->tileEntities[v5];
		if(v12) {
			CompoundTag* v13 = new CompoundTag();
			if(v12->save(v13)) {
				v11->add(v13);
			} else {
				delete v13;
			}
		}
	}

	CompoundTag v22;
	v22.put("Entities", v6);
	v22.put("TileEntities", v11);
	RakNet::BitStream v23;
	RakDataOutput a1;
	a1.bitStream = &v23;
	Tag::writeNamedTag(&v22, &a1);
	int n = v23.GetNumberOfBytesUsed();
	FILE* v15 = fopen((this->anotherDataFolder + "/entities.dat").c_str(), "wb");
	if(v15) {
		int sz = 1;
		fwrite("ENT", 1, 4, v15);
		fwrite(&sz, 4, 1, v15);
		fwrite(&n, 4, 1, v15);
		fwrite(v23.GetData(), 1, n, v15);
		fclose(v15);
	}
	v22.deleteChildren();
	getTimeS();
}
void ExternalFileLevelStorage::saveAll(Level* a2, std::vector<LevelChunk*>& a3) {
	ChunkStorage::saveAll(a2, a3);
	return this->savePendingUnsavedChunks(-1);
}
void ExternalFileLevelStorage::tick() {
	if(this->level) {
		this->field_24 = this->field_24 + 1;
		if((this->field_24 % 50) == 0) {
			for(int32_t z = 0; z != 16; ++z) {
				for(int32_t x = 0; x != 16; ++x) {
					LevelChunk* chunk = this->level->getChunk(x, z);
					if(chunk && chunk->unsaved) {
						for(auto&& el: this->field_2C) {
							if(el.index == (x + 16 * z)) {
								el.timeMs = RakNet::GetTimeMS();
								goto LABEL_12;
							}
						}

						this->field_2C.push_back({x + 16 * z, (int32_t)RakNet::GetTimeMS(), chunk});
LABEL_12:
						chunk->unsaved = 0;
					}
				}
			}
			this->savePendingUnsavedChunks(2);
		}
		if(this->field_24 - this->field_34 > 1200) {
			this->saveEntities(this->level, 0);
			this->level->savePlayers();
		}
	}
}
void ExternalFileLevelStorage::flush() {
}
