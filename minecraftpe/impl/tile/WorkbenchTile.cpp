#include <tile/WorkbenchTile.hpp>
#include <entity/Player.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


WorkbenchTile::WorkbenchTile(int32_t a2)
	: Tile(a2, Material::wood) {
	TextureAtlasTextureItem* texItem; // r7

	this->field_80 = this->getTextureUVCoordinateSet("planks", 0);

	texItem = this->getTextureItem("crafting_table");
	this->field_98 = *texItem->getUV(0);
	this->field_B0 = *texItem->getUV(1);
	this->field_C8 = *texItem->getUV(2);
}

WorkbenchTile::~WorkbenchTile() {
}
TextureUVCoordinateSet* WorkbenchTile::getTexture(int32_t a2) {
	if(a2 == 1) {
		return &this->field_98;
	}
	if(!a2) {
		return &this->field_80;
	}
	if((uint32_t)(a2 - 4) > 1) {
		return &this->field_C8;
	}
	return &this->field_B0;
}
bool_t WorkbenchTile::use(Level* level, int32_t x, int32_t y, int32_t z, Player* player) {
	player->startCrafting(x, y, z, 1);
	return 1;
}
