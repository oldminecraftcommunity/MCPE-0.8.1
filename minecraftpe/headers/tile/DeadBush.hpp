#pragma once
#include <tile/Bush.hpp>

struct DeadBush : Bush
{
	DeadBush(int32_t, const std::string&);

	virtual ~DeadBush();
	virtual int32_t getResource(int32_t, Random*);
	virtual void playerDestroy(Level*, Player*, int32_t, int32_t, int32_t, int32_t);
	virtual bool_t mayPlaceOn(int32_t);
};
