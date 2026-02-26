#include <item/BucketItem.hpp>
#include <tile/Tile.hpp>
#include <entity/Player.hpp>
#include <inventory/Inventory.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

BucketItem::BucketItem(int32_t id)
	: Item(id) {
	TextureAtlasTextureItem* texItem = this->getTextureItem("bucket");
	this->field_48 = *texItem->getUV(0);
	this->field_78 = *texItem->getUV(1);
	this->field_90 = *texItem->getUV(2);
	this->field_60 = *texItem->getUV(3);
	this->setStackedByData(1);
	this->setMaxDamage(0);
}
bool_t BucketItem::emptyBucket(Level* level, int32_t type, int32_t x, int32_t y, int32_t z){
	int32_t v10;   // r9
	Material* v11; // r0

	if(type <= 0) {
		return 0;
	}
	v10 = level->getTile(x, y, z);
	if(v10) {
		v11 = level->getMaterial(x, y, z);
		if(v11->isSolid()) {
			return 0;
		}
	}
	level->setTileAndData(x, y, z, type, 0, 3);
	if(type == Tile::water->blockID && (v10 == Tile::fire->blockID || v10 == Tile::lava->blockID || v10 == Tile::calmLava->blockID)) {
		level->playSound((float)x + 0.5, (float)y + 0.5, (float)z + 0.5, "random.fizz", 0.5, (float)((float)(level->random.nextFloat() - level->random.nextFloat()) * 0.8) + 2.6);
	}
	return 1;
}

BucketItem::~BucketItem() {
}
int32_t BucketItem::getMaxStackSize(const ItemInstance* a2) {
	if(a2->getAuxValue()) return 1;
	return 16;
}
TextureUVCoordinateSet* BucketItem::getIcon(int32_t a2, int32_t, bool_t) {
	if(a2 == Tile::water->blockID) {
		return &this->field_90;
	}
	if(a2 == Tile::lava->blockID) {
		return &this->field_60;
	}
	if(a2 == 1) {
		return &this->field_78;
	}
	return &this->field_48;
}
bool_t BucketItem::useOn(ItemInstance* item, Player* player, Level* level, int32_t x, int32_t y, int32_t z, int32_t face, float fx, float fy, float fz) {
	ItemInstance* v12; // r4
	int32_t v14;		   // r5
	int32_t v15;		   // r6
	int32_t v16;		   // r7
	Material* v17;	   // r0
	Material* v18;	   // r11
	Tile* v19;		   // r3
	int32_t v20;		   // r3
	ItemInstance* v21; // r3
	int32_t metadata;	   // r1
	bool_t v23;		   // zf
	int32_t v24;		   // r3
	int32_t v25;		   // r1
	int32_t meta;		   // [sp+10h] [bp-48h]

	v12 = item;
	v14 = x;
	v15 = y;
	v16 = z;
	meta = item->getAuxValue();
	if(player->inventory->getEmptySlotsCount() > 0 || v12->count == 1) {
		if(!meta) {
LABEL_5:
			v17 = level->getMaterial(x, y, z);
			v18 = v17;
			if(v17 != Material::water && v17 != Material::lava || level->getData(x, y, z)) {
				return 0;
			}
			level->removeTile(x, y, z);
			if(player->abilities.instabuild) {
				return 1;
			}
			if(v18 == Material::water) {
				v19 = Tile::water;
			} else {
				v19 = Tile::lava;
			}
			ItemInstance v29(Item::bucket, 1, v19->blockID);
			v20 = v12->count - 1;
			v12->count = v20;
			if(!v20) {
				/*v21 = &v29;
				do
				{
					metadata = v21->metadata;
					v23 = &v21->itemClass == (Item **)&v29.isValid;
					v12->count = v21->count;
					v21 = (ItemInstance *)((char *)v21 + 8);
					v12->metadata = metadata;
					v12 = (ItemInstance *)((char *)v12 + 8);
				}
				while ( !v23 );*/
				*v12 = v29;
				return 1;
			}
			player->inventory->add(&v29);
			return 1;
		}
LABEL_17:
		if(meta <= 1) {
			return 0;
		}
		if(face) {
			switch(face) {
				case 1:
					v15 = y + 1;
					break;
				case 2:
					v16 = z - 1;
					break;
				case 3:
					v16 = z + 1;
					break;
				case 4:
					v14 = x - 1;
					break;
				case 5:
					v14 = x + 1;
					break;
			}
		} else {
			v15 = y - 1;
		}
		if(!this->emptyBucket(level, meta, v14, v15, v16)) {
			return 0;
		}
		ItemInstance v29(Item::bucket, 1, 0);
		v24 = v12->count - 1;
		v12->count = v24;
		if(!v24) {
			/*v21 = &v29;
			do
			{
				v25 = v21->metadata;
				v23 = &v21->itemClass == (Item **)&v29.isValid;
				v12->count = v21->count;
				v21 = (ItemInstance *)((char *)v21 + 8);
				v12->metadata = v25;
				v12 = (ItemInstance *)((char *)v12 + 8);
			}
			while ( !v23 );*/
			*v12 = v29;
			return 1;
		}
		player->inventory->add(&v29);
		return 1;
	}
	if(meta) {
		goto LABEL_17;
	}
	if(player->abilities.instabuild) {
		goto LABEL_5;
	}
	return 0;
}
bool_t BucketItem::isLiquidClipItem(int32_t a2) {
	return a2 == 0;
}
std::string BucketItem::getDescriptionId(const ItemInstance* a3) {
	int32_t meta; // r0
	bool_t v7;  // zf

	meta = a3->getAuxValue();
	if(meta == Tile::water->blockID) {
		return "item.bucketWater";
	} else {
		v7 = meta == Tile::lava->blockID;
		if(v7) {
			return "item.bucketLava";
		} else {
			return "item.bucket";
		}
	}
}
bool_t BucketItem::isEmissive(int32_t a2) {
	return a2 == Tile::lava->blockID;
}
