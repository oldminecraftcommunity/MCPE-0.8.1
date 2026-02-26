#include <tile/entity/FurnaceTileEntity.hpp>
#include <crafting/FurnaceRecipes.hpp>
#include <entity/Player.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>
#include <nbt/ListTag.hpp>
#include <tile/FurnaceTile.hpp>
#include <tile/material/Material.hpp>

int32_t FurnaceTileEntity::getBurnDuration(const ItemInstance& a1) {
	int32_t itemID; // r5

	if(!a1.isNull()) {
		itemID = a1.itemClass->itemID;
		if(itemID <= 255 && Tile::tiles[itemID]->material == Material::wood) {
			return 300;
		}
		if(itemID == Item::stick->itemID) {
			return 100;
		}
		if(itemID == Item::coal->itemID) {
			return 1600;
		}
		if(itemID == Item::bucket->itemID && a1.getAuxValue() == Tile::lava->blockID) {
			return 20000;
		}
		if(itemID == Tile::sapling->blockID) {
			return 100;
		}
		if(itemID == Tile::coalBlock->blockID) {
			return 16000;
		}
		if(itemID == Item::bow->itemID || itemID == Item::bowl->itemID || itemID == Item::shovel_wood->itemID || itemID == Item::hoe_wood->itemID || itemID == Item::pickAxe_wood->itemID || itemID == Item::sword_wood->itemID) {
			return 200;
		}
	}
	return 0;
}
bool_t FurnaceTileEntity::isFuel(const ItemInstance& a1) {
	return FurnaceTileEntity::getBurnDuration(a1) > 0;
}

FurnaceTileEntity::FurnaceTileEntity()
	: TileEntity(1) {
	this->field_5C = -1;
	this->field_60 = 2;
	this->field_64 = 0;
	this->burnTime = 0;
	this->field_6C = 0;
	this->cookTime = 0;
	this->field_B0 = 0;
	this->field_B1 = 0;
}
void FurnaceTileEntity::burn() {
	Item* itemClass; // r3
	int32_t v9;		 // r3

	if(this->canBurn()) {
		ItemInstance v10 = FurnaceRecipes::getInstance()->getResult(this->inventory[0].itemClass->itemID);
		if(this->inventory[2].isNull()) {
			this->inventory[2] = v10;
		} else {
			itemClass = this->inventory[2].itemClass;
			if(itemClass == v10.itemClass) {
				if(itemClass) {
					++this->inventory[2].count;
				}
			}
		}
		v9 = this->inventory[0].count - 1;
		this->inventory[0].count = v9;
		if(v9 <= 0) {
			this->inventory[0].setNull();
		}
	}
}
bool_t FurnaceTileEntity::canBurn() {
	int32_t count; // r6
	int32_t v5;	   // r6
	int32_t v6;	   // r4

	if(this->inventory[0].isNull()) {
		return 0;
	}
	ItemInstance v7 = FurnaceRecipes::getInstance()->getResult(this->inventory[0].itemClass->itemID);
	if(v7.isNull()) {
		return 0;
	}
	if(this->inventory[2].isNull()) {
		return 1;
	}
	if(!this->inventory[2].sameItemAndAux(&v7)) {
		return 0;
	}
	count = this->inventory[2].count;
	if(count < this->getMaxStackSize()) {
		v5 = this->inventory[2].count;
		if(v5 < this->inventory[2].getMaxStackSize()) {
			return 1;
		}
	}
	v6 = this->inventory[2].count;
	return v6 < v7.getMaxStackSize();
}
int32_t FurnaceTileEntity::getBurnProgress(int32_t a2) {
	return this->cookTime * a2 / 200;
}
int32_t FurnaceTileEntity::getLitProgress(int32_t a2) {
	int32_t r; // r0

	if(!this->field_6C) {
		this->field_6C = 200;
	}
	r = this->burnTime * a2 / this->field_6C;
	if(r >= a2) {
		return a2;
	}
	return r;
}
bool_t FurnaceTileEntity::isLit() {
	return this->burnTime > 0;
}
bool_t FurnaceTileEntity::isSlotEmpty(int32_t a2) {
	return this->inventory[a2].isNull();
}

