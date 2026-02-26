#pragma once
#include <_types.h>
#include <nbt/Tag.hpp>

struct ByteTag : public Tag{
	int8_t value;

	ByteTag(const std::string&, int8_t);

	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);

	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
