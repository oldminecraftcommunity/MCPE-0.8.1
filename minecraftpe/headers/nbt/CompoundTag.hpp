#pragma once
#include <_types.h>
#include "Tag.hpp"
#include <map>
struct ListTag;

struct CompoundTag : public Tag{
	std::map<const std::string, Tag*> value;

	CompoundTag(const CompoundTag&);
	CompoundTag(const std::string&);
	CompoundTag(void);

	bool_t contains(const std::string&) const;
	bool_t contains(const std::string &, int32_t) const;
	virtual Tag* copy(void);
	virtual void deleteChildren(void);
	virtual int32_t getId(void) const;
	bool_t equals(const Tag&);
	virtual void load(IDataInput*);
	virtual	void print(const std::string&, PrintStream&);
	virtual std::string toString(void);
	virtual void write(IDataOutput*);


	Tag* get(const std::string&) const;
	int8_t getByte(const std::string&) const;
	CompoundTag* getCompound(const std::string&) const;
	int32_t getInt(const std::string&) const;
	float getFloat(const std::string&) const; //TODO this thing is always inlined?
	ListTag* getList(const std::string&) const;
	int64_t getLong(const std::string&) const;
	int16_t getShort(const std::string&) const;
	std::string getString(const std::string&) const;

	void put(const std::string&, Tag*);
	void putBoolean(const std::string&, bool_t);
	void putFloat(const std::string&, float); //TODO this thing is always inlined?
	void putByte(const std::string&, int8_t);
	void putInt(const std::string&, int32_t);
	void putLong(const std::string&, int64_t);
	void putShort(const std::string&, int16_t);
	void putString(const std::string&, const std::string&);
};
