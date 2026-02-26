#include <gui/buttons/SmallButton.hpp>

SmallButton::SmallButton(int32_t a2, int32_t a3, int32_t a4, Options::Option* a5, const std::string& a6)
	: Button(a2, a3, a4, 150, 20, a6) {
	this->option = a5;
}
SmallButton::SmallButton(int32_t a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, const std::string& a7)
	: Button(a2, a3, a4, a5, a6, a7) {
	this->option = 0;
}
SmallButton::SmallButton(int32_t a2, int32_t a3, int32_t a4, const std::string& a5)
	: Button(a2, a3, a4, 150, 20, a5) {
	this->option = 0;
}

Options::Option* SmallButton::getOption() {
	return this->option;
}
SmallButton::~SmallButton() {
}
