#pragma once
#include <gui/pane/ScrollingPane.hpp>

struct NinePatchLayer;
struct Textures;
struct IItemPaneCallback;
struct Font;
struct ItemPane: ScrollingPane
{
	Font* font;
	Textures* textures;
	IItemPaneCallback* callback;
	int32_t field_230;
	int8_t field_234, field_235, field_236, field_237;
	NinePatchLayer* field_238;
	NinePatchLayer* field_23C;

	ItemPane(IItemPaneCallback*, Textures*, const IntRectangle&, int32_t, int32_t, int32_t, bool_t);
	void drawScrollBar(ScrollBar&);

	virtual ~ItemPane();
	virtual void renderBatch(std::vector<ScrollingPane::GridItem>&, float, float, float);
	virtual bool_t onSelect(int32_t, bool_t);
};
