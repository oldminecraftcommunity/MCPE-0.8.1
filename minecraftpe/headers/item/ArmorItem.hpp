#pragma once
#include <item/Item.hpp>

struct ArmorItem: Item
{
	struct ArmorMaterial
	{
		int32_t health;
		int32_t defenceForSlot[4]; //licenCe > licenSe *coloUwUr*
		ArmorMaterial(int32_t h, int32_t d0, int32_t d1, int32_t d2, int32_t d3);

		int32_t getDefenseForSlot(int32_t) const; //>=< :wsndow0_angry:
		int32_t getHealthForSlot(int32_t) const;
	};
	static int32_t healthPerSlot[];
	static ArmorMaterial CLOTH, CHAIN, IRON, GOLD, DIAMOND;

	int32_t field_48, defenseForSlot, field_50;
	const ArmorItem::ArmorMaterial* armorMaterial;

	ArmorItem(int32_t, const ArmorItem::ArmorMaterial&, int32_t, int32_t);

	virtual ~ArmorItem();
	virtual bool_t isArmor();
};
