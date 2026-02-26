#pragma once
#include <_types.h>
#include "Tag.hpp"

struct ByteArrayTag : public Tag{
	int8_t* value;
	int32_t count;

	ByteArrayTag(const std::string&, int8_t*, int32_t);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
