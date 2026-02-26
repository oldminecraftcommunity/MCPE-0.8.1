#pragma once
#include <gui/GuiComponent.hpp>

struct Tesselator;
struct Minecraft;
struct ScrolledSelectionList: GuiComponent
{
	Minecraft* minecraft;
	float field_8, field_C;
	int32_t field_10, field_14, field_18;
	float field_1C, field_20;
	int32_t field_24, field_28;
	float field_2C, field_30, field_34;
	int32_t field_38, field_3C;
	bool_t renderSelection, field_41;
	int8_t field_42, field_43;
	int32_t field_44;

	ScrolledSelectionList(Minecraft*, int32_t, int32_t, int32_t, int32_t, int32_t);
	void renderDirtBackground();
	void setRenderHeader(bool_t, int32_t);

	virtual ~ScrolledSelectionList();
	virtual void setRenderSelection(bool_t);
	virtual int32_t getNumberOfItems() = 0;
	virtual void selectItem(int32_t, bool_t) = 0;
	virtual bool_t isSelectedItem(int32_t) = 0;
	virtual int32_t getMaxPosition();
	virtual void renderItem(int32_t, int32_t, int32_t, int32_t, Tesselator&) = 0;
	virtual void renderHeader(int32_t, int32_t, Tesselator&);
	virtual void renderBackground() = 0;
	virtual void renderDecorations(int32_t, int32_t);
	virtual void clickedHeader(int32_t, int32_t);
	virtual int32_t getItemAtPosition(int32_t, int32_t);
	virtual float capYPosition();
	virtual void render(int32_t, int32_t, float);
	virtual void renderHoleBackground(float, float, int32_t, int32_t);
};
