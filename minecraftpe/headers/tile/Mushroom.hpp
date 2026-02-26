#pragma once
#include <tile/Bush.hpp>

struct Mushroom: Bush
{
	Mushroom(int32_t, const std::string&);

	virtual ~Mushroom();
	virtual bool_t mayPlace(Level*, int32_t, int32_t, int32_t, uint8_t);
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual bool_t canSurvive(Level*, int32_t, int32_t, int32_t);
	virtual bool_t mayPlaceOn(int32_t);

};
