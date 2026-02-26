#include <input/Keyboard.hpp>

int32_t Keyboard::_states[256];
std::vector<KeyboardAction> Keyboard::_inputs;
std::vector<KeyboardInputText> Keyboard::_inputText;
int32_t Keyboard::_textIndex = -1;
int32_t Keyboard::_index = -1;

void Keyboard::feed(uint8_t a1, int32_t a2) {
	Keyboard::_inputs.emplace_back(KeyboardAction{a2, a1});
	Keyboard::_states[a1] = a2;
}
void Keyboard::feedText(const std::string& a2, bool_t a3) {
	Keyboard::_inputText.emplace_back(KeyboardInputText{a2, a3});
}
void Keyboard::reset() {
	Keyboard::_inputs.clear();
	Keyboard::_inputText.clear();
	Keyboard::_index = -1;
	Keyboard::_textIndex = -1;
}
