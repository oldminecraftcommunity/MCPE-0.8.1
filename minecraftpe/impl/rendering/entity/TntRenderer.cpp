#include <rendering/entity/TntRenderer.hpp>
#include <entity/PrimedTnt.hpp>
#include <GL/gl.h>
#include <tile/Tile.hpp>

TntRenderer::TntRenderer()
	: EntityRenderer()
	, tileRenderer(0) {
}

TntRenderer::~TntRenderer() {
}
void TntRenderer::render(Entity* a2_, float a3, float a4, float a5, float a6, float a7) {
	PrimedTnt* a2 = (PrimedTnt*)a2_;
	float v11;	 // s15
	float v12;	 // s15
	float v13;	 // r2
	int32_t v14; // r5

	glPushMatrix();
	glTranslatef(a3, a4, a5);
	v11 = (float)((float)a2->ticksUntilExplode - a7) + 1.0;
	if(v11 < 10.0) {
		v12 = 1.0 - (float)(v11 / 10.0);
		if(v12 < 0.0) {
			v12 = 0.0;
		} else if(v12 > 1.0) {
			v12 = 1.0;
		}
		v13 = (float)((float)((float)(v12 * v12) * (float)(v12 * v12)) * 0.3) + 1.0;
		glScalef(v13, v13, v13);
	}
	glColor4f(1.0, 1.0, 1.0, (float)(1.0 - (float)((float)((float)((float)a2->ticksUntilExplode - a7) + 1.0) / 100.0)) * 0.8);
	if(((a2->ticksUntilExplode / 5) & 1) != 0) {
		EntityRenderer::bindTexture("terrain-atlas.tga");
		this->tileRenderer.renderTile(Tile::tnt, 0, 1);
	} else {
		glDisable(0xDE1u);
		glBlendFunc(0x302u, 0x304u);
		if(this->isFancy()) {
			v14 = 2896;
			glDisable(0xB50u);
		} else {
			v14 = 0;
		}
		this->tileRenderer.renderTile(Tile::tnt, 0, 1);
		if(v14) {
			glEnable(v14);
		}
		glBlendFunc(0x302u, 0x303u);
		glEnable(0xDE1u);
	}
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glPopMatrix();
}
