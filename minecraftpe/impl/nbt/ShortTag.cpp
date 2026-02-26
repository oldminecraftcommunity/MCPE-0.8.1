#include <nbt/ShortTag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
ShortTag::ShortTag(const std::string& s, int16_t v) : Tag(s){
	this->value = v;
}
void ShortTag::write(IDataOutput* out){
	out->writeShort(this->value);
}
void ShortTag::load(IDataInput* in){
	this->value = in->readShort();
}
int32_t ShortTag::getId(void) const{
	return 2;
}
std::string ShortTag::toString(void){
	//XXX might be not like in mcpe
	return std::to_string(this->value);
}
Tag* ShortTag::copy(void){
	ShortTag* t = new ShortTag(this->getName(), this->value);
	return t;
}
bool_t ShortTag::equals(const Tag& v){
	ShortTag* tg = &v;
	bool_t eq = Tag::equals(v);
	if(eq) return this->value == tg->value;
	return eq;
}
