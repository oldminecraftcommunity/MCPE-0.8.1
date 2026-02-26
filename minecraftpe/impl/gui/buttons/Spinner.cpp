#include <gui/buttons/Spinner.hpp>
#include <Minecraft.hpp>
#include <utils.h>
#include <rendering/Font.hpp>

Spinner::Spinner()
	: GuiElement(1, 1, 0, 0, 24, 24) {
	this->height = 12;
	this->width = 12;
}

//TODO is this wchar_t?
static char_t _off_d67589b0[4] = {'-', '\\', '|', '/'};

void Spinner::render(Minecraft* mc, int32_t a3, int32_t a4) {
	if(this->visible) {
		int32_t v6 = (int32_t)(getTimeS() * 5.5) % 4;
		//TODO weird stuff is happening here
		char_t* v8 = _off_d67589b0[v6];
		{
			std::string a2(v8, 1);
			int32_t v9 = mc->font->width(a2);
			mc->font->draw(a2, (float)(this->posX-v9/2), (float)this->posY, -1);
		}

	}
}

Spinner::~Spinner(){

}
