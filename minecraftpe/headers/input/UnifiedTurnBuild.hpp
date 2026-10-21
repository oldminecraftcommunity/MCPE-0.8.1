#pragma once
#include <input/TouchAreaModel.hpp>
#include <util/area/IncludeExcludeArea.hpp>

#include <gui/GuiComponent.hpp>
#include <input/ITurnInput.hpp>
#include <input/IBuildInput.hpp>
#include <util/area/RectangleArea.hpp>
#include <input/Multitouch.hpp>
#include <input/BuildActionIntention.hpp>
#include <entity/Player.hpp>
#include <Minecraft.hpp>
#include <input/IInputHolder.hpp>

struct Minecraft;
struct Entity;
struct Options;
struct IInputHolder;
struct Player;
struct BuildActionIntention;


//usercall <s0> (<s0> <s1>)
static float sub_D65CE970(float a1, float a2) {
	float v2; // s0
	float v3; // s0

	if(a2 <= a1) {
		if(a2 < a1) {
			v3 = a1 - 0.04;
			if(v3 > 1.0) {
				return 1.0;
			} else if(v3 > a2) {
				return v3;
			}
		} else {
			return a1;
		}
	} else {
		v2 = a1 + 0.02;
		if(v2 <= a2) {
			a2 = 0.0;
			if(v2 > 0.0) {
				return v2;
			}
		}
	}
	return a2;
}

struct UnifiedTurnBuild: GuiComponent, ITurnInput, IBuildInput
{
	int32_t field_1C;
	int8_t field_20, field_21, field_22, field_23;
	int32_t field_24, field_28, field_2C, field_30;
	RectangleArea field_34, moveButtonsArea, field_64, hotbarArea, field_94;
	IInputHolder* field_AC;
	int32_t field_B0;
	float field_B4, field_B8;
	int8_t field_BC, field_BD, field_BE, field_BF;
	TouchAreaModel field_C0;
	IncludeExcludeArea allowCameraMovement;
	int32_t field_F0, field_F4;
	double field_F8;
	float field_100, field_104, field_108;
	Player* field_10C;
	double field_110;
	int32_t field_118;
	int8_t field_11C, field_11D, field_11E, field_11F;
	int32_t field_120;
	Options* options;

	UnifiedTurnBuild(int32_t a2, int32_t a3, int32_t a4, float a5, float a6, IInputHolder* a7, Minecraft* a8) :
			field_34(1, -1, -1, 0, 0), moveButtonsArea(1, -1, -1, 0, 0), field_64(1, -1, -1, 0, 0), hotbarArea(1, -1, -1, 0, 0), field_94(1, -1, -1, 0, 0) {
		this->curTime = -1.0;
		this->field_1C = a2;
		this->field_34.field_4 = 1;
		this->field_28 = 0;
		this->field_20 = 0;
		this->field_2C = 0;
		this->field_30 = 0;
		this->field_AC = a7;
		this->field_B4 = 0.0;
		this->field_B8 = 0.0;
		this->field_BC = 0;
		this->field_100 = 0.0;
		this->field_104 = a5;
		this->field_10C = 0;
		this->field_118 = 0;
		this->field_11C = 0;
		this->field_11D = 0;
		this->field_11E = 0;
		this->field_120 = 0;
		this->allowCameraMovement.field_4 = 0;
		this->options = &a8->options;
		this->field_108 = a6;
		this->onConfigChanged(createConfig(a8));
		double TimeS = getTimeS();
		this->field_F8 = TimeS;
		this->field_110 = TimeS;
	}
	static float getSpeedSquared(Entity* a1) {
		float v1; // s13
		float v2; // s15
		float v3; // s14
		v1 = a1->posX - a1->prevX;
		v2 = a1->posY - a1->prevY;
		v3 = a1->posZ - a1->prevZ;
		return (float) (((float) ((v2 * v2)) + (float) ((v1 * v1)))) + (float) ((v3 * v3));
	}

