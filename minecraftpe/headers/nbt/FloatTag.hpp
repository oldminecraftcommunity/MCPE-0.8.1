#pragma once
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <sstream>

struct FloatTag : public Tag{
	float value;

	FloatTag(const std::string& n, float v) : Tag(n){
		this->value = v;
	}
	FloatTag(const std::string& s)
		: Tag(s) {
	}
	virtual void write(IDataOutput* out) {
		out->writeFloat(this->value);
	}
	virtual void load(IDataInput* in) {
		this->value = in->readFloat();
	}
	virtual char getId(void) const {
		return 5;
	}
	virtual std::string toString(void) const {
		std::stringstream ss;
		ss << this->value;
		return ss.str();
	}
	virtual Tag* copy(void) const {
		return new FloatTag(this->getName(), this->value);
	}
	bool_t equals(const Tag& v) const {
		const FloatTag* tg = (const FloatTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
