#include <gui/screens/ChestScreen.hpp>
#include <FlyingItem.hpp>
#include <ItemDiffer.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <gui/NinePatchFactory.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/pane/Touch_InventoryPane.hpp>
#include <inventory/BaseContainerMenu.hpp>
#include <inventory/ChestMenu.hpp>
#include <inventory/Inventory.hpp>
#include <level/Level.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/ContainerSetSlotPacket.hpp>
#include <perf/StopwatchNLast.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <tile/entity/ChestTileEntity.hpp>
#include <utils.h>

ChestScreen::ChestScreen(Player* a2, ChestTileEntity* a3)
	: field_60(4, "")
	, field_D0(5, "Inventory")
	, field_104(6, a3->pair ? "Large Chest" : "Chest") {
	this->field_50 = new ChestMenu(a3);
	this->field_138 = 0;
	this->field_140.width = 1;
	this->field_140.height = 1;
	this->field_13C = 0;
	this->field_140.minX = 0;
	this->field_140.minY = 0;
	this->needsSetup = 0;
	this->field_16C = -1;
	this->field_170 = 0;
	this->field_174 = 0;
	this->field_178 = 0;
	this->field_17C = 0;
	this->player = a2;
	this->tileEntity = a3;
	this->field_18C = 0;
}
void ChestScreen::drawSlotItemAt(Tesselator& a2, const ItemInstance* a3, int32_t a4, int32_t a5, bool_t a6) {
	float v6;  // s17
	float v10; // s16

	v6 = (float)a4;
	v10 = (float)a5;
	this->field_174->draw(a2, (float)a4, (float)a5);
	if(a6) {
		this->field_17C->draw(a2, v6 - 2.0, v10 - 2.0);
	}
	if(a3) {
		if(!a3->isNull()) {
			ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, a3, 0, v6 + 7.0, v10 + 8.0, 1.0, 1.0, 1.0);
			this->minecraft->gui.renderSlotText(a3, v6 + 3.0, v10 + 3.0, 1, 1);
		}
	}
}
static int32_t _D67AD154 = -1;
static int32_t _D67AD158 = -1;
bool_t ChestScreen::handleAddItem(FillingContainer* a2, FillingContainer* a3, int32_t a4) {
	int v29 = a4 + a2->getLinkedSlotsCount();
	ItemInstance* v7 = a2->getItem(v29);
	FillingContainer* te;
	if(this->tileEntity) {
		te = this->tileEntity;
	} else {
		te = 0;
	}
	Touch::InventoryPane* v10 = this->field_138;
	Touch::InventoryPane* v12;
	if(a2 == te) {
		v12 = this->field_13C;
	} else {
		v12 = this->field_138;
		v10 = this->field_13C;
	}

	if(!v7) {
		v10->field_254 = v12->field_254 = -1;
		return 0;
	}
	int v13;
	if(v7->isNull()) {
		v13 = 0;
	} else {
		v13 = _D67AD158 * v7->count / 100;
	}
	if(v7->isNull() || v13 && _D67AD154 > 199) {
		if(v13 <= 0) {
			v10->field_254 = v12->field_254 = -1;
			return 0;
		}
	} else {
		v13 = 1;
	}
	ItemInstance v34(*v7);
	v34.count = v13;
	ItemDiffer idiff(this->getItems(v10));
	a3->add(&v34);
	bool v28 = v34.count != v13;
	if(v34.count != v13) {
		v7->count += v34.count - v13;
		std::vector<int> vec;
		std::vector<const ItemInstance*> vec2 = this->getItems(v10);
		idiff.getDiff(vec2, vec);
		ScrollingPane::GridItem v36;
		v12->getGridItemFor_slow(a4, v36);

		for(int v15 = 0; v15 < vec.size(); ++v15) {
			FlyingItem v39;
			v39.field_18 = getTimeS();
			v39.field_0 = *v7;
			v39.field_20 = v36.field_C;
			v39.field_24 = v36.field_10;
			ScrollingPane::GridItem v37;
			v10->getGridItemFor_slow(vec[v15], v37);
			v39.field_30 = v10;
			v39.field_28 = v37.field_C;
			v39.field_2C = v37.field_10;
			this->field_190.push_back(v39);
			if(!(a2 == te) && this->minecraft->level->isClientMaybe) {
				const ItemInstance* v23 = vec2[vec[v15]];
				ContainerSetSlotPacket v38(0, this->field_50->field_0, vec[v15], v23 ? ItemInstance(*v23) : ItemInstance());
				this->minecraft->rakNetInstance->send(v38);
			}
		}
		v12->refreshItems();
	}

	if(a2 == te) {
		ContainerSetSlotPacket v39(0, this->field_50->field_0, v29, v7->count > 0 ? ItemInstance(*v7) : ItemInstance());
		this->minecraft->rakNetInstance->send(v39);
	}
	if(v7->count <= 0) {
		a2->clearSlot(v29);
	}
	if(idiff.items) {
		delete[] idiff.items;
	}
	v10->field_254 = -1;
	v12->field_254 = -1;
	return v28;
}
void ChestScreen::handleRenderPane(Touch::InventoryPane* a2, Tesselator& a3, int32_t a4, int32_t a5, float a6) {
	if(a2) {
		a2->field_254 = -1;
		int32_t v25, v24;
		if(a2->queryHoldTime(&v25, &v24)) {
			_D67AD154 = v24;
			FillingContainer* inventory;
			if(a2 == this->field_138) {
				inventory = this->minecraft->player->inventory;
			} else {
				inventory = this->tileEntity ? this->tileEntity : 0;
			}

			ItemInstance* v13 = inventory->getItem(v25 + inventory->getLinkedSlotsCount());
			if(v13) {
				int32_t cnt = v13->isNull() ? 0 : v13->count;
				if(cnt > 1) {
					int32_t v20 = _D67AD154;
					a2->field_254 = v25;
					a2->field_250 = 1;
					float v18 = (float)(10 * v13->count + 700);
					float v21 = (float)(v20 - 200) / v18;
					float v22;
					if(v21 >= 0.0) {
						v22 = (float)(v20 - 200) / v18;
					} else {
						v22 = 0.0;
					}
					a2->field_258 = v22;
					float v23 = v21 * 100.0;
					if(v23 > 100.0) {
						v23 = 100.0;
					} else if(v23 <= 0.0) {
						v23 = 0.0;
					}
					_D67AD158 = (int)v23;
					if((int)v23 > 99) {
						this->addItem(a2, v25);
					}
				}
			}
		}
		a2->render(a4, a5, a6);
		this->field_180->draw(a3, (float)(a2->field_228.minX - 1), (float)(a2->field_228.minY - 1));
	}
}
void ChestScreen::setupPane() {
	this->field_150.clear();
	for(int32_t v2 = 9; v2 < this->minecraft->player->inventory->getContainerSize(); ++v2) {
		this->field_150.emplace_back(this->minecraft->player->inventory->getItem(v2));
	}
	this->field_15C.clear();
	for(int32_t v7 = 0; v7 < this->tileEntity->getContainerSize(); ++v7) {
		this->field_15C.emplace_back(this->tileEntity->getItem(v7));
	}
	if(this->field_138) {
		delete this->field_138;
	}
	int32_t width = this->width;
	int32_t v11 = width / 2;
	int32_t v12 = width / 2 - 5;
	if(v12 < 0) {
		v12 = v11 + 26;
	}
	int32_t a5 = v12 & 0xFFFFFFE0;
	IntRectangle v26 = {(v11 - a5) / 2, 30, a5, this->height - 36};
	this->field_138 = new Touch::InventoryPane(this, this->minecraft, v26, a5, 4, this->minecraft->player->inventory->getContainerSize() - 9, 32, 4, 1);
	this->field_138->field_248 = 0;
	this->field_138->field_24C = 0;
	this->field_180->setSize((float)a5 + 2.0f, (float)v26.height + 2.0f);

	if(this->field_13C) {
		delete this->field_13C;
	}
	int32_t minY = v26.minY;
	int32_t v19 = v26.width;
	height = v26.height;
	this->field_140.minX = v26.minX;
	this->field_140.minY = minY;
	this->field_140.width = v19;
	this->field_140.height = height;
	int32_t v22 = this->width / 2;
	v26.minX += v22;
	this->field_140.width += v22;
	this->field_13C = new Touch::InventoryPane(this, this->minecraft, v26, a5, 4, this->tileEntity->getContainerSize(), 32, 4, 1);
	this->field_13C->field_248 = 0;
	this->field_13C->field_24C = 0;
}

