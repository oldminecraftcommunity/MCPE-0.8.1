#include <rendering/TextureAtlasTextureItem.hpp>

TextureAtlasTextureItem::TextureAtlasTextureItem(void){
	this->name = "error";
	this->uvCoords.minX = -1;
	this->uvCoords.maxY = -1;
	this->uvCoords.maxX = -1;
	this->uvCoords.maxY = -1;
	this->uvCoords.width = 0;
	this->uvCoords.height = 0;
	this->uv.push_back(this->uvCoords);
	this->uvCount = this->uv.size();
}

TextureAtlasTextureItem::TextureAtlasTextureItem(const std::string& a2, const TextureUVCoordinateSet& a3, const std::vector<TextureUVCoordinateSet>& a4) {
	this->name = a2;
	this->uvCoords = a3;
	this->uv.push_back(this->uvCoords);

	for(auto pp: a4) {
		this->uv.push_back(pp);
	}
	this->uvCount = this->uv.size();
}
void TextureAtlasTextureItem::getName(void) const{}

const TextureUVCoordinateSet* TextureAtlasTextureItem::getUV(int32_t a2) const{
	if(a2 <= 0)
		return &this->uvCoords;
	if(a2 > this->uvCount) a2 = this->uvCount - 1;
	return this->uv.data() + a2;
}

int32_t TextureAtlasTextureItem::getUVCount(void) const{
	return this->uvCount;
}
