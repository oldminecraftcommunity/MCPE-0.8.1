#pragma once
#include <_types.h>
struct Entity;
struct PRInfo
{
	Entity* entity;
	int i;

	PRInfo(Entity* e, int i) {
		this->entity = e;
		this->i = i;
	}
};
