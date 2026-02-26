#include <tile/QuartzBlockTile.hpp>
#include <item/ItemInstance.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>

QuartzBlockTile::QuartzBlockTile(int32_t id)
	: Tile(id, Material::stone) {
	TextureAtlasTextureItem texItem(*this->getTextureItem("quartz_block"));
	this->field_80 = *texItem.getUV(0);
	this->field_98 = *texItem.getUV(1);
	this->field_B0 = *texItem.getUV(2);
	this->field_C8 = *texItem.getUV(3);
	this->field_E0 = *texItem.getUV(4);
	this->field_F8 = *texItem.getUV(5);
	this->field_110 = *texItem.getUV(6);
}

QuartzBlockTile::~QuartzBlockTile() {
}
TextureUVCoordinateSet* QuartzBlockTile::getTexture(int32_t a2, int32_t a3) {
	if((uint32_t)a2 > 1) {
		if(a3 == 1) {
			return &this->field_F8;
		} else if(a3 == 2) {
			return &this->field_C8;
		} else {
			return &this->field_B0;
		}
	} else if(a3 == 1) {
		return &this->field_110;
	} else if(a3 == 2) {
		return &this->field_E0;
	} else if(a2) {
		return &this->field_98;
	} else {
		return &this->field_80;
	}
}
std::string QuartzBlockTile::getDescriptionId(const ItemInstance* a2) {
	int32_t v4; // r0

	v4 = a2->getAuxValue() & 0xF;
	if(v4 == 1) {
		return Tile::TILE_DESCRIPTION_PREFIX + "quartzBlockChiseled";
	} else if(v4 == 2) {
		return Tile::TILE_DESCRIPTION_PREFIX + "quartzBlockPillar";
	} else {
		return Tile::TILE_DESCRIPTION_PREFIX + "quartzBlock";
	}
}
int32_t QuartzBlockTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2;
}
