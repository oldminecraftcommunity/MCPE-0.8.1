#include <gui/screens/PaneCraftingScreen.hpp>
#include <I18n.hpp>
#include <Minecraft.hpp>
#include <algorithm>
#include <crafting/CItem.hpp>
#include <crafting/Recipe.hpp>
#include <entity/LocalPlayer.hpp>
#include <gui/NinePatchFactory.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/pane/ItemPane.hpp>
#include <gui/pane/ScrollingPane.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <perf/StopwatchNLast.hpp>
#include <rendering/Font.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <string.h>
#include <tile/Tile.hpp>
#include <gui/buttons/CategoryButton.hpp>
#include <crafting/Recipes.hpp>

static NinePatchLayer* _D6E06298;
PaneCraftingScreen::PaneCraftingScreen(int32_t a2)
	: closeButton(2, "")
	, craftButton(1) {
	this->field_78 = -1;
	this->field_7C = 0;
	this->scrollingPane = 0;
	this->field_184.minX = 0;
	this->field_184.minY = 0;
	this->field_1B0 = 0;
	this->field_1B4 = 0;
	this->field_1B8 = 0;
	this->field_1BC = 0;
	this->field_17C = a2;
	this->field_184.width = 1;
	this->field_184.height = 1;
	this->field_194 = 4;
	for(int v7 = 0; v7 < this->field_194; ++v7) {
		this->intvec1.emplace_back(1 << v7);
		this->intvec2.push_back(v7);
	}
}

static bool _D65FAB7C(CItem* a1, CItem* a2) {
	if((uint8_t)a2->field_34 == (uint8_t)a1->field_34) {
		return a1->field_1C.compare(a2->field_1C) >> 31; //TODO check
	}
	return a1->field_34;
}

