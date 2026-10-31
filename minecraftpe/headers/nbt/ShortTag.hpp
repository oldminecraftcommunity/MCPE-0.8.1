#pragma once
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <sstream>

struct ShortTag : public Tag{
	int16_t value;

	ShortTag(const std::string& s, int16_t v) : Tag(s){
		this->value = v;
	}
	ShortTag(const std::string& s)
		: Tag(s) {
	}
	virtual void write(IDataOutput* out) {
		out->writeShort(this->value);
	}
	virtual void load(IDataInput* in) {
		this->value = in->readShort();
	}
	virtual char getId(void) const {
		return 2;
	}
	virtual std::string toString(void) const {
		std::stringstream ss;
		ss << this->value;
		return ss.str();
	}
	virtual Tag* copy(void) const {
		ShortTag* t = new ShortTag(this->getName(), this->value);
		return t;
	}
	bool_t equals(const Tag& v) const {
		const ShortTag* tg = (const ShortTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
