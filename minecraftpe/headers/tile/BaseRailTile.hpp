#pragma once
#include <tile/Tile.hpp>
#include <util/TilePos.hpp>

struct BaseRailTile : Tile{

	struct Rail{
		struct Level* level;
		int32_t x, y, z;
		int8_t field_10, field_11, field_12, field_13;
		std::vector<TilePos> connections;

		Rail(struct Level*, int32_t, int32_t, int32_t);
		bool_t canConnectTo(BaseRailTile::Rail*);
		void connectTo(BaseRailTile::Rail*);
		bool_t connectsTo(BaseRailTile::Rail*);
		int32_t countPotentialConnections();
		std::shared_ptr<BaseRailTile::Rail> getRail(const TilePos&);
		bool_t hasConnection(int32_t, int32_t, int32_t);
		bool_t hasNeighborRail(int32_t, int32_t, int32_t);
		bool_t hasRail(int32_t, int32_t, int32_t);
		void place(bool_t, bool_t);
		void removeSoftConnections();
		void updateConnections(int32_t);
	};

	bool_t useDataBit;
	int8_t field_7D, field_7E, field_7F;

	static bool_t isRail(int32_t);
	static bool_t isRail(struct Level*, int32_t, int32_t, int32_t);

	BaseRailTile(int32_t, bool_t);
	virtual ~BaseRailTile();
	virtual bool_t isCubeShaped();
	virtual int32_t getRenderShape();
	virtual void updateShape(LevelSource*, int32_t, int32_t, int32_t);
	virtual AABB* getAABB(Level*, int32_t, int32_t, int32_t);
	virtual bool_t isSolidRender();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t);
	virtual void neighborChanged(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void onPlace(Level*, int32_t, int32_t, int32_t);
	virtual void onRemove(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getResourceCount(Random*);
	virtual HitResult clip(Level*, int32_t, int32_t, int32_t, const Vec3&, const Vec3&);
	virtual int32_t getRenderLayer();
	virtual float getThickness();
	virtual void updateState(Level*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);

	bool_t blocksLight();
	bool_t isUsesDataBit();
	void updateDir(Level*, int32_t, int32_t, int32_t, bool_t);
};
