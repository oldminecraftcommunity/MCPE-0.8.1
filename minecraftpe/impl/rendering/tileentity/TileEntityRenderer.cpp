#include <rendering/tileentity/TileEntityRenderer.hpp>
#include <rendering/TileEntityRenderDispatcher.hpp>
#include <rendering/Textures.hpp>

TileEntityRenderer::TileEntityRenderer(void) {
	this->dispatcher = 0;
}
void TileEntityRenderer::bindTexture(const std::string& a2) {
	this->dispatcher->textures->loadAndBindTexture(a2);
}
Font* TileEntityRenderer::getFont() {
	return this->dispatcher->getFont();
}
Level* TileEntityRenderer::getLevel() {
	return this->dispatcher->level;
}
void TileEntityRenderer::init(TileEntityRenderDispatcher* a2) {
	this->dispatcher = a2;
}

TileEntityRenderer::~TileEntityRenderer() {
}
void TileEntityRenderer::onNewLevel(Level*) {
}
