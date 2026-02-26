#pragma once
#include <_types.h>
#include <string>

struct GuiMessage
{
	int32_t field_0, field_4;
	std::string field_8, field_C, field_10;

	GuiMessage(const GuiMessage&);
	GuiMessage(GuiMessage&&);
	GuiMessage(const std::string&, const std::string&, int32_t);
	GuiMessage& operator=(const GuiMessage&);
	GuiMessage& operator=(GuiMessage&&);
	virtual ~GuiMessage();
};
