#pragma once
#include <_types.h>
#include <string>
#include <math/AABB.hpp>
#include <rendering/tileentity/TileEntityRendererId.hpp>
#include <map>

struct Packet;
struct CompoundTag;
struct TileEntity
{
	static int32_t _runningId;
	static std::map<int32_t, std::string> classIdMap;
	static std::map<std::string, int32_t> idClassMap;

	struct Level* level;
	int32_t posX, posY, posZ;
	AABB aabb;
	int32_t blockMetadata;
	int32_t type, id;
	bool_t field_34;
	int8_t field_35, field_36, field_37;
	TileEntityRendererId renderId;
	struct Tile* block;
	bool_t removed;
	int8_t field_41, field_42, field_43;
	float field_44, field_48, field_4C;
	float field_50, field_54;

	static void initTileEntities();
	static void teardownTileEntities();
	static TileEntity* loadStatic(CompoundTag*);
	static bool_t isType(TileEntity*, int32_t);
	static void setId(int32_t, const std::string&);

	TileEntity(int32_t);
	void _destructionWobble(float&, float&, float&);
	void _resetAABB(void);
	void clearRemoved(void);
	void destroyTick(const struct Mob*, float);
	float distanceToSqr(float, float, float);
	float getBrightness(float);
	int32_t getData(void);
	struct Tile* getTile();
	bool_t isRemoved();
	bool_t isType(int32_t);
	void setChanged(void);
	void setData(int32_t);
	void setupLighting(bool_t, float);


	virtual ~TileEntity();
	virtual bool_t shouldSave() = 0;
	virtual void load(CompoundTag*);
	virtual bool_t save(CompoundTag*);
	virtual void tick();
	virtual bool_t isFinished();
	virtual void setLevelAndPos(struct Level*, int32_t, int32_t, int32_t);
	virtual Packet* getUpdatePacket();
	virtual void onUpdatePacket(CompoundTag*);
	virtual void setRemoved(void);
	virtual void triggerEvent(int32_t, int32_t);
	virtual void clearCache(void);
	virtual void onNeighborChanged(int32_t, int32_t, int32_t);
	virtual float getShadowRadius();
};
