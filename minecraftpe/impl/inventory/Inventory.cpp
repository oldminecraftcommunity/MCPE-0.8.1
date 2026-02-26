#include <inventory/Inventory.hpp>
#include <entity/Player.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

Inventory::Inventory(Player* a2, bool_t a3)
	: FillingContainer(9, 9, -1, a3) {
	this->player = a2;
	this->selectedSlot = 0;
	this->setupDefault();
	this->compressLinkedSlotList(0);
}
bool_t Inventory::canDestroy(Tile* a2) {
	if(a2->material->isAlwaysDestroyable()) {
		return 1;
	}
	ItemInstance* res = this->getSelected();
	if(res) return res->canDestroySpecial(a2);
	return 0;
}
void Inventory::clearInventoryWithDefault() {
	this->clearInventory(-1);
	this->setupDefault();
}
int32_t Inventory::getAttackDamage(Entity* a2) {
	ItemInstance* sel = this->getSelected();
	if(sel) return sel->getAttackDamage(a2);
	return 1;
}
float Inventory::getDestroySpeed(Tile* a2) {
	ItemInstance* sel = this->getSelected();
	if(sel) {
		return sel->getDestroySpeed(a2);
	}
	return 1;
}
int32_t Inventory::getLinkedSlotForItem(int32_t a2) {
	int32_t v3;		  // r4
	ItemInstance* v4; // r6

	v3 = 0;
	v4 = this->getItem(a2);
	while(v3 < this->getLinkedSlotsCount()) {
		if(v4 == this->getLinked(v3)) {
			return v3;
		}
		++v3;
	}
	return -1;
}
int32_t Inventory::getLinkedSlotForItemAndAux(int32_t a2, int32_t a3) {
	int32_t i;			  // r4
	ItemInstance* linked; // r0
	ItemInstance* v8;	  // r0

	for(i = 0; i < this->getLinkedSlotsCount(); ++i) {
		if(this->getLinked(i)) {
			linked = this->getLinked(i);
			if(linked->getId() == a2) {
				v8 = this->getLinked(i);
				if(v8->getAuxValue() == a3) {
					return i;
				}
			}
		}
	}
	return -1;
}
ItemInstance* Inventory::getSelected() {
	int32_t selectedSlot; // r1

	selectedSlot = this->selectedSlot;
	if(selectedSlot < 0 || selectedSlot >= this->items.size()) {
		return 0;
	} else {
		return this->getLinked(selectedSlot);
	}
}
int32_t Inventory::getSelectionSize() {
	return 9;
}
bool_t Inventory::moveToEmptySelectionSlot(int32_t a2) {
	return this->linkEmptySlot(a2);
}
bool_t Inventory::moveToSelectedSlot(int32_t a2) {
	return this->linkSlot(this->selectedSlot, a2);
}
bool_t Inventory::moveToSelectionSlot(int32_t a2, int32_t a3) {
	return this->linkSlot(a2, a3);
}
bool_t Inventory::removeItemInstance(const ItemInstance* a2) {
	int32_t i; // r3

	for(i = 9; i < this->items.size(); ++i) {
		if(this->items[i] == a2) {
			this->clearSlot(i);
			return 1;
		}
	}
	return 0;
}
void Inventory::selectSlot(int32_t a2) {
	if((uint32_t)a2 <= 8) {
		this->selectedSlot = a2;
	}
}
void Inventory::setupDefault() {
	if(this->field_20) {
		this->items.resize(9); //TODO check is this done like this
		this->items.emplace_back(new ItemInstance(Tile::rock));
		this->items.emplace_back(new ItemInstance(Tile::stoneBrick));
		this->items.emplace_back(new ItemInstance(Tile::dirt));
		this->items.emplace_back(new ItemInstance(Tile::wood));
		this->items.emplace_back(new ItemInstance(Tile::wood, 1, 1));
		this->items.emplace_back(new ItemInstance(Tile::torch));
		this->items.emplace_back(new ItemInstance(Tile::stairs_brick));
		this->items.emplace_back(new ItemInstance(Tile::cobbleWall));
		this->items.emplace_back(new ItemInstance(Tile::sapling));
		for(int32_t i = 0; i != 9; ++i) {
			this->linkSlot(i, i + 9);
		}
	} else {
		this->clearInventory(45);
	}
	for(int32_t j = 0;; ++j) {
		if(j >= (uint32_t)this->items.size()) {
			break;
		}
		ItemInstance* v18 = this->items[j];
		if(v18 && this->field_20) {
			v18->count = 5;
		} else if((uint32_t)j <= 8) {
			this->items[j] = 0;
		}
	}
}

Inventory::~Inventory() {
}
int32_t Inventory::getContainerSize() {
	return this->items.size();
}
bool_t Inventory::stilValid(Player* a2) {
	return !this->player->isDead && a2->distanceToSqr(this->player) <= 64;
}
bool_t Inventory::add(ItemInstance* a2) {
	return this->field_20 || this->player->field_CB4 || FillingContainer::add(a2);
}

void Inventory::doDrop(ItemInstance* a2, bool_t a3) {
	return this->player->drop(a2, a3);
}
