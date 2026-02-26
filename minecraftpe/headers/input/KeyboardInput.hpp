#pragma once
#include <input/IMoveInput.hpp>

struct Options;
struct Player;

struct KeyboardInput: IMoveInput
{
	float strafeInput, forwardInput;
	int8_t field_8;
	bool_t jumpingMaybe, sneakingMaybe;
	int8_t field_B;
	int8_t field_C, field_D;
	int8_t inputs[10];
	Options* options;

	KeyboardInput(Options*);

	virtual ~KeyboardInput();
	virtual void tick(Player*);
	virtual void setKey(int32_t, bool_t);
	virtual void releaseAllKeys();
};