void PaneCraftingScreen::_resortRecipes() {
	for(int i = 0; i < this->field_6C.size(); ++i) {
		std::stable_sort(this->field_6C[i].begin(), this->field_6C[i].end(), _D65FAB7C);
	}

	if(this->field_78 >= 0) {
		int32_t v8 = 0;
		for(auto&& e: this->field_6C[this->field_78]) {
			if(e == this->field_7C) {
				this->scrollingPane->setSelected(v8, 1);
			}
			++v8;
		}
	}
}
void PaneCraftingScreen::addItem(Recipe* a2) {
	const std::vector<ItemInstance>* v4 = a2->getResultItem();
	ItemInstance is(v4->at(0));
	CItem* v6 = new CItem(is, a2, is.getName());
	if(Tile::cloth == is.tileClass && Tile::cloth) {
		v6->field_1C = "Wool " + v6->field_18;
	}
	if(Item::dye_powder == is.itemClass && Item::dye_powder) {
		v6->field_1C = "ZDye " + v6->field_18;
	}
	this->field_60.push_back(v6);
	if(is.itemClass->field_38 >= 0) {
		for(int32_t i = 0; i < this->intvec1.size(); ++i) {
			if((this->intvec1[i] & is.itemClass->field_38) != 0) {
				this->field_6C[i].push_back(v6);
			}
		}
	}
}
void PaneCraftingScreen::clearCategoryItems() {
	for(uint32_t i = 0; i < this->field_84.size(); ++i) {
		if(this->field_84[i]) {
			delete this->field_84[i];
		}
	}
	this->field_84.clear();
}
void PaneCraftingScreen::closeScreen() {
	if(this->minecraft->useTouchscreen() && !this->field_17C) {
		this->minecraft->screenChooser.setScreen(INVENTORY_SCREEN);
	} else {
		this->minecraft->setScreen(0);
	}
}
void PaneCraftingScreen::craftSelectedItem() {
	if(this->field_7C) {
		if(this->field_7C->field_34) {
			if(this->minecraft->player) {
				for(int32_t i = 0; i < this->field_7C->field_28.size(); ++i) {
					ItemInstance* v3 = &this->field_7C->field_28[i].item;
					ItemInstance v11(*v3);
					if(v3->tileClass == Tile::sandStone && v3->getAuxValue() == -1) {
						v11.setAuxValue(0);
						v11.count = this->minecraft->player->inventory->removeResource(v11, 1);
						v11.setAuxValue(-1);
					}
					if(v11.count > 0) {
						this->minecraft->player->inventory->removeResource(v11);
					}
				}

				const std::vector<ItemInstance>* v7 = this->field_7C->recipe->getResultItem();
				for(auto p: *v7) { //p should be a copy of ItemInstance
					if(!this->minecraft->player->inventory->add(&p)) {
						this->minecraft->player->drop(&p, 0);
					}
				}
				this->recheckRecipes();
			}
		}
	}
}
void PaneCraftingScreen::initCategories() {
	int v2 = this->field_194;
	this->field_6C.resize(v2);
	for(int i = 0; i < this->field_194; ++i) {
		CategoryButton* v8 = new CategoryButton(i + 100, this->field_1B8, this->field_1BC, &this->field_1B0);
		this->field_54.emplace_back(v8);
		this->buttons.emplace_back(v8);
	}

	std::vector<Recipe*>* vec = Recipes::getInstance()->getRecipes();
	std::vector<Recipe*> a3;
	a3.reserve(vec->size());
	for(int j = 0; j < vec->size(); ++j) {
		if(this->field_17C >= vec->at(j)->getCraftingSize()) {
			a3.emplace_back(vec->at(j));
		}
	}
	this->filterRecipes(a3);
	for(int v22 = 0; v22 < a3.size(); ++v22) {
		this->addItem(a3[v22]);
	}
	this->recheckRecipes();

}
void PaneCraftingScreen::onItemSelected(int32_t a2, CItem* a3) {
	int32_t a6;

	this->field_7C = a3;
	this->field_80 = I18n::getDescriptionString(a3->field_0);
	if(a2 != this->field_78) {
		this->clearCategoryItems();
		a6 = this->field_6C[a2].size();
		if(this->scrollingPane) {
			delete this->scrollingPane;
		}
		this->scrollingPane = new ItemPane(this, this->minecraft->texturesPtr, this->field_184, a6, this->height, this->minecraft->field_20, 1);
		((ItemPane*)this->scrollingPane)->font = this->minecraft->font;
		this->field_78 = a2;
	}
}
void PaneCraftingScreen::recheckRecipes() {
	ItemPack v33;
	if(this->minecraft->player) {
		if(this->minecraft->player->inventory) {
			for(int i = 9; i < this->minecraft->player->inventory->getContainerSize(); ++i) {
				ItemInstance* v5 = this->minecraft->player->inventory->getItem(i);
				if(v5) {
					v33.add(ItemPack::getIdForItemInstance(v5), v5->count);
				}
			}
		}
	}

	v33.print();
	Stopwatch res;
	res.start();
	for(int v3 = 0; v3 < this->field_60.size(); ++v3) {
		CItem* v9 = this->field_60[v3];
		v9->field_28.clear();
		v9->field_34 = 1;
		v9->field_24 = v33.getCount(ItemPack::getIdForItemInstance(&v9->field_0));
		std::vector<ItemInstance> v32 = v9->recipe->getItemPack()->getItemInstances();

		for(int v10 = 0; v10 < v32.size(); ++v10) {
			ItemInstance* v14 = &v32[v10];
			bool v = Recipe::isAnyAuxValue(v14->getId());
			int count;
			if(v || v14->getAuxValue() != -1) {
				count = v33.getCount(ItemPack::getIdForItemInstance(v14));
			} else {
				ItemInstance v34(*v14);
				count = 0;
				for(int i = 0; i != 16; ++i) {
					v34.setAuxValue(i);
					count += v33.getCount(ItemPack::getIdForItemInstance(&v34));
				}
			}
			CItem::ReqItem v34(*v14, count);
			v9->field_28.emplace_back(v34); //TODO check

			if(v9->field_34) {
				v9->field_34 = v34.field_14 >= v34.item.count;
			} else {
				v9->field_34 = 0;
			}
		}
	}

	res.stop();
	res.printEvery(1, "> craft ");
	this->_resortRecipes();
}
void PaneCraftingScreen::setSingleCategoryAndIcon(int32_t a2, int32_t a3) {
	this->field_194 = 1;
	this->intvec2.clear();
	this->intvec2.push_back(a3);
	this->intvec1.clear();
	this->intvec1.push_back(a2);
}

