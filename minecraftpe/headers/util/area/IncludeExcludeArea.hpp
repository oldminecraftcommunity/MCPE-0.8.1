#pragma once
#include <util/area/IArea.hpp>
#include <vector>

struct IncludeExcludeArea: IArea
{
	std::vector<IArea*> areas1;
	std::vector<IArea*> areas2;

	virtual ~IncludeExcludeArea();
	virtual bool_t isInside(float x, float y);
	virtual void clear();
};
