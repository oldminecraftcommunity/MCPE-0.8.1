#pragma once
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <sstream>

struct LongTag : public Tag{
	int32_t field_C;
	int64_t value;

	LongTag(const std::string& n, int64_t v) : Tag(n){
		this->value = v;
	}
	LongTag(const std::string& s)
		: Tag(s) {
	}
	virtual void write(IDataOutput* out){
		out->writeLongLong(this->value);
	}
	virtual void load(IDataInput* in){
		this->value = in->readLongLong();
	}
	virtual char getId(void) const{
		return 4;
	}
	virtual std::string toString(void) const {
		std::stringstream ss;
		ss << this->value;
		return ss.str();
	}
	virtual Tag* copy(void) const {
		return new LongTag(this->getName(), this->value);
	}
	bool_t equals(const Tag& v) const {
		const LongTag* tg = (const LongTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
