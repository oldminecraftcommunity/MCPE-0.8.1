#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <input/KeyboardAction.hpp>
#include <input/KeyboardTextInput.hpp>

struct KeyboardTextInput;
struct Keyboard
{
	static int32_t _states[256];
	static std::vector<KeyboardAction> _inputs;
	static std::vector<KeyboardTextInput> _inputText;
	static int32_t _textIndex;
	static int32_t _index;

	static void feed(uint8_t a1, int32_t a2) {
		Keyboard::_inputs.push_back(KeyboardAction(a2, a1));
		Keyboard::_states[a1] = a2;
	}
	static void feedText(const std::string& a2, bool_t a3) {
		Keyboard::_inputText.push_back(KeyboardTextInput { a2, a3 });
	}
	static void reset() {
		Keyboard::_inputs.clear();
		Keyboard::_inputText.clear();
		Keyboard::_index = -1;
		Keyboard::_textIndex = -1;
	}
};
