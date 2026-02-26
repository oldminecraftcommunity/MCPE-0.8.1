#include <nbt/ListTagFloatAdder.hpp>
#include <nbt/ListTag.hpp>
#include <nbt/FloatTag.hpp>

ListTagFloatAdder& ListTagFloatAdder::operator()(float a2) {
	if(!this->tag) {
		this->tag = new ListTag();
	}
	this->tag->add(new FloatTag("", a2));
	return *this;
}
