#pragma once
#include <_types.h>

struct IArea{
	bool field_4;
	//these fields may seem useless but they are actually very important for correct evil std:: stuff sizes
	//i think we need evil_std:: namespace
	int8_t field_5;
	int8_t field_6;
	int8_t field_7;

	virtual ~IArea(){}
	virtual bool_t isInside(float x, float y) = 0;
};
