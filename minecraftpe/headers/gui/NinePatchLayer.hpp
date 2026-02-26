#pragma once
#include <_types.h>
#include <gui/GuiElement.hpp>
#include <gui/NinePatchDescription.hpp>

struct NinePatchLayer : GuiElement{

	struct CachedQuad{
		float field_0, field_4, field_8, field_C;
		float field_10, field_14, field_18, field_1C;
		float field_20;
	};

	float width2, height2;
	NinePatchDescription patchDescription;
	std::string field_64;
	struct Textures* textures;
	int32_t excluded;
	NinePatchLayer::CachedQuad cachedQuads[9];

	NinePatchLayer(const NinePatchDescription&, const std::string&, struct Textures*, float, float);
	void buildQuad(int32_t);
	void d(struct Tesselator&, const NinePatchLayer::CachedQuad&);
	void draw(struct Tesselator&, float, float);
	NinePatchLayer* exclude(int32_t);
	void getPatchInfo(int32_t, int32_t, float&, float&, float&, float&);
	NinePatchLayer* setExcluded(int32_t);
	void setSize(float, float);
	virtual ~NinePatchLayer();
};
