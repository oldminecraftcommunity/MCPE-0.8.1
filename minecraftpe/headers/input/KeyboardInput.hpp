#pragma once
#include <input/IMoveInput.hpp>

struct Options;
struct Player;

struct KeyboardInput: IMoveInput
{
	bool inputs[10];
	Options* options;

	KeyboardInput(Options*);

	virtual ~KeyboardInput() {
	}
	virtual void tick(Player*);
	virtual void setKey(int32_t key, bool_t);
	virtual void releaseAllKeys();
};