ChestScreen::~ChestScreen() {
	if(this->field_138) delete this->field_138;
	if(this->field_13C) delete this->field_13C;
	if(this->field_170) delete this->field_170;
	if(this->field_174) delete this->field_174;
	if(this->field_178) delete this->field_178;
	if(this->field_17C) delete this->field_17C;
	if(this->field_180) delete this->field_180;
	if(this->field_50) delete this->field_50;
	if(this->tileEntity->field_34) delete this->tileEntity;
}
void ChestScreen::render(int32_t a2, int32_t a3, float a4) {
	static StopwatchNLast _sw(5);
	this->field_170->draw(Tesselator::instance, 0, 0);
	Screen::render(a2, a3, a4);
	_D67AD154 = -1;
	this->handleRenderPane(this->field_138, Tesselator::instance, a2, a3, a4);
	this->handleRenderPane(this->field_13C, Tesselator::instance, a2, a3, a4);
	std::vector<FlyingItem> v16;
	glEnable(0xC11u);
	double timeS = getTimeS();
	Tesselator::instance.begin(0);
	Tesselator::instance.voidBeginAndEndCalls(1);
	this->minecraft->gui.setScissorRect(this->field_140);

	for(int32_t v9 = 0; v9 < this->field_190.size(); ++v9) {
		FlyingItem* v11 = &this->field_190[v9];
		float v12 = timeS - v11->field_18;
		if(v12 <= 0.3) {
			ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, &v11->field_0, 0, (float)(v11->field_20 + (float)((float)(v11->field_28 - v11->field_20) * (float)((float)(v12 / 0.3) * (float)(v12 / 0.3)))) + 7.0, (float)(v11->field_24 + (float)((float)(v11->field_2C - v11->field_24) * (float)((float)(v12 / 0.3) * (float)(v12 / 0.3)))) + 8.0, 1.0, 1.0, 1.0);
			v16.push_back(*v11);
		} else {
			v11->field_30->refreshItems();
		}
	}
	Tesselator::instance.voidBeginAndEndCalls(0);
	Tesselator::instance.draw(1);
	glDisable(0xC11u);
	this->field_190 = v16;
	Tesselator::instance.colorABGR(-1);
	this->minecraft->texturesPtr->loadAndBindTexture("gui/spritesheet.png");
}
void ChestScreen::init() {
	ImageDef a2;
	a2.field_0 = "gui/spritesheet.png";
	a2.field_4 = 0;
	a2.height = 18.0;
	a2.width = 18.0;
	a2.field_18 = 0;
	a2.field_14 = 60;
	a2.field_8 = 1;
	a2.field_1C = 18;
	a2.field_20 = 18;
	a2.field_24 = 1;
	this->field_60.setImageDef(a2, 1);
	this->field_60.field_64 = 0;
	this->buttons.emplace_back(&this->field_D0);
	this->buttons.emplace_back(&this->field_104);
	this->buttons.emplace_back(&this->field_60);
	NinePatchFactory a1(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_170 = a1.createSymmetrical({0, 0, 16, 16}, 4, 4, 32, 32);
	this->field_174 = a1.createSymmetrical({0, 32, 8, 8}, 3, 3, 32, 32);
	this->field_178 = a1.createSymmetrical({0, 44, 8, 8}, 3, 3, 32, 32);
	this->field_17C = a1.createSymmetrical({10, 42, 16, 16}, 5, 5, 32, 32);
	this->field_180 = a1.createSymmetrical({28, 42, 4, 4}, 1, 1, 32, 32)->exclude(4);
	this->field_18C = 1;
}
void ChestScreen::setupPositions() {
	int32_t width; // r1

	width = this->width;
	this->field_D0.posX = 0;
	this->field_104.posY = 0;
	this->field_D0.posY = 0;
	this->field_60.posY = 0;
	this->field_104.width = width / 2;
	this->field_D0.width = width / 2;
	this->field_104.posX = width / 2;
	this->field_60.height = 19;
	this->field_60.width = 19;
	this->field_60.posX = width - 19;
	this->field_170->setSize((float)width, (float)this->height);
	this->setupPane();
}
void ChestScreen::tick() {
	if(this->field_138) this->field_138->tick();
	if(this->field_13C) this->field_13C->tick();
	if(this->needsSetup) {
		this->setupPane();
		this->needsSetup = 0;
	}
}
bool_t ChestScreen::renderGameBehind() {
	return 0;
}
void ChestScreen::onInternetUpdate() {
	this->field_13C->refreshItems();
}
void ChestScreen::buttonClicked(Button* a2) {
	if(&this->field_60 == a2) {
		this->minecraft->player->closeContainer();
	}
}
bool_t ChestScreen::addItem(const Touch::InventoryPane* a2, int32_t a3) {
	if(this->field_138 == a2) {
		if(this->tileEntity) {
			return this->handleAddItem(this->minecraft->player->inventory, this->tileEntity, a3);
		}
		return this->handleAddItem(this->minecraft->player->inventory, this->tileEntity, a3);
	} else {
		if(this->tileEntity) {
			return this->handleAddItem(this->tileEntity, this->minecraft->player->inventory, a3);
		} else {
			return this->handleAddItem(0, this->minecraft->player->inventory, a3);
		}
	}
	return 0;
}
bool_t ChestScreen::isAllowed(int32_t) {
	return 1;
}
std::vector<const ItemInstance*> ChestScreen::getItems(const Touch::InventoryPane* a3) {
	if(this->field_138 == a3) {
		for(int32_t i = 9;; ++i) {
			if(i >= this->minecraft->player->inventory->getContainerSize()) break;
			//TODO check
			this->field_150[i-9] = this->minecraft->player->inventory->getItem(i);
		}
		return std::vector<const ItemInstance*>(this->field_150);
	} else {
		for(int32_t j = 0; j < this->tileEntity->getContainerSize(); ++j) {
			this->field_15C[j] = this->tileEntity->getItem(j);
		}
		return std::vector<const ItemInstance*>(this->field_15C);
	}
}
