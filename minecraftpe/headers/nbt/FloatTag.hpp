#pragma once
#include <_types.h>
#include "Tag.hpp"

struct FloatTag : public Tag{
	float value;

	FloatTag(const std::string& n, float v);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
