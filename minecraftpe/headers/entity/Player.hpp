#pragma once
#include <_types.h>
#include <entity/Mob.hpp>
#include <RakNetTypes.h>
#include <item/ItemInstance.hpp>
#include <entity/player/Abilities.hpp>
#include <entity/player/SimpleFoodData.hpp>
#include <util/TilePos.hpp>

struct FurnaceTileEntity;
struct ChestTileEntity;
struct BaseContainerMenu;
struct Tile;
struct Player : Mob{
	static const float DEFAULT_FLY_SPEED, DEFAULT_WALK_SPEED;
	int8_t field_C6C, field_C6D, field_C6E, field_C6F;
	int32_t score;
	float field_C74, field_C78;
	std::string username;
	int32_t dimension;
	Abilities abilities;
	SimpleFoodData foodData;
	struct BaseContainerMenu* currentContainer;
	int8_t field_C90, field_C91, field_C92, field_C93;
	RakNet::RakNetGUID rakNetGUID;
	std::string field_CA4;
	int32_t field_CA8;
	int32_t field_CAC;
	struct Inventory* inventory;
	bool field_CB4;
	Pos bedPosition;
	float field_CC4;
	float field_CC8;
	float field_CCC;
	bool playerVerified;
	ItemInstance item;
	int32_t useItemDuration;
	int16_t sleepingCounter;
	ItemInstance armorSlots[4];
	Pos spawn;
	bool hasRespawnPos;
	bool sleeping;
	bool allPlayersSleeping;
	bool isDestroying;

	Player(Level*, bool_t);
	void _init();
	void animateRespawn(Player*, Level*);
	static Player* asPlayer(Entity*);
	void attack(Entity*);
	bool_t canDestroy(Tile*);
	bool_t canUseCarriedItemWhileMoving();
	bool_t checkBed();
	void findStandUpPosition(Entity*);
	ItemInstance* getArmor(int32_t);
	int32_t getArmorTypeHash();
	float getDestroySpeed(Tile*);
	TilePos getRespawnPosition();
	int32_t getScore();
	ItemInstance* getSelectedItem();
	float getSleepRotation();
	int32_t getTicksUsingItem();
	ItemInstance* getUseItem();
	bool_t hasRespawnPosition();
	void interact(Entity*);
	bool_t isHurt();
	static bool_t isPlayer(Entity*);
	bool_t isSleepingLongEnough();
	bool_t isUsingItem();
	void reallyDrop(struct ItemEntity*);
	void releaseUsingItem();
	void respawn();
	void setAllPlayersSleeping();
	void setArmor(int32_t, const ItemInstance*);
	void setBedOffset(int32_t);
	void setDefaultHeadHeight();
	void setRespawnPosition(const struct Pos&);
	void spawnEatParticles(const ItemInstance*, int32_t);
	void startUsingItem(ItemInstance, int32_t);
	void stopUsingItem();
	void tileEntityDestroyed(int32_t);
	void touch(Entity*);

	virtual ~Player();
	virtual void reset();
	virtual void remove();
	virtual void tick();
	virtual void rideTick();
	virtual float getRidingHeight();
	virtual void ride(Entity*);
	virtual bool_t isInWall();
	virtual float getHeadHeight();
	virtual bool_t isShootable();
	virtual bool_t isPlayer();
	virtual bool_t isCreativeModeAllowed();
	virtual bool_t hurt(Entity*, int32_t);
	virtual void handleEntityEvent(char);
	virtual void awardKillScore(Entity*, int32_t);
	virtual int32_t getEntityTypeId() const {
		return 0;
	}
	virtual void resetPos(bool_t);
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual void die(Entity*);
	virtual bool_t isSleeping();
	virtual float getBaseSpeed() {
		return Player::DEFAULT_WALK_SPEED;
	}
	virtual int32_t getMaxHealth();
	virtual int32_t getArmorValue();
	virtual void travel(float, float);
	virtual void aiStep();
	virtual ItemInstance* getCarriedItem();
	virtual int32_t getUseItemDuration();
	virtual bool_t isImmobile();
	virtual void updateAi();
	virtual float getWalkingSpeedModifier();
	virtual void hurtArmor(int32_t);
	virtual bool_t hasResource(int32_t);
	virtual void completeUsingItem();
	virtual void take(Entity*, int32_t);
	virtual void drop(const ItemInstance*);
	virtual void drop(const ItemInstance*, bool_t);
	virtual void startCrafting(int32_t, int32_t, int32_t, int32_t);
	virtual void startStonecutting(int32_t, int32_t, int32_t);
	virtual void startDestroying() {
		this->isDestroying = 1;
	}
	virtual void stopDestroying() {
		this->isDestroying = 0;
	}
	virtual void openContainer(ChestTileEntity*);
	virtual void openFurnace(FurnaceTileEntity*);
	virtual void displayClientMessage(const std::string&);
	virtual void animateRespawn();
	virtual int32_t startSleepInBed(int32_t, int32_t, int32_t);
	virtual void stopSleepInBed(bool_t, bool_t, bool_t);
	virtual int32_t getSleepTimer();
	virtual void openTextEdit(struct TileEntity*);
	virtual bool_t isLocalPlayer();
	virtual void closeContainer();
};
