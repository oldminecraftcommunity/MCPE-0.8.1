#pragma once
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <sstream>


struct DoubleTag : public Tag{
	int32_t field_C; //do all numeric tags have this thing? maybe it should be a part of some class that got removed during compilation?
	double value;

	DoubleTag(const std::string& n, double v) : Tag(n){
		this->value = v;
	}
	DoubleTag(const std::string& s)
		: Tag(s) {
	}
	virtual void write(IDataOutput* out) {
		out->writeDouble(this->value);
	}
	virtual void load(IDataInput* in) {
		this->value = in->readDouble();
	}
	virtual char getId(void) const {
		return 6;
	}
	virtual std::string toString(void) const {
		std::stringstream ss;
		ss << this->value;
		return ss.str();
	}
	virtual Tag* copy(void) const {
		return new DoubleTag(this->getName(), this->value);
	}
	bool_t equals(const Tag& v) const {
		const DoubleTag* tg = (const DoubleTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
