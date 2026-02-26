#include <inventory/FillingContainer.hpp>
#include <crafting/Recipe.hpp>
#include <entity/Player.hpp>
#include <tile/Tile.hpp>
#include <nbt/ListTag.hpp>
#include <nbt/CompoundTag.hpp>

FillingContainer::FillingContainer(int32_t a2, int32_t a3, int32_t a4, bool_t a5) {
	this->field_4 = a4;
	this->field_0 = -1;
	this->field_20 = a5;
	if(a3) {
		this->linkedSlots.resize(a3); //_M_default_append
	}
	this->items.resize(a2);
}
int32_t FillingContainer::addItem(ItemInstance* a2) {
	for(int32_t i = this->getLinkedSlotsCount(); i < this->getContainerSize(); ++i) {
		if(!this->getItem(i)) {
			this->setItem(i, a2);
			return i;
		}
	}
	a2->getDescriptionId();
	delete a2;
	return -1;
}
int32_t FillingContainer::addResource(const ItemInstance& a2) {
	int32_t id = a2.getId();
	int32_t count = a2.count;

	if(a2.getMaxStackSize() == 1) {
		int32_t freeSlot = this->getFreeSlot();
		if(freeSlot >= 0) {
			ItemInstance* v8 = this->getItem(freeSlot);
			ItemInstance* v9 = (ItemInstance*)&a2; //TODO unsafe?
			if(!v8) {
				v9 = ItemInstance::clone(&a2);
			}
			this->setItem(freeSlot, v9);
			return 0;
		}
	} else {
		int32_t slot = this->getSlotWithRemainingSpace(a2);
		int32_t v11 = slot;
		if(slot >= 0 || ((v11 = this->getFreeSlot()), v11 >= 0)) {
			ItemInstance* v12 = this->getItem(v11);
			int32_t v13;
			if(v12) {
				v13 = v12->count;
			} else {
				v13 = 0;
			}
			ItemInstance v18(id, v13, a2.getAuxValue());
			this->setItem(v11, &v18);
			ItemInstance* v15 = this->getItem(v11);
			this->linkEmptySlot(v11);
			int32_t v16;
			if(count <= v15->getMaxStackSize() - v15->count) {
				v16 = count;
			} else {
				v16 = v15->getMaxStackSize() - v15->count;
			}

			if(v16 > this->getMaxStackSize() - v15->count) {
				v16 = this->getMaxStackSize() - v15->count;
			}
			if(v16) {
				count -= v16;
				v15->count += v16;
			}
		}
	}
	return count;
}
void FillingContainer::clearInventory(int32_t a2) {
	int32_t i;	   // r5
	int32_t j;	   // r5
	uint32_t size; // r1

	for(i = 0; i < this->getLinkedSlotsCount(); ++i) {
		this->linkedSlots[i].field_0 = i;
	}
	for(j = this->getLinkedSlotsCount(); j < this->getContainerSize(); ++j) {
		this->release(j);
	}
	if(a2 < 0) {
		size = this->getContainerSize();
	} else {
		size = a2;
	}
	this->items.resize(size);
}
void FillingContainer::clearSlot(int32_t a2) {
	if(a2 >= 0) {
		if(a2 >= this->getLinkedSlotsCount()) {
			this->release(a2);
		} else {
			this->release(this->linkedSlots[a2].field_0);
			this->linkedSlots[a2].field_0 = -1;
		}
		this->compressLinkedSlotList(a2);
	}
}
void FillingContainer::compressLinkedSlotList(int32_t a2) {
	int32_t v3;		 // r6
	int32_t v4;		 // r4
	int32_t i;		 // r7
	int32_t slotCnt; // r0
	int32_t v7;		 // r3
	int32_t v8;		 // r2

	v3 = this->field_20;
	if(!this->field_20) {
		v4 = a2 - 1;
		for(i = a2;; ++i) {
			++v4;
			slotCnt = this->getLinkedSlotsCount();
			v7 = v4 - v3;
			if(v4 >= slotCnt) {
				break;
			}
			this->linkedSlots[v7].field_0 = this->linkedSlots[i].field_0;
			if(!this->getLinked(v4)) {
				++v3;
			}
		}
		v8 = v7;
		while(v7 < v4) {
			++v7;
			this->linkedSlots[v8++].field_0 = -1;
		}
	}
}
bool_t FillingContainer::contains(ItemInstance* a2) {
	uint32_t i;		  // r4
	ItemInstance* v5; // r0

	for(i = 0;; ++i) {
		if(i >= this->items.size()) {
			return 0;
		}
		v5 = this->items[i];
		if(v5) {
			if(ItemInstance::matches(v5, a2)) {
				break;
			}
		}
	}
	return 1;
}
void FillingContainer::dropAll(bool_t a2) {
	uint32_t i; // r4

	for(i = this->getLinkedSlotsCount(); i < this->items.size(); ++i) {
		this->dropSlot(i, a2, 1);
	}
}
void FillingContainer::dropSlot(int32_t a2, bool_t a3, bool_t a4) {
	int32_t v4;		  // r4
	ItemInstance* v9; // r1

	v4 = a2;
	if(a2 >= 0) {
		if(a2 < this->getLinkedSlotsCount()) {
			v4 = this->linkedSlots[v4].field_0;
		}
		if(v4 >= 0) {
			if(v4 < this->items.size()) {
				v9 = this->items[v4];
				if(v9) {
					if(v9->count) {
						if(!a3) {
							this->doDrop(v9, a4);
						}
						this->items[v4]->count = 0;
						this->release(v4);
						this->compressLinkedSlotList(v4);
					}
				}
			}
		}
	}
}
void FillingContainer::fixBackwardCompabilityItem(ItemInstance& a2) {
	int32_t v3; // r1

	if(Tile::stoneSlabHalf == a2.tileClass) {
		if(Tile::stoneSlabHalf) {
			v3 = a2.getAuxValue() & 7;
			a2.setAuxValue(v3);
		}
	}
}
int32_t FillingContainer::getEmptySlotsCount() {
	int32_t v2;		  // r6
	int32_t i;		  // r4
	ItemInstance* v4; // r0

	v2 = 0;
	for(i = this->getLinkedSlotsCount(); i < this->getContainerSize(); ++i) {
		v4 = this->getItem(i);
		if(!v4 || v4->isNull()) {
			++v2;
		}
	}
	return v2;
}
int32_t FillingContainer::getFreeSlot() {
	int32_t i;		  // r4
	ItemInstance* v3; // r0

	for(i = this->getLinkedSlotsCount(); i < this->getContainerSize(); ++i) {
		v3 = this->getItem(i);
		if(!v3 || v3->isNull()) {
			return i;
		}
	}
	return -1;
}
ItemInstance* FillingContainer::getLinked(int32_t a2) {
	int32_t ls; // r5

	ls = this->getLinkedSlot(a2);
	if(ls < this->getLinkedSlotsCount() || ls >= this->getContainerSize()) {
		return 0;
	} else {
		return this->getItem(ls);
	}
}
int32_t FillingContainer::getLinkedSlot(int32_t a2) {
	if(a2 >= 0 && a2 < this->getLinkedSlotsCount()) {
		return this->linkedSlots[a2].field_0;
	} else {
		return -1;
	}
}
int32_t FillingContainer::getLinkedSlotsCount() {
	return this->linkedSlots.size();
}
int32_t FillingContainer::getNonEmptySlot(int32_t a2) {
	int32_t i;		  // r4
	ItemInstance* v5; // r0

	for(i = this->getLinkedSlotsCount(); i < this->getContainerSize(); ++i) {
		v5 = this->getItem(i);
		if(v5 && v5->getId() == a2 && v5->count > 0) {
			return i;
		}
	}
	return -1;
}
int32_t FillingContainer::getNonEmptySlot(int32_t a2, int32_t a3) {
	int32_t i;		  // r4
	ItemInstance* v7; // r0
	ItemInstance* v8; // r6

	for(i = this->getLinkedSlotsCount(); i < this->getContainerSize(); ++i) {
		v7 = this->getItem(i);
		v8 = v7;
		if(v7 && v7->getId() == a2 && v8->getAuxValue() == a3 && v8->count > 0) {
			return i;
		}
	}
	return -1;
}
int32_t FillingContainer::getSlot(int32_t a2) {
	int32_t i;		  // r4
	ItemInstance* v5; // r0

	for(i = this->getLinkedSlotsCount(); i < this->getContainerSize(); ++i) {
		v5 = this->getItem(i);
		if(v5 && v5->getId() == a2) {
			return i;
		}
	}
	return -1;
}
int32_t FillingContainer::getSlot(int32_t a2, int32_t a3) {
	int32_t i;		  // r4
	ItemInstance* v7; // r0
	ItemInstance* v8; // r8

	for(i = this->getLinkedSlotsCount(); i < this->getContainerSize(); ++i) {
		v7 = this->getItem(i);
		v8 = v7;
		if(v7 && v7->getId() == a2 && v8->getAuxValue() == a3) {
			return i;
		}
	}
	return -1;
}
std::vector<ItemInstance*>* FillingContainer::getSlotList(int32_t&) {
	return &this->items;
}
int32_t FillingContainer::getSlotWithRemainingSpace(const ItemInstance& a2) {
	int32_t i;		  // r4
	ItemInstance* v5; // r0
	ItemInstance* v6; // r6
	Item* itemClass;  // r3
	int32_t count;	  // r8
	int32_t v9;		  // r8
	int32_t aux;	  // r6

	for(i = 0; i < this->getContainerSize(); ++i) {
		v5 = (ItemInstance*)this->getItem(i);
		v6 = v5;
		if(v5) {
			itemClass = a2.itemClass;
			if(itemClass == v5->itemClass) {
				if(itemClass) {
					if(v5->isStackable()) {
						count = v6->count;
						if(count < v6->getMaxStackSize()) {
							v9 = v6->count;
							if(v9 < this->getMaxStackSize()) {
								if(!v6->isStackedByData()) {
									return i;
								}
								aux = v6->getAuxValue();
								if(aux == a2.getAuxValue()) {
									return i;
								}
							}
						}
					}
				}
			}
		}
	}
	return -1;
}
bool_t FillingContainer::hasResource(int32_t a2) {
	return this->field_20 || this->getSlot(a2) >= 0;
}
bool_t FillingContainer::linkEmptySlot(int32_t a2) {
	int32_t v3; // r5
	int32_t i;	// r5

	v3 = this->field_20;
	if(!this->field_20) {
		while(v3 < this->getLinkedSlotsCount()) {
			if(this->linkedSlots[v3].field_0 == a2) {
				return 1;
			}
			++v3;
		}
		for(i = 0; i < this->getLinkedSlotsCount(); ++i) {
			if(!this->getLinked(i)) {
				this->linkedSlots[i].field_0 = a2;
				return 1;
			}
		}
	}
	return 0;
}
bool_t FillingContainer::linkSlot(int32_t a2, int32_t a3) {
	if(a2 < 0) {
		return 0;
	}
	if(a2 >= this->getLinkedSlotsCount()) {
		return 0;
	}
	if(a3 < this->getLinkedSlotsCount()) {
		return 0;
	}
	if(a3 >= this->getContainerSize()) {
		return 0;
	}
	if(a3 == this->linkedSlots[a2].field_0) {
		return 0;
	}
	this->linkedSlots[a2].field_0 = a3;
	return 1;
}
void FillingContainer::load(ListTag* a2) {
	if(this->field_20) {
		if(a2->value.size() == 0) return;
	} else {
		this->clearInventory(-1);
	}
	int32_t v4 = a2->value.size() - 1;
	while(v4 >= 0) {
		Tag* v7;
		if(v4 >= a2->value.size()) {
			v7 = 0;
			a2->field_0 |= 1;
		} else {
			v7 = a2->value[v4];
		}

		if(v7->getId() == 10) { //nullptr ref is possible?
			CompoundTag* v7_ = (CompoundTag*)v7;
			int32_t slot = v7_->getByte("Slot");

			ItemInstance* v9 = ItemInstance::fromTag(v7_);
			if(v9 && v9->isValid) {
				if(!this->field_20 && slot < this->getLinkedSlotsCount()) {
					if(slot < this->items.size() && v9->getId() == 255 && v9->count == 255) {
						int32_t auxv = v9->getAuxValue();
						if(auxv >= this->getLinkedSlotsCount() && auxv < this->items.size()) {
							this->linkSlot(slot, auxv);
						}
					} else {
						v9->getId();
					}
					goto LABEL_46;
				}
				if(slot > 95 || slot < this->getLinkedSlotsCount() || !v9->count) {
					goto LABEL_46;
				}
				if(!this->field_20 && slot >= this->items.size()) {
					this->doDrop(v9, 1);
LABEL_46:
					delete v9;
					goto LABEL_30;
				}
				if(slot < this->items.size()) {
					this->fixBackwardCompabilityItem(*v9);
					this->items[slot] = v9;
				}
			}
		}
LABEL_30:
		--v4;
	}
	this->compressLinkedSlotList(0);
}
void FillingContainer::release(int32_t a2) {
	if(this->getItem(a2)) {
		this->setItem(a2, 0);
	}
}
bool_t FillingContainer::removeResource(const ItemInstance& a2) {
	return this->removeResource(a2, 0) == 0;
}
int32_t FillingContainer::removeResource(const ItemInstance& a2, bool_t a3) {
	int32_t count;		  // r4
	int32_t v7;			  // r0
	ItemInstance* v8;	  // r7
	int32_t v9;			  // r0
	int32_t v10;		  // r3
	int32_t id;			  // r0
	int32_t nonEmptySlot; // r0
	int32_t v13;		  // r7
	int32_t auxValue;	  // r0
	int32_t v15;		  // r1

	if(!this->field_20) {
		count = a2.count;
		while(count > 0) {
			if(!a3 && ((v7 = a2.getId(), Recipe::isAnyAuxValue(v7)) || a2.getAuxValue() == -1)) {
				id = a2.getId();
				nonEmptySlot = this->getNonEmptySlot(id);
			} else {
				v13 = a2.getId();
				auxValue = a2.getAuxValue();
				nonEmptySlot = this->getNonEmptySlot(v13, auxValue);
			}
			v15 = nonEmptySlot;
			if(nonEmptySlot < 0) {
				return count;
			}
			v8 = this->items[nonEmptySlot];
			if(count >= v8->count) {
				v9 = v8->count;
			} else {
				v9 = count;
			}
			v10 = v8->count - v9;
			count -= v9;
			v8->count = v10;
			if(v10 <= 0) {
				this->clearSlot(v15);
			}
		}
	}
	return 0;
}
bool_t FillingContainer::removeResource(int32_t a2) {
	int32_t slot;	  // r0
	ItemInstance* v5; // r2
	int32_t v6;		  // r3

	if(this->field_20) {
		return 1;
	}
	slot = this->getSlot(a2);
	if(slot >= 0) {
		v5 = this->items[slot];
		v6 = v5->count - 1;
		v5->count = v6;
		if(v6 <= 0) {
			this->release(slot);
		}
		return 1;
	}
	return 0;
}
void FillingContainer::replace(std::vector<ItemInstance> a2, int32_t a3) {
	int32_t v6;		   // r3
	int32_t v7;		   // r3
	int32_t slotCnt;   // r7
	int32_t v9;		   // r0
	int32_t v10;	   // r9
	int32_t i;		   // r4
	ItemInstance* v12; // r2

	this->clearInventory(-1);
	v6 = a2.size();
	if(a3 >= 0) {
		v7 = v6;
		//-858993459 * v6;
		if(a3 >= v7) {
			a3 = v7;
		}
	} else {
		a3 = v6;
		//-858993459 * v6;
	}
	slotCnt = this->getLinkedSlotsCount();
	v9 = this->getContainerSize() - slotCnt;
	if(v9 >= a3) {
		v10 = a3;
	} else {
		v10 = v9;
	}
	for(i = 0; i < v10; ++i) {
		if(a2[i].isNull()) {
			v12 = 0;
		} else {
			v12 = &a2[i];
		}
		this->replaceSlot(i + slotCnt, v12);
	}
}
void FillingContainer::replaceSlot(int32_t a2, ItemInstance* a3) {
	ItemInstance** v7; // r2
	ItemInstance* v8;  // r3
	int v9;			   // t1

	if(a3) {
		if(!this->items[a2]) {
			this->items[a2] = new ItemInstance();
		}
		*this->items[a2] = *a3;
	} else {
		this->release(a2);
	}
}
ListTag* FillingContainer::save(ListTag* a2) {
	ItemInstance v14;
	for(int32_t i = 0; i < this->items.size(); ++i) {
		ItemInstance* v5 = this->items[i];
		if(i >= this->getLinkedSlotsCount()) {
			if(!v5) continue;
		} else {
			v14 = ItemInstance(0xff, 255, this->linkedSlots[i].field_0);
			v5 = &v14;
		}
		CompoundTag* v6 = new CompoundTag();
		v6->putByte("Slot", i);
		if(v5->count < 0) v5->count = 0;
		if(v5->count > 255) v5->count = 255;
		ItemInstance ii(*v5);
		ii.save(v6);
		a2->add(v6);
	}
	return a2;
}
void FillingContainer::setContainerChanged() {
}
void FillingContainer::swapSlots(int32_t a2, int32_t a3) {
	ItemInstance* v4 = this->items[a3];
	this->items[a3] = this->items[a2];
	this->items[a2] = v4;
}
void FillingContainer::unlinkSlot(int32_t a2) {
	if(a2 >= 0 && a2 < this->getLinkedSlotsCount()) {
		this->linkedSlots[a2].field_0 = -1;
	}
}

