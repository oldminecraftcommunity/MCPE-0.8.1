#pragma once
#include <entity/Mob.hpp>

struct Player;
struct TripodCamera: Mob
{
	int32_t field_C70;
	Player* player;
	bool_t field_C78;
	byte field_C79, field_C7A, field_C7B;

	TripodCamera(Level*, Player*, float, float, float);

	virtual ~TripodCamera();
	virtual void tick();
	virtual float getShadowHeightOffs();
	virtual bool_t interactPreventDefault();
	virtual bool_t interactWithPlayer(Player*);
	virtual bool_t isPickable();
	virtual bool_t isPushable();
	virtual int32_t getEntityTypeId() const;
	virtual float getBaseSpeed();
};