FurnaceTileEntity::~FurnaceTileEntity() {
}
bool_t FurnaceTileEntity::shouldSave() {
	if(this->burnTime <= 0) {
		int32_t v2 = 0;
		while(this->inventory[2].isNull()) {
			if(++v2 == 3) return 0;
		}
	}
	return 1;
}
void FurnaceTileEntity::load(CompoundTag* a2) {
	TileEntity::load(a2);
	ListTag* v4 = a2->getList("Items");
	this->inventory[0].setNull();
	this->inventory[1].setNull();
	this->inventory[2].setNull();
	for(int32_t i = 0; i < v4->value.size(); ++i) {
		Tag* t = v4->value[i];
		if(t->getId() == 10) {
			CompoundTag* v6 = (CompoundTag*)t;
			int32_t slot = (uint8_t)v6->getByte("Slot");
			if(slot <= 2) {
				ItemInstance* v8 = ItemInstance::fromTag(v6);
				if(v8) {
					this->inventory[slot] = *v8;
					delete v8;
				} else {
					this->inventory[slot].setNull();
				}
			}
		}
	}
	this->burnTime = a2->getShort("BurnTime");
	this->cookTime = a2->getShort("CookTime");
	this->field_6C = FurnaceTileEntity::getBurnDuration(this->inventory[1]);
}
bool_t FurnaceTileEntity::save(CompoundTag* a2) {
	if(TileEntity::save(a2)) {
		a2->putShort("BurnTime", this->burnTime);
		a2->putShort("CookTime", this->cookTime);
		ListTag* v5 = new ListTag();
		for(int32_t i = 0; i != 3; ++i) {
			if(!this->inventory[i].isNull()) {
				CompoundTag* v7 = new CompoundTag();
				v7->putByte("Slot", i);
				this->inventory[i].save(v7);
				v5->value.insert(v5->value.end(), v7);
			}
		}
		a2->put("Items", v5);
		return 1;
	}
	return 0;
}
void FurnaceTileEntity::tick() {
	int32_t burnTime;	  // r3
	int32_t v3;			  // r6
	int32_t v4;			  // r5
	int32_t v5;			  // r0
	int32_t burnDuration; // r0
	int32_t v7;			  // r3

	burnTime = this->burnTime;
	v3 = burnTime > 0;
	if(burnTime > 0) {
		this->burnTime = burnTime - 1;
	}
	if(!this->level->isClientMaybe) {
		v4 = this->burnTime;
		if(!v4 && this->canBurn()) {
			burnDuration = FurnaceTileEntity::getBurnDuration(this->inventory[1]);
			this->burnTime = burnDuration;
			this->field_6C = burnDuration;
			if(burnDuration > 0) {
				if(!this->inventory[1].isNull()) {
					this->inventory[1].useAsFuel();
				}
				v4 = 1;
			}
		} else {
			v4 = 0;
		}
		if(this->isLit() && this->canBurn()) {
			v7 = this->cookTime + 1;
			this->cookTime = v7;
			if(v7 == 200) {
				this->cookTime = 0;
				v4 = 1;
				this->burn();
			}
		} else {
			this->cookTime = 0;
		}
		v5 = this->burnTime > 0;
		if(v3 != v5) {
			FurnaceTile::setLit(v5, this->level, this->posX, this->posY, this->posZ);
LABEL_16:
			this->setChanged();
			return;
		}
		if(v4) {
			goto LABEL_16;
		}
	}
	if(!v3) {
		this->field_B1 = 1;
	}
}
bool_t FurnaceTileEntity::isFinished() {
	if(this->field_B0) {
		return this->field_B1;
	} else {
		return this->field_B0;
	}
}
void FurnaceTileEntity::setRemoved() {
	if(!this->field_64) {
		this->setRemoved();
	}
}
ItemInstance* FurnaceTileEntity::getItem(int32_t a2) {
	return &this->inventory[a2];
}
void FurnaceTileEntity::setItem(int32_t a2, ItemInstance* a3) {
	this->inventory[a2] = *a3;
	if(a3->count > this->getMaxStackSize()) {
		this->inventory[a2].count = this->getMaxStackSize();
	}
}
ItemInstance FurnaceTileEntity::removeItem(int32_t a3, int32_t a4) {
	if(!this->inventory[a3].isNull()) {
		if(this->inventory[a3].count > a4) {
			ItemInstance v10 = this->inventory[a3].remove(a4);
			if(this->inventory[a3].count) {
				return ItemInstance(v10);
			}
			this->inventory[a3].setNull();
			return ItemInstance(v10);
		} else {
			this->inventory[a3].setNull();
			return ItemInstance(ItemInstance(this->inventory[a3]));
		}
	}
	return ItemInstance();
}
std::string FurnaceTileEntity::getName() {
	return "Furnace";
}
int32_t FurnaceTileEntity::getMaxStackSize() {
	return 64;
}
int32_t FurnaceTileEntity::getContainerSize() {
	return 3;
}
bool_t FurnaceTileEntity::stillValid(Player* a2) {
	TileEntity* te; // r0

	te = this->level->getTileEntity(this->posX, this->posY, this->posZ);
	return te == this && a2->distanceToSqr((float)te->posX + 0.5, (float)te->posY + 0.5, (float)te->posZ + 0.5) <= 64.0;
}
void FurnaceTileEntity::startOpen() {
}
void FurnaceTileEntity::stopOpen() {
}
