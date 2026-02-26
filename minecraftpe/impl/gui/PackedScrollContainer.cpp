#include <gui/PackedScrollContainer.hpp>
#include <Minecraft.hpp>
#include <gui/Gui.hpp>
#include <gui/pane/ScrollingPane.hpp>
#include <util/IntRectangle.hpp>

PackedScrollContainer::PackedScrollContainer(bool_t a2, int32_t a3, int32_t a4)
	: GuiElementContainer(0, 1, 0, 0, 24, 24) {
	this->scrollingPane = 0;
	this->field_38 = 0;
	this->field_3C = a2;
	this->field_40 = a3;
	this->field_44 = a4;
}

PackedScrollContainer::~PackedScrollContainer() {
	if(this->scrollingPane) {
		delete this->scrollingPane;
		this->scrollingPane = 0;
	}
}
void PackedScrollContainer::tick(Minecraft* a2) {
	if(!this->scrollingPane) {
		this->setupPositions();
	}
	this->scrollingPane->tick();
	GuiElementContainer::tick(a2);
}
void PackedScrollContainer::render(Minecraft* a2, int32_t a3, int32_t a4) {
	int32_t posX;				  // r2
	int32_t v9;					  // lr
	int32_t width;				  // r12
	int32_t v11;				  // r0
	int32_t v12;				  // r3
	int32_t posY;				  // r1
	int32_t v14;				  // r9
	int32_t height;				  // r2
	int32_t v16;				  // s16
	int32_t v17;				  // s17
	int32_t v18;				  // r9
	int32_t v21;				  // r3
	int32_t v22;				  // r3
	ScrollBar* VerticleScrollBar; // r0
	float color;				  // s13
	int32_t v25;				  // [sp+Ch] [bp-3Ch]

	GuiElement::render(a2, a3, a4);
	this->setupPositions();
	glEnable(0xC11u);
	posX = this->posX;
	v9 = this->field_40;
	width = this->width;
	v11 = posX + v9;
	v12 = this->field_44;
	posY = this->posY;
	v14 = posX + width;
	height = this->height;
	v16 = v11;
	v25 = posY + v12;
	v9 *= -2;
	v17 = posY + height - v12;
	v18 = v14 + 1 + v9;
	glScissor((uint32_t)(float)(Gui::GuiScale * (float)v11), a2->field_20 - (uint32_t)(float)(Gui::GuiScale * (float)v17), (uint32_t)(float)(Gui::GuiScale * (float)(width + 1 + v9)), (uint32_t)(float)(Gui::GuiScale * (float)(height - 2 * v12)));

	for(auto v26: this->children) {
		v21 = v26->posX;
		if(v21 + v26->width >= v16 && v21 <= v18) {
			v22 = v26->posY;
			if(v22 + v26->height >= v25 && v22 < v17) {
				v26->render(a2, a3, a4);
			}
		}
	}
	this->scrollingPane->render(a3, a4, 1.0);
	VerticleScrollBar = this->scrollingPane->getVerticleScrollBar();
	color = VerticleScrollBar->color;
	if(color > 0.0) {
		this->fill(VerticleScrollBar->field_0, VerticleScrollBar->field_4 + 2.0, VerticleScrollBar->field_0 + VerticleScrollBar->field_8, (float)(VerticleScrollBar->field_4 + VerticleScrollBar->field_C) + 2.0, ((int32_t)(float)(color * 255.0) << 24) | 0xFFFFFF);
	}
	glDisable(0xC11u);
}
void PackedScrollContainer::setupPositions() {
	int32_t v3;			// r5
	int32_t v5;			// r6
	int32_t v8;			// r5
	int32_t v9;			// r3
	ScrollingPane* v10; // r0
	float v11;			// s16
	ScrollingPane* v12; // r0
	int32_t height;		// r2
	int32_t posY;		// r3
	int32_t v15;		// r1
	int32_t posX;		// r0
	int32_t v18;		// r7
	float v21;			// s15

	if(this->scrollingPane) {
		v3 = (int32_t)this->scrollingPane->getContentOffset()->y;
	} else {
		v3 = 0;
	}

	v5 = v3 + this->posY + this->field_44;
	for(auto a8: this->children) {
		a8->posX = this->posX + this->field_40;
		a8->width = this->width - 2 * this->field_40;
		a8->posY = v5 + this->field_44;
		a8->setupPositions();
		v5 += a8->height;
	}
	v8 = v5 - v3 - this->posY;
	v9 = this->field_38;
	if(!v9 || v8 != v9) {
		v10 = this->scrollingPane;
		if(v10) {
			v11 = v10->getContentOffset()->y;
			v12 = this->scrollingPane;
			if(v12) {
				delete v12;
			}
		} else {
			v11 = 0.0;
		}
		height = this->height;
		posY = this->posY;
		posX = this->posX;
		if(this->field_3C) {
			v18 = 529;
			if(v8 >= height) {
				v18 = 513;
			}
		} else {
			v18 = 513;
		}

		this->scrollingPane = new ScrollingPane(v18, IntRectangle{posX, posY, this->width, height}, IntRectangle{0, 0, this->width, (v8 < height ? height : v8) / 2}, 1, 2, Gui::GuiScale, {0, 0, 0, 0});
		v21 = (float)((this->height - v8) & ((this->height - v8) >> 31));
		if(v11 > v21) {
			v21 = v11;
		}
		this->scrollingPane->getContentOffset()->y = v21;
		this->scrollingPane->tick();
		this->field_38 = v8;
		if(v8 > 0) {
			this->setupPositions();
		}
	}
}
void PackedScrollContainer::mouseClicked(Minecraft* a2, int32_t a3, int32_t a4, int32_t a5) {
	if(this->pointInside(a3, a4)) {
		for(auto e: this->children) {
			e->mouseClicked(a2, a3, a4, a5);
		}
	}
}
void PackedScrollContainer::setTextboxText(const std::string& a2) {
	for(auto e: this->children) {
		e->setTextboxText(a2);
	}
}
