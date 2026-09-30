#pragma once
#include <nbt/Tag.hpp>
#include <map>
#include <nbt/StringTag.hpp>
#include <nbt/FloatTag.hpp>
#include <nbt/IntTag.hpp>
#include <nbt/ShortTag.hpp>
#include <nbt/ByteTag.hpp>
#include <nbt/LongTag.hpp>
#include <nbt/ListTag.hpp>
#include <util/output/IDataOutput.hpp>
#include <sstream>
struct ListTag;

struct CompoundTag : public Tag{
	std::map<std::string, Tag*> value;


	CompoundTag(const std::string& name) : Tag(name){

	}
	CompoundTag(const CompoundTag& tag) : Tag(tag.getName()), value(tag.value){
	}
	CompoundTag(void) : CompoundTag(""){}

	bool_t contains(const std::string& name) const {
		return this->value.find(name) != this->value.end();
	}
	bool_t contains(const std::string& name, int32_t id) const {
		Tag* t = this->get(name);
		if (t) {
			return t->getId() == id;
		}
		return 0;
	}
	virtual Tag* copy(void) const {
		CompoundTag* cp = new CompoundTag(this->getName());
		std::map<std::string, Tag*>::const_iterator it;
		for (it = this->value.begin(); it != this->value.end(); ++it) {
			const std::string& name = it->first;
			Tag* tag = it->second->copy();
			tag->setName(name);
			cp->value.insert(std::pair<std::string,Tag *>(name, tag));
		}
		return cp;
	}
	virtual void deleteChildren(void) {
		std::map<std::string, Tag*>::iterator it_this = this->value.begin();
		for (; it_this != this->value.end(); ++it_this) {
			Tag* tag = it_this->second;
			if (tag) {
				tag->deleteChildren();
				delete tag; //should check for null once more
			}
		}
	}
	virtual int32_t getId(void) const {
		return 10;
	}
	bool_t equals(const Tag& t) const {
		CompoundTag* tg = (CompoundTag*) (&t);
		bool_t eq = Tag::equals(t);
		if (eq) {
			std::map<std::string, Tag*>::const_iterator it_this = this->value.begin();
			std::map<std::string, Tag*>::const_iterator it_that = tg->value.begin();
			for (; it_this != this->value.end(); ++it_this) {
				if (it_that == tg->value.end()) return 0;

				const std::string& name_this = it_this->first;
				const std::string& name_that = it_that->first;
				Tag* tag_this = it_this->second;
				Tag* tag_that = it_that->second;
				if (name_this != name_that) return 0;

				if (!tag_this->equals(*tag_that)) return 0;

				++it_that;
			}
			if (it_that != tg->value.end()) return 0;

			return 1;
		}
		return eq;
	}
	virtual void load(IDataInput* in) {
		this->value.clear();
		while (1) {
			Tag* tag = Tag::readNamedTag(in);
			if (!tag) break;

			int id = tag->getId();
			if (id == 0) {
				delete tag;
				return;
			}
			this->value.insert(std::pair<std::string,Tag *>(tag->getName(), tag));
		}
	}
	virtual void print(const std::string&, PrintStream&) const {
		//XXX does something, but probably useless
	}
	virtual std::string toString(void) const {
		std::stringstream ss;
		ss << this->value.size();
		ss << " entries";
		return ss.str();
	}
	virtual void write(IDataOutput* out) {
		std::map<std::string, Tag*>::iterator it_this = this->value.begin();
		while (it_this != this->value.end()) {
			Tag* tag = it_this->second;
			Tag::writeNamedTag(tag, out);
			++it_this;
		}
		out->writeByte(0);
	}


	Tag* get(const std::string& name) const {
		auto&& it = this->value.find(name);
		if (it == this->value.end()) return 0;

		return it->second;
	}
	int8_t getByte(const std::string& name) const {
		if (this->contains(name, 1)) {
			ByteTag* tag = (ByteTag*) (this->get(name));
			return tag->value;
		}
		return 0;
	}
	CompoundTag* getCompound(const std::string& name) const {
		if (this->contains(name, 10)) {
			CompoundTag* tag = (CompoundTag*) (this->get(name));
			return tag;
		}
		return new CompoundTag(name);
	}
	int32_t getInt(const std::string& name) const {
		if (this->contains(name, 3)) {
			IntTag* tag = (IntTag*) (this->get(name));
			return tag->value;
		}
		return 0;
	}
	float getFloat(const std::string& name) const {
		if (this->contains(name, 5)) {
			FloatTag* tag = (FloatTag*) (this->get(name));
			return tag->value;
		}
		return 0;
	}
	ListTag* getList(const std::string& name) const {
		if (this->contains(name, 9)) {
			ListTag* tag = (ListTag*) (this->get(name));
			return tag;
		}
		return new ListTag(name);
	}
	int64_t getLong(const std::string& name) const {
		if (this->contains(name, 4)) {
			LongTag* tag = (LongTag*) (this->get(name));
			return tag->value;
		}
		return 0;
	}
	int16_t getShort(const std::string& name) const {
		if (this->contains(name, 2)) {
			ShortTag* tag = (ShortTag*) (this->get(name));
			return tag->value;
		}
		return 0;
	}
	std::string getString(const std::string& name) const {
		if (this->contains(name, 8)) {
			StringTag* tag = (StringTag*) (this->get(name));
			return tag->value;
		}
		return "";
	}

	void put(const std::string& name, Tag* tag){
		//i wonder is there some easier way to do it
		this->value.insert(std::move<std::pair<std::string, Tag*>>({name, tag->setName(name)}));
	}
	void putBoolean(const std::string& name, bool_t b){
		this->value.insert(std::move<std::pair<std::string, ByteTag*>>({name, new ByteTag(name, b)}));
	}
	void putFloat(const std::string& name, float f){
		this->value.insert(std::move<std::pair<std::string, FloatTag*>>({name, new FloatTag(name, f)}));
	}
	void putByte(const std::string& name, char b){
		this->value.insert(std::move<std::pair<std::string, ByteTag*>>({name, new ByteTag(name, b)}));
	}
	void putInt(const std::string& name, int32_t n){
		this->value.insert(std::move<std::pair<std::string, IntTag*>>({name, new IntTag(name, n)}));
	}
	void putLong(const std::string& name, long n) {
		this->value.insert(std::move < std::pair<std::string, LongTag*> > ( {name, new LongTag(name, n)}));
	}
	void putShort(const std::string& name, int16_t n){
		this->value.insert(std::move<std::pair<std::string, ShortTag*>>({name, new ShortTag(name, n)}));
	}
	void putString(const std::string& name, const std::string& s){
		this->value.insert(std::move<std::pair<std::string, StringTag*>>({name, new StringTag(name, s)}));
	}
};
