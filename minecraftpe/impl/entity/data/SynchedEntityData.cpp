#include <entity/data/SynchedEntityData.hpp>
#include <util/output/IDataOutput.hpp>
#include <util/input/IDataInput.hpp>

SynchedEntityData::SynchedEntityData() {
	this->isDirty = 0;
}
void SynchedEntityData::assignValues(std::vector<DataItem*>* a2) {
	for(auto&& ptr: *a2) {
		auto&& d = this->data.find(ptr->dataId);
		if(d != this->data.end()) {
			switch(ptr->typeId) {
				case 0:
					if(d->second->typeId && d->second->typeId == 0) {
						if(((DataItem2<int8_t>*)ptr)->value != ((DataItem2<int8_t>*)d->second)->value) {
							((DataItem2<int8_t>*)d->second)->value = ((DataItem2<int8_t>*)ptr)->value;
							d->second->dirty = 1;
							this->isDirty = 1;
						}
					}
					break;
				case 1:
					if(d->second->typeId && d->second->typeId == 1) {
						if(((DataItem2<int16_t>*)ptr)->value != ((DataItem2<int16_t>*)d->second)->value) {
							((DataItem2<int16_t>*)d->second)->value = ((DataItem2<int16_t>*)ptr)->value;
							d->second->dirty = 1;
							this->isDirty = 1;
						}
					}
					break;
				case 2:
					if(d->second->typeId && d->second->typeId == 2) {
						if(((DataItem2<int32_t>*)ptr)->value != ((DataItem2<int32_t>*)d->second)->value) {
							((DataItem2<int32_t>*)d->second)->value = ((DataItem2<int32_t>*)ptr)->value;
							d->second->dirty = 1;
							this->isDirty = 1;
						}
					}
					break;
				case 3:
					if(d->second->typeId && d->second->typeId == 3) {
						if(((DataItem2<float>*)ptr)->value != ((DataItem2<float>*)d->second)->value) {
							((DataItem2<float>*)d->second)->value = ((DataItem2<float>*)ptr)->value;
							d->second->dirty = 1;
							this->isDirty = 1;
						}
					}
					break;
				case 4:
					if(d->second->typeId && d->second->typeId == 4) {
						if(((DataItem2<std::string>*)ptr)->value != ((DataItem2<std::string>*)d->second)->value) {
							((DataItem2<std::string>*)d->second)->value = ((DataItem2<std::string>*)ptr)->value;
							d->second->dirty = 1;
							this->isDirty = 1;
						}
					}
					break;
				case 5:
					if(d->second->typeId && d->second->typeId == 5) {
						if(!(((DataItem2<ItemInstance>*)ptr)->value == ((DataItem2<ItemInstance>*)d->second)->value)) {
							((DataItem2<ItemInstance>*)d->second)->value = ((DataItem2<ItemInstance>*)ptr)->value;
							d->second->dirty = 1;
							this->isDirty = 1;
						}
					}
					break;
				case 6:
					if(d->second->typeId && d->second->typeId == 6) {
						if(!(((DataItem2<Pos>*)ptr)->value == ((DataItem2<Pos>*)d->second)->value)) {
							((DataItem2<Pos>*)d->second)->value = ((DataItem2<Pos>*)ptr)->value;
							d->second->dirty = 1;
							this->isDirty = 1;
						}
					}
					break;
				default:
					continue;
			}
		}
	}
}
int8_t SynchedEntityData::getByte(int32_t a2) {
	auto&& v = this->data.find(a2);
	if(v == this->data.end() || v->second->dataId != 0) {
		return 0;
	}
	return ((DataItem2<int8_t>*)v->second)->value;
}
float SynchedEntityData::getFloat(int32_t a2) {
	auto&& v = this->data.find(a2);
	if(v == this->data.end() || v->second->dataId != 3) {
		return 0;
	}
	return ((DataItem2<float>*)v->second)->value;
}
int32_t SynchedEntityData::getInt(int32_t a2) {
	auto&& v = this->data.find(a2);
	if(v == this->data.end() || v->second->dataId != 2) {
		return 0;
	}
	return ((DataItem2<int32_t>*)v->second)->value;
}
ItemInstance SynchedEntityData::getItemInstance(int32_t a2) {
	auto&& v = this->data.find(a2);
	if(v == this->data.end() || v->second->dataId != 5) {
		return ItemInstance();
	}
	return ItemInstance(((DataItem2<ItemInstance>*)v->second)->value);
}
Pos SynchedEntityData::getPos(int32_t a2) {
	auto&& v = this->data.find(a2);
	if(v == this->data.end() || v->second->dataId != 6) {
		return {0, 0, 0};
	}
	return ((DataItem2<Pos>*)v->second)->value;
}
int16_t SynchedEntityData::getShort(int32_t a2) {
	auto&& v = this->data.find(a2);
	if(v == this->data.end() || v->second->dataId != 1) {
		return 0;
	}
	return ((DataItem2<int16_t>*)v->second)->value;
}
std::string SynchedEntityData::getString(int32_t a2) {
	auto&& v = this->data.find(a2);
	if(v == this->data.end() || v->second->dataId != 4) {
		return "";
	}
	return ((DataItem2<std::string>*)v->second)->value;
}
void SynchedEntityData::markDirty(int32_t a2) {
	this->data[a2]->dirty = 1;
	this->isDirty = 1;
}
void SynchedEntityData::pack(std::vector<DataItem*>* a1, IDataOutput* a2) {
	if(a1) {
		for(auto&& v: *a1) {
			SynchedEntityData::writeDataItem(a2, v);
		}
	}
	a2->writeByte(127);
}
void SynchedEntityData::packAll(IDataOutput* a2) const {
	for(auto&& v: this->data) {
		SynchedEntityData::writeDataItem(a2, v.second);
	}
	a2->writeByte(127);
}
std::vector<DataItem*> SynchedEntityData::packDirty() {
	std::vector<DataItem*> res;
	if(this->isDirty) {
		for(auto&& v: this->data) {
			if(v.second->dirty) {
				v.second->dirty = 0;
				res.push_back(v.second);
			}
		}
	}
	this->isDirty = 0;
	return res;
}

