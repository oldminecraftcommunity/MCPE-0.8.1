#include <tile/CakeTile.hpp>
#include <level/Level.hpp>
#include <entity/Player.hpp>
#include <tile/material/Material.hpp>

CakeTile::CakeTile(int32_t id)
	: Tile(id, Material::cake) {
	this->field_80 = this->getTextureUVCoordinateSet("cake_top", 0);
	this->field_98 = this->getTextureUVCoordinateSet("cake_bottom", 0);
	this->field_B0 = this->getTextureUVCoordinateSet("cake_inner", 0);
	this->field_C8 = this->getTextureUVCoordinateSet("cake_side", 0);
}

CakeTile::~CakeTile() {
}
bool_t CakeTile::isCubeShaped() {
	return 0;
}
void CakeTile::updateShape(LevelSource* ls, int32_t x, int32_t y, int32_t z) {
	int32_t d = ls->getData(x, y, z);
	this->setShape((float)(2 * d + 1) * 0.0625, 0.0, 0.0625, 0.9375, 0.5, 0.9375);
}
void CakeTile::updateDefaultShape() {
	this->setShape(0.0625, 0.0, 0.0625, 0.9375, 0.5, 0.9375);
}
TextureUVCoordinateSet* CakeTile::getTexture(int32_t a2, int32_t a3) {
	if(a2 == 1) return &this->field_80;
	if(!a2) return &this->field_98;
	if(a3 > 0 && a2 == 4) return &this->field_B0;
	return &this->field_C8;
}
bool_t CakeTile::isSolidRender() {
	return 0;
}
bool_t CakeTile::mayPlace(Level* a2, int32_t a3, int32_t a4, int32_t a5, uint8_t a6) {
	return a6 == 1;
}
void CakeTile::neighborChanged(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t, int32_t, int32_t, int32_t) {
	if(!this->canSurvive(a2, a3, a4, a5)) {
		a2->removeTile(a3, a4, a5);
	}
}
int32_t CakeTile::getResourceCount(Random*) {
	return 0;
}
bool_t CakeTile::use(Level* a2, int32_t a3, int32_t a4, int32_t a5, Player* a6) {
	if(a6->abilities.invulnerable && a6->isHurt()) {
		a6->foodData.eat(2);
		int32_t v9 = a2->getData(a3, a4, a5) + 1;
		if(v9 <= 5) a2->setData(a3, a4, a5, v9, 2);
		else a2->removeTile(a3, a4, a5);
	}
	return 1;
}
bool_t CakeTile::canSurvive(Level* level, int32_t x, int32_t y, int32_t z) {
	return level->getMaterial(x, y - 1, z)->isSolid();
}
