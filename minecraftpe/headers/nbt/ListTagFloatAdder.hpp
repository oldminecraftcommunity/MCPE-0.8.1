#pragma once
#include <_types.h>

struct ListTag;
struct ListTagFloatAdder
{
	ListTag* tag;

	ListTagFloatAdder& operator()(float);
};
