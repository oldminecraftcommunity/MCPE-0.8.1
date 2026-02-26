#include <nbt/StringTag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
//XXX might be not like in vanilla
StringTag::StringTag(const std::string& name, const std::string& value) : Tag(name){
	this->value = value;
}

void StringTag::write(IDataOutput* out){
	out->writeString(this->value);
}
void StringTag::load(IDataInput* in){
	this->value = in->readString();
}
int32_t StringTag::getId(void) const{
	return 8;
}
std::string StringTag::toString(void){
	return this->value.c_str();
}
Tag* StringTag::copy(void){
	return new StringTag(this->getName(), this->value);
}
bool_t StringTag::equals(const Tag& v){
	StringTag* tg = &v;
	bool_t eq = Tag::equals(v);
	if(eq) return this->value == tg->value;
	return eq;
}
