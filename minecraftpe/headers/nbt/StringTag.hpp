#pragma once
#include "../_types.h"
#include <string>
#include "Tag.hpp"

struct StringTag : public Tag{
	std::string value;
	//XXX has 2 vars, and probably uses not std::string
	StringTag(const std::string&, const std::string&);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
};
