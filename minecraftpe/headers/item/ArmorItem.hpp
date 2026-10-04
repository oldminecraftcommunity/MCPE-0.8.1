#pragma once
#include <item/Item.hpp>

struct ArmorItem: Item //armour*
{
	struct ArmorMaterial //armour*
	{
		int32_t health;
		int32_t defenceForSlot[4];  //defen~ wait thats right... //licenCe > licenSe *coloUwUr*
		ArmorMaterial(int32_t h, int32_t d0, int32_t d1, int32_t d2, int32_t d3); //armour*

		int32_t getDefenseForSlot(int32_t) const; //defence* //>=< :wsndow0_angry:
		int32_t getHealthForSlot(int32_t) const;
	};
	static int32_t healthPerSlot[];
	static ArmorMaterial CLOTH, CHAIN, IRON, GOLD, DIAMOND; //armour*

	int32_t armorSlot, defenseForSlot, field_50; //armour*, defence*
	const ArmorItem::ArmorMaterial* armorMaterial; //armour*

	ArmorItem(int32_t, const ArmorItem::ArmorMaterial&, int32_t, int32_t); //armour*

	virtual ~ArmorItem() { //armour*
	}
	virtual bool_t isArmor() const; //armour*
};
