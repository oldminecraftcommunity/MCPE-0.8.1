#pragma once
#include <_types.h>
#include <nbt/Tag.hpp>

struct IntTag : public Tag{
	int32_t value;

	IntTag(const std::string&, int32_t);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
