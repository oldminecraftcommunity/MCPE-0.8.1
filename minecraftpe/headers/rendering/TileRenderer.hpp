#pragma once
#include <_types.h>
#include <rendering/TextureUVCoordinateSet.hpp>

struct Tile;
struct TileRenderer
{
	int8_t field_0, field_1, field_2, field_3;
	struct LevelSource* levelSource;
	TextureUVCoordinateSet field_8;
	bool_t hasUVCoords;
	int8_t field_21;
	bool_t disableCulling;
	int8_t field_23;
	float field_24, field_28, field_2C, field_30;
	float field_34, field_38, field_3C, field_40;
	float field_44, field_48, field_4C, field_50;
	int32_t field_54, field_58, field_5C, field_60;
	int32_t field_64, field_68;

	void _randomizeFaceDirection(Tile*, int32_t, float, float, float);
	static bool_t canRender(int32_t);

	TileRenderer(struct LevelSource*);
	float getWaterHeight(int32_t, int32_t, int32_t, const struct Material*);
	void renderEast(Tile*, float, float, float, const struct TextureUVCoordinateSet&);
	void renderFaceDown(Tile*, float, float, float, const struct TextureUVCoordinateSet&);
	void renderFaceUp(Tile*, float, float, float, const struct TextureUVCoordinateSet&);
	void renderGuiTile(Tile*, int32_t, float, float);
	void renderNorth(Tile*, float, float, float, const struct TextureUVCoordinateSet&);
	void renderSouth(Tile*, float, float, float, struct TextureUVCoordinateSet); //mojang moment
	void renderTile(Tile*, int32_t, bool_t);
	void renderWest(Tile*, float, float, float, const struct TextureUVCoordinateSet&);
	bool_t tesselateBedInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateBlockInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateBlockInWorld(Tile*, int32_t, int32_t, int32_t, float, float, float);
	bool_t tesselateBlockInWorldWithAmbienceOcclusion(Tile*, int32_t, int32_t, int32_t, float, float, float);
	bool_t tesselateCactusInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateCactusInWorld(Tile*, int32_t, int32_t, int32_t, float, float, float);
	bool_t tesselateCrossInWorld(Tile*, int32_t, int32_t, int32_t);
	void tesselateCrossTexture(Tile*, int32_t, float, float, float);
	bool_t tesselateDoorInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateFenceGateInWorld(struct FenceGateTile*, int32_t, int32_t, int32_t);
	bool_t tesselateFenceInWorld(struct FenceTile*, int32_t, int32_t, int32_t);
	bool_t tesselateFireInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateInWorld(Tile* a2, int32_t a3, int32_t a4, int32_t a5);
	bool_t tesselateInWorld(Tile*, int32_t, int32_t, int32_t, const struct TextureUVCoordinateSet&);
	bool_t tesselateInWorldNoCulling(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateLadderInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateRailInWorld(struct BaseRailTile*, int32_t, int32_t, int32_t);
	bool_t tesselateRowInWorld(Tile*, int32_t, int32_t, int32_t);
	void tesselateRowTexture(Tile*, int32_t, float, float, float);
	bool_t tesselateStairsInWorld(struct StairTile*, int32_t, int32_t, int32_t);
	void tesselateStemDirTexture(Tile*, int32_t, int32_t, float, float, float, float);
	bool_t tesselateStemInWorld(Tile*, int32_t, int32_t, int32_t);
	void tesselateStemTexture(Tile*, int32_t, float, float, float, float);
	bool_t tesselateThinFenceInWorld(struct ThinFenceTile*, int32_t, int32_t, int32_t);
	void tesselateTorch(Tile*, float, float, float, float, float);
	bool_t tesselateTorchInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateTreeInWorld(Tile*, int32_t, int32_t, int32_t);
	bool_t tesselateWallInWorld(struct WallTile*, int32_t, int32_t, int32_t);
	bool_t tesselateWaterInWorld(Tile*, int32_t, int32_t, int32_t);
};
