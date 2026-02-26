#pragma once
#include <_types.h>
#include <nbt/Tag.hpp>

struct LongTag : public Tag{
	int32_t field_C;
	int64_t value;

	LongTag(const std::string& n, int64_t v);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
