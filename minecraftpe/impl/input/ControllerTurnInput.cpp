#include <input/ControllerTurnInput.hpp>
#include <input/Controller.hpp>
#include <input/Mouse.hpp>
ControllerTurnInput::ControllerTurnInput(){
	this->curTime = -1.0;
	this->field_20 = 0;
	this->field_18 = 0.0;
	this->field_1C = 0.0;
	this->field_10 = 2;
	this->field_14 = 2;
}
ControllerTurnInput::~ControllerTurnInput() {
}
Vec3 ControllerTurnInput::getTurnDelta() {
#ifdef PCTWEAKS
	return Vec3(Mouse::getDX() * 0.3, Mouse::getDY() * 0.3, 0);
#endif

	bool_t isTouched; // r0
	int32_t v5; // r3
	int32_t v6; // r5
	float dt; // s19
	float v8; // s18
	float v9; // s17
	float v10; // r0
	float v11; // r1
	float v12; // r2
	float v13; // s14
	float v14; // r0
	float v15; // s16
	float v16; // s15
	float v17; // r0
	float v18; // r0
	float v19; // r0

	isTouched = Controller::isTouched(this->field_14);
	v5 = this->field_10;
	v6 = isTouched;
	if(v5 == 1) {
		dt = this->getDeltaTime();
		if(v6) {
			v8 = Controller::getX(this->field_14);
			v9 = Controller::getY(this->field_14);
		} else {
			v8 = this->field_18 * 0.7;
			v9 = this->field_1C * 0.7;
		}
		v10 = ITurnInput::linearTransform(v8, 0.1, 250.0, 0);
		v11 = 0.1;
		v12 = 200.0;
		v13 = v10;
		v14 = v9;
		v15 = v13 * dt;
		goto LABEL_14;
	}
	if(v5 == 2 && (this->field_20 || isTouched)) {
		v8 = Controller::getX(this->field_14);
		v17 = Controller::getY(this->field_14);
		v9 = v17;
		if(!this->field_20) {
			this->field_18 = v8;
			this->field_1C = v17;
		}
		if(v6) {
			dt = 100.0;
			v18 = ITurnInput::linearTransform(v8 - this->field_18, 0.0, 1.0, 0);
			v11 = 0.0;
			v12 = 1.0;
			v15 = v18 * 100.0;
			v14 = v9 - this->field_1C;
LABEL_14:
			v19 = ITurnInput::linearTransform(v14, v11, v12, 0);
			this->field_18 = v8;
			this->field_1C = v9;
			v16 = v19 * dt;
			goto LABEL_15;
		}
	}
	v16 = 0.0;
	v15 = 0.0;
LABEL_15:
	this->field_20 = v6;
	return Vec3(v15, -v16, 0); //TOOD returns something with 2 params
}
