#include <gui/pane/ItemPane.hpp>
#include <crafting/CItem.hpp>
#include <gui/Gui.hpp>
#include <gui/NinePatchFactory.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/pane/IItemPaneCallback.hpp>
#include <rendering/Font.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <util/IntRectangle.hpp>
#include <util/Util.hpp>

ItemPane::ItemPane(IItemPaneCallback* a2, Textures* a3, const IntRectangle& a4, int32_t a6, int32_t a7, int32_t a8, bool_t a9)
	: ScrollingPane(a9 ? 513 : 514, a4, a9 ? IntRectangle{0, 0, a4.width, 22} : IntRectangle{0, 0, 32, a4.height}, a9 ? 1 : a6, a6, Gui::GuiScale, {0, 0, 0, 0}) {
	this->field_234 = a9;
	this->field_238 = 0;
	this->field_23C = 0;
	this->field_5C.minX = this->field_5C.minX - 4.0;
	this->field_5C.minY = 0;
	this->field_5C.maxX = this->field_5C.maxX + 4.0;
	this->field_5C.maxY = a7;
	this->field_230 = a8;
	this->textures = a3;
	this->callback = a2;
	NinePatchFactory factory(a3, "gui/spritesheet.png");
	this->field_238 = factory.createSymmetrical(IntRectangle{20, 32, 8, 8}, 2, 2, 32, 32);
	this->field_23C = factory.createSymmetrical(IntRectangle{28, 32, 8, 8}, 2, 2, 32, 32);
	this->field_238->setSize(a4.width + 4.0, 22);
	this->field_23C->setSize(a4.width + 4.0, 22);
}
void ItemPane::drawScrollBar(ScrollBar& a2) {
	float color; // s14

	color = a2.color;
	if(color > 0.0) {
		this->fill(a2.field_0 + 2.0, a2.field_4, (float)(a2.field_0 + 2.0) + a2.field_8, a2.field_4 + a2.field_C, ((int32_t)(float)(color * 255.0) << 24) | 0xFFFFFF);
	}
}

