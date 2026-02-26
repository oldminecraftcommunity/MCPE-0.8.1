#include <rendering/entity/FallingTileRenderer.hpp>
#include <rendering/TileRenderer.hpp>
#include <GL/gl.h>
#include <tile/Tile.hpp>
#include <entity/FallingTile.hpp>

FallingTileRenderer::FallingTileRenderer() {
	this->tileRenderer = new TileRenderer(0);
}

FallingTileRenderer::~FallingTileRenderer() {
	delete this->tileRenderer;
}
void FallingTileRenderer::render(Entity* a2, float x, float y, float z, float a6, float a7) {
	glPushMatrix();
	glTranslatef(x, y, z);
	this->bindTexture("terrain-atlas.tga");
	Tile* v11 = Tile::tiles[((FallingTile*)a2)->blockID];
	if(v11) {
		this->tileRenderer->renderTile(v11, 0, 1);
	}
	glPopMatrix();
}
