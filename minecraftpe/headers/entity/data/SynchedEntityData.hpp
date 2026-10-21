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
	void define(int32_t a2, const T& a3) {
		if(a2 > 31) return;
		if(this->data.find(a2) == this->data.end()){
			this->data.insert(std::pair<int, DataItem*>(a2, new DataItem2<T>(a2, a3)));
		}
	}
	int8_t getByte(int32_t) const;
	float getFloat(int32_t) const;
	int32_t getInt(int32_t) const;
	ItemInstance getItemInstance(int32_t);
	Pos getPos(int32_t) const;
	int16_t getShort(int32_t) const;
	std::string getString(int32_t) const;
	void markDirty(int32_t a2) {
		this->data[a2]->dirty = 1;
		this->isDirty = 1;
	}
	static void pack(std::vector<DataItem*>*, IDataOutput*);
	void packAll(IDataOutput*) const;
	std::vector<DataItem*> packDirty();
	template<typename T>
	void set(int32_t a2, const T& a3) {
		DataItem* di = this->data[a2];
		if(di) {
			if((di->typeId == (DataType<T>::typeId)) && !(((DataItem2<T>*)di)->value == a3)) {
				((DataItem2<T>*)di)->value = a3;
				((DataItem2<T>*)di)->dirty = 1;
				this->isDirty = 1;
			}
		}
	}
	template<typename T> //exists only for char in 0.8
	void setFlag(int32_t a2, int32_t a3) {
		DataItem* it = this->data[a2];
		int32_t v6 = ((DataItem2<T>*)it)->value;
		T v7 = (1 << a3) | (v6);
		((DataItem2<T>*)it)->value = v7;
		if((((int32_t)v7 >> a3) & 1) != ((v6 >> a3) & 1)) {
			this->markDirty(a2);
		}
	}
	static std::vector<DataItem*> unpack(IDataInput*);
	static void writeDataItem(IDataOutput*, const DataItem*);

	~SynchedEntityData();

	 //may not exist - should always be inlined
	template<typename T>
	T get(int a2) {
		return ((DataItem2<T>*)this->data[a2])->value;
	}
};

