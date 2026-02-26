#include <input/TouchscreenInput.hpp>
#include <Config.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <util/Color4.hpp>
#include <input/Multitouch.hpp>
#include <math/Mth.hpp>
#include <sound/SoundEngine.hpp>

static int _D6E06658, _D6E0665C, _D6E06660, _D6E06664, _D6E06668;
TouchscreenInput::TouchscreenInput(Minecraft* a2, Options* a3)
	: field_1C(1, 0, 0, 1, 1) {
	this->field_4 = 0.0;
	this->field_8 = 0.0;
	this->field_C = 0;
	this->field_D = 0;
	this->field_E = 0;
	this->field_F = 0;
	this->field_10 = 0;
	this->field_11 = 0;
	this->field_40 = 0;
	this->field_41 = 0;
	this->field_42 = 0;
	this->options = a3;
	this->rectArea7 = 0;
	this->rectArea8 = 0;
	this->rectArea1 = 0;
	this->rectArea6 = 0;
	this->rectArea9 = 0;
	this->rectArea5 = 0;
	this->rectArea2 = 0;
	this->rectArea3 = 0;
	this->field_7C = 0;
	this->minecraft = a2;
	this->field_A8 = 0;
	this->field_AC = -999.0;
	this->releaseAllKeys();
	this->onConfigChanged(createConfig(a2));

	_D6E0665C = Color4(0.75294, 0.75294, 0.75294, 0.49804).toARGB();
	_D6E06660 = Color4(1, 1, 1, 0.49804).toARGB();
	_D6E06658 = Color4(1, 1, 1, 0.49804).toARGB();
	_D6E06664 = Color4(0.75294, 0.75294, 0.75294, 0.31373).toARGB();
	_D6E06668 = Color4(0.75294, 0.75294, 0.75294, 0.31373).toARGB();
}
void TouchscreenInput::clear() {
	this->touchAreaModel.clear();
	if(this->rectArea2) delete this->rectArea2;
	this->rectArea2 = 0;
	if(this->rectArea3) delete this->rectArea3;
	this->rectArea3 = 0;
}
RectangleArea* TouchscreenInput::getPauseRectangleArea() {
	return this->field_68;
}
RectangleArea* TouchscreenInput::getRectangleArea() {
	return &this->field_1C;
}
bool_t TouchscreenInput::isButtonDown(int32_t a2) {
	return this->field_B0[a2 - 100]; //TODO check
}

static void sub_D6604D0C(RectangleArea* a1, int a2, int a3, float a4) { //XXX usercall r0,r1,r2,s0
	float v4;															// s16
	float v5;															// s17
	float v6;															// s19
	float v7;															// s22
	float v8;															// s20
	float v9;															// s18

	if(a1) {
		v4 = (float)a3 * 0.0039062;
		v5 = (float)a2 * 0.0039062;
		v6 = Gui::InvGuiScale * a1->minX;
		v7 = Gui::InvGuiScale * a1->maxY;
		v8 = Gui::InvGuiScale * a1->maxX;
		v9 = Gui::InvGuiScale * a1->minY;
		Tesselator::instance.vertexUV(v6, v7, 0.0, v5, v4 + (float)(a4 * 0.0039062));
		Tesselator::instance.vertexUV(v8, v7, 0.0, v5 + (float)(a4 * 0.0039062), v4 + (float)(a4 * 0.0039062));
		Tesselator::instance.vertexUV(v8, v9, 0.0, v5 + (float)(a4 * 0.0039062), v4);
		Tesselator::instance.vertexUV(v6, v9, 0.0, v5, v4);
	}
}

