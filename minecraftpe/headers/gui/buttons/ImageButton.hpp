#pragma once
#include <_types.h>
#include <gui/buttons/Button.hpp>
#include <util/Color4.hpp>
#include <util/ImageDef.hpp>
struct Minecraft;

struct ImageButton : Button{
	ImageDef image;
	Color4 color;
	int8_t field_64, field_65, field_66, field_67;
	int32_t yOffset;

	ImageButton(int32_t, const std::string&);
	ImageButton(int32_t, const std::string &, const struct ImageDef&);
	void setImageDef(const ImageDef&, bool_t);

	virtual ~ImageButton();
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void renderBg( Minecraft*, int32_t, int32_t);
	virtual void setYOffset(int32_t);
	virtual void setupDefault(void);
	virtual bool_t isSecondImage(bool_t);
};
