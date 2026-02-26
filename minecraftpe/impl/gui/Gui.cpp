#include <gui/Gui.hpp>
#include <Config.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <entity/player/gamemode/GameMode.hpp>
#include <input/IInputHolder.hpp>
#include <input/Mouse.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <rendering/Font.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <rendering/states/DisableState.hpp>
#include <sstream>
#include <string.h>
#include <tile/material/Material.hpp>
#include <util/GuiMessage.hpp>
#include <util/IntRectangle.hpp>
#include <util/OffsetPosTranslator.hpp>
#include <utils.h>

float Gui::InvGuiScale = 0.333333;
float Gui::GuiScale;
float Gui::DropTicks = 40.0;

Gui::Gui(Minecraft* mc) {
	this->field_10 = 0;
	this->field_18 = 240;
	this->field_14 = "";
	this->minecraftInst = mc;
	this->field_9FC = 0;
	this->field_A00 = 2;
	this->field_A04 = "";
	this->field_A08 = 0;
	this->field_A0C = 0;
	this->field_A10 = 1;
	this->field_A18 = -1;
	this->invUpdated = 1;
	this->field_A20 = -1;
	this->field_A28 = 0;
	this->slotsAmount = 4;
	this->field_A80 = -1;
	this->tipMessage = "";
	this->field_A84 = -1;
	this->field_A8C = 0;
	this->field_A94 = 0;
	AppPlatform::_singleton->listeners.emplace(1.0f, this);
}

Gui::~Gui() {
	AppPlatform::_singleton->removeListener(this);
}

void Gui::onAppSuspended() {
}
void Gui::onConfigChanged(const Config& a2) {
	int v4;			   // r8
	AppPlatform* v5;   // r0
	float v6;		   // s17
	float v7;		   // s16
	float v8;		   // s19
	int v9;			   // s15
	float v10;		   // s20
	float v11;		   // s21
	float v12;		   // r0
	float v13;		   // s15
	float v14;		   // s13
	float v15;		   // s14
	int v16;		   // r7
	int v17;		   // s14
	float v18;		   // r0
	float v19;		   // s17
	float v20;		   // r0
	int sp;			   // r0
	int v22;		   // r4
	int v23;		   // [sp+Ch] [bp-8Ch] BYREF
	int v24;		   // [sp+10h] [bp-88h] BYREF
	int v25;		   // [sp+14h] [bp-84h] BYREF
	MeshBuffer result; // [sp+18h] [bp-80h] BYREF

	v4 = 0;
	v5 = this->minecraftInst->platform();
	v6 = (float)(v5->getPixelsPerMillimeter() * 12.0) * 0.3333;
	if(v6 >= 40.0) {
		v6 = 40.0;
	}
	v7 = v6 * 0.95;
	v8 = 6.2832 / 24.0;
	Tesselator::instance.begin(96);
	do {
		v9 = v4++;
		v10 = (float)v9 * v8;
		v11 = Mth::cos(v10);
		v12 = Mth::cos(v10 + v8);
		v13 = Mth::sin(v10);
		v14 = v12;
		v15 = Mth::sin(v10 + v8);
		Tesselator::instance.vertexUV(v7 * v11, v7 * v13, 0.0, 0.0, 1.0);
		Tesselator::instance.vertexUV(v7 * v14, v7 * v15, 0.0, 1.0, 1.0);
		Tesselator::instance.vertexUV(v6 * v14, v6 * v15, 0.0, 1.0, 0.0);
		Tesselator::instance.vertexUV(v6 * v11, v6 * v13, 0.0, 0.0, 0.0);
	} while(v4 != 24);
	this->meshBuffer1 = Tesselator::instance.end();
	v16 = 0;

	Tesselator::instance.begin(6, 26);
	Tesselator::instance.vertex(0.0, 0.0, 0.0);
	do {
		v17 = v16--;
		v18 = (float)v17 * v8;
		v19 = v18 * 10430.0;
		v20 = Mth::cos(v18);
		Tesselator::instance.vertex(v7 * v20, v7 * Mth::sin(v19), 0.0);
	} while(v16 != -25);
	this->meshBuffer2 = Tesselator::instance.end();
	sp = a2.mc->useTouchscreen();
	if(sp) {
		if(a2.mc->options.useJoypad) {
			v22 = 6;
		} else {
			v22 = 6;
			if(a2.field_0 > 480) {
				do {
					this->getSlotPos(0, v23, v25);
					sp = this->getSlotPos(v22, v24, v25);
					if((float)((float)((float)a2.field_0 - (float)((float)(v24 - v23) * a2.guiScale)) * a2.field_1C) < 80.0) {
						break;
					}
					++v22;
				} while(v22 != 8);
			}
		}
		this->slotsAmount = v22;
	} else {
		this->slotsAmount = 9;
	}
	this->field_18 = a2.field_10;
}

