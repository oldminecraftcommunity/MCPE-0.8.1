#pragma once
#include <_types.h>

struct Player;
struct PlayerData
{
	float x, y, z;
	float motX, motY, motZ;
	float yaw, pitch;
	float fallDistance;
	int16_t fire, field_26;
	bool_t onGround;
	char align1, align2, align3;
	PlayerData(); //inlined
	/*
	 * this->playerData.x = 0.0;
	this->playerData.y = 0.0;
	this->playerData.z = 0.0;
	this->playerData.motX = 0.0;
	this->playerData.motY = 0.0;
	this->playerData.motZ = 0.0;
	*/

	void loadPlayer(Player*);
};
