#include <nbt/EndTag.hpp>

EndTag::EndTag() : Tag(""){}

void EndTag::write(IDataOutput*){

}
void EndTag::load(IDataInput*){

}

Tag* EndTag::copy(void){
	return new EndTag();
}

std::string	EndTag::toString(void){
	return "END";
}
int32_t EndTag::getId(void) const{
	return 0;
}
