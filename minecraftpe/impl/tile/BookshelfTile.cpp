#include <tile/BookshelfTile.hpp>
#include <item/Item.hpp>

BookshelfTile::BookshelfTile(int32_t id, std::string a2, const struct Material* a3)
	: Tile(id, a2, a3) {
	this->uv = this->getTextureUVCoordinateSet("planks", 0);
}
BookshelfTile::~BookshelfTile() {
}
TextureUVCoordinateSet* BookshelfTile::getTexture(int32_t a2) {
	if(a2 > 1) return &this->textureUV;
	return &this->uv;
}
int32_t BookshelfTile::getResource(int32_t a2, Random* a3) {
	return Item::book->itemID;
}
int32_t BookshelfTile::getResourceCount(Random*) {
	return 3;
}
