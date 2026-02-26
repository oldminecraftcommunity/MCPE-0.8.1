#pragma once
#include <_types.h>
#include <string>
#include <gui/buttons/ImageButton.hpp>

struct LargeImageButton : ImageButton{
	float field_6C;

	LargeImageButton(int32_t, const std::string&);
	LargeImageButton(int32_t, const std::string&, struct ImageDef&);

	virtual ~LargeImageButton();
	virtual void render(struct Minecraft*, int32_t, int32_t);
	virtual void setupDefault();
};