FillingContainer::~FillingContainer() {
	for(int32_t i = this->getLinkedSlotsCount();; ++i) {
		if(i >= this->items.size()) break;
		delete this->items[i];
	}
}
ItemInstance* FillingContainer::getItem(int32_t a2) {
	int32_t v2 = a2;
	if(a2 < 0) return 0;
	if(a2 >= this->items.size()) return 0;
	ItemInstance* result;
	if(a2 >= this->getLinkedSlotsCount()) {
		result = this->getSlotList(v2)->at(a2);
	} else {
		result = this->getLinked(a2);
	}
	if(!result || !result->itemClass) {
		return 0;
	}
	return result;
}
void FillingContainer::setItem(int32_t a2, ItemInstance* a3) {
	int32_t v2 = a2;
	if(a2 >= 0 && a2 < this->items.size()) {
		std::vector<ItemInstance*>* slotList = this->getSlotList(v2);
		if(slotList) {
			delete slotList->at(v2);
			if(a3) {
				(*slotList)[a2] = new ItemInstance(*a3);
			} else {
				(*slotList)[a2] = 0;
			}
		}
	}
}
ItemInstance FillingContainer::removeItem(int32_t a3, int32_t a4) {
	ItemInstance* v8; // r0
	int32_t count;	  // r3
	int32_t v10;	  // r3

	v8 = this->getItem(a3);
	if(v8) {
		if(a4 >= v8->count) {
			count = v8->count;
		} else {
			count = a4;
		}
		v10 = v8->count - count;
		v8->count = v10;
		if(v10 <= 0) {
			this->clearSlot(a3);
		}
	}
	return ItemInstance();
}
std::string FillingContainer::getName() {
	return "Inventory";
}
int32_t FillingContainer::getMaxStackSize() {
	return 254;
}
bool_t FillingContainer::stillValid(Player* a2) {
	return !a2->isDead;
}
void FillingContainer::startOpen() {
}
void FillingContainer::stopOpen() {
}

bool_t FillingContainer::add(ItemInstance* a2) {
	if(this->field_20 || !a2 || a2->isNull()) {
		return 1;
	}
	if(a2->isDamaged()) {
		int32_t freeSlot = this->getFreeSlot();
		if(freeSlot < 0) return 0;
		this->setItem(freeSlot, ItemInstance::clone(a2));
		this->linkEmptySlot(freeSlot);
		a2->count = 0;
		return 1;
	}
	int count, v5;
	do {
		count = a2->count;
		v5 = this->addResource(*a2);
		a2->count = v5;
	} while(v5 > 0 && v5 < count);
	return v5 < count;
}
void FillingContainer::doDrop(ItemInstance*, bool_t) {
}
