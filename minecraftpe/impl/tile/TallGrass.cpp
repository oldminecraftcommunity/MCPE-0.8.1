#include <tile/TallGrass.hpp>
#include <item/Item.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


TallGrass::TallGrass(int32_t id, const std::string& a3)
	: Bush(id, a3, Material::replaceable_plant) {
	this->setShape(0.1, 0.0, 0.1, 0.9, 0.8, 0.9);
	TextureAtlasTextureItem texItem(*this->getTextureItem("tallgrass"));

	this->field_80 = *texItem.getUV(0);
	this->field_B0 = *texItem.getUV(2);
	this->field_98 = *texItem.getUV(3);
	this->field_C8 = *texItem.getUV(4);
	this->replaceable = 1;
}

TallGrass::~TallGrass() {
}
TextureUVCoordinateSet* TallGrass::getTexture(int32_t a2, int32_t a3) {
	if(a3 == 1) {
		return &this->field_80;
	}
	if(a3 == 2) {
		return &this->field_B0;
	}
	return &this->textureUV;
}
TextureUVCoordinateSet* TallGrass::getCarriedTexture(int32_t a2, int32_t a3) {
	if(a3 == 1) {
		return &this->field_98;
	}
	if(a3 == 2) {
		return &this->field_C8;
	}
	return &this->textureUV;
}
int32_t TallGrass::getResource(int32_t a2, Random* a3) {
	if(a3->genrand_int32() << 29) {
		return -1;
	} else {
		return Item::seeds_wheat->itemID;
	}
}
int32_t TallGrass::getColor(int32_t a2) {
	return Tile::grass->getColor(a2);
}
int32_t TallGrass::getColor(LevelSource* level, int32_t x, int32_t y, int32_t z){
	return Tile::grass->getColor(level, x, y, z);
}
void TallGrass::playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t meta) {

	if(!level->isClientMaybe && player->getSelectedItem() && Item::shears == player->getSelectedItem()->itemClass && Item::shears) {
		this->popResource(level, x, y, z, ItemInstance(Tile::tallgrass, 1, meta));
	} else {
		Tile::playerDestroy(level, player, x, y, z, meta);
	}
}
std::string TallGrass::getDescriptionId(const ItemInstance* a3) {
	if(a3->getAuxValue() == 1) {
		return "tile.tallgrass.grass";
	} else {
		return "tile.tallgrass.fern";
	}
}
