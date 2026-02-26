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
	this->field_20 = 0;
	this->mc = a2;
	this->field_58 = 0;
	Tesselator::instance.color(0xC0C0C0, 128);
	_col_D6E06628 = Tesselator::instance.getColor();
	Tesselator::instance.color(0xFFFFFF, 128);
	_col_D6E0662C = Tesselator::instance.getColor();
	this->onConfigChanged(createConfig(a2));
}

XperiaPlayInput::~XperiaPlayInput() {
}
void XperiaPlayInput::tick(Player* player){
	bool_t sneakingMaybe; // r6
	bool_t jumpingMaybe; // r3
	bool_t v6; // r2
	int32_t isTouched; // r0
	bool_t v8; // r3
	bool_t v9; // r5
	int32_t v10; // r5
	int32_t v11; // r0

	sneakingMaybe = this->sneakingMaybe;
	KeyboardInput::tick(player);
	jumpingMaybe = this->jumpingMaybe;
	this->sneakingMaybe = sneakingMaybe;
	v6 = jumpingMaybe && this->inputs[0];
	this->field_B = v6;
	if ( jumpingMaybe )
	{
		jumpingMaybe = this->inputs[1];
	}
	this->field_C = jumpingMaybe;
	if ( jumpingMaybe || v6 )
	{
		if ( player )
		{
			if ( player->abilities.flying )
			{
				this->forwardInput = 0.0;
			}
		}
	}
	isTouched = Controller::isTouched(1);
	if ( isTouched )
	{
		if ( !this->field_20 )
		{
			this->sneakingMaybe ^= 1u;
		}
	}
	v8 = this->sneakingMaybe;
	this->field_20 = isTouched;
	if ( v8 )
	{
		this->strafeInput = this->strafeInput * 0.3;
		this->forwardInput = this->forwardInput * 0.3;
	}
	v9 = this->field_58;
	this->field_58 = 0;
	if ( Mouse::isButtonDown(1) )
	{
		v10 = Mouse::getX();
		v11 = Mouse::getY();
		if ( this->field_40.isInside((float)v10, (float)v11) )
		{
			this->field_58 = 1;
		}
	}
	else if ( v9 )
	{
		this->mc->soundEngine->playUI("random.click", 1.0, 1.0);
		this->mc->screenChooser.setScreen(CHAT_SCREEN);
	}
}
void XperiaPlayInput::render(float a2) {
	int32_t v3;	  // r1
	float v4; // s17
	float v5; // s19
	float v6; // s18
	float v7; // s16

	if(!this->options->hideGUI && !this->mc->currentScreen) {
		Tesselator::instance.begin(0);
		if(this->field_58) {
			v3 = _col_D6E06628;
		} else {
			v3 = _col_D6E0662C;
		}
		Tesselator::instance.colorABGR(v3);
		v4 = Gui::InvGuiScale * this->field_28.minX;
		v5 = Gui::InvGuiScale * this->field_28.maxY;
		v6 = Gui::InvGuiScale * this->field_28.maxX;
		v7 = Gui::InvGuiScale * this->field_28.minY;
		Tesselator::instance.vertexUV(v4, v5, 0.0, 0.78125, 0.39062);
		Tesselator::instance.vertexUV(v6, v5, 0.0, 0.85156, 0.39062);
		Tesselator::instance.vertexUV(v6, v7, 0.0, 0.85156, 0.32031);
		Tesselator::instance.vertexUV(v4, v7, 0.0, 0.78125, 0.32031);
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

	v2 = a2.field_0;
	field_C84 = this->mc->field_C84;
	v4 = Gui::GuiScale;
	this->field_28.field_4 = 1;
	this->field_40.field_4 = 1;
	v5 = field_C84 * 10.0;
	v6 = v4 * 18.0;
	this->field_28.minY = 4.0;
	if((float)(v4 * 18.0) > v5) {
		v6 = v5;
	}
	v7 = v6 + 4.0;
	this->field_28.maxY = v6 + 4.0;
	v8 = (float)v2 - (float)(v6 + 4.0);
	this->field_28.minX = v8;
	v9 = v8 + v6;
	v10 = v6 * 0.25;
	this->field_28.maxX = v9;
	this->field_40.minX = v8 - v10;
	this->field_40.minY = 4.0 - v10;
	this->field_40.maxX = v9 + v10;
	this->field_40.maxY = v7 + v10;
}
