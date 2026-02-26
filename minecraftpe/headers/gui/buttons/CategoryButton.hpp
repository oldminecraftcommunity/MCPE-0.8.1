#pragma once
#include <gui/buttons/ImageButton.hpp>
#include <gui/NinePatchLayer.hpp>

struct CategoryButton: ImageButton
{
	Button** field_70;
	NinePatchLayer *field_74, *field_78;

	CategoryButton(int32_t, NinePatchLayer*, NinePatchLayer*, Button**);
	CategoryButton(std::string, int32_t, NinePatchLayer*, NinePatchLayer*, Button**);
	virtual ~CategoryButton();
	virtual void renderBg(struct Minecraft*, int32_t, int32_t);
	virtual bool_t isSecondImage(bool_t);
};
