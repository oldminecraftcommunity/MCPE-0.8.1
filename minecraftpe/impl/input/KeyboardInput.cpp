#include <input/KeyboardInput.hpp>
#include <Options.hpp>
#include <entity/Player.hpp>

KeyboardInput::KeyboardInput(Options* a2) {
	this->strafeInput = 0;
	this->forwardInput = 0;
	this->idkWhatIsThis = 0;
	this->jumping = 0;
	this->sneaking = 0;
	this->flyUpPressed = this->flyDownPressed = this->idkWhatIsThis2 = 0;
	for(int32_t i = 0; i != 10; ++i) {
		this->inputs[i] = 0;
	}
	this->options = a2;
}

void KeyboardInput::tick(Player* a2) {
	this->strafeInput = 0.0f;
	this->forwardInput = 0.0f;

	if(this->inputs[0]) {
		this->forwardInput = 1.0f;
	}
	if(this->inputs[1]) {
		this->forwardInput = this->forwardInput - 1.0f;
	}
	if(this->inputs[2]) {
		this->strafeInput = 1.0f;
	}
	if(this->inputs[3]) {
		this->strafeInput = this->strafeInput - 1.0f;
	}
	this->jumping = this->inputs[4];
	this->sneaking = this->inputs[5];
	if(this->sneaking) {
		this->strafeInput = this->strafeInput * 0.3f;
		this->forwardInput = this->forwardInput * 0.3f;
	}
	if(this->inputs[6]) {
		a2->startCrafting((int32_t)a2->posX, (int32_t)a2->posY, (int32_t)a2->posZ, 0);
	}
}

void KeyboardInput::setKey(int32_t key, bool_t state) {
	int32_t v4 = -1;		  // r3
	if(key == this->options->keyForward.keyCode) v4 = 0;
	if(key == this->options->keyBack.keyCode) v4 = 1;
	if(key == this->options->keyLeft.keyCode) v4 = 2;
	if(key == this->options->keyRight.keyCode) v4 = 3;
	if(key == this->options->keyJump.keyCode) v4 = 4;
	if(key == this->options->keySneak.keyCode) v4 = 5;
	if(key == this->options->keyCrafting.keyCode) v4 = 6;
	if(v4 != -1) this->inputs[v4] = state;
}

void KeyboardInput::releaseAllKeys() {
	this->strafeInput = 0;
	this->forwardInput = 0;
	for(int32_t i = 0; i != 10; ++i) {
		this->inputs[i] = 0;
	}
	this->flyDownPressed = 0;
	this->flyUpPressed = 0;
#ifdef DIFFERENTTWEAKS
	//force release keys to prevent jumping/sneaking in guis
	this->jumping = 0;
	this->sneaking = 0;
#endif
}
