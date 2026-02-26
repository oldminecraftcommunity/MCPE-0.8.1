#pragma once
#include <rendering/entity/EntityRenderer.hpp>
#include <rendering/entity/ItemRenderChunkType.hpp>

struct Tesselator;
struct ItemInstance;
struct TextureUVCoordinateSet;
struct Textures;
struct TileRenderer;

struct ItemRenderer: EntityRenderer
{
	static TileRenderer* tileRenderer;
	static bool_t inited;
	static float rndFloats[];

	ItemRenderer();
	static void blit(float, float, float, float, float, float);
	static void fillRect(Tesselator&, float, float, float, float, int32_t);
	static int32_t getAtlasPos(const ItemInstance*);
	static void iconBlit(float, float, const TextureUVCoordinateSet&, float, float, float, float, int32_t, float);
	static void renderGuiItem(Font*, Textures*, const ItemInstance*, float, float, bool_t);
	static void renderGuiItem(Font*, Textures*, const ItemInstance*, float, float, float, float, bool_t);
	static void renderGuiItemCorrect(Font*, Textures*, const ItemInstance*, int32_t, int32_t);
	static void renderGuiItemDecorations(const ItemInstance*, float, float);
	static void renderGuiItemInChunk(ItemRenderChunkType, Textures*, const ItemInstance*, float, float, float, float, float);
	static void renderGuiItemNew(Textures*, const ItemInstance*, int32_t, float, float, float, float, float);
	static void teardown_static();

	virtual ~ItemRenderer();
	virtual void render(Entity*, float, float, float, float, float);

};