int32_t Gui::itemCountItoa(char_t* buf, int32_t n) {
	if(n < 0) return 0;
	if(n > 9) {
		if(n > 99) {
			strcpy(buf, "99+");
			return 3;
		}
		*buf = n / 10 + 48;
		buf[2] = 0;
		buf[1] = n + 48 - 10 * (n / 10);
		return 2;
	} else {
		*buf = n + 48;
		buf[1] = 0;
		return 1;
	}
}

void Gui::addMessage(const std::string& a2, const std::string& a3, int32_t a4) {
	GuiMessage* v7; // r0
	char* v8;		// r0

	if(this->minecraftInst->font) {
		GuiMessage v13(a2, a3, a4);
		this->chatMessages.emplace(this->chatMessages.begin(), v13);

		if(!this->minecraftInst->isOnlineClient() && v13.field_8[0] == '/') {
#ifdef WIP
			std::string v10 = ServerCommandParser::executeCommand(&v13); //TODO check - for some reason references (ServerCommandParser*)this->minecraftInst->field_D30,
#else
			std::string v10 = "WIP - Gui::addMessage";
#endif
			this->chatMessages.emplace(this->chatMessages.begin(), GuiMessage("server", v10, 200));
		}

		while(1) { //TODO check
			if(this->chatMessages.size() <= 30) break;
			this->chatMessages.pop_back();
		}
	}
}
float Gui::cubeSmoothStep(float a2, float a3, float a4) {
	return (float)(a2 * a2) * (float)(3.0 - (float)(a2 + a2));
}
void Gui::displayClientMessage(const std::string& a2) {
	this->addMessage("", a2, 200);
}
void Gui::flashSlot(int32_t a2) {
	this->field_A18 = a2;
	this->field_A20 = getTimeS();
}
float Gui::floorAlignToScreenPixel(float a1) {
	return (float)(int32_t)(float)(a1 * Gui::GuiScale) * Gui::InvGuiScale;
}
int32_t Gui::getNumSlots() {
	return this->slotsAmount;
}
RectangleArea Gui::getRectangleArea(int32_t a3) {
	int32_t v6;				  // s12
	int32_t NumSlots;		  // r0
	float v8;				  // s16
	Minecraft* minecraftInst; // r3
	float v10;				  // s15
	float v11;				  // s14
	float v12;				  // s13
	int32_t v13;			  // s12
	int32_t v14;			  // s13

	v6 = this->minecraftInst->field_1C / 2;
	NumSlots = this->getNumSlots();
	v8 = (float)v6 + 2.0;
	minecraftInst = this->minecraftInst;
	v10 = (float)((float)(10 * NumSlots + 3) + 1.0) * Gui::GuiScale;
	v11 = Gui::GuiScale * 25.0;
	if(a3 < 0) {
		v12 = (float)minecraftInst->field_20;
		return RectangleArea(1, 0, v12, (float)(v8 + v10), v12);
	}
	if(!a3) {
		v14 = minecraftInst->field_20;
		v12 = (float)v14;
		return RectangleArea(1, v8 - v10, v12 - v11, (float)(v8 + v10) + 2, v12);
	}
	v12 = (float)minecraftInst->field_20;
	v13 = minecraftInst->field_1C;
	return RectangleArea(1, v8 - v10, v12 - v11, v13, v12);
}
int32_t Gui::getSlotIdAt(int32_t a2, int32_t a3) {
	int32_t v5;	 // r6
	int32_t v6;	 // r3
	int32_t v7;	 // s14
	int32_t v8;	 // r2
	int32_t v9;	 // r4
	int32_t v10; // r0

	v5 = (int32_t)(float)((float)this->minecraftInst->field_1C * Gui::InvGuiScale);
	v6 = (int32_t)(float)((float)this->minecraftInst->field_20 * Gui::InvGuiScale);
	v8 = (int32_t)(float)((float)a3 * Gui::InvGuiScale);
	if(v8 < v6 - 19) {
		return -1;
	}
	if(v8 > v6) {
		return -1;
	}
	v7 = (int32_t)(float)((float)a2 * Gui::InvGuiScale);
	v10 = v7 - (v5 / 2 + 2 - 10 * this->getNumSlots());
	if(v10 < 0) {
		return -1;
	}
	v9 = v10 / 20;
	if(v10 / 20 >= this->getNumSlots()) {
		return -1;
	}
	return v9;
}
int32_t Gui::getSlotPos(int32_t slot, int32_t& x, int32_t& y) {
	Minecraft* minecraftInst; // r4
	int32_t v8;				  // r5
	int32_t v9;				  // r4
	int32_t result;			  // r0

	minecraftInst = this->minecraftInst;
	v8 = (int32_t)(float)((float)minecraftInst->field_20 * Gui::InvGuiScale);
	v9 = (int32_t)(float)((float)minecraftInst->field_1C * Gui::InvGuiScale);
	result = v9 / 2 - 10 * this->getNumSlots();
	x = result + 20 * slot;
	y = v8 - 22;
	return result;
}
void Gui::handleClick(int32_t a2, int32_t a3, int32_t a4) {
	int32_t SlotIdAt;		  // r5
	bool_t v6;				  // zf
	Minecraft* minecraftInst; // r0
	Screen* currentScreen;	  // r1
	Minecraft** p_minecraft;  // r0
	ScreenId v10;			  // r1

	if(a2 == 1) {
		SlotIdAt = this->getSlotIdAt(a3, a4);
		if(SlotIdAt != -1) {
			v6 = SlotIdAt == this->getNumSlots() - 1;
			minecraftInst = this->minecraftInst;
			if(v6) {
				currentScreen = minecraftInst->currentScreen;
				if(currentScreen) {
					v10 = ScreenId::NONE_SCREEN;
				} else {
					v10 = ScreenId::INVENTORY_SCREEN;
				}
				minecraftInst->screenChooser.setScreen(v10);
			} else {
				minecraftInst->player->inventory->selectSlot(SlotIdAt);
				this->resetItemNameOverlay();
			}
		}
	}
}
void Gui::handleKeyPressed(int32_t a2) {
	Inventory* inventory; // r3
	int32_t selectedSlot; // r2
	int32_t v5;			  // r2
	int32_t v6;			  // r5

	switch(a2) {
		case 99:
			inventory = this->minecraftInst->player->inventory;
			selectedSlot = inventory->selectedSlot;
			if(selectedSlot <= 0) {
				return;
			}
			v5 = selectedSlot - 1;
LABEL_7:
			inventory->selectedSlot = v5;
			return;
		case 4:
			v6 = this->minecraftInst->player->inventory->selectedSlot;
			if(v6 >= this->getNumSlots() - 2) {
				return;
			}
			inventory = this->minecraftInst->player->inventory;
			v5 = inventory->selectedSlot + 1;
			goto LABEL_7;
		case 100:
			this->minecraftInst->screenChooser.setScreen(ScreenId::INVENTORY_SCREEN);
			break;
	}
}
void Gui::inventoryUpdated() {
	this->invUpdated = 1;
}
bool_t Gui::isInside(int32_t x, int32_t y) {
	return this->getSlotIdAt(x, y) != -1;
}

