#pragma once
#include <gui/PackedScrollContainer.hpp>

struct OptionsGroup;
struct OptionsPane: PackedScrollContainer
{
	OptionsPane();
	OptionsGroup* createOptionsGroup(std::string a2);

	virtual ~OptionsPane();
	virtual void setupPositions();
};
