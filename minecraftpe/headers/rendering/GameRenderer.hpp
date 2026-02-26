#pragma once
#include <_types.h>
#include <util/IntRectangle.hpp>
#include <util/Color4.hpp>
#include <math/Vec3.hpp>

extern int32_t t_keepPic;
struct GameRenderer{
	struct ItemInHandRenderer* itemInHandRenderer;
	struct Minecraft* minecraft;
	float field_8;
	int32_t field_C;
	Vec3 viewVector;
	int32_t field_1C;
	int32_t field_20, field_24, field_28, field_2C;
	int32_t field_30;
	float field_34, field_38;
	int32_t field_3C, field_40, field_44, field_48;
	float field_4C, field_50, field_54;
	float field_58, field_5C, field_60, field_64;
	float fov, field_6C, field_70;
	Color4 field_74;
	Color4 field_84;
	float field_94, field_98;
	float field_9C, field_A0, field_A4, field_A8;
	float field_AC;
	float projectionMat[16];
	float modelViewMat[16];
	float field_130, field_134, field_138;
	bool_t enableScissorTest;
	int8_t _align[3];
	IntRectangle scissorRect;
	bool_t field_150;
	int8_t field_151, field_152, field_153;
	float field_154;

	GameRenderer(struct Minecraft*);
	void bobHurt(float);
	void bobView(float);
	float getFov(float, bool_t);
	void moveCameraToPlayer(float);
	void pick(float);
	void render(float);
	void renderItemInHand(float, int32_t);
	void renderLevel(float);
	void renderSky(struct LevelRenderer*, float, float);
	void saveMatrices(void);
	void setupCamera(float, int32_t);
	void setupClearColor(float);
	void setupFog(int32_t);
	void setupGuiScreen(bool_t);
	void tick(int32_t, int32_t);
	void tickFov();
	void unZoomRegion();
	void updateAllChunks();
	bool_t updateFreeformPickDirection(float, struct Vec3&, struct Vec3&);
	~GameRenderer();

};
