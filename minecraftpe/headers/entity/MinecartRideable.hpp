#pragma once
#include <entity/Minecart.hpp>

struct MinecartRideable: Minecart
{
	MinecartRideable(Level*);
	MinecartRideable(Level*, float, float, float);

	virtual ~MinecartRideable();
	virtual bool_t interactWithPlayer(Player*);
	virtual int32_t getType();
};
