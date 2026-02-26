#include <item/ItemInstance.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <nbt/CompoundTag.hpp>
#include <nbt/ByteTag.hpp>

ItemInstance::ItemInstance(const Item* a2) {
	this->init(a2->itemID, 1, 0);
}
ItemInstance::ItemInstance(const Item* a2, int32_t a3) {
	this->init(a2->itemID, a3, 0);
}
ItemInstance::ItemInstance(const Item* a2, int32_t a3, int32_t a4) {
	this->init(a2->itemID, a3, a4);
}
ItemInstance::ItemInstance(const ItemInstance& a2) {
	this->init(a2.getId(), a2.count, a2.metadata);
}

ItemInstance::ItemInstance(const Tile* a2) {
	this->init(a2->blockID, 1, 0);
}
ItemInstance::ItemInstance(const Tile* a2, int32_t a3) {
	this->init(a2->blockID, a3, 0);
}
ItemInstance::ItemInstance(const Tile* a2, int32_t a3, int32_t a4) {
	this->init(a2->blockID, a3, a4);
}
ItemInstance::ItemInstance(bool_t a2) {
	this->init(0, 0, 0);
	this->isValid = a2;
}
ItemInstance::ItemInstance(int32_t a2, int32_t a3, int32_t a4) {
	this->init(a2, a3, a4);
}
ItemInstance::ItemInstance(void) {
	this->init(0, 0, 0);
}
bool_t ItemInstance::_setItem(int32_t itemID) {
	Item* itemClass; // r0
	bool_t result; // r0
	Tile* tileClass; // r2

	if((uint32_t)itemID >= 512) {
		itemClass = 0;
	} else {
		itemClass = Item::items[itemID];
	}
	this->itemClass = itemClass;
	if(itemClass) {
		result = 1;
	} else {
		result = itemID == 0;
	}
	this->isValid = result;
	if(result) {
		if(itemID > 255) {
			tileClass = 0;
		} else {
			tileClass = Tile::tiles[itemID];
		}
		this->tileClass = tileClass;
	} else {
		this->itemClass = 0;
		this->tileClass = 0;
		this->count = -1;
		this->metadata = -1;
	}
	return result;
}
bool_t ItemInstance::canDestroySpecial(Tile* a2) {
	return this->itemClass->canDestroySpecial(a2);
}
ItemInstance* ItemInstance::clone(const ItemInstance* a) {
	if(!a) return 0;
	return new ItemInstance(*a);
}

