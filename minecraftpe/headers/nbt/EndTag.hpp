#pragma once
#include "../_types.h"
#include "Tag.hpp"

struct EndTag : public Tag{
	EndTag() : Tag(""){}

	virtual void write(IDataOutput*) {
	}
	virtual void load(IDataInput*) {
	}
	virtual char getId(void) const {
		return 0;
	}
	virtual std::string toString(void) const {
		return "END";
	}
	virtual Tag* copy(void) const {
		return new EndTag();
	}

	bool_t equals(const Tag& a2) const {
		return Tag::equals(a2);
	}

};
