#pragma once
#include <_types.h>
#include <nbt/Tag.hpp>

struct DoubleTag : public Tag{
	double value;

	DoubleTag(const std::string& n, double v);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
