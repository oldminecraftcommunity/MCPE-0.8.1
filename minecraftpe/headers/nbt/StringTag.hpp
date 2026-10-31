#pragma once
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <sstream>

struct StringTag : public Tag{
	std::string value;
	int nameLength;
	StringTag(const std::string& name, const std::string& value) : Tag(name), value(value){
		this->nameLength = name.length();
	}
	StringTag(const std::string& name) : Tag(name){
		this->nameLength = name.length();
	}
	virtual void write(IDataOutput* out) {
		out->writeString(this->value);
	}
	virtual void load(IDataInput* in) {
		this->value = in->readString();
	}
	virtual char getId(void) const {
		return 8;
	}
	virtual std::string toString(void) const {
		std::stringstream str;
		str << this->value;
		return str.str();
	}
	virtual Tag* copy(void) const {
		return new StringTag(this->getName(), this->value);
	}
	bool_t equals(const Tag& v) const {
		const StringTag* tg = (const StringTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) return this->value == tg->value;

		return eq;
	}
};
