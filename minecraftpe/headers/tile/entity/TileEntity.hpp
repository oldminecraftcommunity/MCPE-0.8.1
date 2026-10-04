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
	void _resetAABB(void) {
		float posX; // s12
		float x; // s9
		float y; // s10
		float z; // s11
		float posY; // s13
		float posZ; // s14
		float v7; // s9
		float v8; // s10
		float v9; // s11
		posX = (float) (this->posX);
		x = Vec3::ONE.x;
		y = Vec3::ONE.y;
		z = Vec3::ONE.z;
		posY = (float) (this->posY);
		posZ = (float) (this->posZ);
		if (posX == 0.0) {
			posX = 0.0;
		}
		this->aabb.minX = posX;
		if (posY == 0.0) {
			posY = 0.0;
		}
		this->aabb.minY = posY;
		v7 = posX + x;
		v8 = posY + y;
		if (posZ == 0.0) {
			posZ = 0.0;
		}
		this->aabb.minZ = posZ;
		v9 = posZ + z;
		if (v7 == 0.0) {
			v7 = 0.0;
		}
		this->aabb.maxX = v7;
		if (v8 == 0.0) {
			v8 = 0.0;
		}
		this->aabb.maxY = v8;
		if (v9 == 0.0) {
			v9 = 0.0;
		}
		this->aabb.maxZ = v9;
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
