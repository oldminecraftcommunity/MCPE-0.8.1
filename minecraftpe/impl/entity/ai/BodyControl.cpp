#include <entity/ai/BodyControl.hpp>
#include <entity/Mob.hpp>
#include <math/Mth.hpp>
#include <math.h>

BodyControl::BodyControl(Mob* a2) {
	this->controlledEntity = a2;
	this->field_4 = 0;
	this->field_8 = 0;
}
void BodyControl::clientTick() {
	Mob* controlledEntity; // r4
	float v3;			   // s14
	float v4;			   // s16
	float v5;			   // r0
	float v6;			   // s15
	Mob* v7;			   // r4
	float v8;			   // s16
	float v9;			   // r0
	float v10;			   // s15
	float v11;			   // s16
	int32_t v12;			   // r3
	float v13;			   // s15
	float headYaw;		   // s17
	float v15;			   // r0
	float v16;			   // s15

	controlledEntity = this->controlledEntity;
	v3 = this->controlledEntity->posX - this->controlledEntity->prevX;
	if((float)((float)((float)(this->controlledEntity->posZ - this->controlledEntity->prevZ) * (float)(this->controlledEntity->posZ - this->controlledEntity->prevZ)) + (float)(v3 * v3)) <= 0.00000025) {
		v11 = 75.0;
		if(fabsf(controlledEntity->headYaw - this->field_8) <= 15.0) {
			v12 = this->field_4;
			this->field_4 = v12 + 1;
			if(v12 + 1 > 10) {
				v13 = 1.0 - (float)((float)(v12 - 9) / 10.0);
				if(v13 < 0.0) {
					v13 = 0.0;
				}
				v11 = v13 * 75.0;
			}
		} else {
			this->field_4 = 0;
			this->field_8 = controlledEntity->headYaw;
		}
		headYaw = controlledEntity->headYaw;
		v15 = Mth::wrapDegrees(headYaw - controlledEntity->field_124);
		v16 = -v11;
		if(v15 >= (float)-v11) {
			v16 = v15;
		}
		if(v16 < v11) {
			v11 = v16;
		}
		controlledEntity->field_124 = headYaw - v11;
		this->controlledEntity->yaw = this->controlledEntity->field_124;
	} else {
		v4 = controlledEntity->field_124;
		v5 = Mth::wrapDegrees(controlledEntity->yaw - v4);
		v6 = v5;
		if(v5 > 10.0) {
			v6 = 10.0;
		} else if(v5 < -10.0) {
			v6 = -10.0;
		}
		controlledEntity->field_124 = v4 + v6;
		v7 = this->controlledEntity;
		v8 = this->controlledEntity->field_124;
		v9 = Mth::wrapDegrees(v8 - this->controlledEntity->headYaw);
		v10 = v9;
		if(v9 < -75.0) {
			v10 = -75.0;
		} else if(v9 >= 75.0) {
			v10 = 75.0;
		}
		v7->headYaw = v8 - v10;
		this->field_8 = this->controlledEntity->headYaw;
		this->field_4 = 0;
	}
}
