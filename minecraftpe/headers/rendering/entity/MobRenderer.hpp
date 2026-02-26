#pragma once
#include <rendering/entity/EntityRenderer.hpp>

struct Model;
struct Mob;
struct Color4;
struct MobRenderer: EntityRenderer
{
	static int8_t menuMode;

	Model* model;
	Model* armorModel;
	float field_8, field_C, field_10, field_14, field_18, field_1C, field_20;

	MobRenderer(Model*, float);
	void _renderColorOverlay(Mob*, const Color4&, float);
	Model* getArmor();
	void setArmor(Model*);

	virtual ~MobRenderer();
	virtual void render(Entity*, float, float, float, float, float);
	virtual int32_t prepareArmor(Mob*, int32_t slot, float);
	virtual void setupPosition(Entity*, float, float, float);
	virtual void setupRotations(Entity*, float, float, float);
	virtual float getAttackAnim(Mob*, float);
	virtual float getBob(Mob*, float);
	virtual float getFlipDegrees(Mob*);
	virtual int32_t getOverlayColor(Mob*, float, float);
	virtual void scale(Mob*, float);
	virtual void additionalRendering(Mob*, float);
	virtual int32_t getArmorTransparencyMode();
};