void TouchscreenInput::rebuild() {
	Options* options; // r2
	int hideGUI;	  // r6
	int v4;			  // r1
	int v5;			  // r1
	int v6;			  // r1
	int v7;			  // r1
	int v8;			  // r2
	int v9;			  // r1
	int v10;		  // r1
	int v11;		  // r2
	int v12;		  // r1
	int v13;		  // r2
	int v14;		  // r1

	options = this->options;
	hideGUI = options->hideGUI;
	if(!options->hideGUI) {
		Tesselator::instance.begin(0);
		if(!this->field_11 && (this->field_42 || (hideGUI = this->field_41) != 0)) {
			hideGUI = 1;
		}
		if(!this->minecraft->player->isRiding()) {
			if(hideGUI || this->field_11) {
				v4 = _D6E06658;
			} else if(this->isButtonDown(102)) {
				v4 = _D6E0665C;
			} else {
				v4 = _D6E06660;
			}
			Tesselator::instance.colorABGR(v4);
			sub_D6604D0C(this->rectArea7, 26, 107, 26.0);
			if(hideGUI || this->field_11) {
				v5 = _D6E06658;
			} else if(this->isButtonDown(103)) {
				v5 = _D6E0665C;
			} else {
				v5 = _D6E06660;
			}
			Tesselator::instance.colorABGR(v5);
			sub_D6604D0C(this->rectArea8, 78, 107, 26.0);
			if(hideGUI) {
				v6 = _D6E06658;
			} else if(this->isButtonDown(101)) {
				v6 = _D6E0665C;
			} else {
				v6 = _D6E06660;
			}
			Tesselator::instance.colorABGR(v6);
			if(this->field_11) {
				v7 = 78;
				v8 = 133;
			} else {
				v7 = 52;
				v8 = 107;
			}
			sub_D6604D0C(this->rectArea6, v7, v8, 26.0);
			if(hideGUI) {
				Tesselator::instance.colorABGR(_D6E06660);
				sub_D6604D0C(this->rectArea2, 0, 133, 26.0);
				sub_D6604D0C(this->rectArea3, 26, 133, 26.0);
			}
		}
		if(this->isButtonDown(100)) {
			v9 = _D6E0665C;
		} else {
			v9 = _D6E06660;
		}
		Tesselator::instance.colorABGR(v9);
		if(this->field_11) {
			v10 = 52;
			v11 = 133;
		} else {
			v10 = 0;
			v11 = 107;
		}
		sub_D6604D0C(this->rectArea1, v10, v11, 26.0);
		if(this->field_43 && hideGUI) {
			v12 = _D6E06658;
		} else if(this->isButtonDown(104)) {
			v12 = _D6E0665C;
		} else {
			v12 = _D6E06660;
		}
		Tesselator::instance.colorABGR(v12);
		if(this->field_43) {
			v13 = 133;
		} else {
			v13 = 107;
		}
		sub_D6604D0C(this->rectArea5, 104, v13, 26.0);
		if(!this->minecraft->currentScreen) {
			if(this->isButtonDown(106)) {
				v14 = _D6E0665C;
			} else {
				v14 = _D6E06660;
			}
			Tesselator::instance.colorABGR(v14);
			sub_D6604D0C(this->rectArea9, 200, 82, 18.0);
		}
		glColor4f(1.0, 1.0, 1.0, 0.65);
		Tesselator::instance.draw(1);
	}
}

