#include <gui/buttons/Spinner.hpp>
#include <Minecraft.hpp>
#include <cpputils.hpp>
#include <rendering/Font.hpp>

Spinner::Spinner()
	: GuiElement(1, 1, 0, 0, 24, 24) {
	this->height = 12;
	this->width = 12;
}

static char* _progressCircle[4] = {"-", "\\", "|", "/"};

void Spinner::render(Minecraft* mc, int32_t a3, int32_t a4) {
	if(this->visible) {
		int32_t v6 = (int32_t)(getTimeS() * 5.5f) % 4;
		char* v8 = _progressCircle[v6];
		int32_t v9 = mc->font->width(std::string(v8, 1));
		mc->font->draw(v8, (float)(this->posX-v9/2), (float)this->posY, -1);
	}
}
