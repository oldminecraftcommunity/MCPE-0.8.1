#pragma once
#include <_types.h>
#include <map>
#include <item/ItemInstance.hpp>
#include <string>
#include <vector>
#include <math/Pos.hpp>
#include <entity/data/DataItem2.hpp>
struct IDataOutput;
struct DataItem;
struct IDataInput;
struct SynchedEntityData{
	std::map<int32_t, DataItem*> data;
	bool_t isDirty;

	SynchedEntityData();
	void assignValues(std::vector<DataItem*>*);
	template<typename T> //exists only for char in 0.8
	void clearFlag(int32_t a2, int32_t a3) {
		DataItem2<T>* v5 = (DataItem2<T>*) this->data[a2];
		T value = v5->value;
		T newvalue = value & ~(1 << a3);
		v5->value = newvalue;
		if(((newvalue >> a3) & 1) != ((value >> a3) & 1)) {
			this->markDirty(a2);
		}
	}
	template<typename T> //exists only for int in 0.8
	void define(int32_t a2, const T& a3){
		if(this->data.end() == this->data.find(a2)){
			//TODO check
			this->data.insert({a2, new DataItem2<T>(a2, a3)});
		}
	}
	int8_t getByte(int32_t);
	float getFloat(int32_t);
	int32_t getInt(int32_t);
	ItemInstance getItemInstance(int32_t);
	Pos getPos(int32_t);
	int16_t getShort(int32_t);
	std::string getString(int32_t);
	void markDirty(int32_t);
	static void pack(std::vector<DataItem*>*, IDataOutput*);
	void packAll(IDataOutput*) const;
	std::vector<DataItem*> packDirty();
	template<typename T>
	void set(int32_t a2, const T& a3);
	template<typename T> //exists only for char in 0.8
	void setFlag(int32_t, int32_t);
	static std::vector<DataItem*> unpack(IDataInput*);
	static void writeDataItem(IDataOutput*, const DataItem*);

	~SynchedEntityData();
};
