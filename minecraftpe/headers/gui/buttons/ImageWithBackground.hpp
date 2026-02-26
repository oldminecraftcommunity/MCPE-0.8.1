#pragma once
#include <_types.h>
#include <gui/buttons/LargeImageButton.hpp>
#include <util/IntRectangle.hpp>

struct ImageWithBackground : LargeImageButton{
	struct NinePatchLayer* field_70;
	struct NinePatchLayer* field_74;
	int32_t field_78;

	ImageWithBackground(int32_t);
	void init(struct Textures*, int32_t, int32_t, IntRectangle, IntRectangle, int32_t, int32_t, const std::string&);
	void setSize(float, float);

	virtual ~ImageWithBackground();
	virtual void render(struct Minecraft*, int32_t, int32_t);
	virtual void renderBg(struct Minecraft*, int32_t, int32_t);

};
