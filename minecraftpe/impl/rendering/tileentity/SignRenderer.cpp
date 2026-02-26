#include <rendering/tileentity/SignRenderer.hpp>
#include <rendering/Font.hpp>
#include <tile/Tile.hpp>
#include <tile/entity/SignTileEntity.hpp>
#include <util/Color4.hpp>
#include <utils.h>

SignRenderer::SignRenderer() : TileEntityRenderer(){

}
SignRenderer::~SignRenderer() {
}
void SignRenderer::render(TileEntity* tee, float x, float y, float z, float a6, bool_t a7) {
	SignTileEntity* te = (SignTileEntity*)tee;
	Tile* tile;	 // r8
	int8_t v13;	 // r3
	int32_t v14; // r0
	float v15;	 // r8
	Font* font;	 // r5
	int32_t v17; // r8
	int32_t v18; // r9
	float v19;	 // s17
	int32_t v20; // r6
	int32_t v21; // r10
	int32_t v26; // r0
	int32_t v27; // r0

	tile = te->getTile();
	te->setupLighting(a7, a6);
	glPushMatrix();
	if(tile == Tile::sign) {
		glTranslatef(x + 0.5, y + 0.5, z + 0.5);
		glRotatef(-vcvts_n_f32_s32(360 * te->getData(), 4u), 0.0, 1.0, 0.0);
		v13 = 1;
	} else {
		v14 = te->getData();
		switch(v14) {
			case 2:
				v15 = 180.0;
				break;
			case 4:
				v15 = 90.0;
				break;
			case 5:
				v15 = -90.0;
				break;
			default:
				v15 = 0.0;
				break;
		}
		glTranslatef(x + 0.5, y + 0.5, z + 0.5);
		glRotatef(-v15, 0.0, 1.0, 0.0);
		glTranslatef(0.0, -0.3125, -0.4375);
		v13 = 0;
	}
	this->model.field_9C.field_1D = v13;
	this->bindTexture("item/sign.png");
	glPushMatrix();
	glScalef(0.66667, -0.66667, -0.66667);
	this->model.render();
	glPopMatrix();
	font = this->getFont();
	glTranslatef(0.0, 0.33333, 0.046667);
	glScalef(0.011111, -0.011111, 0.011111);
	glEnable(0xBE2u);
	glEnableClientState(0x8076u);
	glDepthMask(0);
	if(a7) {
		v17 = 32885;
		glDisable(0xB50u);
		glDisableClientState(0x8075u);
		v18 = 0xB50;
	} else {
		v17 = 0;
		v18 = 0;
	}
	v19 = -20.0;
	v20 = 0;
	uint8_t b = (uint32_t)(float)(Color4::BLACK.r * 255.0);
	uint8_t g = (uint32_t)(float)(Color4::BLACK.g * 255.0);
	uint8_t r = (uint32_t)(float)(Color4::BLACK.b * 255.0);
	uint8_t a = (uint32_t)(float)(Color4::BLACK.a * 255.0);
	v21 = (a << 24) | (r << 16) | (g << 8) | (b);
	do {
		font->field_4 = 0;
		if(v20 == te->field_6C) {
			std::string a2 = "> " + te->textLines[v20] + " <";
			v26 = font->width(a2);
			font->draw(a2, (float)-v26 * 0.5, v19, v21);
		} else {
			v27 = font->width(te->textLines[v20]);
			font->draw(te->textLines[v20], (float)-v27 * 0.5, v19, v21);
		}
		++v20;
		v19 = v19 + 10.0;
	} while(v20 != 4);
	if(v17) {
		glEnableClientState(v17);
	}
	if(v18) {
		glEnable(v18);
	}
	glDepthMask(1u);
	glDisableClientState(0x8076u);
	glDisable(0xBE2u);
	glPopMatrix();
}
