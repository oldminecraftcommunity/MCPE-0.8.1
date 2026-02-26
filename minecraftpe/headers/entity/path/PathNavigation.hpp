#pragma once
#include <_types.h>
#include <math/Vec3.hpp>

struct Mob;
struct Level;
struct Path;
struct PathNavigation
{
	Mob* mob;
	Level* level;
	Path* path;
	float speedMultiplier;
	float field_10;
	bool_t avoidSun;
	//byte align_1, align_2, align_3;
	int32_t field_18, field_1C;
	Vec3 field_20;
	bool_t _canPassDoors, _canOpenDoors, avoidWater, canFloat;

	PathNavigation(Mob*, Level*, float);
	bool_t canMoveDirectly(Vec3, Vec3, int32_t, int32_t, int32_t);
	bool_t canOpenDoors();
	bool_t canPassDoors();
	bool_t canUpdatePath();
	bool_t canWalkAbove(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, Vec3, float, float);
	bool_t canWalkOn(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, Vec3, float, float);
	Path* createPath(Mob*);
	Path* createPath(float, float, float);
	bool_t getAvoidWater();
	Path* getPath();
	int32_t getSurfaceY();
	Vec3 getTempMobPos();
	bool_t isDone();
	bool_t isInLiquid();
	bool_t moveTo(Mob*, float);
	bool_t moveTo(Path*, float);
	bool_t moveTo(float, float, float, float);
	void setAvoidSun(bool_t);
	void setAvoidWater(bool_t);
	void setCanFloat(bool_t);
	void setCanOpenDoors(bool_t);
	void setCanPassDoors(bool_t);
	void setLevel(Level*);
	void setSpeed(float);
	void stop();
	void tick();
	void trimPathFromSun();
	void updatePath();
	~PathNavigation();
};
