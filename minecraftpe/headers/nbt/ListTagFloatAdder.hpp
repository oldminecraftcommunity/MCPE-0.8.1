#pragma once
#include <nbt/ListTag.hpp>
#include <nbt/FloatTag.hpp>

struct ListTag;
struct ListTagFloatAdder
{
	ListTag* tag;
	ListTagFloatAdder(float f)
		: tag(0) {
		(*this)(f);
	}

	ListTagFloatAdder& operator()(float a2) {
		if (!this->tag) {
			this->tag = new ListTag();
		}
		this->tag->add(new FloatTag("", a2));
		return *this;
	}
};
