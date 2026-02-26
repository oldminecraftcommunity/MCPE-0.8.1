#include <gui/buttons/BlankButton.hpp>

BlankButton::BlankButton(int32_t a2)
	: Button(a2, "") {
	this->visible = 0;
}

BlankButton::BlankButton(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6)
	: Button(a2, a3, a4, a5, a6, "") {
	this->visible = 0;
}

BlankButton::~BlankButton() {
}
