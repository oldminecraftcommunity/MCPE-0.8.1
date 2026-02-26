#include <nbt/NbtIo.hpp>
#include <nbt/Tag.hpp>

Tag* NbtIo::read(IDataInput* in){
	Tag* tag;
	tag = Tag::readNamedTag(in);
	if(!tag || tag->getId() != 10) return 0; //XXX wat
	return tag;
}