PaneCraftingScreen::~PaneCraftingScreen() {
	for(int32_t i = 0; i < this->field_60.size(); ++i) {
		if(this->field_60[i]) {
			delete this->field_60[i];
		}
	}

	for(int32_t i = 0; i < this->field_54.size(); ++i) {
		if(this->field_54[i]) {
			delete this->field_54[i];
		}
	}

	this->clearCategoryItems();

	if(this->scrollingPane) delete this->scrollingPane;
	if(this->field_1B4) delete this->field_1B4;
	if(this->field_1B8) delete this->field_1B8;
	if(this->field_1BC) delete this->field_1BC;
	if(_D6E06298) delete _D6E06298;
}
void PaneCraftingScreen::render(int32_t a2, int32_t a3, float a4) {
	static StopwatchNLast swlast(5);

	this->field_1B4->draw(Tesselator::instance, 0, 0);
	Screen::render(a2, a3, a4);
	swlast.start();
	_D6E06298->draw(Tesselator::instance, this->field_184.minX - 1, this->field_184.minY - 2);
	if(this->scrollingPane) this->scrollingPane->render(a2, a3, a4);
	swlast.stop();
	float v9 = (float)this->craftButton.width * 0.5;
	float v10 = (float)this->craftButton.height * 0.5;
	float v11 = (float)((float)this->craftButton.posX + (float)(v9 * 0.5)) - 8.0;
	float v12 = (float)((float)this->craftButton.posY + (float)(v10 * 0.5)) - 9.0;
	ItemInstance v30;
	if(this->field_7C) {
		for(int i = 0; i < this->field_7C->field_28.size(); ++i) {
			v30 = this->field_7C->field_28[i].item;
			if(v30.getAuxValue() == -1) {
				v30.setAuxValue(0);
			}
			float a5 = v12 + (float)(v10 * (float)(i >> 1));
			float v18 = v11 + (float)(v9 * (float)(i & 1));
			ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, (const ItemInstance*)&v30, 0, v18, a5, 1.0, 1.0, 1.0);
		}
		Tesselator::instance.begin(0);
		Tesselator::instance.voidBeginAndEndCalls(1);
		Tesselator::instance.scale2d(0.66667, 0.66667);
		for(int v22 = 0; v22 < this->field_7C->field_28.size(); ++v22) {
			CItem::ReqItem* v23 = &this->field_7C->field_28[v22];
			char buf[16]; //TODO check size
			int v24 = Gui::itemCountItoa(buf, v23->field_14);
			int v25 = v24 + 1;
			strcpy(&buf[v24], "/");
			buf[v25 + Gui::itemCountItoa(buf + v25, v23->item.count)] = 0;
			if(v23->field_14 < v23->item.count) {
				this->minecraft->font->draw(buf, (float)((float)((float)(v11 + (float)(v9 * (float)(v22 & 1))) * 1.5) + 4.0) + 1.0, (float)((float)((float)(v12 + (float)(v10 * (float)(v22 >> 1))) * 1.5) + 23.0) + 1.0, 0xC0AAAAAA);
				this->minecraft->font->draw(buf, (float)((float)(v11 + (float)(v9 * (float)(v22 & 1))) * 1.5) + 4.0, (float)((float)(v12 + (float)(v10 * (float)(v22 >> 1))) * 1.5) + 23.0, 0xC0635558);
			} else {
				this->minecraft->font->drawShadow(buf, (float)((float)(v11 + (float)(v9 * (float)(v22 & 1))) * 1.5) + 4.0, (float)((float)(v12 + (float)(v10 * (float)(v22 >> 1))) * 1.5) + 23.0, 0xFFF0F0F0);
			}
		}
		Tesselator::instance.resetScale();
		Tesselator::instance.voidBeginAndEndCalls(0);
		Tesselator::instance.draw(1);
		this->minecraft->font->drawWordWrap(this->field_80, (float)this->craftButton.posX, (float)(this->craftButton.posY + this->craftButton.height + 6), (float)this->craftButton.width, 0xFFF0F0F0, 1, 0);
	}
}
void PaneCraftingScreen::init() {
	ImageDef a2;
	a2.field_0 = "gui/spritesheet.png";
	a2.field_8 = 1;
	a2.height = 18.0;
	a2.width = 18.0;
	a2.field_24 = 1;
	a2.field_14 = 60;
	a2.field_4 = 0;
	a2.field_1C = 18;
	a2.field_20 = 18;
	a2.field_18 = 0;
	this->closeButton.setImageDef(a2, 1);
	this->closeButton.field_64 = 0;
	this->craftButton.init(this->minecraft->texturesPtr);
	this->buttons.emplace_back(&this->craftButton);
	this->buttons.emplace_back(&this->closeButton);
	NinePatchFactory a1(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_1B4 = a1.createSymmetrical({0, 0, 16, 16}, 4, 4, 32, 32);
	_D6E06298 = a1.createSymmetrical({0, 20, 8, 8}, 1, 2, 32, 32)->setExcluded(16);
	this->field_1B8 = a1.createSymmetrical({8, 32, 8, 8}, 2, 2, 32, 32);
	this->field_1BC = a1.createSymmetrical({0, 32, 8, 8}, 2, 2, 32, 32);
	this->initCategories();
}
void PaneCraftingScreen::setupPositions() {
	int v2;			 // r1
	int height;		 // r0
	int v4;			 // r9
	int v5;			 // r7
	int v7;			 // r5
	int i;			 // r3
	ImageButton* v9; // r8
	int v10;		 // r10
	int width;		 // r2
	int v13;		 // r1
	int v14;		 // s14
	int v15;		 // r1
	int v16;		 // r3

	v2 = this->field_194;
	height = this->height;
	v4 = 6;
	if(v2 < 4) {
		v2 = 4;
	}

	v7 = (height - 16) / v2;
	i = 6;
	for(v5 = 0; v5 < this->field_54.size(); ++v5) {
		v4 += v7 + 1;
		v9 = this->field_54[v5];
		v9->posX = i;
		v9->posY = ~v7 + v4;
		v9->width = v7;
		v9->height = v7;
		v10 = this->intvec2[v5];
		ImageDef a2;
		a2.height = (float)v7;
		a2.width = (float)v7;
		a2.field_0 = "gui/spritesheet.png";
		a2.field_24 = 1;
		a2.field_14 = 32 * (v10 / 2);
		a2.field_18 = 32 * ((v10 & 1) + 2);
		a2.field_1C = 32;
		a2.field_20 = 32;
		v9->setImageDef(a2, 0);
	}
	this->craftButton.posX = this->width - 95;
	this->craftButton.posY = 20;
	this->craftButton.setSize(88.0, 62.0);
	width = this->width;
	this->closeButton.height = 19;
	this->closeButton.width = 19;
	this->field_184.minY = 8;
	this->closeButton.posX = width - 19;
	v13 = this->height;
	this->closeButton.posY = 0;
	this->field_184.minX = v7 + 12;
	v13 -= 16;
	this->field_184.height = v13;
	v14 = width - (v7 + 12) - 100;
	this->field_184.width = v14;
	_D6E06298->setSize((float)v14 + 2.0, (float)v13 + 4.0);
	this->field_1B4->setSize((float)this->width, (float)this->height);
	this->field_1B8->setSize((float)v7, (float)v7);
	this->field_1BC->setSize((float)v7, (float)v7);
	v15 = this->field_78;
	this->field_78 = -1;
	if(this->scrollingPane) {
		v16 = v15;
	} else {
		v16 = 0;
	}
	this->buttonClicked(this->field_54[v16]);
}
bool_t PaneCraftingScreen::handleBackEvent(bool_t a2) {
	if(a2) {
		this->closeScreen();
	}
	return 1;
}
void PaneCraftingScreen::tick() {
	ScrollingPane* scrollingPane; // r0

	scrollingPane = this->scrollingPane;
	if(scrollingPane) {
		scrollingPane->tick();
	}
}
bool_t PaneCraftingScreen::renderGameBehind() {
	return 0;
}
bool_t PaneCraftingScreen::closeOnPlayerHurt() {
	return 1;
}
void PaneCraftingScreen::buttonClicked(Button* a2) {
	uint32_t v4; // r6
	if(a2 == &this->craftButton) {
		this->craftSelectedItem();
	}
	if(a2 == &this->closeButton) {
		this->closeScreen();
	}
	v4 = a2->buttonID - 100;
	if(v4 <= 0x63) {
		std::vector<CItem*>* v5 = &this->field_6C[v4];
		if(v5->begin() != v5->end()) {
			this->onItemSelected(a2->buttonID - 100, v5->at(0));
			this->scrollingPane->setSelected(0, 1);
		}
		this->field_78 = v4;
		this->field_1B0 = a2;
		this->_resortRecipes();
	}
}
void PaneCraftingScreen::onItemSelected(const ItemPane* a2, int32_t a3) {
	if(this->field_78 < this->field_6C.size()) {
		if(a3 < this->field_6C[this->field_78].size()) {
			this->onItemSelected(this->field_78, this->field_6C[this->field_78][a3]);
		}
	}
}
std::vector<CItem*>* PaneCraftingScreen::getItems(const ItemPane* a2) {
	return &this->field_6C[this->field_78];
}
void PaneCraftingScreen::filterRecipes(std::vector<Recipe*>& a2) {
	int32_t v5 = a2.size() - 1;
	while(v5 >= 0) { //TODO check does it work
		if(!this->filterRecipe(*a2[v5])) {
			a2.erase(a2.begin()+v5);
		}
		--v5;
	}
}
