#pragma once
#include <gui/GuiComponent.hpp>
#include <input/ITurnInput.hpp>
#include <input/IBuildInput.hpp>
#include <util/area/RectangleArea.hpp>
#include <input/TouchAreaModel.hpp>
#include <util/area/IncludeExcludeArea.hpp>

struct Minecraft;
struct Entity;
struct Options;
struct IInputHolder;
struct Player;
struct BuildActionIntention;
struct UnifiedTurnBuild: GuiComponent, ITurnInput, IBuildInput
{
	int32_t field_1C;
	int8_t field_20, field_21, field_22, field_23;
	int32_t field_24, field_28, field_2C, field_30;
	RectangleArea field_34, field_4C, field_64, field_7C, field_94;
	IInputHolder* field_AC;
	int32_t field_B0;
	float field_B4, field_B8;
	int8_t field_BC, field_BD, field_BE, field_BF;
	TouchAreaModel field_C0;
	IncludeExcludeArea field_D0;
	int32_t field_F0, field_F4;
	double field_F8;
	float field_100, field_104, field_108;
	int32_t field_10C;
	double field_110;
	int32_t field_118;
	int8_t field_11C, field_11D, field_11E, field_11F;
	int32_t field_120;
	Options* options;

	UnifiedTurnBuild(int32_t, int32_t, int32_t, float, float, IInputHolder*, Minecraft*);
	static float getSpeedSquared(Entity*);

	virtual ~UnifiedTurnBuild();
	virtual void onConfigChanged(const Config&);
	virtual Vec3 getTurnDelta();
	virtual bool_t tickBuild(Player*, BuildActionIntention*);

};
