#include <nbt/ByteArrayTag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <string.h>

//XXX also doesnt delete this->value ??
ByteArrayTag::ByteArrayTag(const std::string& n, int8_t* arr, int32_t length) : Tag(n){
	this->value = arr;
	this->count = length;
}
void ByteArrayTag::write(IDataOutput* out){
	out->writeInt(this->count);
	out->writeBytes(this->value, this->count);
}
void ByteArrayTag::load(IDataInput* in){
	int32_t n = in->readInt();
	int8_t* arr = new int8_t[n];
	this->value = arr;
	//XXX doesnt change count for some reason

	in->readBytes(this->value, n);
}
int32_t ByteArrayTag::getId(void) const{
	return 7;
}
std::string ByteArrayTag::toString(){
	std::string result = "[";
	result += this->count;
	result += " bytes]";
	return result;
}
Tag* ByteArrayTag::copy(void){
	int8_t* arr = new int8_t[this->count];
	memcpy(arr, this->value, this->count);
	return new ByteArrayTag(this->getName(), arr, 0); //XXX count is 0??????
}
bool_t ByteArrayTag::equals(const Tag& t){
	ByteArrayTag* tg = &t;
	bool_t eq = Tag::equals(t);

	if(eq){
		int32_t count = this->count;
		return count == tg->count && memcmp(this->value, tg->value, count) == 0;
	}
	return eq;
}
