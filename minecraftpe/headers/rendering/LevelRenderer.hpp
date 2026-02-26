#pragma once
#include <AppPlatform.hpp>
#include <level/LevelListener.hpp>
#include <rendering/MeshBuffer.hpp>
#include <util/Color4.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>
#include <memory>
#include <math/Vec3.hpp>

struct TextureAtlas;
struct Level;
struct RenderChunk;
struct Minecraft;
struct Textures;
struct FrustumCuller;
struct AABB;
struct HitResult;
struct Tile;
struct TileRenderer;
struct Mob;

struct LevelRenderer: LevelListener, AppPlatform::Listener
{
	float field_8;
	float field_C;
	float field_10;
	float field_14;
	int32_t field_18;
	int32_t field_1C;
	int32_t field_20;
	int32_t field_24;
	int32_t totalLoaded;
	int32_t frustrumClippedCnt;
	int32_t occludedCnt;
	int32_t totalRendered;
	int32_t field_38;
	int32_t field_3C;
	int32_t field_40;
	int32_t field_44;
	int32_t field_48;
	int32_t field_4C;
	int32_t field_50;
	int32_t field_54;
	Level* level;
	std::vector<RenderChunk*> _renderChunks;
	RenderChunk** chunks;
	int32_t chunksToRenderSize;
	TileRenderer* field_70;
	int32_t renderXsize;
	int32_t renderYsize;
	int32_t renderZSize;
	int32_t field_80;
	Minecraft* minecraft;
	bool_t field_88;
	int8_t field_89;
	int8_t field_8A;
	int8_t field_8B;
	int32_t renderDistance;
	int32_t ticksElapsed;
	MeshBuffer shadowVolumeBuffer;
	MeshBuffer shadowOverlayBuffer;
	MeshBuffer skyMesh;
	MeshBuffer cloudsMesh;
	MeshBuffer starsMesh;
	int32_t field_15C;
	int32_t field_160;
	Color4 field_164;
	Textures* textures;
	std::multimap<int32_t, Entity*, std::greater<int>> field_178;
	std::vector<TileEntity *> field_190;
	std::multimap<float, RenderChunk*> field_19C; //TODO not sure is this multimap or map, but seems to be more stable with multimap
	std::multimap<float, RenderChunk*> field_1B4; //TODO same as above
	Vec3 field_1CC;
	TextureAtlasTextureItem destroyTexture;
	float shadowRed;
	float shadowGreen;
	float shadowBlue;
	float shadowAlpha;

	LevelRenderer(Minecraft*, std::shared_ptr<TextureAtlas>);
	void _buildShadowOverlay(const Color4&);
	void _buildShadowVolume();
	void _buildStarsMesh();
	void _initResources();
	bool_t _renderChunk(MeshBuffer&);
	void _renderShadow(float, const Vec3&, float);
	void _renderStars(float);
	void _renderSunOrMoon(float, bool_t);
	void cullAndSort(FrustumCuller*, float, float);
	void deleteChunks();
	std::string gatherStats1();
	void generateSky();
	static int32_t getLayerFeature(int32_t, bool_t);
	void render(const AABB&);
	int32_t renderChunks(int32_t, float, bool_t);
	void renderClouds(float);
	void renderDebug(const AABB&, float);
	void renderEntities(Vec3, FrustumCuller*, bool_t, float);
	int32_t renderFarChunks(float);
	void renderFilledHitSelect(Player*, float, Tile*, const HitResult&);
	void renderHit(Player*, const HitResult&, int32_t, void*, float);
	void renderHitOutline(Player*, const HitResult&, int32_t, void*, float);
	void renderHitSelect(Player*, const HitResult&, int32_t, void*, float);
	void renderNameTags(float);
	void renderOutlineHitSelect(Player*, float, Tile*, const HitResult&);
	void renderShadows(const std::multimap<int32_t, Entity*, std::greater<int>>&, const std::vector<TileEntity*>&, float);
	void renderSky(float);
	int32_t renderStencilChunks(float);
	void resortChunks(int32_t, int32_t, int32_t);
	void setDirty(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void setLevel(Level*);
	void tick();
	bool updateDirtyChunks(Mob*, bool_t);

	virtual ~LevelRenderer();
	virtual void setTilesDirty(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void tileChanged(int32_t, int32_t, int32_t);
	virtual void skyColorChanged();
	virtual void allChanged();
	virtual void takePicture(TripodCamera*, Entity*);
	virtual Particle* addParticle(ParticleType, float, float, float, float, float, float, int32_t);
	virtual void playSound(const std::string&, float, float, float, float, float);
	virtual void entityAdded(Entity*);
	virtual void levelEvent(Player*, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void onAppSuspended();
	virtual void onAppResumed();
};
