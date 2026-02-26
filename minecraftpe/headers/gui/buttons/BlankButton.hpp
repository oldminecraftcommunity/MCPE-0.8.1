#pragma once
#include <gui/buttons/Button.hpp>

struct BlankButton: Button
{
	BlankButton(int32_t);
	BlankButton(int32_t, int32_t, int32_t, int32_t, int32_t);

	virtual ~BlankButton();
};
