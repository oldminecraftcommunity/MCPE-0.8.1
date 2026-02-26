#include <nbt/IntTag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>

IntTag::IntTag(const std::string& n, int32_t v) : Tag(n){
	this->value = v;
}
void IntTag::write(IDataOutput* out){
	out->writeInt(this->value);
}
void IntTag::load(IDataInput* in){
	this->value = in->readInt();
}
int32_t IntTag::getId(void) const{
	return 3;
}
std::string IntTag::toString(void){
	//XXX might be not like in mcpe
	return std::to_string(this->value);
}
Tag* IntTag::copy(void){
	return new IntTag(this->getName(), this->value);
}
bool_t IntTag::equals(const Tag& v){
	const IntTag* tg = (const IntTag*) &v;
	bool_t eq = Tag::equals(v);
	if(eq) return this->value == tg->value;
	return eq;
}
