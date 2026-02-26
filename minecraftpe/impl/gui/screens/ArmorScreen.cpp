#include <gui/screens/ArmorScreen.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <gui/NinePatchLayer.hpp>
#include <gui/pane/Touch_InventoryPane.hpp>
#include <inventory/Inventory.hpp>
#include <item/ArmorItem.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <rendering/entity/MobRenderer.hpp>
#include <utils.h>
#include <gui/NinePatchFactory.hpp>

ArmorScreen::ArmorScreen()
	: Screen()
	, backButton(4, "Back", 0)
	, field_B8(0)
	, field_E8(1)
	, field_118(2)
	, field_148(3)
	, header(5, "Armor") {
	this->field_58 = 0;
	this->field_5C = 0;
	this->field_60 = 0;
	this->field_64 = "";
	this->field_7C = 90.0;
	this->field_1BC = 0;
	this->field_1C0.minX = 0;
	this->field_1C0.minY = 0;
	this->field_1C0.width = 1;
	this->field_1C0.height = 1;
	this->field_1D0 = 0;
	this->field_1D4 = 0;
	this->field_1D8 = 1;
	this->field_1DC = 1;
	this->performUpdate = 0;
	this->field_1F0 = 0;
	this->field_1F4 = 0;
	this->field_1F8 = 0;
	this->field_1FC = 0;
}
bool_t ArmorScreen::canMoveToSlot(int32_t a2, const ItemInstance* a3) {
	if(ItemInstance::isArmorItem(a3)) {
		ArmorItem* it = (ArmorItem*)a3->itemClass; //TODO uses a3->field_48
		return it->field_48 == a2;
	}
	return 0;
}
void ArmorScreen::closeScreen() {
	this->minecraft->screenChooser.setScreen(INVENTORY_SCREEN);
}
void ArmorScreen::drawSlotItemAt(Tesselator& a2, int32_t a3, const ItemInstance* a4, int32_t a5, int32_t a6) {
	float v6;			   // s17
	float v10;			   // s16
	Textures* texturesPtr; // r4

	v6 = (float)a5;
	v10 = (float)a6;
	this->field_1F4->draw(a2, (float)a5, (float)a6);
	if(a4 && !a4->isNull()) {
		ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, a4, 0, v6 + 3.0, v10, 1.0, 1.0, 1.0);
		glDisable(0xDE1u);
		ItemRenderer::renderGuiItemDecorations(a4, v6 + 2.0, v10 + 3.0);
		glEnable(0xDE1u);
	} else {
		this->minecraft->texturesPtr->loadAndBindTexture("items-opaque.png");
		this->blit(a5 + 2, a6, 240, 16 * a3, 16, 16, 16, 16);
	}
}
void ArmorScreen::handleRenderPane(Touch::InventoryPane* a2, Tesselator& a3, int32_t a4, int32_t a5, float a6) {
	if(a2) {
		a2->render(a4, a5, a6);
		this->field_1F8->draw(a3, (float)(a2->field_228.minX - 1), (float)(a2->field_228.minY - 1));
	}
}
void ArmorScreen::renderPlayer(float a2, float a3) {
	bool_t graphics;				  // r3
	GLenum state;					  // r3
	GLenum v10;						  // r3
	LocalPlayer* player;			  // r4
	float v12;						  // s20
	float yaw;						  // r11
	float pitch;					  // r10
	float headYaw;					  // r9
	float TimeS;					  // s15
	float v17;						  // s16
	float v18;						  // s19
	float v19;						  // s16
	float v20;						  // s16
	float v21;						  // s18
	GLfloat v22;					  // s18
	float v23;						  // s16
	GLfloat ridingHeight;			  // r1
	float v25;						  // s18
	float v26;						  // s16
	float v27;						  // s19
	EntityRenderDispatcher* Instance; // r0
	int32_t v33;					  // [sp+1Ch] [bp-5Ch] BYREF
	int32_t v34;					  // [sp+20h] [bp-58h] BYREF
	int32_t v35;					  // [sp+24h] [bp-54h] BYREF

	//TODO use rendering/states/

	glEnableClientState(0x8078u);
	glDisable(0xBE2u);
	glEnable(0xB71u);
	int32_t v32_state = 0;
	v33 = 0;
	graphics = this->minecraft->options.graphics;
	v34 = 0;
	v35 = 0;
	if(graphics) {
		glEnable(v33 = 0xB50u);
		glEnable(v34 = 0x4000u);
		glEnable(v35 = 0xBA1u);
		glEnableClientState(v32_state = 0x8075u);
		glLightfv(0x4000u, 0x1201u, &Color4::WHITE.r);
		float vals[] = {3.4f, 3.7f, 4.0f, 1.0f};
		glLightfv(0x4000u, 0x1200u, vals);
		vals[0] = -0.2;
		vals[1] = -0.7;
		vals[2] = 0.6;
		vals[3] = 0.0;
		glLightfv(0x4000u, 0x1203u, vals);
	} else {
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
	glPushMatrix();
	glTranslatef(a2, a3, -200.0);
	glScalef(-45.0, 45.0, 45.0);
	glRotatef(180.0, 0.0, 0.0, 1.0);
	player = this->minecraft->player;
	v12 = player->field_124;
	yaw = player->yaw;
	pitch = player->pitch;
	headYaw = player->headYaw;
	TimeS = getTimeS();
	v17 = Mth::sin(TimeS) * 10.0;
	v18 = Mth::cos((float)(TimeS * 0.05)) * 10.0;
	glRotatef(135.0, 0.0, 1.0, 0.0);
	glRotatef(-135.0, 0.0, 1.0, 0.0);
	v19 = atan((float)(v17 / 40.0));
	v20 = v19 * 20.0;
	v21 = atan((float)(v18 / 40.0));
	v22 = v21 * -20.0;
	glRotatef(v22, 1.0, 0.0, 0.0);
	player->field_124 = v20;
	v23 = v20 + v20;
	player->pitch = v22;
	ridingHeight = player->ridingHeight;
	player->yaw = v23;
	player->headYaw = v23;
	glTranslatef(0.0, ridingHeight, 0.0);
	v25 = player->field_16C;
	v26 = player->field_168;
	player->field_16C = 0.25;
	v27 = player->field_170;
	player->field_168 = 0.25;
	player->field_170 = (float)(getTimeS() * player->field_16C) * 20.0;
	Instance = EntityRenderDispatcher::getInstance();
	Instance->field_14 = 180.0;
	MobRenderer::menuMode = 1;
	Instance->render(player, 0.0, 0.0, 0.0, 0.0, 1.0);
	player->field_170 = v27;
	MobRenderer::menuMode = 0;
	player->field_16C = v25;
	player->field_168 = v26;
	player->field_124 = v12;
	player->yaw = yaw;
	player->pitch = pitch;
	player->headYaw = headYaw;
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glPopMatrix();
	if(v35) glDisable(v35);
	if(v34) glDisable(v34);
	if(v33) glDisable(v33);
	if(v32_state) glDisableClientState(v32_state);
	glDisable(0xB71u);
	glEnable(0xBE2u);
	glDisableClientState(0x8078u);
}
bool_t ArmorScreen::takeAndClearSlot(int32_t a2) {
	ItemInstance* item = this->player->getArmor(a2);
	if(item) {
		int32_t empty = this->minecraft->player->inventory->getEmptySlotsCount();
		if(!this->minecraft->player->inventory->add(item)) {
			this->minecraft->player->drop(item, 0);
		}
		this->player->setArmor(a2, 0);
		int32_t nempty = this->minecraft->player->inventory->getEmptySlotsCount();
		if(this->performUpdate) {
			this->performUpdate = 1;
			return 1;
		} else {
			this->performUpdate = nempty != empty;
			return this->performUpdate;
		}
	}
	return 0;
}
void ArmorScreen::updateItems() {
	this->field_1E0.clear();
	for(int32_t i = 9; i < this->minecraft->player->inventory->getContainerSize(); ++i) {
		ItemInstance* v5 = this->minecraft->player->inventory->getItem(i);
		if(ItemInstance::isArmorItem(v5)) {
			this->field_1E0.emplace_back(v5);
		}
	}
}

void ArmorScreen::setupInventoryPane() {
	if(this->field_1BC) delete this->field_1BC;
	this->field_1BC = new Touch::InventoryPane(this, this->minecraft, this->field_1C0, this->field_1C0.width, 4.0f, this->field_1E0.size(), 32, 4, 1);
	this->field_1BC->field_248 = 0;
	this->field_1BC->field_24C = 0;
}
ArmorScreen::~ArmorScreen() {
	if(this->field_1BC) delete this->field_1BC;
	if(this->field_1F0) delete this->field_1F0;
	if(this->field_1F4) delete this->field_1F4;
	if(this->field_1F8) delete this->field_1F8;
	if(this->field_1FC) delete this->field_1FC;

	if(this->field_58) delete this->field_58;
}
void ArmorScreen::render(int32_t a2, int32_t a3, float a4) {
	int32_t v8;			 // r3
	int32_t v9;			 // r6
	ItemInstance* armor; // r0
	BlankButton* v11;	 // r2
	int32_t v12;		 // r2
	int32_t posX;		 // [sp+0h] [bp-20h]
	int32_t posY;		 // [sp+4h] [bp-1Ch]

	Tesselator::instance.addOffset(0.0, 0.0, -500.0);
	this->field_1F0->draw(Tesselator::instance, 0.0, 0.0);
	Tesselator::instance.addOffset(0.0, 0.0, 500.0);
	Screen::render(a2, a3, a4);
	v8 = a2;
	v9 = 0;
	this->handleRenderPane(this->field_1BC, Tesselator::instance, v8, a3, a4);
	Tesselator::instance.colorABGR(-1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	Tesselator::instance.addOffset(0.0, 0.0, -490.0);
	this->field_1FC->draw(Tesselator::instance, (float)this->field_1D0, (float)this->field_1D4);
	Tesselator::instance.addOffset(0.0, 0.0, 490.0);
	glClear(0x100u);
	this->renderPlayer((float)(this->field_1D0 + this->field_1D8 / 2), (float)this->height * 0.85);
	do {
		armor = this->player->getArmor(v9);
		v11 = this->field_178[v9];
		posX = v11->posX;
		posY = v11->posY;
		v12 = v9++;
		this->drawSlotItemAt(Tesselator::instance, v12, armor, posX, posY);
	} while(v9 != 4);
}
void ArmorScreen::init() {
	Screen::init();
	this->player = this->minecraft->player;
	this->backButton.width = 38;
	this->backButton.height = 18;
	this->backButton.init(this->minecraft);
	this->buttons.emplace_back(&this->header);
	this->buttons.emplace_back(&this->backButton);
	this->field_178[0] = &this->field_B8;
	this->field_178[1] = &this->field_E8;
	this->field_178[2] = &this->field_118;
	this->field_178[3] = &this->field_148;
	for(int32_t i = 0; i != 4; ++i) {
		this->buttons.emplace_back(this->field_178[i]);
	}
	NinePatchFactory npf(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_1F0 = npf.createSymmetrical({0, 0, 16, 16}, 4, 4, 32, 32);
	this->field_1F4 = npf.createSymmetrical({0, 32, 8, 8}, 3, 3, 20, 20);
	this->field_1F8 = npf.createSymmetrical({28, 42, 4, 4}, 1, 1, 32, 32)->setExcluded(16);
	this->field_1FC = npf.createSymmetrical({0, 20, 8, 8}, 3, 3, 32, 32);
	this->updateItems();
}
void ArmorScreen::setupPositions() {
	float width;	 // s14
	int v3;			 // r3
	int v4;			 // r2
	int v5;			 // r6
	int i;			 // r3
	BlankButton* v7; // r2
	int minY;		 // r0
	int v9;			 // r0
	int v10;		 // r5
	int v11;		 // r6
	int v12;		 // r5
	int height;		 // r3
	int v14;		 // s12
	int v15;		 // [sp+Ch] [bp-4h]

	width = (float)this->width;
	this->header.posY = 0;
	this->header.posX = 0;
	this->header.width = this->width;
	this->backButton.posX = 4;
	this->backButton.posY = 4;
	v3 = (int)(float)(width / 1.8);
	v4 = v3 - 20;
	if(v3 - 20 < 0) {
		v4 = v3 + 11;
	}
	v5 = (v4 & 0xFFFFFFE0) + 20;
	v15 = this->height - 40;
	this->field_1C0.minX = 10;
	this->field_1C0.minY = 32;
	this->field_1C0.width = v4 & 0xFFFFFFE0;
	this->field_1C0.height = v15;
	for(i = 0; i != 16; i += 4) {
		v7 = this->field_178[i / 4u];
		v7->posX = v5;
		minY = this->field_1C0.minY;
		v7->width = 20;
		v7->height = 20;
		v9 = minY + 6 * i;
		v7->posY = v9;
	}
	v10 = this->width;
	this->field_1D4 = this->field_1C0.minY;
	v11 = this->field_178[0]->posX + this->field_178[0]->width;
	v12 = v10 - v11;
	this->field_1D0 = v11 + v12 / 10;
	height = this->field_1C0.height;
	v14 = this->field_1C0.width;
	this->field_1DC = height;
	this->field_1D8 = v12 + 2 * (v12 / -10);
	this->field_1F8->setSize((float)v14 + 2.0, (float)height + 2.0);
	this->field_1FC->setSize((float)this->field_1D8, (float)this->field_1DC);
	this->field_1F0->setSize((float)this->width, (float)this->height);
	this->updateItems();
	this->setupInventoryPane();
}
bool_t ArmorScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->closeScreen();
	}
	return 1;
}
void ArmorScreen::tick() {
	if(this->field_1BC) {
		this->field_1BC->tick();
	}
	if(this->performUpdate) {
		this->updateItems();
		this->setupInventoryPane();
		this->performUpdate = 0;
	}
}
bool_t ArmorScreen::renderGameBehind() {
	return 0;
}

void ArmorScreen::buttonClicked(Button* a2) {
	if(a2 == &this->backButton) {
		this->closeScreen();
	}
	uint32_t bid = a2->buttonID;
	if(bid <= 3) {
		this->takeAndClearSlot(bid);
	}
}
bool_t ArmorScreen::addItem(const Touch::InventoryPane* a2, int32_t a3) {
	const ItemInstance* v5 = this->field_1E0[a3];
	if(ItemInstance::isArmorItem(v5)) {
		ItemInstance* armor = this->player->getArmor(((ArmorItem*)v5->itemClass)->field_48);
		ItemInstance v15;
		if(ItemInstance::isArmorItem(armor)) {
			v15 = *armor;
		}
		this->player->setArmor(((ArmorItem*)v5->itemClass)->field_48, v5);
		this->player->inventory->removeItemInstance(v5);
		this->field_1E0[a3] = 0;
		if(!v15.isNull() && !this->player->inventory->add(&v15)) {
			this->player->drop(&v15, 0);
		}
		this->performUpdate = 1;
		return 1;
	}
	return 0;
}
bool_t ArmorScreen::isAllowed(int32_t) {
	return 1;
}
std::vector<const ItemInstance*> ArmorScreen::getItems(const Touch::InventoryPane* a3) {
	return std::vector<const ItemInstance*>(this->field_1E0);
}
