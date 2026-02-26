#pragma once
#include <gui/buttons/ImageButton.hpp>
#include <util/IntRectangle.hpp>
struct Textures;
struct NinePatchLayer;
struct CraftButton: ImageButton
{
	NinePatchLayer* field_70;
	NinePatchLayer* field_74;
	int32_t field_78;

	CraftButton(int32_t);
	IntRectangle getItemPos(int32_t); //TODO check type
	void init(Textures*);
	void setSize(float, float);

	virtual ~CraftButton();
	virtual void renderBg(Minecraft*, int32_t, int32_t);

};
