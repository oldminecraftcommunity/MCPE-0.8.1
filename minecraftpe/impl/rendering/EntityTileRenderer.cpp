#include <rendering/EntityTileRenderer.hpp>
#include <tile/entity/ChestTileEntity.hpp>
#include <rendering/TileEntityRenderDispatcher.hpp>

EntityTileRenderer* EntityTileRenderer::instance = new ChestTileEntity();
void EntityTileRenderer::render(Tile* a2, int32_t a3, float a4) {
	//TODO check
	TileEntityRenderDispatcher::getInstance()->render((TileEntity*) this, 0, 0, 0, 0);
}
