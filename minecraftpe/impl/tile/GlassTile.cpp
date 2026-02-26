#include <tile/GlassTile.hpp>

GlassTile::GlassTile(int32_t id, const std::string& s, Material* m)
	: HalfTransparentTile(id, s, m) {
}

GlassTile::~GlassTile(){

}
int32_t GlassTile::getRenderLayer() {
	return 1;
}
int32_t GlassTile::getResourceCount(Random*) {
	return 0;
}
