#pragma once
#include <level/Level.hpp>
#include <entity/Entity.hpp>
#include <algorithm>
#include <list>

struct Entity;
struct MultiPlayerLevel: Level
{
	struct ResetInfo
	{
		int32_t x, y, z;
		int32_t field_C;
		int32_t id, meta;
	};

	std::list<MultiPlayerLevel::ResetInfo> field_BA4;
	std::map<int32_t, Entity*> field_BAC;
	std::set<Entity*> field_BC4;
	std::set<Entity*> field_BDC;
	int8_t field_BF4, field_BF5, field_BF6, field_BF7;

	bool_t addEntity(Entity* a2) {
		bool_t v3 = Level::addEntity(a2);
		this->field_BC4.insert(a2);
		if (!v3) {
			this->field_BDC.insert(a2);
		}
		return v3;
	}
	void putEntity(int32_t eid, Entity* ent) {
		//TODO check
		auto&& p = this->field_BAC.find(eid);
		if (p != this->field_BAC.end()) {
			this->removeEntity(p->second);
			this->field_BC4.erase(p->second);
		}
		this->field_BC4.insert(ent);
		ent->entityId = eid;
		if (!this->addEntity(ent)) {
			this->field_BDC.insert(ent);
		}
		this->field_BAC.insert(std::pair<int,Entity*>(eid, ent));
	}

	MultiPlayerLevel(LevelStorage* a2, const std::string& a3, const LevelSettings& a4, bool a5, int a6, Dimension* a7) :
			Level(a2, a3, a4, a5, a6, a7) {
	}
	virtual ~MultiPlayerLevel() {
	}
	virtual void tick() {
		if (this->isClientMaybe) {
			if (this->adventureSettings.daylightCycle) {
				this->setTime(this->getTime() + 1);
			}
			this->updateSkyDarken();
			int32_t v3 = 10;
			do {
				//TODO check
				if (this->field_BDC.size() == 0) break;

				auto&& e = this->field_BDC.rbegin();
				this->field_BDC.erase(*e);
				if (this->entities.end() == std::find(this->entities.begin(), this->entities.end(), *e)) {
					this->addEntity(*e);
				}
				--v3;
			} while (v3);
			//TODO check
			for (auto&& it = this->field_BA4.begin(); it != this->field_BA4.end();) {
				int32_t v4 = it->field_C - 1;
				it->field_C = v4;
				if (v4) {
					++it;
				} else {
					this->setTileAndDataNoUpdate(it->x, it->y, it->z, it->id, it->meta);
					this->sendTileUpdated(it->x, it->y, it->z);
					auto&& svd = it;
					++it;
					this->field_BA4.erase(svd);
				}
			}
		} else {
			this->tick();
		}
	}
	virtual bool_t tickPendingTicks(bool_t) {
		return 0;
	}
	virtual void addToTickNextTick(int32_t x, int32_t y, int32_t z, int32_t id, int32_t delay) {
		if (!this->isClientMaybe) {
			Level::addToTickNextTick(x, y, z, id, delay);
		}
	}
	virtual ChunkSource* createChunkSource() {
		return 0;
	}
	virtual void tickTiles() {
	}
};
