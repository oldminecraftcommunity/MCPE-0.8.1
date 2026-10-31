#pragma once
#include <math/AABB.hpp>
#include <rendering/tileentity/TileEntityRendererId.hpp>
#include <map>
#include <vector>
#include <string>

struct Packet;
struct CompoundTag;
struct TileEntity
{
	static std::map<std::string, int32_t> idClassMap;
	static std::map<int32_t, std::string> classIdMap;
	static int32_t _runningId;

	struct Level* level;
	int32_t posX, posY, posZ;
	AABB aabb;
	int32_t blockMetadata;
	int32_t type, id;
	bool_t field_34;
	TileEntityRendererId renderId;
	struct Tile* block;
	bool_t removed;
	float field_44;
	Vec3 field_48;
	float field_54;

	static void initTileEntities();
	static void teardownTileEntities();
	static TileEntity* loadStatic(CompoundTag*);
	static bool_t isType(TileEntity*, int32_t);
	static void setId(int32_t, const std::string&);

	TileEntity(int32_t);
	void _destructionWobble(float&, float&, float&);
	void _resetAABB(void) {

		this->aabb.assign(Vec3(this->posX, this->posY, this->posZ), Vec3::ONE);
	}
	void clearRemoved(void);
	void destroyTick(const struct Mob*, float);
	float distanceToSqr(float, float, float);
	float getBrightness(float);
	int32_t getData(void);
	struct Tile* getTile();
	bool_t isRemoved() const;
	bool_t isType(int32_t);
	void setChanged(void);
	void setData(int32_t);
	void setupLighting(bool_t, float);


	virtual ~TileEntity() {}
	virtual bool_t shouldSave() = 0;
	virtual void load(CompoundTag*);
	virtual bool_t save(CompoundTag*);
	virtual void tick() {
	}
	virtual bool_t isFinished();
	virtual void setLevelAndPos(struct Level*, int32_t, int32_t, int32_t);
	virtual Packet* getUpdatePacket();
	virtual void onUpdatePacket(CompoundTag*) {
	}
	virtual void setRemoved(void);
	virtual void triggerEvent(int32_t, int32_t);
	virtual void clearCache(void);
	virtual void onNeighborChanged(int32_t, int32_t, int32_t) {
	}
	virtual float getShadowRadius() {
		return 0;
	}
};

int partitionTileEntities(const std::vector<TileEntity*>& a1, std::vector<TileEntity*>& a2, std::vector<TileEntity*>& a3);