	virtual ~UnifiedTurnBuild() {
	}
	virtual void onConfigChanged(const Config& a2) {
		float v2; // s15
		int v3; // s10
		float maxX; // s12
		float minX; // s11
		float v9; // s10
		float v10; // s13
		float minY; // s12
		float maxY; // s13
		float v13; // s10
		float v14; // s15
		v2 = (float) (a2.height);
		v3 = a2.width;
		maxX = this->moveButtonsArea.maxX;
		minX = this->moveButtonsArea.minX;
		this->field_34.field_4 = 1;
		this->field_34.minX = 0.0;
		this->field_34.minY = 0.0;
		this->field_34.maxY = v2;
		this->field_34.maxX = (float) (v3);
		v9 = (float) (((float) ((maxX - minX)) * 0.05)) + 10.0;
		v10 = maxX + v9;
		minY = this->moveButtonsArea.minY;
		this->moveButtonsArea.maxX = v10;
		maxY = this->moveButtonsArea.maxY;
		this->moveButtonsArea.minX = minX - v9;
		v13 = (float) (((float) ((maxY - minY)) * 0.05)) + 10.0;
		this->moveButtonsArea.maxY = maxY + v13;
		this->field_94.minX = this->field_94.minX - 10.0;
		this->field_94.maxX = this->field_94.maxX + 10.0;
		this->field_94.minY = this->field_94.minY - 10.0;
		v14 = this->field_94.maxY + 10.0;
		this->moveButtonsArea.minY = minY - v13;
		this->field_94.maxY = v14;
		this->allowCameraMovement.clear();
		IArea* vro = &this->field_34; //all 3 are important to be similar to real mc
		this->allowCameraMovement.includeAreas.push_back(vro);
		vro = &this->moveButtonsArea;
		this->allowCameraMovement.excludeAreas.push_back(vro);
		vro = &this->hotbarArea;
		this->allowCameraMovement.excludeAreas.push_back(vro);
		this->field_C0.clear();
		TouchAreaModel::Area* v15 = new TouchAreaModel::Area(&this->allowCameraMovement);
		v15->field_4 = 100;
		this->field_C0.areas.push_back(v15);
	}
	virtual Vec3 getTurnDelta() {
		double TimeS; // r0
		int v5; // r6
		double v6; // d8
		int v7; // r5
		int v8; // r0
		int v9; // r10
		int v10; // r0
		float v11; // s23
		float v12; // s22
		bool movement;
		int v14; // r5
		Player* v15; // r5
		bool v16;
		int v17; // r3
		double v18; // d9
		float v19; // s20
		float v20; // s21
		float v21; // s20
		float v22; // s15
		float v23; // s24
		int v24; // r3
		float v25; // s14
		int v26; // r0
		int v27; // r3
		float v28; // s16
		IInputHolder* v29; // r6
		float v30; // s1
		float v31; // s0
		int v32; // [sp+4h] [bp-5Ch]
		int v33; // [sp+8h] [bp-58h]
		TimeS = getTimeS();
		v5 = 0;
		v33 = Multitouch::_activePointerCount;
		v6 = TimeS;
		while (1) {
			if (v5 >= v33) {
				movement = 0;
				v12 = 0.0;
				v14 = 0;
				v11 = 0.0;
				goto LABEL_30;
			}
			v7 = Multitouch::_activePointerList[v5];
			if (v7 < 0) {
				v8 = Multitouch::_activePointerList[v5];
			} else {
				v8 = v7 >= 11 ? 11 : Multitouch::_activePointerList[v5];
			}
			v9 = Multitouch::_pointers[v8].getX();
			if (v7 < 0) {
				v10 = v7;
			} else {
				v10 = v7 >= 11 ? 11 : v7;
			}
			v32 = Multitouch::_pointers[v10].getY();
			if (this->field_C0.getPointerId(v9, v32, v7) == 100) {
				break;
			}
			++v5;
		}
		v11 = vcvts_n_f32_s32((int16_t) v9, 1u);
		v12 = (float) ((int16_t) (v32)) * -0.5;
		if (v7 >= 0 && v7 >= 11) {
			v7 = 11;
		}
		movement = Multitouch::_pointers[v7].wasFirstMovement();
		if (this->field_BC) {
			v14 = 1;
			LABEL_30: if (this->field_BC) {
				if (!v14) {
					this->field_11C = 0;
					this->field_120 = 0;
				}
			}
			goto LABEL_33;
		}
		v15 = this->field_10C;
		this->field_F8 = v6;
		this->field_100 = 0.0;
		if (v15) {
			v16 = UnifiedTurnBuild::getSpeedSquared(v15) > 0.01;
		} else {
			v16 = 0;
		}
		this->field_120 = 1;
		v17 = !v16;
		this->field_11E = 0;
		this->field_11D = v17;
		if (!v17) {
			if (v15) {
				if (v15->canUseCarriedItemWhileMoving()) {
					this->field_11E = 1;
					this->field_11D = 1;
				}
			}
		}
		v14 = 1;
		this->field_11C = 0;
		LABEL_33: v18 = this->field_F8;
		if (this->field_1C != 2) {
			goto LABEL_55;
		}
		if (this->field_BC) {
			if (!v14) {
				goto LABEL_56;
			}
			LABEL_38: v19 = this->field_108;
			v20 = v19 * ITurnInput::linearTransform(v11 - this->field_B4, 0.0, 1.0, 0);
			v21 = v19 * ITurnInput::linearTransform(v12 - this->field_B8, 0.0, 1.0, 0);
			v22 = fabsf(v20) + fabsf(v21);
			if (v22 > this->field_104) {
				v22 = 0.0;
				v21 = 0.0;
				v20 = 0.0;
			}
			v23 = v22 + this->field_100;
			v24 = this->field_120;
			this->field_100 = v23;
			if (v24 == 1 && v23 >= 20.0) {
				this->field_120 = 2;
			}
			if (this->field_120 == 1) {
				v25 = v6 - v18;
				if (v25 >= 0.4) {
					if (this->field_10C) {
						v26 = UnifiedTurnBuild::getSpeedSquared(this->field_10C) > 0.01;
					} else {
						v26 = 0;
					}
					if (this->field_11E || v23 <= 20.0 && !v26) {
						this->field_120 = 3;
						this->field_11D = 1;
					} else {
						this->field_120 = 2;
					}
				}
			}
			if (movement) {
				v21 = 0.0;
				v20 = 0.0;
			}
			this->field_B4 = v11;
			this->field_B8 = v12;
		} else {
			if (v14) {
				this->field_B4 = v11;
				this->field_B8 = v12;
				goto LABEL_38;
			}
			LABEL_55: this->field_120 = 0;
			LABEL_56: v21 = 0.0;
			v20 = 0.0;
		}
		if (!this->field_11D) {
			this->field_AC->field_C = -0.05;
			goto LABEL_67;
		}
		v27 = this->field_120;
		switch (v27) {
		case 1:
			v28 = v6 - v18;
			this->field_AC->field_C = (float) ((v28 / 0.4)) * (float) ((v28 / 0.4));
			break;
		case 3:
			v29 = this->field_AC;
			v30 = 1.0;
			v31 = v29->field_C;
			LABEL_65: v29->field_C = sub_D65CE970(v31, v30);
			break;
		case 2:
		case 0:
			v29 = this->field_AC;
			v30 = 0.0;
			v31 = v29->field_C;
			goto LABEL_65;
		}
		LABEL_67: this->field_BC = v14;
		return Vec3(v20, -v21, 0);
	}
	virtual bool_t tickBuild(Player* a2, BuildActionIntention* a3) {
		this->field_10C = a2;
		if (this->field_120 == 3) {
			if (this->field_11C && a2->isUsingItem()) {
				a3->field_0 = this->field_11E ? 16 : 18;
				return 1;
			} else {
				a3->field_0 = this->field_11E ? 16 : 20;
				this->field_11C = 1;
				return 1;
			}
		} else {
			bool ret = 0;
			Multitouch::_index = -1;
			double timeS = getTimeS();
			this->field_20 = 0;
			while (++Multitouch::_index < Multitouch::_inputs.size()) {
				MouseAction* cur = &Multitouch::_inputs[Multitouch::_index];
				if (cur->evButton) {
					if (this->field_C0.getPointerId(cur->field_0, cur->field_2, (uint8_t) cur->field_A) != 100) {
						continue;
					}

					this->field_20 = 1;
					uint8_t state = (uint8_t) cur->state;
					if (this->field_100 > 20 || cur->state || ret) {
						if (state != 1) {
							continue;
						}
						this->field_110 = timeS;
						this->field_118 = 0;
					} else {
						if (this->field_120 <= 1) {
							float v11 = timeS - this->field_110;
							if (v11 >= 0 && v11 < 0.25) {
								ret = 1;
								a3->field_0 = 9;
							}
						}
						state = 0;
					}
					this->field_120 = state;
				}
			}
			Multitouch::_index -= 1; //TODO check
			return ret;
		}
	}

};
