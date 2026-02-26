#pragma once
#include <_types.h>
#include <string>

struct Level;
struct Font;
struct TileEntityRenderDispatcher;
struct TileEntity;
struct TileEntityRenderer
{
	TileEntityRenderDispatcher* dispatcher;

	TileEntityRenderer(void);
	void bindTexture(const std::string&);
	Font* getFont();
	Level* getLevel();
	void init(TileEntityRenderDispatcher*);

	virtual ~TileEntityRenderer();
	virtual void render(TileEntity*, float, float, float, float, bool_t) = 0;
	virtual void onNewLevel(Level*);
};
