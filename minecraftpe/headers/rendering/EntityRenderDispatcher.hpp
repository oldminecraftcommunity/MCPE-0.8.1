#pragma once
#include <_types.h>
#include <memory>
#include <rendering/EntityRendererId.hpp>

struct Textures;
struct Level;
struct Minecraft;
struct Mob;
struct Options;
struct Font;
struct ItemInHandRenderer;
struct EntityRenderer;
struct Entity;

struct EntityRenderDispatcher
{
	static EntityRenderDispatcher* instance;
	static float xOff, yOff, zOff;

	ItemInHandRenderer* itemInHandRenderer;
	Textures* textures;
	Level* level;
	Minecraft* minecraft;
	Mob* cameraEntity;
	float field_14, field_18;
	Options* options;
	float field_20, field_24, field_28;
	Font* font;
	std::shared_ptr<EntityRenderer> renderers[EntityRendererId::LENGTH];

	EntityRenderDispatcher();
	void assign(EntityRendererId, EntityRenderer*);
	static void destroy();
	float distanceToSqr(float, float, float);
	Font* getFont();
	static EntityRenderDispatcher* getInstance();
	EntityRenderer* getRenderer(Entity*);
	EntityRenderer* getRenderer(EntityRendererId);
	void prepare(Level*, Font*, Mob*, Options*, float);
	void render(Entity*, float);
	void render(Entity*, float, float, float, float, float);
	void setLevel(Level*);
	void setMinecraft(Minecraft*);
	~EntityRenderDispatcher();
};
