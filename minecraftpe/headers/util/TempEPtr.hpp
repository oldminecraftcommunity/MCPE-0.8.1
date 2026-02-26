#pragma once
#include <_types.h>
#include <util/_TickPtr.hpp>
#include <level/Level.hpp>

//templates is the worst thing in C++
//(except std)
template<typename T>
struct TempEPtr : _TickPtr
{
	T* entity;
	int32_t entityId;
	Level* level;
	bool_t locked;
	byte align[3];

	TempEPtr() {
		this->entity = 0;
		this->entityId = 0;
		this->level = 0;
		this->locked = 0;
	}

	T* lock() {
		if(!this->locked) {
			if(this->level) {
				if(this->entityId > 0) {
					this->entity = (T*) this->level->getEntity(this->entityId);
					if(!this->entity) {
						this->entity =(T*) this->level->getEntity(this->entityId); //?????????
					}
				}
			}
			this->locked = 1;
		}
		return this->entity;
	}
	void unset() {
		this->entity = 0;
		this->entityId = 0;
		this->locked = 0;
		if(this->level) {
			this->level->unregisterTemporaryPointer(this);
		}
		this->level = 0;
	}

	virtual void invalidate() {
		this->entity = 0;
		this->locked = 0;
	}
	virtual ~TempEPtr() {
		this->unset();
	}
};