//TODO get rid of this
#define _SynchedEntityData_set_base(T, Tid) \
	DataItem* di = this->data[a2]; \
	if(di) { \
		if((di->typeId == (Tid)) && !(((DataItem2<T>*)di)->value == a3)) { \
			((DataItem2<T>*)di)->value = a3; \
			((DataItem2<T>*)di)->dirty = 1; \
			this->isDirty = 1; \
		} \
	}

template<>
void SynchedEntityData::set(int32_t a2, const int8_t& a3) {
	_SynchedEntityData_set_base(int8_t, 0)
}

template<>
void SynchedEntityData::set(int32_t a2, const int16_t& a3) {
	_SynchedEntityData_set_base(int16_t, 1)
}
template<>
void SynchedEntityData::set(int32_t a2, const int32_t& a3) {
	_SynchedEntityData_set_base(int32_t, 2)
}
template<>
void SynchedEntityData::set(int32_t a2, const float& a3) {
	_SynchedEntityData_set_base(float, 3)
}
template<>
void SynchedEntityData::set(int32_t a2, const std::string& a3) {
	_SynchedEntityData_set_base(std::string, 4)
}
template<>
void SynchedEntityData::set(int32_t a2, const ItemInstance& a3) {
	_SynchedEntityData_set_base(ItemInstance, 5)
}
template<>
void SynchedEntityData::set(int32_t a2, const Pos& a3) {
	_SynchedEntityData_set_base(Pos, 6)
}

template<> //exists only for char in 0.8
void SynchedEntityData::setFlag<char>(int32_t a2, int32_t a3) {
	DataItem* it = this->data[a2];
	int32_t v6 = ((DataItem2<int8_t>*)it)->value;
	uint8_t v7 = (1 << a3) | (v6);
	((DataItem2<int8_t>*)it)->value = v7;
	if((((int32_t)v7 >> a3) & 1) != ((v6 >> a3) & 1)) {
		this->markDirty(a2);
	}
}

std::vector<DataItem*> SynchedEntityData::unpack(IDataInput* a2) {
	std::vector<DataItem*> vec;
	for(int32_t i = a2->readByte(); i != 127; i = a2->readByte()) {
		int32_t v5 = i & 0x1f;
		DataItem* v22 = 0;
		switch((uint8_t)i >> 5) {
			case 0:
				v22 = new DataItem2<int8_t>(v5, a2->readByte()); //signed char
				break;
			case 1:
				v22 = new DataItem2<int16_t>(v5, a2->readShort()); //short
				break;
			case 2:
				v22 = new DataItem2<int32_t>(v5, a2->readInt()); //int
				break;
			case 3:
				v22 = new DataItem2<float>(v5, a2->readFloat());
				break;
			case 4:
				v22 = new DataItem2<std::string>(v5, a2->readString());
				break;
			case 5:
				v22 = new DataItem2<ItemInstance>(v5, ItemInstance(a2->readShort(), a2->readByte(), a2->readShort()));
				break;
			case 6:
				v22 = new DataItem2<Pos>(v5, Pos{a2->readInt(), a2->readInt(), a2->readInt()});
				break;
		}
		if(!v22) break;
		vec.push_back(v22);
		if(!a2->hasBytesLeft(1)) break;
	}
	return vec;
}

void SynchedEntityData::writeDataItem(IDataOutput* a1, const DataItem* a2) {
	a1->writeByte(a2->dataId & 0x1F | (32 * a2->typeId));
	switch(a2->typeId) {
		case 0:
			a1->writeByte(((const DataItem2<int8_t>*)a2)->value);
			break;
		case 1:
			a1->writeShort(((const DataItem2<int16_t>*)a2)->value);
			break;
		case 2:
			a1->writeInt(((const DataItem2<int32_t>*)a2)->value);
			break;
		case 3:
			a1->writeFloat(((const DataItem2<float>*)a2)->value);
			break;
		case 4:
			a1->writeString(((const DataItem2<std::string>*)a2)->value);
			break;
		case 5:
			a1->writeShort(((const DataItem2<ItemInstance>*)a2)->value.getId());
			a1->writeByte(((const DataItem2<ItemInstance>*)a2)->value.count);
			a1->writeShort(((const DataItem2<ItemInstance>*)a2)->value.getAuxValue());
			break;
		case 6:
			a1->writeInt(((const DataItem2<Pos>*) a2)->value.x);
			a1->writeInt(((const DataItem2<Pos>*) a2)->value.y);
			a1->writeInt(((const DataItem2<Pos>*) a2)->value.z);
			break;
		default:
			return;
	}
}
SynchedEntityData::~SynchedEntityData() {
	for(auto&& v: this->data) {
		delete v.second;
	}
}
