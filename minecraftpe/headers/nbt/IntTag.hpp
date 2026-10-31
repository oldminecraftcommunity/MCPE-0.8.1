#pragma once
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <sstream>

struct IntTag : public Tag{
	int32_t value;

	IntTag(const std::string& n, int32_t v) : Tag(n){
		this->value = v;
	}
	IntTag(const std::string& s)
		: Tag(s) {
	}
	virtual void write(IDataOutput* out) {
		out->writeInt(this->value);
	}
	virtual void load(IDataInput* in) {
		this->value = in->readInt();
	}
	virtual char getId(void) const {
		return 3;
	}
	virtual std::string toString(void) const {
		std::stringstream ss;
		ss << this->value;
		return ss.str();
	}
	virtual Tag* copy(void) const {
		return new IntTag(this->getName(), this->value);
	}
	bool_t equals(const Tag& v) const {
		const IntTag* tg = (const IntTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
