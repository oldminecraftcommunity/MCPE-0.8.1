/*
 * WoodSlabTileItem.hpp
 *
 *  Created on: Oct 14, 2026
 *      Author: gh
 */
#include <tile/WoodSlabTile.hpp>
#include <item/AuxDataTileItem.hpp>

#pragma once

struct WoodSlabTile::Item : AuxDataTileItem{
	Item(int id, Tile* tile) : AuxDataTileItem(id, tile){

	}
	virtual ~Item() {
	}
	virtual bool_t useOn(ItemInstance* a2, Player* a3, Level* a4, int32_t x, int32_t y, int32_t z, int32_t face, float a9, float a10, float a11) {
		int32_t AuxValue; // r11
		uint32_t meta;	  // r0
		uint32_t v16;	  // r10
		int32_t v17;	  // r3
		const AABB* v18;  // r0
		int32_t id;		  // [sp+14h] [bp-44h]

		if(a2->count) {
			id = a4->getTile(x, y, z);
			AuxValue = a2->getAuxValue();
			meta = a4->getData(x, y, z);
			v16 = meta;
			v17 = (meta >> 3) & 1;
			if(face == 1) {
				if(v17) {
					return TileItem::useOn(a2, a3, a4, x, y, z, face, a9, a10, a11);
				}
			} else if(face || !v17) {
				return TileItem::useOn(a2, a3, a4, x, y, z, face, a9, a10, a11);
			}
			if(id == Tile::woodSlabHalf->blockID) {
				if((meta ^ AuxValue) << 29) {
					return 0;
				}
				v18 = Tile::woodSlab->getAABB(a4, x, y, z);
				if(a4->isUnobstructed(*v18)) {
					if(a4->setTileAndData(x, y, z, Tile::woodSlab->blockID, v16 | AuxValue, 3)) {
						a4->playSound((float)x + 0.5, (float)y + 0.5, (float)z + 0.5, Tile::woodSlab->soundType->field_C, (float)(Tile::woodSlab->soundType->field_0 + 1.0) * 0.5, Tile::woodSlab->soundType->field_4 * 0.8);
						--a2->count;
					}
				}
				return 1;
			}
			return TileItem::useOn(a2, a3, a4, x, y, z, face, a9, a10, a11);
		}
		return 0;
	}

};
