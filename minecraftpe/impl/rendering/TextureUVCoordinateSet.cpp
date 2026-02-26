#include <rendering/TextureUVCoordinateSet.hpp>

TextureUVCoordinateSet::TextureUVCoordinateSet(float minX, float minY, float maxX, float maxY, float width, float height){
	this->width = width;
	this->height = height;
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
}

TextureUVCoordinateSet::TextureUVCoordinateSet(){
	this->minX = 0;
	this->minY = 0;
	this->maxX = 0;
	this->maxY = 0;
}

TextureUVCoordinateSet TextureUVCoordinateSet::fromOldSystem(int32_t sprite){
	int32_t spx, spy;
	spx = sprite % 16;
	spy = sprite / 16;

	return TextureUVCoordinateSet(
		(16*spx) * 0.0039062,
		(16*spy) * 0.0039062,
		(16*(spx+1)) * 0.0039062,
		(16*(spy+1)) * 0.0039062,
		256.0,
		256.0
	);
}
