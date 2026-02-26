#pragma once
#include <gui/buttons/Button.hpp>
struct Options
{
	struct Option;
};


struct SmallButton: Button
{
	Options::Option* option;
	SmallButton(int32_t, int32_t, int32_t, Options::Option*, const std::string&);
	SmallButton(int32_t, int32_t, int32_t, int32_t, int32_t, const std::string&);
	SmallButton(int32_t, int32_t, int32_t, const std::string&);

	Options::Option* getOption();

	virtual ~SmallButton();
};
