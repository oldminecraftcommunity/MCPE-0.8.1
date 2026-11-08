#pragma once
#include <nbt/FloatTag.hpp>
#include <string>
#include <vector>
#include <util/input/IDataInput.hpp>
#include <util/output/IDataOutput.hpp>

struct ListTag : public Tag{
	std::vector<Tag*> value;
	int8_t tagType;


	ListTag(void) : Tag(""), value(){}
	ListTag(const std::string& s) : Tag(s), value(){}
	virtual void write(IDataOutput* out) {
		if (this->value.size() > 0) {
			this->tagType = this->value[0]->getId();
		} else {
			this->tagType = 1;
		}
		out->writeByte(this->tagType);
		out->writeInt(this->value.size());
		for (Tag* t : this->value) {
			t->write(out);
		}
	}
	virtual void load(IDataInput* in) {
		this->tagType = in->readByte();
		int32_t cnt = in->readInt();
		for (int32_t i = 0; i < cnt; ++i) {
			Tag* t = Tag::newTag(this->tagType, Tag::NullString);
			t->load(in);
			this->value.insert(this->value.end(), t);
		}
	}
	virtual char getId(void) const {
		return 9;
	}
	virtual std::string toString(void) const {
		std::stringstream ss;
		ss << this->value.size() << "entries of type " << Tag::getTagName(this->tagType);
		return ss.str();
	}
	virtual Tag* copy(void) const {
		ListTag* tg = new ListTag(this->getName());
		tg->tagType = this->tagType;
		for (Tag* t : this->value) {
			Tag* cp = t->copy();
			tg->value.insert(tg->value.end(), cp);
		}
		return tg;
	}
	bool_t equals(const Tag& v) const {
		const ListTag* tg = (const ListTag*) (&v);
		bool_t eq = Tag::equals(v);
		if (eq) {
			if (this->tagType == tg->tagType && tg->value.size() == this->value.size()) {
				for (int i = 0; i < this->value.size(); ++i) {
					Tag* t = this->value[i];
					const Tag* t2 = tg->value[i];
					if (t->equals(*t2)) return 0; //XXX WAT
				}
				return 1;
			}
			return 0;
		}
		return eq;
	}
	virtual void deleteChildren(void) {
		for (auto t : this->value) {
			if (t) {
				t->deleteChildren();
				delete t;
			}
		}
	}
	virtual void print(const std::string& s, PrintStream& ps) const {
		Tag::print(s, ps);
		std::string v14 = s;
		ps.println("{");
		v14 += "   ";
		for(auto&& t = this->value.begin(); t != this->value.end(); ++t){
			(*t)->print(v14, ps);
		}
		ps.println("}");
	}
	//TODO there are other methods like this(FillingContainer & Player - inlined getCompound)
	float getFloat(int32_t n) {
		if (n >= (int)this->value.size()) {
			this->err |= 1;
			return 0;
		}
		Tag* t = this->value[n];
		if (t) {
			if(t->getId() != 5){
				this->err |= 2;
				return 0;
			}
			FloatTag* ft = (FloatTag*) (t);
			return ft->value;
		}
		return 0;
	}
	void add(Tag* t) {
		this->tagType = t->getId();
		this->value.insert(this->value.end(), t);
	}
		
};
