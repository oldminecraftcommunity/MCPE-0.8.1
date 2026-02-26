#include <tile/MelonTile.hpp>
#include <util/Random.hpp>
#include <item/Item.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


MelonTile::MelonTile(int32_t id)
	: Tile(id, Material::vegetable) {
	TextureAtlasTextureItem texItem(*this->getTextureItem("melon"));
	this->field_7C = *texItem.getUV(0);
	this->field_94 = *texItem.getUV(1);
}

MelonTile::~MelonTile() {
}
TextureUVCoordinateSet* MelonTile::getTexture(int32_t a2) {
	if(a2 > 1) {
		return &this->field_7C;
	} else {
		return &this->field_94;
	}
}
TextureUVCoordinateSet* MelonTile::getTexture(LevelSource*, int32_t, int32_t, int32_t, int32_t a6) {
	return this->getTexture(a6);
}
int32_t MelonTile::getResource(int32_t, Random*) {
	return Item::melon->itemID;
}
int32_t MelonTile::getResourceCount(Random* a2) {
	return a2->genrand_int32() % 5 + 3;
}
