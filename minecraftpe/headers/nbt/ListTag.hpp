#pragma once
#include "../_types.h"
#include <string>
#include <vector>
#include "Tag.hpp"

struct ListTag : public Tag{
	std::vector<Tag*> value;
	int8_t tagType;

	ListTag(void);
	ListTag(const std::string&);
	virtual void write(IDataOutput*);
	virtual void load(IDataInput*);
	virtual int32_t getId(void) const;
	virtual std::string toString(void);
	virtual Tag* copy(void);
	bool_t equals(const Tag&);
	virtual void deleteChildren(void);
	virtual	void print(const std::string&, PrintStream&);
	float getFloat(int32_t);
	void add(Tag*);
		
};
