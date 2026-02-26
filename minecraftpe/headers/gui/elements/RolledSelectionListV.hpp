#pragma once
#include <gui/GuiComponent.hpp>
struct Minecraft;
struct Tesselator;
struct RolledSelectionListV: GuiComponent
{
	Minecraft* minecraft;
	float field_8, field_C;
	int32_t field_10, field_14, field_18;
	float field_1C, field_20;
	int32_t field_24;
	float field_28, field_2C, field_30, field_34, field_38;
	int32_t field_3C;
	bool_t renderSelection, componentSelected;
	int8_t field_42, field_43, field_44, field_45, field_46, field_47;
	int32_t field_48, field_4C, field_50;
	int8_t field_54, field_55, field_56, field_57;
	int32_t field_58, field_5C;
	float field_60, field_64;

	RolledSelectionListV(Minecraft*, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);

	void evaluate(int32_t, int32_t);
	int32_t getItemAtYPositionRaw(int32_t);
	void renderDirtBackground();
	void setRenderHeader(bool_t, int32_t);

	virtual ~RolledSelectionListV();
	virtual int32_t getItemAtPosition(int32_t, int32_t);
	virtual int32_t capYPosition();
	virtual void tick();
	virtual void render(int32_t, int32_t, float);
	virtual void renderHoleBackground(float, float, int32_t, int32_t);
	virtual void setRenderSelection(bool_t);
	virtual void setComponentSelected(bool_t);
	virtual int32_t getNumberOfItems() = 0;
	virtual void selectStart(int32_t);
	virtual void selectCancel();
	virtual void selectItem(int32_t, bool_t) = 0;
	virtual bool_t isSelectedItem(int32_t) = 0;
	virtual int32_t getMaxPosition();
	virtual float getPos(float);
	virtual void touched();
	virtual void renderItem(int32_t, int32_t, int32_t, int32_t, Tesselator&) = 0;
	virtual void renderHeader(int32_t, int32_t, Tesselator&);
	virtual void renderBackground() = 0;
	virtual void renderForeground();
	virtual void renderDecoration(int32_t, int32_t);
	virtual void clickedHeader(int32_t, int32_t);
	virtual int32_t convertSelection(int32_t, int32_t, int32_t);
	virtual void onPreRender();
	virtual void onPostRender();

};
