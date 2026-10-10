#include <gui/Screen.hpp>
#include <Minecraft.hpp>
#include <gui/GuiElement.hpp>
#include <gui/buttons/Button.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/states/DisableState.hpp>
#include <unigl.hpp>
#include <math/Mth.hpp>
#include <util/Color4.hpp>
#include <input/Mouse.hpp>
#include <sound/SoundEngine.hpp>
#include <input/Keyboard.hpp>
#include <gui/elements/TextBox.hpp>

static char_t* panorama_images[] = {
	"gui/background/panorama_0.png",
	"gui/background/panorama_1.png",
	"gui/background/panorama_2.png",
	"gui/background/panorama_3.png",
	"gui/background/panorama_4.png",
	"gui/background/panorama_5.png"
};

Screen::Screen(){
	this->width = 1;
	this->height = 1;
	this->field_C = 0;
	this->minecraft = 0;
	this->field_44 = 0;
	this->font = 0;
	this->lastPressedButton = 0;
}

void Screen::updateTabButtonSelection(){
	if(!this->minecraft->useTouchscreen()){
		for(int32_t i = 0; i < this->field_2C.size(); ++i) {
			Button* b = this->field_2C[i];
			b->text = (i - this->field_44) == 0;
		}
	}
}
void Screen::init(struct Minecraft* mc, int32_t w, int32_t h){
	this->minecraft = mc;
	this->height = h;
	this->font = mc->font;
	this->width = w;
	this->init();
	this->setupPositions();
	this->updateTabButtonSelection();
}
void Screen::setSize(int32_t w, int32_t h){
	this->width = w;
	this->height = h;
	this->setupPositions();
}

void Screen::render(int32_t x, int32_t y, float){
	if(this->supppressedBySubWindow()){
		for(auto&& p: this->elements) {
			p->topRender(this->minecraft, x, y);
		}
	}else{
		for(auto&& p: this->elements) {
			p->render(this->minecraft, x, y);
		}

		for(int i = 0; i < this->buttons.size(); ++i){
			Button* b = this->buttons[i];
			if(!b->isOveridingScreenRendering()){
				b->render(this->minecraft, x, y);
			}
		}
	}
}
void Screen::init(){}
void Screen::setupPositions(void){
	for(auto&& p: this->elements) {
		p->setupPositions();
	}
}
void Screen::updateEvents(){
	if(!this->field_C){
		while(Mouse::next()){
			this->mouseEvent();
		}

		while ( Keyboard::_index++ < Keyboard::_inputs.size() ){
			this->keyboardEvent();
		}
		while ( Keyboard::_textIndex++ < Keyboard::_inputText.size() ){
			this->keyboardTextEvent();
		}
	}
}
void Screen::mouseEvent(void) {
	MouseAction* ma = Mouse::getEvent();
	if(ma->isButton()) {
		bool_t b = Mouse::getEventButtonState();
		int32_t v5 = this->width * ma->field_0 / this->minecraft->width;
		int32_t v6 = ma->field_2 * this->height / this->minecraft->height;
		int32_t evb = Mouse::getEventButton();
		if(b){
			this->mouseClicked(v5, v6-1, evb);
		}else{
			this->mouseReleased(v5, v6-1, evb);
		}
	}
}
void Screen::keyboardEvent(){
	if(Keyboard::_inputs[Keyboard::_index].field_0) {
		this->keyPressed(Keyboard::_inputs[Keyboard::_index].field_4);
	}
}
void Screen::keyboardTextEvent(){
	this->keyboardNewChar(Keyboard::_inputText[Keyboard::_textIndex].field_0, Keyboard::_inputText[Keyboard::_textIndex].field_4);
}
bool_t Screen::handleBackEvent(bool_t a2){
	for(auto&& p: this->elements) {
		if(p->backPressed(this->minecraft, a2)) return 1;
	}
	return 0;
}
void Screen::tick(){
	for(auto&& p: this->elements) {
		p->tick(this->minecraft);
	}
}

void Screen::renderBackground(int32_t a2){
	if(this->renderGameBehind()){
		this->fill(0, 0, this->width, this->height, 0x7f000000);
	}else{
		this->renderDirtBackground(a2);
	}
}
void Screen::renderDirtBackground(int32_t a2){
	this->minecraft->texturesPtr->loadAndBindTexture("gui/background.png");
	glColor4f(1, 1, 1, 1);
	float v5 = a2;
	Tesselator::instance.begin(4);
	Tesselator::instance.color(0x404040);
	Tesselator::instance.vertexUV(0, this->height, 0, 0, v5 + (float)this->height*0.03125);
	Tesselator::instance.vertexUV(this->width, this->height, 0, (float)this->width*0.03125, v5 + (float)this->height*0.03125);
	float v6 = v5+0;
	Tesselator::instance.vertexUV(this->width, 0, 0, (float)this->width*0.03125, v6);
	Tesselator::instance.vertexUV(0, 0, 0, 0, v6);
	Tesselator::instance.draw(1);
}

static float dword_D6E05C20 = 0;

