#include <input/XperiaPlayInput.hpp>
#include <Config.hpp>
#include <Minecraft.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <entity/Player.hpp>
#include <input/Mouse.hpp>
#include <sound/SoundEngine.hpp>
#include <input/Controller.hpp>

static int32_t _col_D6E06628 = 0;
static int32_t _col_D6E0662C = 0;

XperiaPlayInput::XperiaPlayInput(Minecraft* a2, Options* a3)
	: KeyboardInput(a3)
	, field_28(1, 0, 0, 0, 0)
	, field_40(1, 0, 0, 0, 0) {
	this->sneakTouched = 0;
	this->mc = a2;
	this->chatScreenPressed = 0;
	Tesselator::instance.color(0xC0C0C0, 128);
	_col_D6E06628 = Tesselator::instance.getColor();
	Tesselator::instance.color(0xFFFFFF, 128);
	_col_D6E0662C = Tesselator::instance.getColor();
	this->onConfigChanged(createConfig(a2));
}


void XperiaPlayInput::tick(Player* player){

	bool sneaking = this->sneaking;
	KeyboardInput::tick(player);
	this->sneaking = sneaking;
	this->flyUpPressed = this->jumping && this->inputs[0];
	this->flyDownPressed = this->jumping && this->inputs[1];

	if(this->flyDownPressed || this->flyUpPressed) {
		if(player) {
			if(player->abilities.flying) {
				this->forwardInput = 0.0;
			}
		}
	}
	bool sneakTouched = Controller::isTouched(1);
	if(sneakTouched) {
		if(!this->sneakTouched) {
			this->sneaking = !this->sneaking;
		}
	}
	this->sneakTouched = sneakTouched;

	if(this->sneaking) {
		this->strafeInput = this->strafeInput * 0.3f;
		this->forwardInput = this->forwardInput * 0.3f;
	}

	bool v9 = this->chatScreenPressed;
	this->chatScreenPressed = 0;
	if(Mouse::isButtonDown(1)) {
		if(this->field_40.isInside(Mouse::getX(), Mouse::getY())) {
			this->chatScreenPressed = 1;
		}
	} else if(v9) {
		this->mc->soundEngine->playUI("random.click", 1.0f, 1.0f);
		this->mc->screenChooser.setScreen(CHAT_SCREEN);
	}
}
void XperiaPlayInput::render(float a2) {

	if(!this->options->hideGUI && !this->mc->currentScreen) {
		Tesselator::instance.begin(0);
		int32_t v3;
		if(this->chatScreenPressed) {
			v3 = _col_D6E06628;
		} else {
			v3 = _col_D6E0662C;
		}
		Tesselator::instance.colorABGR(v3);
		float v4 = Gui::InvGuiScale * this->field_28.minX;
		float v5 = Gui::InvGuiScale * this->field_28.maxY;
		float v6 = Gui::InvGuiScale * this->field_28.maxX;
		float v7 = Gui::InvGuiScale * this->field_28.minY;
		Tesselator::instance.vertexUV(v4, v5, 0.0f, 0.78125f, 0.39062f);
		Tesselator::instance.vertexUV(v6, v5, 0.0f, 0.85156f, 0.39062f);
		Tesselator::instance.vertexUV(v6, v7, 0.0f, 0.85156f, 0.32031f);
		Tesselator::instance.vertexUV(v4, v7, 0.0f, 0.78125f, 0.32031f);
		this->mc->texturesPtr->loadAndBindTexture("gui/gui.png");
		Tesselator::instance.draw(1);
	}
}
void XperiaPlayInput::onConfigChanged(const Config& a2) {
	int32_t v2;		 // s12
	float field_C84; // s14
	float v4;		 // s13
	float v5;		 // s14
	float v6;		 // s15
	float v7;		 // s14
	float v8;		 // s12
	float v9;		 // s11
	float v10;		 // s15

	v2 = a2.width;
	field_C84 = this->mc->pixelsPerMillimeter;
	v4 = Gui::GuiScale;
	this->field_28.field_4 = 1;
	this->field_40.field_4 = 1;
	v5 = field_C84 * 10.0f;
	v6 = v4 * 18.0f;
	this->field_28.minY = 4.0f;
	if((float)(v4 * 18.0f) > v5) {
		v6 = v5;
	}
	v7 = v6 + 4.0f;
	this->field_28.maxY = v6 + 4.0f;
	v8 = (float)v2 - (float)(v6 + 4.0f);
	this->field_28.minX = v8;
	v9 = v8 + v6;
	v10 = v6 * 0.25f;
	this->field_28.maxX = v9;
	this->field_40.minX = v8 - v10;
	this->field_40.minY = 4.0f - v10;
	this->field_40.maxX = v9 + v10;
	this->field_40.maxY = v7 + v10;
}
