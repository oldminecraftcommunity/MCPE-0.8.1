#include <tile/CarrotTile.hpp>
#include <item/Item.hpp>

CarrotTile::CarrotTile(int32_t id)
	: CropTile(id, "wheat_stage_x") {
	this->field_AC = *this->getTextureItem("carrots_stage_x");
}

static inline int _texIndex(int a3){
	if(a3 > 6) return 3;
	else {
		if(a3 == 6) a3 = 5;
		return a3 >> 1;
	}
}
const TextureUVCoordinateSet* CarrotTile::getTexture(int32_t a2, int32_t a3) {
	return this->field_AC.getUV(_texIndex(a3));
}

void CarrotTile::spawnResources(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, float a7) {
	CropTile::spawnResources(a2, a3, a4, a5, a6, a7);
}
int32_t CarrotTile::getBasePlantId(){
	return Item::carrot->itemID;
}
Item* CarrotTile::getBaseSeed() {
	return Item::carrot;
}
