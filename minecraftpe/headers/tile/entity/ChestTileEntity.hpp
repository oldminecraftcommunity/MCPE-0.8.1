#pragma once
#include <tile/entity/TileEntity.hpp>
#include <inventory/FillingContainer.hpp>
#include <rendering/EntityTileRenderer.hpp>

struct ChestTileEntity: TileEntity, FillingContainer, EntityTileRenderer
{
	float field_84;
	float field_88;
	int32_t field_8C;
	int32_t field_90;
	ChestTileEntity* pair;
	bool_t isUnpaired;
	int32_t field_9C, field_A0;
	bool_t field_A4;
	bool_t pairSameXPos;
	int32_t field_A8;
	Player* openedBy;

	ChestTileEntity();
	bool_t _canOpenThis();
	void _getCenter(float& x, float& y, float& z);
	bool_t _saveClientSideState(CompoundTag*);
	void _unpair();
	bool_t canOpen();
	bool_t canPairWith(TileEntity*);
	float getModelOffsetX();
	void openBy(Player*);
	void pairWith(ChestTileEntity*, bool_t);
	void unpair();

	virtual ~ChestTileEntity();
	virtual bool_t shouldSave();
	virtual void load(CompoundTag*);
	virtual bool_t save(CompoundTag*);
	virtual void tick();
	virtual Packet* getUpdatePacket();
	virtual void onUpdatePacket(CompoundTag*);
	virtual void setRemoved();
	virtual void triggerEvent(int32_t, int32_t);
	virtual void clearCache();
	virtual void onNeighborChanged(int32_t, int32_t, int32_t);
	virtual int32_t getContainerSize() const;
	virtual int32_t getMaxStackSize() const;
	virtual std::string getName() const;
	virtual ItemInstance* getItem(int32_t);
	virtual void setItem(int32_t, ItemInstance*);
	virtual bool_t stillValid(Player*);
	virtual void startOpen();
	virtual void stopOpen();
};
