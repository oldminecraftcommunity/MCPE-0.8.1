#pragma once
#include <tile/entity/TileEntity.hpp>
#include <inventory/Container.hpp>

struct FurnaceTileEntity: TileEntity, Container
{
	int32_t field_5C, field_60;
	bool_t field_64;
	int32_t burnTime;
	int32_t field_6C;
	int32_t cookTime;
	ItemInstance inventory[3];
	bool_t field_B0, field_B1;

	static int32_t getBurnDuration(const ItemInstance&);
	static bool_t isFuel(const ItemInstance&);

	FurnaceTileEntity();
	void burn();
	bool_t canBurn();
	int32_t getBurnProgress(int32_t);
	int32_t getLitProgress(int32_t);
	bool_t isLit();
	bool_t isSlotEmpty(int32_t);

	virtual ~FurnaceTileEntity();
	virtual bool_t shouldSave();
	virtual void load(CompoundTag*);
	virtual bool_t save(CompoundTag*);
	virtual void tick();
	virtual bool_t isFinished();
	virtual void setRemoved();
	virtual ItemInstance* getItem(int32_t);
	virtual void setItem(int32_t, ItemInstance*);
	virtual ItemInstance removeItem(int32_t, int32_t);
	virtual std::string getName() const;
	virtual int32_t getMaxStackSize() const;
	virtual int32_t getContainerSize() const;
	virtual bool_t stillValid(Player*);
	virtual void startOpen();
	virtual void stopOpen();
};
