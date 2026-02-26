#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <input/KeyboardAction.hpp>
#include <input/KeyboardTextInput.hpp>

struct KeyboardInputText;
struct Keyboard
{
	static int32_t _states[256];
	static std::vector<KeyboardAction> _inputs;
	static std::vector<KeyboardInputText> _inputText;
	static int32_t _textIndex;
	static int32_t _index;

	static void feed(uint8_t, int32_t);
	static void feedText(const std::string&, bool_t);
	static void reset();
};
