#pragma once
#include <_types.h>
#include <nbt/Tag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <string.h>
#include <sstream>

struct ByteArrayTag : public Tag{
	int8_t* value;
	int32_t count;

	ByteArrayTag(const std::string& n, int8_t* arr, int32_t length) : Tag(n), value(arr), count(length){
	}
	ByteArrayTag(const std::string& s)
		: Tag(s) {
		this->value = 0;
		this->count = 0;
	}
	virtual void write(IDataOutput* out){
		out->writeInt(this->count);
		out->writeBytes(this->value, this->count);
	}
	virtual void load(IDataInput* in){
		int32_t n = in->readInt();
		int8_t* arr = new int8_t[n];
		this->value = arr;
		//XXX doesnt change count for some reason

		in->readBytes(this->value, n);
	}
	virtual char getId(void) const{
		return 7;
	}
	virtual std::string toString() const{
		std::stringstream ss;
		ss << "[" << this->count << " bytes]";
		return ss.str();
	}
	virtual Tag* copy(void) const {
		int8_t* arr = new int8_t[this->count];
		memcpy(arr, this->value, this->count);
		return new ByteArrayTag(this->getName(), arr, 0); //XXX count is 0??????
	}
	bool_t equals(const Tag& t) const {
		const ByteArrayTag* tg = (const ByteArrayTag*) (&t);
		bool_t eq = Tag::equals(t);
		if (eq) {
			int32_t count = this->count;
			return count == tg->count && memcmp(this->value, tg->value, count) == 0;
		}
		return eq;
	}
};
