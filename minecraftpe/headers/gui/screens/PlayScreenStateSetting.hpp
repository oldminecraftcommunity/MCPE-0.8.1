#pragma once
#include <_types.h>
#include <string>
#include <gui/screens/PlayScreenStateSetting.hpp>
#include <gui/screens/PlayScreenPanel.hpp>

struct PlayScreenStateSetting
{
	bool_t field_0, field_1, field_2, field_3;
	bool_t field_4, field_5;
	int8_t field_6, field_7;
	PlayScreenPanel panel;
	std::string field_C;

	PlayScreenStateSetting();
	PlayScreenStateSetting(bool_t a3, bool_t a4, bool_t a5, bool_t a6, bool_t a7, bool_t a8, PlayScreenPanel a9);

};
