#include <nbt/ByteTag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
ByteTag::ByteTag(const std::string& s, int8_t v) : Tag(s){
	this->value = v;
}
void ByteTag::load(IDataInput* in){
	this->value = in->readByte();
}
void ByteTag::write(IDataOutput* out){
	out->writeByte(this->value);
}
int32_t ByteTag::getId(void) const{
	return 1;
}
std::string ByteTag::toString(){
	//XXX might be not like in mcpe
	return std::to_string(this->value);
}
Tag* ByteTag::copy(void){
	ByteTag* t = new ByteTag(this->getName(), this->value);
	return t;
}
bool_t ByteTag::equals(const Tag& v){
	const ByteTag* tg = (const ByteTag*) &v;
	bool_t eq = Tag::equals(v);
	if(eq) return this->value == tg->value;
	return eq;
}
