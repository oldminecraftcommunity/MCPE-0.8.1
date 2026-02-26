#include <tile/WebTile.hpp>
#include <item/Item.hpp>
#include <entity/Entity.hpp>

WebTile::WebTile(int32_t id, const std::string& name, Material* mat) : Tile(id, name, mat){

}

WebTile::~WebTile() {
}
bool_t WebTile::isCubeShaped() {
	return 0;
}
int32_t WebTile::getRenderShape() {
	return 1;
}
AABB* WebTile::getAABB(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t WebTile::isSolidRender() {
	return 0;
}
int32_t WebTile::getResource(int32_t, Random*) {
	return Item::string->itemID;
}
int32_t WebTile::getRenderLayer() {
	return 1;
}
void WebTile::entityInside(Level*, int32_t, int32_t, int32_t, Entity* entity) {
	entity->makeStuckInWeb();
}
