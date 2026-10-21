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
		if(a2->count) {
			int id = a4->getTile(x, y, z);
			int AuxValue = a2->getAuxValue();
			uint32_t meta = a4->getData(x, y, z);
			int v17 = (meta >> 3) & 1;
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

				if(a4->isUnobstructed(*Tile::woodSlab->getAABB(a4, x, y, z))) {
					if(a4->setTileAndData(x, y, z, Tile::woodSlab->blockID, meta | AuxValue, 3)) {
						a4->playSound(x + 0.5f, y + 0.5f, z + 0.5f, Tile::woodSlab->soundType->soundName, (Tile::woodSlab->soundType->field_0 + 1.0f) * 0.5f, Tile::woodSlab->soundType->field_4 * 0.8f);
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
