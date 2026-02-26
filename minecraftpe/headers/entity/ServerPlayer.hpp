#pragma once
#include <entity/Player.hpp>
#include <inventory/IContainerListener.hpp>

struct Minecraft;
struct ServerPlayer: Player, IContainerListener
{
	Minecraft* minecraft;
	int32_t lastSentHealth, field_D60, field_D64;

	ServerPlayer(Minecraft*, Level*);
	void disconnect();
	void doCloseContainer();
	void nextContainerCounter();
	void setContainerMenu(BaseContainerMenu*);
	void setPlayerInput(float, float, bool_t, bool_t);


	virtual ~ServerPlayer();
	virtual void tick();
	virtual void ride(Entity*);
	virtual void aiStep();
	virtual void hurtArmor(int32_t);
	virtual bool_t hasResource(int32_t);
	virtual void completeUsingItem();
	virtual void take(Entity*, int32_t);
	virtual void openContainer(ChestTileEntity*);
	virtual void openFurnace(FurnaceTileEntity*);
	virtual void displayClientMessage(const std::string&);
	virtual void stopSleepInBed(bool_t, bool_t, bool_t);
	virtual void closeContainer();
	virtual void setContainerData(BaseContainerMenu*, int32_t, int32_t);
	virtual void slotChanged(BaseContainerMenu*, int32_t, const ItemInstance&, bool_t);
	virtual void refreshContainer(BaseContainerMenu*, const std::vector<ItemInstance>&);
};
