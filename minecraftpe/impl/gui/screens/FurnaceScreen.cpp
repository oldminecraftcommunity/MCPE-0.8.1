#include <gui/screens/FurnaceScreen.hpp>
#include <Minecraft.hpp>
#include <crafting/CItem.hpp>
#include <crafting/FurnaceRecipes.hpp>
#include <entity/LocalPlayer.hpp>
#include <gui/NinePatchFactory.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/pane/Touch_InventoryPane.hpp>
#include <inventory/BaseContainerMenu.hpp>
#include <inventory/Inventory.hpp>
#include <level/Level.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/ContainerSetSlotPacket.hpp>
#include <perf/StopwatchNLast.hpp>
#include <rendering/Font.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <tile/entity/FurnaceTileEntity.hpp>
#include <crafting/ItemPack.hpp>
#include <I18n.hpp>
#include <inventory/FurnaceMenu.hpp>

FurnaceScreen::FurnaceScreen(Player* a2, FurnaceTileEntity* a3): field_84(4, ""), field_F4(0), field_124(1), field_154(2), field_184(5, "Furnace") {
	this->field_50 = new FurnaceMenu(a3);
	this->field_80 = 90.0;
	this->field_1B8 = 0;
	this->field_1BC.minX = 0;
	this->field_1BC.minY = 0;
	this->field_1BC.width = 1;
	this->field_1BC.height = 1;
	this->field_1FC = 0;
	this->field_200 = 0;
	this->resultIdMaybe = 0;
	this->field_208 = 0;
	this->field_20C = 0;
	this->field_210 = 0;
	this->field_214 = 0;
	this->field_218 = 0;
	this->player = a2;
	this->tileEntity = a3;
	this->field_224 = 0;
}
bool_t FurnaceScreen::canMoveToFurnace(int32_t a2, const ItemInstance* a3) {
	ItemInstance* v6; // r0
	ItemInstance* v7; // r4
	int32_t count;	  // r5

	if(this->isAllowed(a2)) {
		v6 = (ItemInstance*)this->tileEntity->getItem(this->field_200);
		v7 = v6;
		if(v6) {
			if(!v6->isNull()) {
				if(!ItemInstance::isStackable(a3, v7)) {
					return 0;
				}
				count = v7->count;
				if(count >= v7->getMaxStackSize()) {
					return 0;
				}
			}
		}
		return 1;
	}
	return 0;
}
void FurnaceScreen::clearItems() {
	for(int32_t i = 0; i < this->field_1CC.size(); ++i) {
		if(this->field_1CC[i]) {
			delete this->field_1CC[i];
		}
	}

	for(int32_t j = 0; j < this->field_1D8.size(); ++j) {
		if(this->field_1D8[j]) {
			delete this->field_1D8[j];
		}
	}

	this->field_1D8.clear();
	this->field_1CC.clear();
}
void FurnaceScreen::drawSlotItemAt(Tesselator& a2, const ItemInstance* a3, int32_t a4, int32_t a5, bool_t a6) {
	float v6;  // s17
	float v10; // s16

	v6 = (float)a4;
	v10 = (float)a5;
	this->field_20C->draw(a2, (float)a4, (float)a5);
	if(a6) {
		this->field_214->draw(a2, v6 - 2.0, v10 - 2.0);
	}
	if(a3) {
		if(!a3->isNull()) {
			ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, a3, 0, v6 + 7.0, v10 + 8.0, 1.0, 1.0, 1.0);
			this->minecraft->gui.renderSlotText(a3, v6 + 3.0, v10 + 3.0, 1, 1);
		}
	}
}
bool_t FurnaceScreen::handleAddItem(int32_t a2, const ItemInstance* a3) {
	ItemInstance* v6 = this->tileEntity->getItem(a2);
	int32_t esc = this->minecraft->player->inventory->getEmptySlotsCount();
	Item* itemClass;
	if(v6 && (itemClass = a3->itemClass, itemClass == v6->itemClass) && itemClass) {
		int32_t v12 = v6->getMaxStackSize() - v6->count;
		if(v12 <= 0) {
			return 0;
		}
		ItemInstance v14 = this->moveOver(a3, v12);
		v6->count += v14.count;
	} else {
		if(!this->tileEntity->isSlotEmpty(a2)) {
			return 1;
		}
		int32_t maxss = a3->getMaxStackSize();
		ItemInstance v14 = this->moveOver(a3, maxss);
		this->player->currentContainer->setSlot(a2, &v14);
	}

	if(this->minecraft->level->isClientMaybe) {
		ContainerSetSlotPacket v14(0, this->field_50->field_0, a2, *v6);
		this->minecraft->rakNetInstance->send(v14);
	}
	return this->player->inventory->getEmptySlotsCount() != esc;
}
static int32_t _D67AD15C = -1;
static int32_t _D67AD160 = -1;
void FurnaceScreen::handleRenderPane(Touch::InventoryPane* a2, Tesselator& a3, int32_t a4, int32_t a5, float a6) {
	int32_t v21, v22;
	if(a2) {
		a2->field_254 = -1;
		if(a2->queryHoldTime(&v22, &v21)) {
			_D67AD15C = v21;
			const ItemInstance* v11 = this->field_1F0[v22];
			if(v11) {
				int32_t count = v11->count;
				int32_t v14;
				if(v11->isNull()) v14 = 0;
				else v14 = v11->count;

				if(v14 > 1) {
					if(this->canMoveToFurnace(v22, v11)) {
						int32_t v16 = v22;
						float v17 = (float)(_D67AD15C - 200);
						a2->field_254 = v22;
						a2->field_250 = 1;
						int32_t v18 = 10 * count + 700;
						float v19 = v17 / (float)v18;
						float v20;
						if(v19 >= 0.0) {
							v20 = v17 / (float)v18;
						} else {
							v20 = 0.0;
						}
						a2->field_258 = v20;
						float v15 = v19 * 100.0;
						if(v15 > 100.0) {
							v15 = 100.0;
						} else if(v15 <= 0.0) {
							v15 = 0.0;
						}
						_D67AD160 = (int)v15;
						if((int)v15 > 99) {
							this->addItem(a2, v16);
						}
					}
				}
			}
		}
		a2->render(a4, a5, a6);
		this->field_218->draw(a3, (float)(a2->field_228.minX - 1), (float)(a2->field_228.minY - 1));
	}
}
ItemInstance FurnaceScreen::moveOver(const ItemInstance* a3, int32_t a4) {
	int32_t v6 = a3->count * _D67AD160 / 100;
	if(v6) {
		if(_D67AD15C <= 199) {
			v6 = 1;
		}
	} else {
		v6 = 1;
	}

	int32_t v7;
	if(v6 >= a4) {
		v7 = a4;
	} else {
		v7 = v6;
	}
	int32_t auxv = a3->getAuxValue();
	ItemInstance v13(a3->itemClass, v7, auxv);
	int32_t esc = this->minecraft->player->inventory->getEmptySlotsCount();
	if(this->minecraft->player->inventory->removeResource(v13)) {
		int32_t esc2 = this->minecraft->player->inventory->getEmptySlotsCount();
		this->field_1FC = this->field_1FC || (esc2 != esc);
		return ItemInstance(v13);
	}
	return ItemInstance();
}
void FurnaceScreen::recheckRecipes() {
	this->clearItems();
	Stopwatch sw;
	sw.start();
	FurnaceRecipes* instance = FurnaceRecipes::getInstance();
	ItemPack v13;
	if(this->minecraft->player) {
		if(this->minecraft->player->inventory) {
			for(int32_t i = 9; i < this->minecraft->player->inventory->getContainerSize(); ++i) {
				ItemInstance* v5 = this->minecraft->player->inventory->getItem(i);
				if(v5) {
					if(FurnaceTileEntity::isFuel(*v5)) {
						this->field_1CC.push_back(new CItem(*v5, 0, ""));
					}
					int32_t id = v5->getId();
					if(instance->isFurnaceItem(id)) {
						this->field_1D8.push_back(new CItem(*v5, 0, ""));
					}
				}
			}
		}
	}
	v13.print();
	sw.stop();
	sw.printEvery(1, "> craft ");
	this->updateItems();
}
void FurnaceScreen::setupInventoryPane() {
	int32_t v3;				  // r6
	Touch::InventoryPane* v4; // r5

	if(this->field_1B8) {
		delete this->field_1B8;
	}
	v3 = this->field_1F0.size();
	v4 = new Touch::InventoryPane(this, this->minecraft, this->field_1BC, this->field_1BC.width, 4.0, v3, 32, 4, 1);
	this->field_1B8 = v4;
	v4->field_248 = 0;
	this->field_1B8->field_24C = 0;
	this->field_218->setSize((float)this->field_1BC.width + 2.0, (float)this->field_1BC.height + 2.0);
}
void FurnaceScreen::takeAndClearSlot(int32_t a2) {
	ItemInstance v10(*this->tileEntity->getItem(a2));
	ItemInstance v11;
	this->tileEntity->setItem(a2, &v11);
	if(this->minecraft->level->isClientMaybe) {
		ContainerSetSlotPacket v12(0, this->field_50->field_0, a2, v11);
		this->minecraft->rakNetInstance->send(v12);
	}
	int32_t esc = this->minecraft->player->inventory->getEmptySlotsCount();
	if(!this->minecraft->player->inventory->add(&v10)) {
		this->minecraft->player->drop(&v10, 0);
	}
	int32_t esc2 = this->minecraft->player->inventory->getEmptySlotsCount();
	this->field_1FC = this->field_1FC || (esc2 != esc);
}
void FurnaceScreen::updateItems() {
	this->field_1F0.clear();
	this->field_1E4.clear();
	std::vector<CItem*> v18;
	v18.assign(this->field_1CC.begin(), this->field_1CC.end());
	v18.insert(v18.end(), this->field_1D8.begin(), this->field_1D8.end());

	for(int i = 9; i < this->minecraft->player->inventory->getContainerSize(); ++i) {
		ItemInstance* v9 = this->minecraft->player->inventory->getItem(i);
		if(v9) {
			for(int j = 0; j < this->field_1CC.size(); ++j) {
				if(v9->matches(&this->field_1CC[j]->field_0)) {
					this->field_1E4.push_back(i);
					this->field_1F0.emplace_back(v9);
					goto LABEL_16;
				}
			}
			for(int k = 0; k < this->field_1D8.size(); ++k){
				if(v9->matches(&this->field_1D8[k]->field_0)) {
					this->field_1E4.push_back(i);
					this->field_1F0.emplace_back(v9);
					goto LABEL_16;
				}
			}
		}
LABEL_16:;
	}
}
void FurnaceScreen::updateResult(const ItemInstance* a2) {
	ItemInstance* v4 = this->tileEntity->getItem(2);
	if(v4->isNull()) {
		int32_t id = v4->getId();
		if(id == this->resultIdMaybe) return;
		this->field_68 = I18n::getDescriptionString(*v4);
		this->resultIdMaybe = id;
		this->field_6C = *v4;
		return;
	}
	int32_t id = a2 ? a2->getId() : 0;
	if(id != this->resultIdMaybe) {
		ItemInstance v16 = FurnaceRecipes::getInstance()->getResult(id);
		if(v16.isNull()) {
			this->field_68 = "";
		} else {
			this->field_68 = I18n::getDescriptionString(v16);
		}
		this->resultIdMaybe = id;
		this->field_6C = v16;
	}
}

