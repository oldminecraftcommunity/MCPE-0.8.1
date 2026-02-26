#pragma once
#include "../_types.h"
#include "Tag.hpp"

struct ShortTag : public Tag{
	int16_t value;

	ShortTag(const std::string&, int16_t);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
