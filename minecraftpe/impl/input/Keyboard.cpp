#include <input/Keyboard.hpp>

int32_t Keyboard::_index = -1;
int32_t Keyboard::_textIndex = -1;
int32_t Keyboard::_states[256];
std::vector<KeyboardAction> Keyboard::_inputs;
std::vector<KeyboardTextInput> Keyboard::_inputText;
