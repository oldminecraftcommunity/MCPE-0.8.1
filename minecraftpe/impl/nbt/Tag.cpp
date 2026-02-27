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
Tag::Tag(const std::string& name){
	this->tagName = name;
}

Tag::~Tag(void){
	//should delete tagName
}
void Tag::deleteChildren(void){

}
bool_t Tag::equals(const Tag& tag){
	return (this->getId() == tag.getId()) && (this->tagName == tag.tagName);
}
void Tag::print(PrintStream& ps){
	std::string result = "";
	this->print(result, ps);
}
void Tag::print(const std::string& s, PrintStream& ps){
	//doesnt seem to do anything with params?
}
void Tag::setName(const std::string& name){
	this->tagName = name;
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
		case 1: return new ByteTag(name, 0);
		case 2: return new ShortTag(name, 0);
		case 3: return new IntTag(name, 0);
		case 4: return new LongTag(name, 0);
		case 5: return new FloatTag(name, 0);
		case 6: return new DoubleTag(name, 0);
		case 7: return new ByteArrayTag(name, 0, 0);
		case 8: return new StringTag(name, "");
		case 9: return new ListTag(name);
		case 10: return new CompoundTag(name);
		default: return 0;
	}
}