FurnaceScreen::~FurnaceScreen() {
	if(this->field_1B8) delete this->field_1B8;
	if(this->field_208) delete this->field_208;
	if(this->field_20C) delete this->field_20C;
	if(this->field_210) delete this->field_210;
	if(this->field_214) delete this->field_214;
	if(this->field_218) delete this->field_218;
	if(this->field_50) delete this->field_50;
	if(this->tileEntity->field_34) delete this->tileEntity;
}
void FurnaceScreen::render(int32_t a2, int32_t a3, float a4) {
	StopwatchNLast _swlast(5);
	this->updateResult(this->tileEntity->getItem(0));
	this->field_208->draw(Tesselator::instance, 0, 0);
	Screen::render(a2, a3, a4);
	glDepthMask(0);
	this->handleRenderPane(this->field_1B8, Tesselator::instance, a2, a3, a4);
	glDepthMask(1u);
	this->drawSlotItemAt(Tesselator::instance, this->tileEntity->getItem(this->field_F4.buttonID), this->field_F4.posX, this->field_F4.posY, this->field_F4.buttonID == this->field_200);
	this->drawSlotItemAt(Tesselator::instance, this->tileEntity->getItem(this->field_124.buttonID), this->field_124.posX, this->field_124.posY, this->field_124.buttonID == this->field_200);
	ItemInstance* v11 = this->tileEntity->getItem(this->field_154.buttonID);
	this->drawSlotItemAt(Tesselator::instance, v11, this->field_154.posX, this->field_154.posY, this->field_154.buttonID == this->field_200);
	if(!this->field_6C.isNull()) {
		if(!v11 || v11->isNull()) {
			ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, &this->field_6C, 0, (float)this->field_154.posX + 7.0, (float)this->field_154.posY + 8.0, 1.0, 0.5, 1.0);
		}
		this->minecraft->font->drawWordWrap(this->field_68, (float)this->field_154.posX - 24.0, (float)(this->field_154.posY + this->field_154.height + 6), this->field_80, -986896, 1, 0);
	}
	this->minecraft->texturesPtr->loadAndBindTexture("gui/spritesheet.png");
	int posY = this->field_154.posY;
	int v15 = this->field_F4.posX + 8;
	int v16 = this->tileEntity->getLitProgress(14) + 2;
	this->blit(v15, posY + 8, 80, 40, 16, 16, 32, 32);
	this->blit(v15, posY + 24 - v16, 112, 72 - 2 * v16, 16, v16, 32, 2 * v16);
	int v18 = this->field_F4.posX + 40;
	int v19 = this->tileEntity->getBurnProgress(24);
	this->blit(v18, posY + 8, 144, 40, 24, 16, 48, 32);
	this->blit(v18, posY + 8, 144, 72, v19, 16, 2 * v19, 32);
}
void FurnaceScreen::init() {
	BaseContainerScreen::init();
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
	this->field_84.setImageDef(a2, 1);
	this->field_84.field_64 = 0;
	this->buttons.emplace_back(&this->field_184);
	this->buttons.emplace_back(&this->field_F4);
	this->buttons.emplace_back(&this->field_124);
	this->buttons.emplace_back(&this->field_154);
	this->buttons.emplace_back(&this->field_84);
	NinePatchFactory a1(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_208 = a1.createSymmetrical({0, 0, 16, 16}, 4, 4, 32, 32);
	this->field_20C = a1.createSymmetrical({0, 32, 8, 8}, 3, 3, 32, 32);
	this->field_210 = a1.createSymmetrical({0, 44, 8, 8}, 3, 3, 32, 32);
	this->field_214 = a1.createSymmetrical({10, 42, 16, 16}, 5, 5, 32, 32);
	this->field_218 = a1.createSymmetrical({28, 42, 4, 4}, 1, 1, 32, 32)->setExcluded(16);
	this->recheckRecipes();
	this->field_224 = 1;
}
void FurnaceScreen::setupPositions(){
	int width; // r5
	int height; // lr
	int v4; // r7
	int v5; // r2
	int v6; // r7
	int width2; // r1
	int height2; // r3
	int v10; // r0
	int v11; // r7
	int v12; // r1
	int v13; // r0

	width = this->width;
	this->field_184.posY = 0;
	this->field_184.posX = 0;
	this->field_84.posY = 0;
	height = this->height;
	this->field_184.width = width;
	v4 = width / 2 - 20;
	this->field_84.height = 19;
	if ( v4 < 0 )
	{
		v4 = width / 2 + 11;
	}
	this->field_84.width = 19;
	this->field_84.posX = width - 19;
	v5 = v4 & 0xFFFFFFE0;
	v6 = (v4 & 0xFFFFFFE0) + 10;
	this->field_1BC.minX = 10;
	this->field_1BC.minY = 32;
	this->field_1BC.width = v5;
	this->field_1BC.height = height - 40;
	width2 = (int)this->field_20C->width2;
	this->field_154.width = width2;
	this->field_124.width = width2;
	this->field_F4.width = width2;
	height2 = (int)this->field_20C->height2;
	this->field_154.height = height2;
	this->field_124.height = height2;
	this->field_F4.height = height2;
	v10 = (width - v6 + 2 * (-20 - width2)) / 2;
	v11 = v6 + v10;
	v12 = width - v10 - width2;
	this->field_124.posX = v11;
	this->field_F4.posX = v11;
	v13 = width - v12 + 20;
	if ( v13 >= 90 )
	{
		v13 = 90;
	}
	this->field_80 = (float)v13;
	this->field_F4.posY = 36;
	this->field_124.posY = height2 + 56;
	this->field_154.posX = v12;
	this->field_154.posY = (height2 + 92) / 2;
	this->field_208->setSize((float)width, (float)height);
	this->field_214->setSize(
		(float)this->field_124.width + 4.0,
		(float)this->field_124.height + 4.0);
	this->recheckRecipes();
	this->setupInventoryPane();
}
void FurnaceScreen::tick() {
	if(this->field_1B8) this->field_1B8->tick();
	if(this->field_1FC) {
		this->recheckRecipes();
		this->setupInventoryPane();
		this->field_1FC = 0;
	}
}
bool_t FurnaceScreen::renderGameBehind() {
	return 0;
}
void FurnaceScreen::buttonClicked(Button* a2) {
	int32_t buttonID;		  // r5
	int32_t v4;				  // r6
	Touch::InventoryPane* v5; // r0
	Touch::InventoryPane* v6; // r0

	buttonID = a2->buttonID;
	if(a2 == (Button*)&this->field_84) {
		this->minecraft->player->closeContainer();
	}
	if((uint32_t)buttonID <= 2) {
		v4 = this->field_200;
		if(buttonID != 2) {
			v5 = this->field_1B8;
			this->field_200 = buttonID;
			if(v5) {
				v5->refreshItems();
			}
		}
		if(v4 == this->field_200) {
			this->takeAndClearSlot(buttonID);
			v6 = this->field_1B8;
			if(v6) {
				v6->refreshItems();
			}
		}
	}
}
bool_t FurnaceScreen::addItem(const Touch::InventoryPane* a2, int32_t a3) {
	if(!this->field_1F0[a3]) {
		return 0;
	}
	if(this->field_1F0[a3]->isNull()) return 0;
	bool_t v11 = this->handleAddItem(this->field_200, this->field_1F0[a3]);
	if(this->field_1FC) {
		v11 = 1;
	}
	this->field_1FC = v11;
	if(v11) {
		if(this->player->inventory->getItem(this->field_1E4[a3])) {
			for(int32_t i = 0; i < this->field_1E4.size(); ++i) {
				if(!this->player->inventory->getItem(i)) {
					a3 = i;
					break;
				}
				++a3;
			}
		}
		this->field_1F0[a3] = 0;
	}
	return 1;
}
bool_t FurnaceScreen::isAllowed(int32_t a2) {
	ItemInstance* v3; // r4
	int32_t v4;		  // r2
	if(a2 < this->field_1F0.size()) {
		v3 = (ItemInstance*)this->field_1F0[a2];
		if(!v3) {
			return 0;
		}
		v4 = this->field_200;
		if(v4 == this->field_124.buttonID) {
			return FurnaceTileEntity::getBurnDuration(*v3) > 0;
		}
		if(v4 == this->field_F4.buttonID) {
			ItemInstance v8 = FurnaceRecipes::getInstance()->getResult(v3->getId());
			return !v8.isNull();
		}
	}
	return 0;
}
std::vector<const ItemInstance*> FurnaceScreen::getItems(const Touch::InventoryPane* a2) {
	return std::vector<const ItemInstance*>(this->field_1F0); //TODO check
}
