#pragma once
#include <entity/player/gamemode/GameMode.hpp>

struct CreativeMode: GameMode
{
	CreativeMode(Minecraft*);
	void creativeDestroyBlock(int32_t, int32_t, int32_t, int32_t);

	virtual ~CreativeMode();
	virtual void startDestroyBlock(int32_t, int32_t, int32_t, int32_t);
	virtual void continueDestroyBlock(int32_t, int32_t, int32_t, int32_t);
	virtual void stopDestroyBlock();
	virtual bool_t isCreativeType();
	virtual void initAbilities(Abilities&);
	virtual void releaseUsingItem(Player*);
};
