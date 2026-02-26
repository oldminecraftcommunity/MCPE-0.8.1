#pragma once
#include <entity/Player.hpp>
#include <inventory/IContainerListener.hpp>
#include <inventory/InventoryMenu.hpp>
#include <math/SmoothFloat.hpp>

struct KeyboardInput;
struct Minecraft;
struct User;
struct ChestTileEntity;
struct FurnaceTileEntity;
struct TileEntity;
struct LocalPlayer: Player, IContainerListener
{
	KeyboardInput* moveInput;
	InventoryMenu inventoryMenu;
	bool_t allowAutojump;
	int8_t field_D79, field_D7A, field_D7B;
	Minecraft* minecraft;
	int32_t flyToggleCounter;
	int32_t field_D84, field_D88;
	int8_t field_D8C, field_D8D, field_D8E, field_D8F;
	float field_D90, field_D94, field_D98;
	SmoothFloat field_D9C, field_DA8, field_DB4;
	int32_t field_DC0;
	int32_t currentItemID, currentItemMeta;
	float field_DCC;
	int32_t lastSentArmorHash;
	ItemInstance field_DD4[4];
	int32_t field_E24;

	LocalPlayer(Minecraft*, Level*, User*, int32_t, bool_t);
	void _init();
	void calculateFlight(float, float, float);
	float getFieldOfViewModifier();
	void hurtTo(int32_t);
	bool_t isSolidTile(int32_t, int32_t, int32_t);
	void releaseAllKeys();
	void respawn();
	void sendPosition();
	void setKey(int32_t, bool_t);
	void updateArmorTypeHash();

	virtual ~LocalPlayer();
	virtual void reset();
	virtual void move(float, float, float);
	virtual void tick();
	virtual void ride(Entity*);
	virtual bool_t isSneaking();
	virtual void causeFallDamage(float);
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual void actuallyHurt(int32_t);
	virtual void aiStep();
	virtual void swing();
	virtual void updateAi();
	virtual void take(Entity*, int32_t);
	virtual void drop(const ItemInstance*, bool_t);
	virtual void startCrafting(int32_t, int32_t, int32_t, int32_t);
	virtual void startStonecutting(int32_t, int32_t, int32_t);
	virtual void openContainer(ChestTileEntity*);
	virtual void openFurnace(FurnaceTileEntity*);
	virtual void displayClientMessage(const std::string&);
	virtual void animateRespawn();
	virtual int32_t startSleepInBed(int32_t, int32_t, int32_t);
	virtual void stopSleepInBed(bool_t, bool_t, bool_t);
	virtual void openTextEdit(TileEntity*);
	virtual bool_t isLocalPlayer();
	virtual void closeContainer();
	virtual void refreshContainer(BaseContainerMenu*, const std::vector<ItemInstance>);
	virtual void slotChanged(BaseContainerMenu*, int32_t, const ItemInstance&, bool_t);
};