TouchscreenInput::~TouchscreenInput() {
	this->clear();
}
void TouchscreenInput::tick(Player* a2) {
	int v2; // r6
	bool v5; // r9
	int v6; // r8
	int v7; // r5
	int v8; // r0
	int v9; // s19
	int v10; // lr
	int v11; // s20
	int pointerId; // r0
	int v13; // r11
	int v14; // r2
	bool v15; // r3
	float v16; // s15
	int isButtonDown; // r0
	int v19; // r0
	float v20; // s18
	float v21; // r0
	float v22; // s15
	float v23; // s15
	int v24; // [sp+4h] [bp-5Ch]
	int v25; // [sp+8h] [bp-58h]

	v2 = 0;
	this->field_4 = 0.0;
	this->field_8 = 0.0;
	this->field_D = 0;
	this->field_B0[0] = 0;
	this->field_B0[1] = 0;
	v5 = 0;
	this->field_B0[2] = 0;
	v6 = 0;
	this->field_B0[3] = 0;
	this->field_B0[4] = 0;
	this->field_B0[5] = 0;
	v24 = 0;
	v25 = Multitouch::_activePointerThisUpdateCount;
	while(v2 < v25) {
		v7 = Multitouch::_activePointerThisUpdateList[v2];
		if(v7 < 0) {
			v8 = Multitouch::_activePointerThisUpdateList[v2];
		} else if(v7 >= 11) {
			v8 = 11;
		} else {
			v8 = Multitouch::_activePointerThisUpdateList[v2];
		}
		v9 = Multitouch::_pointers[v8].getX();
		if(v7 < 0) {
			v10 = v7;
		} else if(v7 >= 11) {
			v10 = 11;
		} else {
			v10 = v7;
		}
		v11 = Multitouch::_pointers[v10].getY();
		if(this->field_1C.isInside((float)v9, (float)v11) && this->field_41 && !this->field_11) {
			v5 = 1;
			v20 = (float)v11 - this->field_1C.centerY();
			v21 = this->field_1C.centerX();
			v22 = atan2(v20, (float)((float)v9 - v21));
			v23 = (float)(v22 + 3.1416);
			this->field_8 = Mth::sin(v23);
			this->field_4 = Mth::cos(v23);
		}
		pointerId = this->touchAreaModel.getPointerId(v9, v11, v7);
		v13 = pointerId;
		if(pointerId > 99) {
			if(v7 < 0) {
				v14 = v7;
			} else if(v7 >= 11) {
				v14 = 11;
			} else {
				v14 = v7;
			}
			if(Multitouch::_wasPressed[v14]) {
				this->field_A8 = pointerId == 104;
			}
			if(pointerId == 104) {
				if(a2->isInWater()) {
					goto LABEL_30;
				}
				if(v7 >= 0 && v7 >= 11) {
					v7 = 11;
				}
				if(Multitouch::_wasPressed[v7]) {
LABEL_30:
					this->field_D = 1;
					goto LABEL_80;
				}
				if(this->field_41 && !a2->abilities.flying) {
					v24 = 1;
					v6 = 1;
					this->field_8 = this->field_8 + 1.0;
					goto LABEL_35;
				}
LABEL_80:
				v6 = 1;
LABEL_40:
				v15 = 1;
LABEL_59:
				this->field_B0[v13 - 100] = v15; //TODO check
				goto LABEL_60;
			}
			if(pointerId == 100) {
LABEL_35:
				if(a2->isInWater()) {
					this->field_D = 1;
				} else if(!this->field_11) {
					v5 = 1;
				}
				v13 = 100;
				this->field_8 = this->field_8 + 1.0;
				goto LABEL_40;
			}
			if(pointerId == 101) {
				if(!this->field_41) {
					this->field_8 = this->field_8 - 1.0;
					goto LABEL_40;
				}
				goto LABEL_57;
			}
			if(pointerId == 102) {
				if(!this->field_41) {
					v16 = this->field_4 + 1.0;
LABEL_50:
					this->field_4 = v16;
					goto LABEL_40;
				}
			} else {
				if(pointerId != 103) {
					if(pointerId == 106) {
						if(v7 >= 0 && v7 >= 11) {
							v7 = 11;
						}
						if(!Multitouch::_wasReleased[v7]) {
							v15 = Multitouch::_wasReleased[v7];
							goto LABEL_59;
						}
						this->minecraft->soundEngine->playUI("random.click", 1.0, 1.0);
						this->minecraft->screenChooser.setScreen(CHAT_SCREEN);
					}
					goto LABEL_57;
				}
				if(!this->field_41) {
					v16 = this->field_4 - 1.0;
					goto LABEL_50;
				}
			}
LABEL_57:
			v15 = 0;
			goto LABEL_59;
		}
LABEL_60:
		++v2;
	}
	this->field_41 = v5;
	if(v24) {
		if(!this->field_42) {
			this->field_D = 1;
		}
		this->field_42 = 1;
	} else {
		this->field_42 = 0;
	}
	this->field_11 = 0;
	isButtonDown = this->isButtonDown(100);
	if(isButtonDown) {
		this->field_F = (this->field_F | this->field_40) & this->field_A8;
	} else {
		this->field_F = 0;
	}

	v19 = this->isButtonDown(101);
	if ( v19 )
	{
		v19 = (this->field_10 | this->field_40) & this->field_A8;
	}
	this->field_10 = v19;
	if ( a2->abilities.flying && (this->field_F || v19 || v6 && !this->field_41) )
	{
		this->field_8 = 0.0;
		this->field_11 = 1;
	}
	this->field_43 = a2->abilities.flying;
	if ( this->field_E )
	{
		this->field_4 = this->field_4 * 0.3;
		this->field_8 = this->field_8 * 0.3;
	}
	this->field_40 = v6;
}
void TouchscreenInput::render(float a2) {
	this->minecraft->texturesPtr->loadAndBindTexture("gui/gui.png");
	this->rebuild();
}
void TouchscreenInput::setKey(int32_t, bool_t) {
}
void TouchscreenInput::releaseAllKeys() {
	this->field_4 = 0.0;
	this->field_8 = 0.0;
	this->field_B0[0] = 0;
	this->field_B0[1] = 0;
	this->field_B0[2] = 0;
	this->field_B0[3] = 0;
	this->field_B0[4] = 0;
	this->field_B0[5] = 0;
	this->field_B0[6] = 0;
	this->field_B0[7] = 0;
	this->field_40 = 0;
	this->field_A8 = 0;
}
void TouchscreenInput::onConfigChanged(const Config& a2) {
	this->clear();
	float v4 = (float)a2.field_0;
	float v5 = this->minecraft->field_C84 * 16.0;
	float v6 = 8.0;
	float v7 = v5 * 3.0;
	float v8 = (float)((float)a2.field_4 - 8.0) - (float)(v5 * 3.0);
	if(this->options->leftHanded) {
		v6 = (float)(v4 - 8.0) - v7;
	}
	this->field_1C.minX = v6;
	this->field_1C.minY = v8;
	this->field_1C.field_4 = 1;
	this->field_1C.maxX = v6 + v7;
	this->field_1C.maxY = v8 + v7;
	float v10 = v8 + v5;
	float v11 = (float)(v6 + v5) + v5;
	float v13 = v6 + (float)(v5 + v5);
	float v16 = (float)(v8 + v5) + v5;
	float v18 = v8 + (float)(v5 + v5);
	this->rectArea1 = new RectangleArea(1, v6 + v5, v8, v11, v8 + v5);
	this->touchAreaModel.addArea(100, this->rectArea1);
	this->rectArea2 = new RectangleArea(1, v6, v8, v6 + v5, v8 + v5);
	this->rectArea3 = new RectangleArea(1, v13, v8, v13 + v5, v8 + v5);
	this->rectArea5 = new RectangleArea(1, v6 + v5, v8 + v5, v11, v16);
	this->touchAreaModel.addArea(104, this->rectArea5);
	this->rectArea6 = new RectangleArea(1, v11, v18, v6 + v5, v18 + v5);
	this->touchAreaModel.addArea(101, this->rectArea6);
	this->rectArea7 = new RectangleArea(1, v6, v10, v6 + v5, v16);
	this->touchAreaModel.addArea(102, this->rectArea7);
	this->rectArea8 = new RectangleArea(1, v13, v10, v13 + v5, v16);
	this->touchAreaModel.addArea(103, this->rectArea8);
	float v21 = Gui::GuiScale * 18.0;
	if((float)(Gui::GuiScale * 18.0) > (float)(this->minecraft->field_C84 * 10.0)) {
		v21 = this->minecraft->field_C84 * 10.0;
	}
	float v23 = v4 - (float)((float)(v21 + 4.0) + 0.0);
	this->rectArea9 = new RectangleArea(1, v23, 4, v21 + 4, v23 + v21);
	this->touchAreaModel.addArea(106, this->rectArea8);
}
