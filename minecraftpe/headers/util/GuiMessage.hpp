#pragma once
#include <_types.h>
#include <string>

struct GuiMessage
{
	int32_t tickCounter, ticksShown;
	std::string message, author, fullMessage;

	GuiMessage(const GuiMessage& a2) = default;
	GuiMessage(GuiMessage&& a2) = default;
	GuiMessage(const std::string& a2, const std::string& a3, int32_t ticksShown)
		: tickCounter(0)
		, ticksShown(ticksShown)
		, message(a3)
		, author(a2) {
		if(a2.size()) {
			this->fullMessage = '<' + a2 + "> " + a3;
		} else {
			this->fullMessage = a3;
		}
	}
	GuiMessage& operator=(const GuiMessage& a2) = default;
	GuiMessage& operator=(GuiMessage&& a2) = default;
	~GuiMessage(){}
};
