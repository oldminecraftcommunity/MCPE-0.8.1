#pragma once
#include <_types.h>
#include <string>

struct GuiMessage
{
	int32_t tickCounter, ticksShown;
	std::string message, author, fullMessage;

	GuiMessage(const GuiMessage& a2)
		: tickCounter(a2.tickCounter)
		, ticksShown(a2.ticksShown)
		, message(a2.message)
		, author(a2.author)
		, fullMessage(a2.fullMessage) {
	}
	GuiMessage(GuiMessage&& a2)
		: tickCounter(a2.tickCounter)
		, ticksShown(a2.ticksShown)
		, message(std::move(a2.message))
		, author(std::move(a2.author))
		, fullMessage(std::move(a2.fullMessage)) {
	}
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
	GuiMessage& operator=(GuiMessage&& a2) {
		this->tickCounter = a2.tickCounter;
		this->ticksShown = a2.ticksShown;
		this->message = a2.message;
		this->author = a2.author;
		this->fullMessage = a2.fullMessage;
		return *this;
	}
	~GuiMessage(){}
};
