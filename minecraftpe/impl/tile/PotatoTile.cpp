#include <tile/PotatoTile.hpp>
#include <item/Item.hpp>

PotatoTile::PotatoTile(int32_t a2)
	: CropTile(a2, "wheat_stage_x") {
	this->field_AC = *this->getTextureItem("potatoes_stage_x");
}

PotatoTile::~PotatoTile() {
}
TextureUVCoordinateSet* PotatoTile::getTexture(int32_t a2, int32_t a3) {
	int32_t v4;
	if(a3 > 6) {
		v4 = 3;
	} else {
		if(a3 == 6) {
			a3 = 5;
		}
		v4 = a3 >> 1;
	}
	return this->field_AC.getUV(v4);
}
void PotatoTile::spawnResources(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float a7) {
	CropTile::spawnResources(level, x, y, z, a6, a7);
}
Item* PotatoTile::getBaseSeed() {
	return Item::potato;
}
int32_t PotatoTile::getBasePlantId() {
	return Item::potato->itemID;
}
