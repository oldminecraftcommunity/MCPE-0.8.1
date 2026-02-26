#include <tile/StoneSlabTile.hpp>
#include <tile/material/Material.hpp>
std::string StoneSlabTile::SLAB_NAMES[] = {
	"stone",
	"sand",
	"wood",
	"cobble",
	"brick",
	"smoothStoneBrick",
	"quartz"
};
StoneSlabTile::StoneSlabTile(int32_t a2, bool_t a3)
	: SlabTile(a2, "wood", a3, Material::stone) {
	this->field_84 = this->getTextureUVCoordinateSet("stone_slab", 0);
	this->field_9C = this->getTextureUVCoordinateSet("stone_slab", 1);
	this->field_B4 = this->getTextureUVCoordinateSet("sandstone", 3);
	this->field_CC = this->getTextureUVCoordinateSet("sandstone", 3);
	this->field_E4 = this->getTextureUVCoordinateSet("sandstone", 0);
	this->field_FC = this->getTextureUVCoordinateSet("planks", 0);
	this->field_114 = this->getTextureUVCoordinateSet("cobblestone", 0);
	this->field_12C = this->getTextureUVCoordinateSet("brick", 0);
	this->field_144 = this->getTextureUVCoordinateSet("stonebrick", 0);
	this->field_15C = this->getTextureUVCoordinateSet("quartz_block", 0);
}

StoneSlabTile::~StoneSlabTile() {
}
TextureUVCoordinateSet* StoneSlabTile::getTexture(int32_t a2) {
	return this->getTexture(a2, 0);
}
TextureUVCoordinateSet* StoneSlabTile::getTexture(int32_t a2, int32_t a3) {
	int32_t v3; // r2

	v3 = a3 & 7;
	if(v3) {
		switch(v3) {
			case 1:
				if(a2) {
					if(a2 == 1) {
						return &this->field_B4;
					} else {
						return &this->field_E4;
					}
				} else {
					return &this->field_CC;
				}
			case 2:
				return &this->field_FC;
			case 3:
				return &this->field_114;
			case 4:
				return &this->field_12C;
			case 5:
				return &this->field_144;
			case 6:
				return &this->field_15C;
			default:
				return &this->field_84;
		}
	} else {
		if(a2 <= 1) {
			return &this->field_84;
		}
		return &this->field_9C;
	}
}
int32_t StoneSlabTile::getResource(int32_t a2, Random* a3) {
	if((a2 & 7) == 2) {
		return Tile::woodSlabHalf->blockID;
	} else {
		return Tile::stoneSlabHalf->blockID;
	}
}
int32_t StoneSlabTile::getSpawnResourcesAuxValue(int32_t a2) {
	int32_t result; // r0

	result = a2 & 7;
	if(result == 2) {
		return 0;
	}
	return result;
}
