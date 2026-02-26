#pragma once
#include <level/Level.hpp>
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

	bool_t addEntity(Entity*);
	void putEntity(int32_t, Entity*);

	MultiPlayerLevel(LevelStorage*, const std::string&, const LevelSettings&, bool,int,Dimension *);
	virtual ~MultiPlayerLevel();
	virtual void tick();
	virtual bool_t tickPendingTicks(bool_t);
	virtual void addToTickNextTick(int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual ChunkSource* createChunkSource();
	virtual void tickTiles();
};
