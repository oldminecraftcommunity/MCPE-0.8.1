#include <gui/buttons/Touch_THeader.hpp>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Font.hpp>

Touch::THeader::THeader(int32_t a2, const std::string& a3)
	: Button(a2, a3) {
	this->field_30 = -99999;
	this->active = 0;
	this->width = 66;
	this->height = 26;
}

Touch::THeader::THeader(int32_t a2, int32_t a3, int32_t a4, const std::string& a5)
	: Button(a2, a3, a4, a5) {
	this->field_30 = -99999;
	this->active = 0;
	this->width = 66;
	this->height = 26;
}

Touch::THeader::THeader(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, const std::string& a7)
	: Button(a2, a3, a4, a5, a6, a7) {
	this->field_30 = -99999;
	this->active = 0;
}

Touch::THeader::~THeader() {}

void Touch::THeader::render(Minecraft* mc, int32_t x, int32_t y) {
	this->renderBg(mc, x, y);
	int32_t v6 = this->field_30;
	if(v6 == -99999) v6 = this->posX + this->width / 2;

	this->drawCenteredString(mc->font, this->maybeTextOnButton, v6, this->posY + (this->height - 8) / 2, 0xe0e0e0);
}

void Touch::THeader::renderBg(Minecraft* mc, int32_t x, int32_t y) {
	mc->texturesPtr->loadAndBindTexture("gui/touchgui.png");
	glColor4f(1.0, 1.0, 1.0, 1.0);
	this->blit(this->posX, this->posY, 150, 26, 2, this->height - 1, 2, 25);
	this->blit(this->posX + 2, this->posY, 153, 26, this->width - 3, this->height - 1, 8, 25);
	this->blit(this->posX+this->width-2, this->posY, 162, 26, 2, this->height-1, 2, 25);
	this->blit(this->posX, this->posY+this->height-1, 153, 52, this->width, 3, 8, 3);
}
