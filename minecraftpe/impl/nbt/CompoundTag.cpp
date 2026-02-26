#include <nbt/CompoundTag.hpp>
#include <nbt/ByteTag.hpp>
#include <nbt/IntTag.hpp>
#include <nbt/ShortTag.hpp>
#include <nbt/LongTag.hpp>
#include <nbt/ListTag.hpp>
#include <nbt/StringTag.hpp>
#include <nbt/FloatTag.hpp>
#include <util/output/IDataOutput.hpp>

CompoundTag::CompoundTag(const std::string& name) : Tag(name){

}

CompoundTag::CompoundTag(const CompoundTag& tag) : Tag(tag.getName()){
	this->value = tag.value;
}

CompoundTag::CompoundTag(void) : CompoundTag(""){

}

bool_t CompoundTag::contains(const std::string& name) const{
	return this->value.find(name) != this->value.end();
}
bool_t CompoundTag::contains(const std::string& name, int32_t id) const{
	Tag* t = this->get(name);
	if(t){
		return t->getId() == id;
	}
	return 0;
}
Tag* CompoundTag::copy(void){
	CompoundTag* cp = new CompoundTag(this->getName());
	std::map<const std::string, Tag*>::iterator it;
	for(it = this->value.begin(); it != this->value.end(); ++it){
		const std::string& name = it->first;
		Tag* tag = it->second->copy();
		tag->setName(name);
		cp->value[name] = tag;
	}
	return cp;
}

void CompoundTag::deleteChildren(void){
	std::map<const std::string, Tag*>::iterator it_this = this->value.begin();
	for(; it_this != this->value.end(); ++it_this){
		Tag* tag = it_this->second;
		if(tag){
			tag->deleteChildren();
			delete tag; //should check for null once more
		}
	}
}
int32_t CompoundTag::getId(void) const{
	return 10;
}
bool_t CompoundTag::equals(const Tag& t){
	CompoundTag* tg = &t;
	bool_t eq = Tag::equals(t);
	if(eq) {
		std::map<const std::string, Tag*>::iterator it_this = this->value.begin();
		std::map<const std::string, Tag*>::iterator it_that = tg->value.begin();
		for(; it_this != this->value.end(); ++it_this){
			if(it_that == tg->value.end()) return 0;
			const std::string& name_this = it_this->first;
			const std::string& name_that = it_that->first;
			Tag* tag_this = it_this->second;
			Tag* tag_that = it_that->second;
			if(name_this != name_that) return 0;
			if(!tag_this->equals(*tag_that)) return 0;
			++it_that;
		}
		if(it_that != tg->value.end()) return 0;
		return 1;
	}
	return eq;
}
void CompoundTag::load(IDataInput* in){
	this->value.clear();
	while(1){
		Tag* tag = Tag::readNamedTag(in);
		if(!tag) break;

		int id = tag->getId();
		if(id == 0){
			delete tag;
			return;
		}

		this->value[tag->getName()] = tag;
	}
}
void CompoundTag::print(const std::string&, PrintStream&){
 //XXX does something, but probably useless
}
std::string CompoundTag::toString(void){
	return std::to_string(this->value.size()) + " entries";
}
void CompoundTag::write(IDataOutput* out){
	std::map<const std::string, Tag*>::iterator it_this = this->value.begin();
	while(it_this != this->value.end()){
		Tag* tag = it_this->second;
		Tag::writeNamedTag(tag, out);
		++it_this;
	}
	out->writeByte(0);
}


Tag* CompoundTag::get(const std::string& name) const {
	auto&& it = this->value.find(name);
	if(it == this->value.end()) return 0;
	return it->second;
}
int8_t CompoundTag::getByte(const std::string& name) const{
	if(this->contains(name, 1)) {
		ByteTag* tag  = (ByteTag*) this->get(name);
		return tag->value;
	}
	return 0;
}
CompoundTag* CompoundTag::getCompound(const std::string& name) const{
	if(this->contains(name, 10)) {
		CompoundTag* tag = (CompoundTag*) this->get(name);
		return tag;
	}
	return new CompoundTag(name);
}
int32_t CompoundTag::getInt(const std::string& name) const{
	if(this->contains(name, 3)) {
		IntTag* tag  = (IntTag*) this->get(name);
		return tag->value;
	}
	return 0;
}
float CompoundTag::getFloat(const std::string& name) const{
	if(this->contains(name, 5)) {
		FloatTag* tag = (FloatTag*)this->get(name);
		return tag->value;
	}
	return 0;
}

ListTag* CompoundTag::getList(const std::string& name) const{
	if(this->contains(name, 9)) {
		ListTag* tag  = (ListTag*) this->get(name);
		return tag;
	}
	return new ListTag(name);
}
int64_t CompoundTag::getLong(const std::string& name) const{
	if(this->contains(name, 4)) {
		LongTag* tag  = (LongTag*) this->get(name);
		return tag->value;
	}
	return 0;
}
int16_t CompoundTag::getShort(const std::string& name) const{
	if(this->contains(name, 2)) {
		ShortTag* tag  = (ShortTag*) this->get(name);
		return tag->value;
	}
	return 0;
}
std::string CompoundTag::getString(const std::string& name) const{
	if(this->contains(name, 8)) {
		StringTag* tag  = (StringTag*) this->get(name);
		return tag->value;
	}
	return "";
}

void CompoundTag::put(const std::string& name, Tag* tag){
	tag->setName(name);
	this->value[name] = tag;
}
void CompoundTag::putBoolean(const std::string& name, bool_t b){
	this->value[name] = new ByteTag(name, b);
}

void CompoundTag::putFloat(const std::string& name, float f){
	this->value[name] = new FloatTag(name, f);
}

void CompoundTag::putByte(const std::string& name, int8_t b){
	this->value[name] = new ByteTag(name, b);
}
void CompoundTag::putInt(const std::string& name, int32_t n){
	this->value[name] = new IntTag(name, n);
}
void CompoundTag::putLong(const std::string& name, int64_t n){
	this->value[name] = new LongTag(name, n);
}
void CompoundTag::putShort(const std::string& name, int16_t n){
	this->value[name] = new ShortTag(name, n);
}
void CompoundTag::putString(const std::string& name, const std::string& s){
	this->value[name] = new StringTag(name, s);
}
