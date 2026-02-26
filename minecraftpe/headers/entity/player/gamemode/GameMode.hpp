#pragma once
#include <_types.h>

struct Minecraft;
struct Player;
struct Entity;
struct Level;
struct Abilities;
struct ItemInstance;
struct Vec3;

struct GameMode
{
	Minecraft* minecraft;
	float field_4, field_8;
	int32_t field_C, delay;

	GameMode(Minecraft*);

	virtual ~GameMode();
	virtual void initLevel(Level*);
	virtual void startDestroyBlock(int32_t, int32_t, int32_t, int32_t);
	virtual bool_t destroyBlock(int32_t, int32_t, int32_t, int32_t);
	virtual void continueDestroyBlock(int32_t, int32_t, int32_t, int32_t) = 0;
	virtual void stopDestroyBlock();
	virtual void tick();
	virtual void render(float);
	virtual float getPickRange();
	virtual bool_t useItem(Player*, Level*, ItemInstance*);
	virtual bool_t useItemOn(Player*, Level*, ItemInstance*, int32_t, int32_t, int32_t, int32_t, const Vec3&);
	virtual Player* createPlayer(Level*);
	virtual void initPlayer(Player*);
	virtual void adjustPlayer(Player*);
	virtual bool_t canHurtPlayer();
	virtual void interact(Player*, Entity*);
	virtual void attack(Player*, Entity*);
	virtual bool_t handleInventoryMouseClick(int32_t, int32_t, int32_t, Player*);
	virtual void handleCloseInventory(int32_t, Player*);
	virtual bool_t isCreativeType();
	virtual bool_t isSurvivalType();
	virtual void initAbilities(Abilities&);
	virtual void releaseUsingItem(Player*);
};
