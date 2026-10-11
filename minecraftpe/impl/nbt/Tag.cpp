#include <nbt/Tag.hpp>
#include <_types.h>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>
#include <nbt/EndTag.hpp>
#include <nbt/ByteTag.hpp>
#include <nbt/ShortTag.hpp>
#include <nbt/IntTag.hpp>
#include <nbt/ByteArrayTag.hpp>
#include <nbt/LongTag.hpp>
#include <nbt/FloatTag.hpp>
#include <nbt/DoubleTag.hpp>
#include <nbt/StringTag.hpp>
#include <nbt/ListTag.hpp>
#include <nbt/CompoundTag.hpp>

std::string Tag::NullString = "";
Tag::Tag(const std::string& name) : field_0(0), tagName(name) {

}

bool_t Tag::equals(const Tag& tag) const{
	return (this->getId() == tag.getId()) && (this->tagName == tag.tagName);
}
void Tag::print(PrintStream& ps) const{
	std::string result = "";
	this->print(result, ps);
}
void Tag::print(const std::string& s, PrintStream& ps) const{
	//TODO figure out what is happening here
	std::string tagName = this->getName();
	Tag::getTagName(this->getId());
	if(tagName.size() != 0) {
		std::string v9;
		v9.reserve(tagName.size() + 2);
		v9 += "(\"";
		v9 += tagName;
		v9 += "\")";
		std::string tagName2 = v9;
	}
	std::string(": ");
	this->toString() + "\n";
	printf("Tag::print - not implemented\n");
}
Tag* Tag::setName(const std::string& name){
	this->tagName = name;
	return this;
}
std::string Tag::getName(void) const{
	return this->tagName;
}

void Tag::writeNamedTag(Tag* tag, IDataOutput* output){
	output->writeByte(tag->getId());
	if(tag->getId()){
		output->writeString(tag->getName());
		tag->write(output);
	}

}
Tag* Tag::readNamedTag(IDataInput* input){
	int8_t type = input->readByte();
	if(type){
		Tag* tag = Tag::newTag(type, input->readString());

		if(tag) tag->load(input);
		return tag;
	}else{
		return new EndTag();
	}
}

std::string Tag::getTagName(char id){
	switch(id){
		case 0: return "TAG_End";
		case 1: return "TAG_Byte";
		case 2: return "TAG_Short";
		case 3: return "TAG_Int";
		case 4: return "TAG_Long";
		case 5: return "TAG_Float";
		case 6: return  "TAG_Double";
		case 7: return "TAG_Byte_Array";
		case 8: return "TAG_String";
		case 9: return "TAG_List";
		case 10: return "TAG_Compound";
		default: return "UNKNOWN";
	}
}
Tag* Tag::newTag(char type, const std::string& name){
	switch(type){
		case 0: return new EndTag();
		case 1: return new ByteTag(name);
		case 2: return new ShortTag(name);
		case 3: return new IntTag(name);
		case 4: return new LongTag(name);
		case 5: return new FloatTag(name);
		case 6: return new DoubleTag(name);
		case 7: return new ByteArrayTag(name);
		case 8: return new StringTag(name);
		case 9: return new ListTag(name);
		case 10: return new CompoundTag(name);
		default: return 0;
	}
}
