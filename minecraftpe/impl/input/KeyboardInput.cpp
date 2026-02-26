#include <input/KeyboardInput.hpp>
#include <Options.hpp>
#include <entity/Player.hpp>

KeyboardInput::KeyboardInput(Options* a2) {
	this->strafeInput = 0;
	this->forwardInput = 0;
	this->field_8 = 0;
	this->jumpingMaybe = 0;
	this->sneakingMaybe = 0;
	this->field_B = this->field_C = this->field_D = 0;
	for(int32_t i = 0; i != 10; ++i) {
		this->inputs[i] = 0;
	}
	this->options = a2;
}

KeyboardInput::~KeyboardInput() {
}
void KeyboardInput::tick(Player* a2) {
	this->strafeInput = 0.0;
	this->forwardInput = 0.0;
	if(this->inputs[0]) {
		this->forwardInput = 1.0;
	}
	if(this->inputs[1]) {
		this->forwardInput = this->forwardInput - 1.0;
	}
	if(this->inputs[2]) {
		this->strafeInput = 1.0;
	}
	if(this->inputs[3]) {
		this->strafeInput = this->strafeInput - 1.0;
	}
	this->jumpingMaybe = this->inputs[4];
	this->sneakingMaybe = this->inputs[5];
	if(this->inputs[5]) {
		this->strafeInput = this->strafeInput * 0.3;
		this->forwardInput = this->forwardInput * 0.3;
	}
	if(this->inputs[6]) {
		a2->startCrafting((int32_t)a2->posX, (int32_t)a2->posY, (int32_t)a2->posZ, 0);
	}
}
void KeyboardInput::setKey(int32_t a2, bool_t a3) {
	Options* options; // r4
	int32_t v4;		  // r3
	int32_t keyCode;  // r5
	int32_t v6;		  // r4

	options = this->options;
	if(a2 == options->keyForward.keyCode) {
		v4 = 0;
	} else {
		v4 = -1;
	}
	if(a2 == options->keyBack.keyCode) {
		v4 = 1;
	}
	if(a2 == options->keyLeft.keyCode) {
		v4 = 2;
	}
	if(a2 == options->keyRight.keyCode) {
		v4 = 3;
	}
	if(a2 == options->keyJump.keyCode) {
		v4 = 4;
	}
	keyCode = options->keySneak.keyCode;
	v6 = options->keyCrafting.keyCode;
	if(a2 == keyCode) {
		v4 = 5;
	}
	if(a2 == v6) {
		v4 = 6;
		goto LABEL_18;
	}
	if(v4 != -1) {
LABEL_18:
		this->inputs[v4] = a3;
	}
}
void KeyboardInput::releaseAllKeys() {
	this->strafeInput = 0;
	this->forwardInput = 0;
	for(int32_t i = 0; i != 10; ++i) {
		this->inputs[i] = 0;
	}
	this->field_C = 0;
	this->field_B = 0;
}