void Screen::renderMenuBackground(float a2){
	float v4 = this->minecraft->field_D34;
	dword_D6E05C20 += v4*30;
	for(char_t* img : panorama_images){
		this->minecraft->texturesPtr->loadTexture(img, 1, 1);
	}
	{
		DisableState be2(0xBE2);
		DisableState b44(0xB44);
		DisableState b71(0xB71);
		glMatrixMode(0x1701);
		glPushMatrix();
		glLoadIdentity();
		gluPerspective(120.0, 1.0, 0.05, 10.0);
		glMatrixMode(0x1700u);
		glPushMatrix();
		glLoadIdentity();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glRotatef(180.0, 1.0, 0.0, 0.0);
		glRotatef(Mth::sin((float)(a2+dword_D6E05C20) / 400)*25 + 20, 1, 0, 0);
		glRotatef(-(float)((float)(a2+dword_D6E05C20) * 0.1), 0.0, 1.0, 0.0);
		for(int v8 = 0; v8 != 6; ++v8){
			glPushMatrix();

			if(v8 == 1) glRotatef(90, 0, 1, 0);
			if(v8 == 2) glRotatef(180, 0, 1, 0);
			if(v8 == 3) glRotatef(-90, 0, 1, 0);
			if(v8 == 4) glRotatef(90, 1, 0, 0);
			if(v8 == 5) glRotatef(-90, 1, 0, 0);

			this->minecraft->texturesPtr->loadAndBindTexture(panorama_images[v8]);
			Tesselator::instance.begin(4);
			Tesselator::instance.vertexUV(-1, -1, 1, 0, 0);
			Tesselator::instance.vertexUV(1, -1, 1, 1, 0);
			Tesselator::instance.vertexUV(1, 1, 1, 1, 1);
			Tesselator::instance.vertexUV(-1, 1, 1, 0, 1);
			Tesselator::instance.draw(1);
			glPopMatrix();
		}
		glMatrixMode(0x1701u);
		glPopMatrix();
		glMatrixMode(0x1700u);
		glPopMatrix();
	} //disablestate constructors are called here

	this->fillGradient(0, 0, this->width, this->height, Color4(1, 1, 1, 0.35).toARGB(), Color4(0, 0, 0, 0.35).toARGB());
}

bool_t Screen::renderGameBehind(){
	return this->minecraft->options.graphics;
}
bool_t Screen::hasClippingArea(struct IntRectangle&){
	return 0;
}
bool_t Screen::isPauseScreen(){
	return 1;
}
bool_t Screen::isErrorScreen(){
	return 0;
}
bool_t Screen::isInGameScreen(){
	return 1;
}
bool_t Screen::closeOnPlayerHurt(){
	return 0;
}

void Screen::lostFocus(){
	for(TextBox* tb: this->field_20) {
		tb->loseFocus(this->minecraft);
	}
}
void Screen::toGUICoordinate(int32_t& x, int32_t& y){
	x = this->width*x / this->minecraft->width;
	y = this->height*y / this->minecraft->height - 1;
}

bool_t Screen::supppressedBySubWindow(){
	bool ret = 0;
	for(auto&& e: this->elements) {
		if(e->suppressOtherGUI()) ret = 1;
	}
	return ret;
}

void Screen::setTextboxText(const std::string& a2){
	for(auto&& e : this->elements){
		if(e->suppressOtherGUI()){
			e->setTextboxText(a2);
		}
	}
}

void Screen::mouseClicked(int32_t a2, int32_t a3, int32_t a4) {
	if(this->supppressedBySubWindow()) {
		for(auto&& e: this->elements) {
			if(e->suppressOtherGUI()) {
				e->focusuedMouseClicked(this->minecraft, a2, a3, a4);
			}
		}
	} else {
		for(auto&& e: this->elements) {
			e->mouseClicked(this->minecraft, a2, a3, a4);
		}

		if(a4 == 1) {
			for(int32_t i = 0; i < this->buttons.size(); ++i) {
				Button* b = this->buttons[i];
				if(b->active) {
					if(b->clicked(this->minecraft, a2, a3)) {
						b->setPressed();
						this->lastPressedButton = b;
					}
				}
			}
		}
	}
}
void Screen::mouseReleased(int32_t a2, int32_t a3, int32_t a4) {
	if(this->supppressedBySubWindow()) {
		for(auto&& e : this->elements){
			if(e->suppressOtherGUI()) {
				e->focusuedMouseReleased(this->minecraft, a2, a3, a4);
			}
		}
	} else {
		for(auto&& e : this->elements){
			e->mouseReleased(this->minecraft, a2, a3, a4);
		}

		if(this->lastPressedButton) {
			if(a4 == 1) {
				for(int32_t i = 0; i < this->buttons.size(); ++i) {
					Button* b = this->buttons[i];
					if(this->lastPressedButton == b) {
						if(this->lastPressedButton->clicked(this->minecraft, a2, a3)) {
							this->buttonClicked(this->lastPressedButton);
							this->minecraft->soundEngine->playUI("random.click", 1, 1);
							this->lastPressedButton->released(a2, a3);
						}
					}
				}
				this->lastPressedButton = 0;
			}
		}
	}
}
void Screen::keyPressed(int32_t a2) {
	for(auto&& e: this->elements) {
		e->keyPressed(this->minecraft, a2);
	}
	if(!this->minecraft->useTouchscreen()) {
		int v7 = this->field_2C.size();
		if(v7) {
			if(a2 == this->minecraft->options.keyMenuNext.keyCode) {
				int v9 = this->field_44 + 1;
				if(v9 == v7) v9 = 0;
				this->field_44 = v9;
			}
			if(a2 == this->minecraft->options.keyMenuPrevious.keyCode) {
				int v10 = this->field_44 - 1;
				this->field_44 = v10;
				if(v10 == -1) {
					this->field_44 = v7 - 1;
				}
			}

			if(a2 == this->minecraft->options.keyMenuOk.keyCode) {
				Button* b = this->field_2C[this->field_44];
				if(b->active) {
					this->minecraft->soundEngine->playUI("random.click", 1, 1);
					this->buttonClicked(b);
				}
			}
			this->updateTabButtonSelection();
		}
	}
}
void Screen::keyboardNewChar(const std::string& a2, bool_t a3) {
	for(auto&& e: this->elements) {
		if(e->suppressOtherGUI()) {
			e->keyboardNewChar(this->minecraft, a2, a3);
		}
	}
}
