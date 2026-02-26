#include <rendering/textures/DynamicTexture.hpp>
#include <string.h>

DynamicTexture::DynamicTexture(const TextureUVCoordinateSet& a2, int32_t a3)
	: uv(a2) {
	this->field_18 = a3;
	this->dataLength = (a3 * a3) << 10;
	this->data = new uint8_t[this->dataLength];
	memset(this->data, 0, this->dataLength);
}
DynamicTexture::~DynamicTexture() {
	if(this->data) delete[] this->data;
}
void DynamicTexture::bindTexture(struct Textures* a2) {
	a2->loadAndBindTexture("terrain-atlas.tga");
}