ItemPane::~ItemPane() {
	if(this->field_238) delete this->field_238;
	if(this->field_23C) delete this->field_23C;
}
void ItemPane::renderBatch(std::vector<ScrollingPane::GridItem>& a2, float a3, float a4, float a5) {
	std::vector<CItem*>* v7;	  // r9
	uint32_t v8;				  // r7
	float v9;					  // s15
	ScrollingPane::GridItem* v10; // r8
	NinePatchLayer* v11;		  // r10
	float v12;					  // r0
	uint32_t v13;				  // r7
	Textures* textures;			  // r11
	int32_t v15;				  // r2
	ScrollingPane::GridItem* v16; // r10
	float v17;					  // r0
	uint32_t v19;				  // r8
	ScrollingPane::GridItem* v20; // r7
	CItem* v21;					  // r10
	Font* font;					  // r11
	float v23;					  // s17
	float v24;					  // r0
	Font* v25;					  // r11
	float v26;					  // r10
	float v27;					  // r0
	float v28;					  // r0
	Font* v29;					  // r11
	float v30;					  // r10
	float v31;					  // r0
	int32_t v32;				  // r5
	int32_t minX;				  // r1
	int32_t minY;				  // r2
	int32_t v35;				  // r3
	int32_t a6;					  // [sp+0h] [bp-68h]
	ItemInstance* v37;			  // [sp+10h] [bp-58h]
	float v38;					  // [sp+14h] [bp-54h]
	float v39;					  // [sp+14h] [bp-54h]
	float v40;					  // [sp+14h] [bp-54h]
	float v41;					  // [sp+14h] [bp-54h]

	v7 = this->callback->getItems(this);
	if(v7->begin() != v7->end()) {
		v8 = 0;
		glEnable(0xC11u);
		v9 = this->field_24;
		glScissor((uint32_t)(float)(v9 * (float)this->field_2C.minX), this->field_230 - (uint32_t)(float)(v9 * (float)(this->field_2C.height + this->field_2C.minY)), (uint32_t)(float)(v9 * (float)this->field_2C.width), (uint32_t)(float)(v9 * (float)this->field_2C.height));
		Tesselator::instance.beginOverride();
		while(v8 < a2.size()) {
			v10 = &a2[v8];
			if(v10->field_14) {
				v11 = this->field_23C;
			} else {
				v11 = this->field_238;
			}
			++v8;
			v38 = Gui::floorAlignToScreenPixel(v10->field_C - 1.0);
			v12 = Gui::floorAlignToScreenPixel(v10->field_10);
			v11->draw(Tesselator::instance, v38, v12);
		}
		v13 = 0;
		Tesselator::instance.endOverrideAndDraw();
		while(1) {
			if(v13 >= a2.size()) {
				break;
			}
			textures = this->textures;
			v15 = v13++;
			v16 = &a2[v15];
			v37 = &v7->at(a2[v15].field_0)->field_0;
			v39 = Gui::floorAlignToScreenPixel((float)((float)this->field_4C.width + a2[v15].field_C) - 16.0);
			v17 = Gui::floorAlignToScreenPixel(v16->field_10 + 2.0);
			ItemRenderer::renderGuiItemNew(textures, v37, 0, v39, v17, 1.0, 1.0, 1.0);
		}
		v19 = 0;
		Tesselator::instance.beginOverride();
		while(v19 < a2.size()) {
			v20 = &a2[v19];
			v21 = v7->at(v20->field_0);
			std::string v42 = Util::toString(v21->field_24);
			font = this->font;
			v23 = v20->field_C - 1.0;
			if(v21->field_34) {
				v40 = Gui::floorAlignToScreenPixel(v23 + 5.0);
				v24 = Gui::floorAlignToScreenPixel(v20->field_10 + 6.0);
				font->drawShadow(v21->field_18, v40, v24, 0xFFF0F0F0);
				Tesselator::instance.scale2d(0.6667, 0.6667);
				v25 = this->font;
				v26 = Gui::floorAlignToScreenPixel((float)((float)(v23 + (float)this->field_4C.width) - (float)(uint32_t)(4 * v42.length())) * 1.5);
				v27 = Gui::floorAlignToScreenPixel((float)((float)((float)this->field_4C.height + v20->field_10) - 8.0) * 1.5);
				v25->drawShadow(v42, v26, v27, 0xFFF0F0F0);
			} else {
				v41 = Gui::floorAlignToScreenPixel(v23 + 5.0);
				v28 = Gui::floorAlignToScreenPixel(v20->field_10 + 7.0);
				font->drawShadow(v21->field_18, v41, v28, 0xC0635558, 0xC0AAAAAA);
				Tesselator::instance.scale2d(0.6667, 0.6667);
				v29 = this->font;
				v30 = Gui::floorAlignToScreenPixel((float)((float)(v23 + (float)this->field_4C.width) - (float)(uint32_t)(4 * v42.length())) * 1.5);
				v31 = Gui::floorAlignToScreenPixel((float)((float)((float)this->field_4C.height + v20->field_10) - 8.0) * 1.5);
				v29->draw(v42, v30, v31, 0xC0635558);
			}
			++v19;
			Tesselator::instance.resetScale();
		}
		Tesselator::instance.endOverrideAndDraw();
		v32 = (uint8_t)this->field_234;
		minX = this->field_2C.minX;
		minY = this->field_2C.minY;
		if(this->field_234) {
			this->fillGradient(minX, minY, minX + this->field_2C.width, minY + 40, 0x44000000, 0);
			a6 = this->field_2C.minY + this->field_2C.height;
			this->fillGradient(this->field_2C.minX, a6 - 40, this->field_2C.minX + this->field_2C.width, a6, 0, 0x44000000);
		} else {
			this->fillHorizontalGradient(minX, minY, minX + 28, minY + this->field_2C.height, 0xBB000000, v32);
			v35 = this->field_2C.minX + this->field_2C.width;
			this->fillHorizontalGradient(v35 - 28, this->field_2C.minY, v35, this->field_2C.minY + this->field_2C.height, v32, 0xBB000000);
		}
		glDisable(0xC11u);
		this->drawScrollBar(this->field_1C4);
		this->drawScrollBar(this->verticalScrollbar);
	}
}
bool_t ItemPane::onSelect(int32_t a2, bool_t a3) {
	if(a3) {
		this->callback->onItemSelected(this, a2);
	}
	return a3;
}
