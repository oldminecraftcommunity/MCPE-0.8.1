#pragma once
#include <input/ITurnInput.hpp>

struct ControllerTurnInput: ITurnInput
{
	int32_t field_10;
	int32_t field_14;
	float field_18, field_1C;
	int8_t field_20, field_21, field_22, field_23;
	int32_t field_24;
	ControllerTurnInput();
	virtual ~ControllerTurnInput();
	virtual Vec3 getTurnDelta();
};
