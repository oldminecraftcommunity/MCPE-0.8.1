#include <nbt/LongTag.hpp>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>

LongTag::LongTag(const std::string& n, int64_t v) : Tag(n){
	this->value = v;
}
void LongTag::write(IDataOutput* out){
	out->writeLongLong(this->value);
}
void LongTag::load(IDataInput* in){
	this->value = in->readLongLong();
}
int32_t LongTag::getId(void) const{
	return 4;
}
std::string LongTag::toString(void){
	//XXX might be not like in mcpe
	return std::to_string(this->value);
}
Tag* LongTag::copy(void){
	return new LongTag(this->getName(), this->value);
}
bool_t LongTag::equals(const Tag& v){
	LongTag* tg = &v;
	bool_t eq = Tag::equals(v);
	if(eq) return this->value == tg->value;
	return eq;
}