ItemInstance ItemInstance::cloneSafe(const ItemInstance* cloneDst) {
	if(cloneDst) return ItemInstance(*cloneDst);
	return ItemInstance();
}
ItemInstance* ItemInstance::fromTag(CompoundTag* a1) {
	ItemInstance* is = new ItemInstance();
	is->load(a1);
	if(!is->itemClass) {
		delete is;
		is = 0;
	}
	return is;
}
int32_t ItemInstance::getAttackDamage(Entity* a2) {
	return this->itemClass->getAttackDamage(a2);
}
int32_t ItemInstance::getAuxValue() const {
	return this->metadata;
}
int32_t ItemInstance::getDamageValue() const {
	return this->metadata;
}
std::string ItemInstance::getDescriptionId() const {
	return this->itemClass->getDescriptionId(this);
}
float ItemInstance::getDestroySpeed(Tile* a2) {
	return this->itemClass->getDestroySpeed(this, a2);
}
TextureUVCoordinateSet* ItemInstance::getIcon(int32_t a2, bool_t a3) const{
	return this->itemClass->getIcon(this->metadata, a2, a3);
}
int32_t ItemInstance::getId() const {
	if(this->isValid) {
		if(this->itemClass) return this->itemClass->itemID;
	} else {
		return -1;
	}
	return 0;
}
int32_t ItemInstance::getMaxDamage() const {
	return this->itemClass->getMaxDamage();
}
int32_t ItemInstance::getMaxStackSize() const {
	return this->itemClass->getMaxStackSize(this);
}
int32_t ItemInstance::getMaxUseDuration() {
	return this->itemClass->getMaxUseDuration();
}
std::string ItemInstance::getName() {
	return this->itemClass->getName(this);
}
int32_t ItemInstance::getUseAnimation() const {
	return this->itemClass->getUseAnimation();
}
void ItemInstance::hurtAndBreak(int32_t destroyAmountMaybe, Mob* a3) {
	int32_t newCount; // r6
	int32_t newMeta; // r3
	Level* level; // r6
	float posX; // r8
	float posY; // r7
	float posZ; // r5

	if(this->isDamageableItem()) {
		newCount = destroyAmountMaybe + this->metadata;
		this->metadata = newCount;
		if(newCount > this->getMaxDamage()) {
			newMeta = this->count - 1;
			if(newMeta < 0) {
				newMeta = 0;
			}
			this->count = newMeta;
			this->metadata = 0;
			level = a3->level;
			posX = a3->posX;
			posY = a3->posY;
			posZ = a3->posZ;
			level->playSound(posX, posY, posZ, "random.break", 1.0, 0.9);
		}
	}
}
void ItemInstance::hurtEnemy(Mob* a2, Mob* a3) {
	this->itemClass->hurtEnemy(this, a2, a3);
}
void ItemInstance::init(int32_t itemID, int32_t count, int32_t meta) {
	this->count = count;
	this->metadata = meta;
	this->_setItem(itemID);
}
void ItemInstance::interactEnemy(Mob* a2, Player* a3) {
	this->itemClass->interactEnemy(this, a2, a3);
}
bool_t ItemInstance::isArmorItem(const ItemInstance* a1) {
	if(a1) {
		if(a1->itemClass) {
			return a1->itemClass->isArmor();
		}
	}
	return 0;
}
bool_t ItemInstance::isDamageableItem() const {
	return this->itemClass->getMaxDamage() > 0;
}
bool_t ItemInstance::isDamaged() const {
	if(this->isDamageableItem()) return this->metadata > 0;
	return 0;
}
bool_t ItemInstance::isItem(const ItemInstance* a1) {
	if(a1) return a1->itemClass != 0;
	return 0;
}
bool_t ItemInstance::isLiquidClipItem() {
	if(this->itemClass) return this->itemClass->isLiquidClipItem(this->metadata);
	return 0;
}
bool_t ItemInstance::isNull() const {
	if(!this->isValid) return 1;
	if(this->count) return 0;
	if(this->metadata) return this->count;
	return this->itemClass == 0;
}
bool_t ItemInstance::isStackable(const ItemInstance* a1, const ItemInstance* a2) {
	int32_t AuxValue; // r5

	if(!a1 || !a2 || a1->itemClass != a2->itemClass || !a2->isStackable()) {
		return 0;
	}
	if(!a2->isStackedByData()) {
		return 1;
	}
	AuxValue = a1->getAuxValue();
	return AuxValue == a2->getAuxValue();
}
bool_t ItemInstance::isStackable() const {
	if(this->getMaxStackSize() <= 1) return 0;
	if(this->isDamageableItem()) return !this->isDamaged();
	return 1;
}
bool_t ItemInstance::isStackedByData() const {
	return this->itemClass->isStackedByData();
}
void ItemInstance::load(CompoundTag* a2) {
	int16_t id = a2->getShort("id");
	this->_setItem(id);
	if(a2->contains("Count", 1)) {
		this->count = ((ByteTag*)a2->get("Count"))->value;
	} else {
		this->count = 0;
	}

	this->metadata = a2->getShort("Damage");
}
bool_t ItemInstance::matches(const ItemInstance* a2) const {
	if(this->itemClass == a2->itemClass && this->count == a2->count) {
		return this->metadata - a2->metadata + (this->metadata == a2->metadata) + a2->metadata - this->metadata;
	}
	return 0;
}
bool_t ItemInstance::matches(const ItemInstance* a1, const ItemInstance* a2) {
	if(!a1) return a2 == 0;
	if(a2) return a1->matches(a2);
	return 0;
}
bool_t ItemInstance::matchesNulls(const ItemInstance* a1, const ItemInstance* a2) {
	bool_t isNull;
	if(a1) isNull = a1->isNull();
	else isNull = 1;

	if(a2) {
		bool_t r = a2->isNull();
		if(isNull) return r;
		if(r) return 0;

		return a1->matches(a2);
	} else {
		return isNull != 0;
	}
}
bool_t ItemInstance::mineBlock(int32_t a2, int32_t a3, int32_t a4, int32_t a5, Mob* a6) {
	return this->itemClass->mineBlock(this, a2, a3, a4, a5, a6);
}
bool_t ItemInstance::operator==(const ItemInstance& a2) {
	return this->matches(&a2);
}
void ItemInstance::releaseUsing(Level* a2, Player* a3, int32_t a4) {
	this->itemClass->releaseUsing(this, a2, a3, a4);
}
ItemInstance ItemInstance::remove(int32_t a3) {
	this->count -= a3;
	return ItemInstance(this->itemClass, a3, this->metadata);
}
bool_t ItemInstance::sameItem(ItemInstance* a2) const{
	if(!a2) return 0;
	return this->itemClass == a2->itemClass && this->itemClass != 0;
}
bool_t ItemInstance::sameItemAndAux(ItemInstance* a2) {
	if(a2) {
		if(this->itemClass == a2->itemClass && this->itemClass) {
			return this->metadata == a2->metadata;
		}
	}
	return 0;
}
void ItemInstance::save(CompoundTag* a2) {
	a2->putShort("id", this->getId());
	a2->putByte("Count", this->count);
	a2->putShort("Damage", this->metadata);
}
void ItemInstance::setAuxValue(int32_t a2) {
	this->metadata = a2;
}
void ItemInstance::setDescriptionId(const std::string&) {
}
void ItemInstance::setNull() {
	this->metadata = 0;
	this->count = 0;
	this->itemClass = 0;
}
void ItemInstance::snap(Player*) {
}
std::string ItemInstance::toString() {
	//TODO check
	return "" + std::to_string(this->count) + " x " + this->getDescriptionId() + "(" + std::to_string(this->itemClass->itemID) + ")" + "@" + std::to_string(this->metadata);
}
ItemInstance* ItemInstance::use(Level* a2, Player* a3) {
	return this->itemClass->use(this, a2, a3);
}
void ItemInstance::useAsFuel() {
	if(this->count == 1 && this->itemClass == Item::bucket && this->getAuxValue() == Tile::lava->blockID) {
		ItemInstance v7(this->itemClass, 1, 0);
		//TODO there is some weird loop here
		this->count = v7.count;
		this->metadata = v7.metadata;
		this->itemClass = v7.itemClass;
		this->tileClass = v7.tileClass;
		this->isValid = v7.isValid;
	} else {
		this->count = this->count - 1;
		if(!this->count) this->setNull();
	}
}
bool_t ItemInstance::useOn(Player* a2, Level* a3, int32_t a4, int32_t a5, int32_t a6, int32_t a7, float a8, float a9, float a10) {
	return this->itemClass->useOn(this, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}
ItemInstance ItemInstance::useTimeDepleted(Level* a2, Player* a3) {
	return this->itemClass->useTimeDepleted(this, a2, a3);
}
