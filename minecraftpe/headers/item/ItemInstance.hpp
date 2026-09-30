#pragma once
#include <_types.h>
#include <string>
struct Item;
struct Tile;
struct CompoundTag;
struct Entity;
struct TextureUVCoordinateSet;
struct Mob;
struct Player;
struct Level;


struct ItemInstance{
	int32_t count;
	int32_t metadata;
	Item* itemClass;
	Tile* tileClass;
	bool isValid;

	ItemInstance(const Item*);
	ItemInstance(const Item*, int32_t);
	ItemInstance(const Item*, int32_t, int32_t);
	ItemInstance(const ItemInstance&);
	ItemInstance(const Tile*);
	ItemInstance(const Tile*, int32_t);
	ItemInstance(const Tile*, int32_t, int32_t);
	ItemInstance(bool_t);
	ItemInstance(int32_t, int32_t, int32_t);
	ItemInstance(void);
	bool_t _setItem(int32_t);
	bool_t canDestroySpecial(Tile*);
	static ItemInstance* clone(const ItemInstance*);
	static ItemInstance cloneSafe(const ItemInstance*);
	static ItemInstance* fromTag(CompoundTag*);
	int32_t getAttackDamage(Entity*);
	int32_t getAuxValue() const;
	int32_t getDamageValue() const;
	std::string getDescriptionId() const;
	float getDestroySpeed(Tile*);
	const TextureUVCoordinateSet* getIcon(int32_t, bool_t) const;
	int32_t getId() const;
	int32_t getMaxDamage() const;
	int32_t getMaxStackSize() const;
	int32_t getMaxUseDuration() const;
	std::string getName() const;
	int32_t getUseAnimation() const;
	void hurtAndBreak(int32_t, Mob*);
	void hurtEnemy(Mob*, Mob*);
	void init(int32_t, int32_t, int32_t);
	void interactEnemy(Mob*, Player*);
	static bool_t isArmorItem(const ItemInstance*);
	bool_t isDamageableItem() const;
	bool_t isDamaged() const;
	static bool_t isItem(const ItemInstance*);
	bool_t isLiquidClipItem();
	bool_t isNull() const;
	static bool_t isStackable(const ItemInstance*, const ItemInstance*);
	bool_t isStackable() const;
	bool_t isStackedByData() const;
	void load(CompoundTag*);
	bool_t matches(const ItemInstance*) const;
	static bool_t matches(const ItemInstance*, const ItemInstance*);
	static bool_t matchesNulls(const ItemInstance*, const ItemInstance*);
	bool_t mineBlock(int32_t, int32_t, int32_t, int32_t, Mob*);
	bool_t operator==(const ItemInstance&) const;
	void releaseUsing(Level*, Player*, int32_t);
	ItemInstance remove(int32_t);
	bool_t sameItem(ItemInstance* a2) const {
		if (!a2) return 0;

		return this->itemClass == a2->itemClass && this->itemClass;
	}
	bool_t sameItemAndAux(ItemInstance*) const;
	void save(CompoundTag*);
	void setAuxValue(int32_t);
	void setDescriptionId(const std::string&);
	void setNull();
	void snap(Player*);
	std::string toString() const;
	ItemInstance* use(Level*, Player*);
	void useAsFuel();
	bool_t useOn(Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	ItemInstance useTimeDepleted(Level*, Player*);
};
