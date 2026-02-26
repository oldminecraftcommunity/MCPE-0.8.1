#include <tile/StonecutterTile.hpp>
#include <entity/Player.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


StonecutterTile::StonecutterTile(int32_t a2)
	: Tile(a2, Material::stone) {
	TextureAtlasTextureItem* texItem = this->getTextureItem("stonecutter");
	this->field_80 = *texItem->getUV(0);
	this->field_98 = *texItem->getUV(1);
	this->field_B0 = *texItem->getUV(2);
	this->field_C8 = *texItem->getUV(3);
}

StonecutterTile::~StonecutterTile() {
}
TextureUVCoordinateSet* StonecutterTile::getTexture(int32_t a2) {
	if(a2 == 1) {
		return &this->field_B0;
	}
	if(!a2) {
		return &this->field_C8;
	}
	if((uint32_t)(a2 - 2) > 1) {
		return &this->field_98;
	}
	return &this->field_80;
}
bool_t StonecutterTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	player->startStonecutting(x, y, z);
	return 1;
}
