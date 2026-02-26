#include <nbt/DoubleTag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>

DoubleTag::DoubleTag(const std::string& n, double v) : Tag(n){
	this->value = v;
}
void DoubleTag::write(IDataOutput* out){
	out->writeDouble(this->value);
}
void DoubleTag::load(IDataInput* in){
	this->value = in->readDouble();
}
int32_t DoubleTag::getId(void) const{
	return 6;
}
std::string DoubleTag::toString(void){
	//XXX might be not like in mcpe
	return std::to_string(this->value);
}
Tag* DoubleTag::copy(void){
	return new DoubleTag(this->getName(), this->value);
}
bool_t DoubleTag::equals(const Tag& v){
	DoubleTag* tg = &v;
	bool_t eq = Tag::equals(v);
	if(eq) return this->value == tg->value;
	return eq;
}
