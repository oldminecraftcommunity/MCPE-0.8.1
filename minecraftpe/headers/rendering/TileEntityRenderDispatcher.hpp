#pragma once
#include <_types.h>
#include <map>
#include <rendering/tileentity/TileEntityRendererId.hpp>

struct TileEntityRenderer;
struct Textures;
struct Level;
struct Mob;
struct Minecraft;
struct Font;
struct TileEntity;
struct TileEntityRenderDispatcher
{
	Textures* textures;
	Level* level;
	Mob* cameraMaybe;
	float camYaw, camPitch;
	float camX, camY, camZ;
	Minecraft* minecraft;
	Font* font;
	std::map<TileEntityRendererId, TileEntityRenderer*> rednerers;

	TileEntityRenderDispatcher();
	static void destroy();
	float distanceToSqr(float, float, float);
	Font* getFont();

	static TileEntityRenderDispatcher* instance;
	static float xOff;
	static float yOff;
	static float zOff;
	static TileEntityRenderDispatcher* getInstance();

	TileEntityRenderer* getRenderer(TileEntity*);
	TileEntityRenderer* getRenderer(TileEntityRendererId);
	void prepare(Level*, Textures*, Font*, Mob*, float);
	void render(TileEntity*, float);
	void render(TileEntity*, float, float, float, float);
	void setLevel(Level*);
	~TileEntityRenderDispatcher();
};