OffsetPosTranslator _spawnPos;
char_t _D6E05AAC[264];

void Gui::onLevelGenerated() {
	if(this->minecraftInst->level) {
		TilePos res = this->minecraftInst->level->getSharedSpawnPos();
		_spawnPos.y = -res.y;
		_spawnPos.z = -res.z;
		_spawnPos.x = -res.x;
	}
}
void Gui::postError(int32_t a2) {
	static std::set<int> _D6E05BAC;
	if(_D6E05BAC.find(a2) != _D6E05BAC.end()) {
		_D6E05BAC.insert(a2); //TODO check

		std::stringstream v11;
		v11 << "Something went wrong! (errcode ";
		v11 << a2;
		v11 << ")\n";
		this->addMessage("error", v11.str(), 200);
	}
}
#include <rendering/LevelRenderer.hpp>

void Gui::render(float a2, bool_t a3, int32_t a4, int32_t a5) {
	Minecraft* minecraftInst; // r3
	Minecraft* v8;			  // r0
	Font* font;				  // r8
	int32_t v10;			  // r0
	Minecraft* v11;			  // r3
	int32_t v12;			  // s13
	float v13;				  // s15
	float v14;				  // s14
	int32_t v15;			  // r7
	int32_t v16;			  // s15
	float v18;				  // s14
	Minecraft* v19;			  // r3
	float v20;				  // s16
	float v21;				  // s12
	float v22;				  // s14
	float v23;				  // s17
	int32_t v24;			  // r0

	minecraftInst = this->minecraftInst;
	if(minecraftInst->level) {
		if(minecraftInst->player) {
			DisableState v25(0xB71);
			v8 = this->minecraftInst;
			font = v8->font;
			v10 = v8->useTouchscreen();
			v11 = this->minecraftInst;
			v12 = v11->field_20;
			v13 = Gui::InvGuiScale;
			v14 = (float)v11->field_1C * Gui::InvGuiScale;
			this->zLayer = -90.0;
			v15 = (int32_t)v14;
			v16 = (int32_t)(float)((float)v12 * v13);
			if(!v11->currentScreen) {
				this->renderProgressIndicator(v10, v15, v16, a2);
			}
			glColor4f(1.0, 1.0, 1.0, 1.0);
			if(this->minecraftInst->gameMode->canHurtPlayer()) {
				this->minecraftInst->texturesPtr->loadAndBindTexture("gui/icons.png");
				Tesselator::instance.beginOverride();
				Tesselator::instance.colorABGR(-1);
				this->renderHearts();
				this->renderBubbles();
				Tesselator::instance.endOverrideAndDraw();
			}
			if(this->minecraftInst->player->getSleepTimer() > 0) {
				this->renderSleepAnimation(v15, v16);
			}
			if(!this->minecraftInst->currentScreen) {
				this->renderToolBar(a2, 0.65);
			}
			v18 = this->field_A8C;
			if(v18 > 0.0) {
				v19 = this->minecraftInst;
				v20 = this->field_A90;
				v21 = (float)v19->field_1C / Gui::GuiScale;
				v22 = v18 / 20.0;
				v23 = (float)((float)(v19->field_20 / 2) / Gui::GuiScale) + 20.0;
				if(v22 >= 1.0) v22 = 1.0;

				v24 = Color4(1, 1, 1, v22 * 0.85).toARGB();
				font->drawShadow(this->tipMessage, (float)(v21 * 0.5) - (float)(v20 * 0.5), v23, v24);
			}
			this->renderChatMessages(v15, v16, 0xAu, this->field_A94, font);
			if(!this->minecraftInst->currentScreen) {
				this->renderOnSelectItemNameText(v15, font, v16 - 19);
			}
			//DisableState::~DisableState((DisableState *)&v25);
		}
	}
}
void Gui::renderBubbles() {
	int32_t relatedToBubbleRendering; // r4
	int32_t v3;						  // r10
	int32_t v4;						  // s14
	int32_t v5;						  // r4
	int32_t v6;						  // r3
	int32_t v7;						  // r9

	if(this->minecraftInst->player->isUnderLiquid(Material::water)) {
		relatedToBubbleRendering = this->minecraftInst->player->air;
		v3 = (int32_t)ceilf((float)((float)(relatedToBubbleRendering - 2) * 10.0) / 300.0);
		v4 = relatedToBubbleRendering;
		v5 = 0;
		v7 = (int32_t)ceilf((float)((float)v4 * 10.0) / 300.0);
		while(v5 < v7) {
			if(v5 < v3) {
				v6 = 16;
			}
			if(v5 >= v3) {
				v6 = 25;
			}
			this->blit(8 * v5++ + 2, 12, v6, 18, 9, 9, 0, 0);
		}
	}
}
void Gui::renderChatMessages(int32_t a2, int32_t a3, uint32_t a4, bool_t a5, struct Font* a6) {
	if(!a5) {
		int32_t v7 = 0;
		if(this->chatMessages.size() != 0) {
			int32_t v12 = this->chatMessages.size() - 1;
			while(v12 >= 0) {
				if(this->chatMessages[v12].field_0 < this->chatMessages[v12].field_4) {
					++v7;
				}
				--v12;
			}
			int32_t v10 = this->chatMessages.size() - 1;
			int32_t v16 = 0;
			while(v10 >= 0) {
				GuiMessage* str = &this->chatMessages[v10];
				if(str->field_0 < str->field_4) {
					float v20 = (float)(1.0 - (float)((float)str->field_0 / (float)str->field_4)) * 10.0;
					if(v20 < 0) v20 = 0;
					else if(v20 > 1) v20 = 1;
					int v21 = (int)(float)((float)(v20 * v20) * 255.0);
					if(v21 > 0) {
						if(v7 <= 10) {
							++v16;
							this->fill(2, (float)(9 * v16 + 18) - 1.0, (float)this->field_18 + 2.0, (float)(9 * v16 + 18) + 8.0, v21 >> 1 << 24);
							Color4* v22;
							if(str->field_8[0] == '/') {
								v22 = &Color4::GREY;
							} else {
								v22 = &Color4::WHITE;
							}
							Color4 v27(v22->r, v22->g, v22->b, 0);
							a6->drawShadow(str->field_10, 2.0, (float)(9 * v16 + 18), v27.toARGB() + (v21 << 24));
						} else {
							--v7;
						}
					}
				}
				--v10;
			}
		}
	}
}
void Gui::renderDebugInfo(void) {
	LocalPlayer* player; // r3
	float v3;			 // s15
	float posX;			 // r2
	float posZ;			 // r3
	float a2;			 // [sp+14h] [bp-24h] BYREF
	float a3;			 // [sp+18h] [bp-20h] BYREF
	float a4;			 // [sp+1Ch] [bp-1Ch] BYREF

	player = this->minecraftInst->player;
	v3 = player->posY - player->ridingHeight;
	posX = player->posX;
	posZ = player->posZ;
	a2 = posX;
	a4 = posZ;
	a3 = v3;
	_spawnPos.to(a2, a3, a4);
	sprintf(_D6E05AAC, "pos: %3.1f, %3.1f, %3.1f\n", a2, a3, a4);
	Tesselator::instance.beginOverride();
	Tesselator::instance.scale2d(Gui::InvGuiScale, Gui::InvGuiScale);
	this->minecraftInst->font->draw(_D6E05AAC, 2.0, 2.0, 0xFFFFFF);
	Tesselator::instance.resetScale();
	Tesselator::instance.endOverrideAndDraw();
}
void Gui::renderHearts() {
	LocalPlayer* player;	 // r4
	int32_t field_DC;		 // r0
	int32_t v4;				 // r9
	int32_t v5;				 // r7
	int32_t v7;				 // r11
	int32_t v8;				 // r1
	int32_t v9;				 // r10
	int32_t health;			 // [sp+18h] [bp-38h]
	int32_t prevHealthMaybe; // [sp+20h] [bp-30h]

	player = this->minecraftInst->player;
	field_DC = player->field_DC;
	if(field_DC <= 9) {
		v4 = 0;
	} else {
		v4 = (field_DC / 3) & 1;
	}
	v5 = 1;
	health = player->health;
	prevHealthMaybe = player->prevHealthMaybe;
	this->randomInst = Random(312871 * this->field_9FC);
	v7 = this->minecraftInst->player->getArmorValue();
	do {
		if(v7 > 0) {
			v8 = 4 * v5 + 82;
			if(v5 >= v7) {
				if(v5 == v7) {
					this->blit(v8, 2, 52, 9, 9, 9, 0, 0);
				} else if(v5 > v7) {
					this->blit(v8, 2, 16, 9, 9, 9, 0, 0);
				}
			} else {
				this->blit(v8, 2, 34, 9, 9, 9, 0, 0);
			}
		}
		if(health > 4) {
			v9 = 2;
		} else {
			v9 = (this->randomInst.genrand_int32() & 1) + 1;
		}
		this->blit(4 * v5 - 2, v9, 9 * v4 + 16, 0, 9, 9, 0, 0);
		if(v4) {
			if(v5 >= prevHealthMaybe) {
				if(v5 == prevHealthMaybe) {
					this->blit(4 * v5 - 2, v9, 79, 0, 9, 9, 0, 0);
				}
			} else {
				this->blit(4 * v5 - 2, v9, 70, 0, 9, 9, 0, 0);
			}
		}
		if(v5 >= health) {
			if(v5 == health) {
				this->blit(4 * v5 - 2, v9, 61, 0, 9, 9, 0, 0);
			}
		} else {
			this->blit(4 * v5 - 2, v9, 52, 0, 9, 9, 0, 0);
		}
		v5 += 2;
	} while(v5 != 21);
}
void Gui::renderOnSelectItemNameText(int32_t a2, struct Font* a3, int32_t a4) {
	ItemInstance* sel; // r4
	int32_t v10;	   // r7
	int32_t v11;	   // r5

	if(this->field_A00 < 1.0) {
		sel = this->minecraftInst->player->inventory->getSelected();
		if(sel) {
			v10 = a3->width(sel->getName());
			if(this->field_A00 <= 0.75) {
				v11 = 255;
			} else {
				v11 = (int32_t)(float)(this->cubeSmoothStep((float)(0.25 - (float)(this->field_A00 - 0.75)) * 4.0, 0.0, 1.0) * 255.0);
				if(!v11) {
					return;
				}
			}

			a3->drawShadow(sel->getName(), (float)(a2 / 2 - v10 / 2), (float)(a4 - 22), (v11 << 24) + 0xFFFFFF);
		}
	}
}
void Gui::renderProgressIndicator(bool_t a2, int32_t a3, int32_t a4, float a5) {
	ItemInstance* Selected;	   // r0
	Item* itemClass;		   // r9
	bool_t v11;				   // r6
	bool_t v12;				   // r3
	Minecraft* minecraftInst;  // r1
	float v15;				   // s17
	IInputHolder* inputHolder; // r2
	float v17;				   // s16
	GameMode* gameMode;		   // r3
	float v19;				   // s18
	float v20;				   // r3
	float v21;				   // s16
	IInputHolder* v22;		   // r3
	float v23;				   // r6
	float v24;				   // r5
	float v25;				   // s16
	float v26;				   // r1

	Selected = this->minecraftInst->player->inventory->getSelected();
	if(Selected) {
		itemClass = Selected->itemClass;
		v11 = itemClass == Item::bow;
		v12 = itemClass == this->minecraftInst->player->getUseItem()->itemClass;
	} else {
		v11 = 0;
		v12 = 0;
	}
	if(!a2 || (minecraftInst = this->minecraftInst, minecraftInst->options.useJoypad)) {
LABEL_8:
		this->minecraftInst->texturesPtr->loadAndBindTexture("gui/icons.png");
		glBlendFunc(0x307u, 0x301u);
		this->blit(a3 / 2 - 8, a4 / 2 - 8, 0, 0, 16, 16, 0, 0);
		glBlendFunc(0x302u, 0x303u);
		return;
	}
	if(v11) {
		if(!v12) {
			return;
		}
		goto LABEL_8;
	}
	v15 = 1.0;
	inputHolder = minecraftInst->inputHolder;
	v17 = inputHolder->field_C;
	gameMode = minecraftInst->gameMode;
	v19 = gameMode->field_8;
	if(v17 > 1.0) {
LABEL_12:
		if(v19 <= 0.0 && v17 > 0.0) {
			v17 = v15;
LABEL_15:
			DisableState v27(3553);
			if(this->minecraftInst->selectedObject.hitType == 2) {
				v21 = v17 * 0.4;
				if(v21 < 0.4) {
					v20 = v21;
				} else {
					v20 = 0.4;
				}
			} else {
				v20 = v17 * 0.8;
			}
			glColor4f(1.0, 1.0, 1.0, v20);
			v22 = this->minecraftInst->inputHolder;
			v23 = Gui::InvGuiScale * v22->mouseX;
			v24 = Gui::InvGuiScale * v22->mouseY;
			glTranslatef(v23, v24, 0.0);
			this->meshBuffer1.render();
			glTranslatef(-v23, -v24, 0.0);
			return;
		}
		goto LABEL_21;
	}
	if(v17 <= 0.0) {
		v15 = 0.0;
		goto LABEL_12;
	}
	if(v19 <= 0.0) {
		goto LABEL_15;
	}
	v15 = inputHolder->field_C;
LABEL_21:
	if(v19 <= 0.0) {
		return;
	}
	v25 = gameMode->field_4;
	DisableState v27(3553);
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, v15 * 0.8);
	glTranslatef(Gui::InvGuiScale * this->minecraftInst->inputHolder->mouseX, Gui::InvGuiScale * this->minecraftInst->inputHolder->mouseY, 0.0);
	this->meshBuffer1.render();
	v26 = (float)((float)(v25 + (float)((float)(v19 - v25) * a5)) * 0.5) + 0.5;
	glScalef(v26, v26, 1.0);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBlendFunc(0x307u, 0x301u);
	this->meshBuffer2.render();
	glBlendFunc(0x302u, 0x303u);
	glPopMatrix();
}
void Gui::renderSleepAnimation(int32_t a2, int32_t a3) {
	int32_t v6 = this->minecraftInst->player->getSleepTimer();
	float v7 = (float)v6 / 100;
	if(v7 > 1) v7 = 1 - (float)(v6 - 100) / 10.0;
	this->fill(0, 0, a2, a3, ((int32_t)(float)(v7 * 220.0) << 24) | 0x101020);
}
void Gui::renderSlot(int32_t a2, int32_t a3, int32_t a4, float a5) {
	LocalPlayer* player; // r0
	ItemInstance* v9;	 // r0
	Item* itemClass;	 // r0
	int32_t v12;		 // r2

	player = this->minecraftInst->player;
	if(player->abilities.instabuild) {
		a2 += 9;
	}
	v9 = player->inventory->getItem(a2);
	if(v9) {
		itemClass = v9->itemClass;
		if(itemClass->field_10) {
			v12 = itemClass->getAnimationFrameFor(this->minecraftInst->player);
		} else {
			v12 = 0;
		}
		ItemRenderer::renderGuiItemNew(this->minecraftInst->texturesPtr, v9, v12, (float)a3, (float)a4, 1.0, 1.0, 1.0);
	}
}
void Gui::renderSlotText(const struct ItemInstance* a2, float a3, float a4, bool_t a5, bool_t a6) {
	int count;	   // r1
	int v11;	   // r3
	Font* font;	   // r0
	int v13;	   // r3
	int v14;	   // r3
	char_t v15[4]; // [sp+Ch] [bp-1Ch] BYREF

	count = a2->count;
	if(count > 1) {
		v15[0] = v15[1] = v15[2] = v15[3] = 0; //float?
		if(a5) {
			Gui::itemCountItoa(v15, count);
		} else {
			v15[0] = -99; //lobyte
		}
		v11 = a2->count;
		font = this->minecraftInst->font;
		if(a6) {
			if(v11 > 0) {
				v13 = 0xFFCCCCCC;
			} else {
				v13 = 0x60CCCCCC;
			}
			font->drawShadow(v15, a3, a4, v13);
		} else {
			if(v11 > 0) {
				v14 = 0xFFCCCCCC;
			} else {
				v14 = 0x60CCCCCC;
			}
			font->draw(v15, a3, a4, v14);
		}
	}
}
void Gui::renderToolBar(float a2, float a3) {
	Minecraft* minecraftInst; // r3
	int32_t v7;				  // r7
	int32_t v8;				  // r6
	int32_t v9;				  // s19
	Inventory* inventory;	  // r9
	float v12;				  // s17
	int32_t v13;			  // r11
	float v14;				  // s18
	int32_t v15;			  // r9
	float v16;				  // r0
	float v17;				  // s18
	int32_t v18;			  // r9
	int32_t v19;			  // r1
	int32_t NumSlots;		  // r0
	int32_t v23;			  // r2
	int32_t v24;			  // r6
	float v25;				  // s18
	int32_t v26;			  // r1
	float v29;				  // s18
	int32_t v31;			  // r5
	float v32;				  // s18
	ItemInstance* v34;		  // r0
	int32_t v35;			  // r11
	float v36;				  // s15
	int32_t sp;				  // [sp+24h] [bp-4Ch] BYREF
	int32_t sp2;			  // [sp+28h] [bp-48h] BYREF

	minecraftInst = this->minecraftInst;
	v7 = (int32_t)(float)((float)minecraftInst->field_1C * Gui::InvGuiScale);
	v8 = (int32_t)(float)((float)minecraftInst->field_20 * Gui::InvGuiScale);
	v9 = v8 - 19;
	glColor4f(1.0, 1.0, 1.0, a3);
	this->minecraftInst->texturesPtr->loadAndBindTexture("gui/gui.png");
	inventory = this->minecraftInst->player->inventory;
	this->getSlotPos(0, sp, sp2);
	v12 = (float)((float)sp + 3.0) + 1.0;
	v13 = 20 * this->getNumSlots();
	this->blit(sp, sp2, 0, 0, v13, 22, 0, 0);
	this->blit(sp + v13, sp2, 180, 0, 2, 22, 0, 0);
	if(this->field_A84 >= 0) {
		if(inventory->getItem(this->field_A84)) {
			v35 = sp + 3 + 20 * this->field_A84;
			v36 = this->field_A80;
			if(v36 >= 3.0) {
				glColor4f(0.0, 1.0, 0.0, a3);
			}
			this->fill(v35, v8 - 3 - (int32_t)(float)((float)((float)(v36 + a2) * 17.0) / 40.0), v35 + 16, v8 - 3, 0x8000FF00);
		}
	}

	this->blit(sp - 1 + 20 * inventory->selectedSlot, sp2 - 1, 0, 22, 24, 22, 0, 0);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	if(this->field_A18 >= 0) {
		v14 = getTimeS() - this->field_A20;
		if(v14 <= 0.2) {
			v15 = -10 * this->getNumSlots() + v7 / 2 + 20 * this->field_A18;
			v16 = Mth::cos(v14 * 62.8);
			this->fill(v15 + 2, v8 - 19, v15 + 18, v8 - 3, ((int32_t)(float)(81.0 - (float)(v16 * 80.0)) << 24) + 0xFFFFFF);
		} else {
			this->field_A18 = -1;
		}
	}
	v17 = v12;
	v18 = 0;
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);
	while(v18 < this->getNumSlots() - 1) {
		v19 = v18++;
		this->renderSlot(v19, (int32_t)v17, v8 - 20, a2);
		v17 = v17 + 20.0;
	}
	this->invUpdated = 0;
	this->minecraftInst->texturesPtr->loadAndBindTexture("gui/gui.png");
	NumSlots = this->getNumSlots();
	v23 = v8 - 13;
	v24 = 0;
	this->blit(10 * NumSlots + v7 / 2 - 16, v23, 228, 248, 14, 4, 28, 8);
	{
		DisableState v39(0xDE1);
		Tesselator::instance.beginOverride();
		v25 = v12 - 1.0;
		while(v24 < this->getNumSlots() - 1) {
			v26 = v24++;
			ItemRenderer::renderGuiItemDecorations(this->minecraftInst->player->inventory->getItem(v26), v25, (float)v9);
			v25 = v25 + 20.0;
		}
		Tesselator::instance.endOverrideAndDraw();
		//DisableState::~DisableState((DisableState*)&v39);
	}
	glPushMatrix();
	glScalef(Gui::InvGuiScale + Gui::InvGuiScale, Gui::InvGuiScale + Gui::InvGuiScale, 1.0);
	v29 = Gui::GuiScale;
	Tesselator::instance.beginOverride();
	if(this->minecraftInst->gameMode->isSurvivalType()) {
		v31 = 0;
		v32 = v29 * 0.5;
		while(v31 < this->getNumSlots() - 1) {
			v34 = this->minecraftInst->player->inventory->getItem(v31);
			if(v34) {
				if(v34->count >= 0) {
					this->renderSlotText(v34, v32 * v12, (float)(v32 * (float)v9) + 1.0, 1, 1);
				}
			}
			v12 = v12 + 20.0;
			++v31;
		}
	}

	this->minecraftInst->texturesPtr->loadAndBindTexture("font/default8.png");
	Tesselator::instance.endOverrideAndDraw();
	glPopMatrix();
}
void Gui::renderVignette(float a2, int32_t a3, int32_t a4) {
	float v7;			   // s15
	float* v8;			   // r4
	float v9;			   // s14
	Textures* texturesPtr; // r4
	float v11;			   // s19
	float v12;			   // s18

	v7 = 1.0 - a2;
	if((float)(1.0 - a2) < 0.0) {
		v7 = 0.0;
	} else if(v7 > 1.0) {
		v7 = 1.0;
	}
	v8 = &this->field_A10;
	v9 = this->field_A10;
	DisableState v13(2929);
	this->field_A10 = v9 + (float)((float)(v7 - v9) * 0.01);
	glBlendFunc(0, 0x301u);
	glDepthMask(0);
	glColor4f(*v8, *v8, *v8, 1.0);
	texturesPtr = this->minecraftInst->texturesPtr;
	texturesPtr->loadAndBindTexture("misc/vignette.png");
	Tesselator::instance.begin(4);
	v11 = (float)a4;
	Tesselator::instance.vertexUV(0.0, v11, -90.0, 0.0, 1.0);
	v12 = (float)a3;
	Tesselator::instance.vertexUV(v12, v11, -90.0, 1.0, 1.0);
	Tesselator::instance.vertexUV(v12, 0.0, -90.0, 1.0, 0.0);
	Tesselator::instance.vertexUV(0.0, 0.0, -90.0, 0.0, 0.0);
	Tesselator::instance.draw(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDepthMask(1u);
	glBlendFunc(0x302u, 0x303u);
}
void Gui::resetItemNameOverlay() {
	this->field_A00 = 0;
}
void Gui::setNowPlaying(const std::string& a2) {
	this->field_A04 = "Now playing: " + a2;
	this->field_A08 = 60;
	this->field_A0C = 1;
}
void Gui::setScissorRect(const IntRectangle& a2) {
	glScissor((uint32_t)(float)(Gui::GuiScale * (float)a2.minX), this->minecraftInst->field_20 - (uint32_t)(float)(Gui::GuiScale * (float)(a2.height + a2.minY)), (uint32_t)(float)(Gui::GuiScale * (float)a2.width), (uint32_t)(float)(Gui::GuiScale * (float)a2.height));
}
void Gui::showTipMessage(const std::string& a2) {
	this->tipMessage = a2;
	this->field_A8C = 40;
	this->field_A90 = this->minecraftInst->font->getPixelLength(a2);
}
void Gui::texturesLoaded(struct Textures*) {
}
void Gui::tick() {
	int32_t v2 = this->field_A08;
	if(v2 > 0) this->field_A08 = v2 - 1;
	float v3 = this->field_A8C;
	if(v3 > 0) this->field_A8C = v3 - 1;
	++this->field_9FC;
	float v4 = this->field_A00;
	if(v4 < 2) this->field_A00 = v4 + 0.05;
	for(int i = 0; i < this->chatMessages.size(); ++i) {
		++this->chatMessages[i].field_0;
	}
	if(!this->minecraftInst->isCreativeMode()) this->tickItemDrop();
}
char_t _D6E05A98;
void Gui::tickItemDrop(void) {
	int32_t v2;				  // r5
	int32_t v3;				  // r0
	int32_t SlotIdAt;		  // r5
	float v5;				  // s15
	Minecraft* minecraftInst; // r3
	Level* levelPtr;		  // r7
	Entity* player;			  // r5

	_D6E05A98 = 0;
	if(Mouse::isButtonDown(1)) {
		v2 = Mouse::getX();
		v3 = Mouse::getY();
		SlotIdAt = this->getSlotIdAt(v2, v3);
		if(SlotIdAt >= 0 && SlotIdAt < this->getNumSlots() - 1) {
			if(SlotIdAt != this->field_A84 || this->minecraftInst->currentScreen) {
				this->field_A80 = 0.0;
				this->field_A84 = SlotIdAt;
			}
			_D6E05A98 = 1;
			v5 = this->field_A80 + 1.0;
			this->field_A80 = v5;
			if(v5 >= 40.0) {
				this->minecraftInst->player->inventory->dropSlot(SlotIdAt, 0, 0);
				minecraftInst = this->minecraftInst;
				levelPtr = minecraftInst->level;
				player = (Entity*)minecraftInst->player;
				levelPtr->playSound(player, "random.pop", 0.3, 1.0);
				_D6E05A98 = 0;
			}
		}
	}
	if(!_D6E05A98) {
		this->field_A84 = -1;
		this->field_A80 = -1.0;
	}
}
