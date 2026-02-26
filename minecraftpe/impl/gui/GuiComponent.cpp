#include <gui/GuiComponent.hpp>
#include <rendering/Tesselator.hpp>
#include <GL/gl.h>
#include <rendering/states/DisableState.hpp>
#include <rendering/Font.hpp>

GuiComponent::GuiComponent(){
	this->zLayer = 0;
}

void GuiComponent::blit(float x, float y, int32_t a4, int32_t a5, float a6, float a7, int32_t a8, int32_t a9){
	int32_t v10, v14;
	float v15, v16;

	v10 = a8;
	v14 = a9;
	if(!a8) v10 = (int32_t)a6;
	if(!a9) v14 = (int32_t)a7;

	Tesselator::instance.begin(4);
	v15 = (float)(v14+a5) * 0.0039062;
	Tesselator::instance.vertexUV(x, y+a7, this->zLayer, (float)a4*0.0039062, v15);
	v16 = (float)(v10+a4) * 0.0039062;
	Tesselator::instance.vertexUV(x+a6, y+a7, this->zLayer, v16, v15);
	Tesselator::instance.vertexUV(x+a6, y, this->zLayer, v16, (float)a5*0.0039062);
	Tesselator::instance.vertexUV(x, y, this->zLayer,(float)a4*0.0039062, (float)a5*0.0039062);
	Tesselator::instance.draw(1);
}


void GuiComponent::blit(int32_t x, int32_t y, int32_t a4, int32_t a5, int32_t a6, int32_t a7, int32_t a8, int32_t a9){
	int32_t v13, v14, v15;
	float v16, v17;

	v13 = a8;
	v14 = a9;
	Tesselator::instance.begin(4);
	if(!a9) v14 = a7;
	v15 = a7+y;
	v16 = (float) x;
	if(!a8) v13 = a6;
	Tesselator::instance.vertexUV(x, v15, this->zLayer, (float)a4*0.0039062, (float)(a5+v14)*0.0039062);
	v17 = (float)(x+a6);
	Tesselator::instance.vertexUV(v17, v15, this->zLayer, (float)(v13+a4)*0.0039062, (float)(a5+v14)*0.0039062);
	Tesselator::instance.vertexUV(v17, y, this->zLayer, (float)(v13+a4)*0.0039062, (float)a5*0.0039062);
	Tesselator::instance.vertexUV(v16, y, this->zLayer, (float)a4*0.0039062, (float)a5*0.0039062);
	Tesselator::instance.draw(1);
}
void GuiComponent::drawCenteredString(struct Font* font, const std::string& s, int32_t x, int32_t y, int32_t color){
	int32_t w = font->width(s);
	font->drawShadow(s, (float)(x-w/2), y, color);
}
void GuiComponent::drawRect(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t color, int32_t a7){
	this->fill(a2, a3, a4, a3 + a7, color);
	this->fill(a2, a5 - a7, a4, a5, color);
	this->fill(a2, a3, a2 + a7, a5, color);
	this->fill(a4 - a7, a3, a4, a5, color);
}
void GuiComponent::drawRect(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t color1, int32_t color2, int32_t color3, int32_t color4, int32_t a10){
	this->fill(a2, a3, a2 + a10, a5, color3);
	this->fill(a4 - a10, a3, a4, a5, color4);
	this->fill(a2, a3, a4, a3 + a10, color1);
	this->fill(a2, a5 - a10, a4, a5, color2);
}
void GuiComponent::drawString(struct Font* font, const std::string& s, int32_t x, int32_t y, int32_t color){
	font->drawShadow(s, x, y, color);
}
void GuiComponent::fill(float a2, float a3, float a4, float a5, int32_t color){
	DisableState state(0xDE1);
	Tesselator::instance.begin(GL_TRIANGLES);
	Tesselator::instance.colorABGR((color&0xff00ff00) | ((color&0xff) << 16) | ((color & 0xff0000) >> 16));
	Tesselator::instance.vertex(a2, a5, 0);
	Tesselator::instance.vertex(a4, a5, 0);
	Tesselator::instance.vertex(a4, a3, 0);
	Tesselator::instance.vertex(a2, a3, 0);
	Tesselator::instance.draw(1);
}
void GuiComponent::fill(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t color){
	this->fill((float) a2, (float) a3, (float) a4, (float) a5, color);
}
void GuiComponent::fillGradient(float a2, float a3, float a4, float a5, int32_t a6, int32_t a7){
	DisableState state(0xDE1);
	glShadeModel(0x1D01);
	Tesselator::instance.begin(4);
	Tesselator::instance.color((float)((a6&0xff0000) >> 16)/255, (float)((a6&0xff00) >> 8)/255, (float)(a6&0xff)/255, (float)((a6&0xff000000) >> 24)/255);
	Tesselator::instance.vertex(a4, a3, 0);
	Tesselator::instance.vertex(a2, a3, 0);
	Tesselator::instance.color((float)((a7&0xff0000) >> 16)/255, (float)((a7&0xff00) >> 8)/255, (float)(a7&0xff)/255, (float)((a7&0xff000000) >> 24)/255);
	Tesselator::instance.vertex(a2, a5, 0);
	Tesselator::instance.vertex(a4, a5, 0);
	Tesselator::instance.draw(1);
	glShadeModel(0x1D00);
}
void GuiComponent::fillGradient(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7){
	this->fillGradient((float)a2, (float)a3, (float)a4, (float)a5, a6, a7);
}
void GuiComponent::fillHorizontalGradient(float a2, float a3, float a4, float a5, int32_t a6, int32_t a7) {
	float v10; // s19
	float v11; // s18
	float v12; // s17
	float v13; // s16
	float v14; // s23
	float v15; // s22
	float v16; // s21
	float v17; // s20

	v10 = (float)((a7 & 0xff000000) >> 24) / 255.0;
	v11 = (float)((a7 & 0x00ff0000) >> 16) / 255.0;
	v12 = (float)((a7 & 0x0000ff00) >> 8) / 255.0;
	v13 = (float)((a7 & 0x000000ff)) / 255.0;
	v14 = (float)((a6 & 0xff000000) >> 24) / 255.0;
	v15 = (float)((a6 & 0x00ff0000) >> 16) / 255.0;
	v16 = (float)((a6 & 0x0000ff00) >> 8) / 255.0;
	v17 = (float)((a6 & 0x000000ff)) / 255.0;

	DisableState v18(0xDE1u);
	glShadeModel(0x1D01u);
	Tesselator::instance.begin(4);
	Tesselator::instance.color(v11, v12, v13, v10);
	Tesselator::instance.vertex(a4, a3, 0.0);
	Tesselator::instance.color(v15, v16, v17, v14);
	Tesselator::instance.vertex(a2, a3, 0.0);
	Tesselator::instance.color(v15, v16, v17, v14);
	Tesselator::instance.vertex(a2, a5, 0.0);
	Tesselator::instance.color(v11, v12, v13, v10);
	Tesselator::instance.vertex(a4, a5, 0.0);
	Tesselator::instance.instance.draw(1);
	glShadeModel(0x1D00u);
	//~v18
}
void GuiComponent::fillHorizontalGradient(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7) {
	this->fillHorizontalGradient((float)a2, (float)a3, (float)a4, (float)a5, a6, a7);
}

GuiComponent::~GuiComponent(){

}
