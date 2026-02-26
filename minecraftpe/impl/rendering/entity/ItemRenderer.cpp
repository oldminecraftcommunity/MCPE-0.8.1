#include <rendering/entity/ItemRenderer.hpp>
#include <rendering/TileRenderer.hpp>
#include <rendering/Tesselator.hpp>
#include <math/Mth.hpp>
#include <rendering/Textures.hpp>
#include <item/ItemInstance.hpp>
#include <GL/gl.h>
#include <tile/Tile.hpp>
#include <item/Item.hpp>
#include <entity/ItemEntity.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/ItemInHandRenderer.hpp>

TileRenderer* ItemRenderer::tileRenderer = new TileRenderer(0);
bool_t ItemRenderer::inited = 0;
float ItemRenderer::rndFloats[16];

ItemRenderer::ItemRenderer()
	: EntityRenderer() {
	if(!ItemRenderer::inited) {
		for(float& f: ItemRenderer::rndFloats) {
			float ff = Mth::random();
			f = (ff + ff) - 1.0;
		}
		ItemRenderer::inited = 1;
	}
}
void ItemRenderer::blit(float a1, float a2, float a3, float a4, float a5, float a6) {
	float v10; // s24
	float v11; // s21

	Tesselator::instance.begin(4);
	v10 = (float)(a4 + a6) * 0.0039062;
	Tesselator::instance.vertexUV(a1, a2 + a6, 0.0, a3 * 0.0039062, v10);
	v11 = (float)(a3 + a5) * 0.0039062;
	Tesselator::instance.vertexUV(a1 + a5, a2 + a6, 0.0, v11, v10);
	Tesselator::instance.vertexUV(a1 + a5, a2, 0.0, v11, a4 * 0.0039062);
	Tesselator::instance.vertexUV(a1, a2, 0.0, a3 * 0.0039062, a4 * 0.0039062);
	Tesselator::instance.draw(1);
}
void ItemRenderer::fillRect(Tesselator& a1, float a2, float a3, float a4, float a5, int32_t a6) {
	float v10; // s17
	float v11; // s19
	float v12; // s18

	a1.begin(4);
	a1.color(a6);
	v10 = a3 + 0.0;
	a1.vertex(a2 + 0.0, a3 + 0.0, 0.0);
	v11 = a3 + a5;
	a1.vertex(a2 + 0.0, v11, 0.0);
	v12 = a2 + a4;
	a1.vertex(v12, v11, 0.0);
	a1.vertex(v12, v10, 0.0);
	a1.draw(1);
}
static int16_t _word_D67239E4[] = {-1, 7, 9, 8, 0, 5, -2, -1, -1, -1, -1, -1, 0xE, 0xF, 0x27, 0x26, 0x25, -2, -2, -1, 0x31, 0x29, 0x2E, -1, -2, -1, -1, -1, -1, -1, 0xF6, -1, -1, -1, -1, -2, -1, 0x89, 0x8A, 0x8B, 0x8C, 0x2B, 0x2C, -1, -2, 6, 0x4C, 0x47, 4, 0x2F, 0x81, -1, -1, 0x16, 0x4A, -1, 0x28, 0x2D, 0x48, -1, -1, 0x4B, -1, -1, -1, 0x80, -1, 0x15, -1, -1, -1, -1, -1, 0x2A, -1, -1, -1, -1, -1, -1, 0x30, 0x4D, 0xA, 0xF4, -1, 0x45, -1, 0x14, -1, 0x32, -1, -1, -1, -1, -1, -1, 0x44, -1, -2, -1, -1, -1, 0x82, 0x4E, -1, -1, -1, 0x46, 0x17, 0x19, -1, -1, 0x13, -1, 0x1A, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, 0x1B, -1, 0x1E, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x49, -1, 0x33, -1, -1, -1, -1, -1, 0x52, -1, -1, 0xB7, 0xB6, 0xB8, 0xF2, 0xF5, 0x98, 0xC7, -2, 0xA2, 0x9F, 0x9E, 0x97, 0xC2, 0xAF, 0xAD, 0xB0, 0xC3, 0xB3, 0xB2, 0xB4, 0xC4, 0xBA, 0xB9, 0xBB, 0xAE, 0xCC, 0xCB, 0xC5, 0xBE, 0xBD, 0xBF, 0xC6, 0xC8, 0xED, 0xB1, 0xB5, 0x94, 0xBC, 0xC0, 0x91, 0xEE, 0xF3, 0xCF, 0xD1, 0xD2, 0xD3, -1, -1, -1, -1, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xC9, 0xA5, 0xA6, 0x88, -1, 0x99, 0x86, -2, -1, -1, -1, -1, -1, -1, 0xEB, -1, 0xD0, -1, 0xA8, 0xA7, 0x8D, 0xE9, 0xEA, -1, -1, -1, 0x96, -1, -1, -1, 0xEC, -1, -1, -2, 0xE8, 0xF0, 0x95, 0x87, -1, -1, -1, 0xC1, 0xCD, -1, 0x92, 0xA9, 0xAA, 0xAB, 0xAC, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0xA4, 0xCE, 0x8E, 0x8F, 0x90, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x10, 0x11, 0x12, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x4F, 0x50, 0x51, -1, 0x4F, 0x50, 0x51, -1, 0x4F, 0x50, 0x51, -1, 0x4F, 0x50, 0x51, -1, 0xB, 0xC, 0xD, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x34, 0x3B, 0x3A, 0x39, 0x38, 0x37, 0x36, 0x35, 0x43, 0x42, 0x41, 0x40, 0x3F, 0x3E, 0x3D, 0x3C, 0x1C, 0x20, 0x1E, 0x1D, 0x1F, 0x21, 0x52, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 2, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x22, 0x24, 0x23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0xF1, 0xA0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x83, 0xEF, -1, -1, -1, -1, -1, -1, 0x84, -1, 0x85, -1, -1, -1, -1, -1, -1, 0xA1, 0xA3, -1, 0xCA, 0xE0, 0xE1, -1, -1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0x93, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0x9A, 0x9B, 0x9C, 0x9D, -1, -1, 0};
int32_t ItemRenderer::getAtlasPos(const ItemInstance* a1) {
	uint32_t itemId; // r0
	int32_t v3;		 // r2
	int32_t result;	 // r0

	itemId = a1->getId();
	v3 = itemId;
	if(itemId <= 406) {
		result = _word_D67239E4[itemId];
		if(result != -2) {
			return result;
		}
		if(v3 == 44) {
			return _word_D67239E4[(a1->getAuxValue() & 0xF) + 487];
		}
		if(v3 > 44) {
			if(v3 == 263) {
				return _word_D67239E4[(a1->getAuxValue() & 0xF) + 535];
			}
			if(v3 > 263) {
				switch(v3) {
					case 351:
						return _word_D67239E4[(a1->getAuxValue() & 0xF) + 567];
					case 383:
						return _word_D67239E4[(a1->getAuxValue() & 0xF) + 583];
					case 325:
						return _word_D67239E4[(a1->getAuxValue() & 0xF) + 551];
				}
			} else {
				if(v3 == 98) {
					return _word_D67239E4[(a1->getAuxValue() & 0xF) + 503];
				}
				if(v3 == 155) {
					return _word_D67239E4[(a1->getAuxValue() & 0xF) + 519];
				}
			}
		} else {
			if(v3 == 18) {
				return _word_D67239E4[(a1->getAuxValue() & 0xF) + 439];
			}
			if(v3 > 18) {
				if(v3 == 24) {
					return _word_D67239E4[(a1->getAuxValue() & 0xF) + 455];
				}
				if(v3 == 35) {
					return _word_D67239E4[(a1->getAuxValue() & 0xF) + 471];
				}
			} else {
				if(v3 == 6) {
					return _word_D67239E4[(a1->getAuxValue() & 0xF) + 407];
				}
				if(v3 == 17) {
					return _word_D67239E4[(a1->getAuxValue() & 0xF) + 423];
				}
			}
		}
	}
	return -1;
}
void ItemRenderer::iconBlit(float a1, float a2, const TextureUVCoordinateSet& a3, float a4, float a5, float a6, float a7, int32_t a8, float a9) {
	float minX; // r7
	float maxX; // r8
	float minY; // r6
	float maxY; // r9
	float v16; // s13
	float v17; // s14
	float v18; // s15
	float v19; // s21
	float v20; // s16
	float v21; // s17
	float v22; // s20
	float v23; // s18
	float v24; // s16

	minX = a3.minX;
	maxX = a3.maxX;
	minY = a3.minY;
	maxY = a3.maxY;
	Tesselator::instance.begin(4);
	if(a8 == -1) {
		Tesselator::instance.color(a6, a6, a6, a7);
	} else {
		v16 = (float)((float)((a8 >> 16) & 0xff) / 255.0) * a6;
		v17 = (float)((float)((a8 >> 8) & 0xff) / 255.0) * a6;
		v18 = (float)((float)(a8 & 0xff) / 255.0) * a6;
		if(v16 > 1.0) {
			v16 = 1.0;
		} else if(v16 <= 0.0) {
			v16 = 0.0;
		}
		if(v17 > 1.0) {
			v17 = 1.0;
		} else if(v17 <= 0.0) {
			v17 = 0.0;
		}
		if(v18 > 1.0) {
			v18 = 1.0;
		} else if(v18 <= 0.0) {
			v18 = 0.0;
		}
		Tesselator::instance.color(v16, v17, v18, a7);
	}
	v19 = (float)(a4 * 0.5) * (float)(a9 - 1.0);
	v20 = (float)(a5 * 0.5) * (float)(a9 - 1.0);
	v21 = a1 - v19;
	v22 = (float)(a2 + a5) + v20;
	Tesselator::instance.vertexUV(a1 - v19, v22, 0.0, minX, maxY);
	v23 = (float)(a1 + a4) + v19;
	Tesselator::instance.vertexUV(v23, v22, 0.0, maxX, maxY);
	v24 = a2 - v20;
	Tesselator::instance.vertexUV(v23, v24, 0.0, maxX, minY);
	Tesselator::instance.vertexUV(v21, v24, 0.0, minX, minY);
	Tesselator::instance.draw(1);
}
void ItemRenderer::renderGuiItem(Font* a1, Textures* a2, const ItemInstance* a3, float a4, float a5, bool_t a6) {
	ItemRenderer::renderGuiItem(a1, a2, a3, a4, a5, 16, 16, a6);
}
void ItemRenderer::renderGuiItem(Font* a1, Textures* a2, const ItemInstance* a3, float a4, float a5, float a6, float a7, bool_t a8) {
	int32_t atlasPos; // r6
	float v13; // s20
	float v14; // s19
	float v15; // s16
	int32_t v16; // r6
	float v17; // s21
	int32_t v18; // r1
	float v19; // s20

	if(a3) {
		atlasPos = ItemRenderer::getAtlasPos(a3);
		if(atlasPos >= 0) {
			a2->loadAndBindTexture("gui/gui_blocks.png");
			if(atlasPos > 127) {
				v16 = atlasPos - 128;
				v13 = 0.03125;
				v15 = (float)((float)(v16 >> 5) * 0.03125) + 0.84375;
				v14 = (float)(v16 & 0x1F) * 0.03125;
			} else {
				v13 = 0.09375;
				v14 = (float)(atlasPos % 10) * 0.09375;
				v15 = (float)(atlasPos / 10) * 0.09375;
			}
			Tesselator::instance.begin(4);
			v17 = v14 + v13;
			if(a3->count > 0) {
				v18 = 0xFFFFFFFF;
			} else {
				v18 = 0x60FFFFFF;
			}
			Tesselator::instance.colorABGR(v18);
			v19 = v15 + v13;
			Tesselator::instance.vertexUV(a4, a5 + a7, 0.0, v14, v19);
			Tesselator::instance.vertexUV(a4 + a6, a5 + a7, 0.0, v17, v19);
			Tesselator::instance.vertexUV(a4 + a6, a5, 0.0, v17, v15);
			Tesselator::instance.vertexUV(a4, a5, 0.0, v14, v15);
			Tesselator::instance.draw(1);
		} else if(Tesselator::instance.field_D6) {
			Tesselator::instance.voidBeginAndEndCalls(0);
			Tesselator::instance.draw(1);
			glDisable(0xDE1u);
			ItemRenderer::fillRect(Tesselator::instance, a4, a5, a6, a7, 0xFF0000);
			glEnable(0xDE1u);
			ItemRenderer::renderGuiItemCorrect(a1, a2, a3, (int32_t)a4, (int32_t)a5);
			Tesselator::instance.begin(0);
			Tesselator::instance.voidBeginAndEndCalls(1);
		} else {
			ItemRenderer::renderGuiItemCorrect(a1, a2, a3, (int32_t)a4, (int32_t)a5);
		}
	}
}
void ItemRenderer::renderGuiItemCorrect(Font* a1, Textures* a2, const ItemInstance* a3, int32_t a4, int32_t a5) {
	int32_t v9; // r0
	TextureUVCoordinateSet* icon; // r0
	if(a3) {
		if(a3->tileClass && (v9 = a3->tileClass->getRenderShape(), TileRenderer::canRender(v9))) {
			a2->loadAndBindTexture("terrain.png");
			glPushMatrix();
			glTranslatef((float)(a4 - 2), (float)(a5 + 3), -8.0);
			glScalef(10.0, 10.0, 10.0);
			glTranslatef(1.0, 0.5, 0.0);
			glRotatef(210.0, 1.0, 0.0, 0.0);
			glRotatef(45.0, 0.0, 1.0, 0.0);
			glScalef(1.0, 1.0, 1.0);
			ItemRenderer::tileRenderer->renderGuiTile(a3->tileClass, a3->getAuxValue(), 1.0, 1.0);
			glPopMatrix();
		} else if(a3->itemClass) {
			a2->loadAndBindTexture(a3->tileClass ? "terrain.png" : "gui/items.png");
			icon = a3->getIcon(0, 0);
			ItemRenderer::blit((float)a4, (float)a5, icon->minX * icon->width, icon->minY * icon->height, 16.0, 16.0);
		}
	}
}
void ItemRenderer::renderGuiItemDecorations(const ItemInstance* a1, float a2, float a3) {
	int32_t damageValue; // r5
	int32_t maxDamage; // r0
	float v8; // r7
	int32_t v9; // r5
	int32_t v10; // r0
	float v11; // s16
	float v12; // s17
	int32_t v13; // r0
	int32_t v14; // r5
	int32_t v15; // r8

	if(a1) {
		if(a1->count > 0 && a1->isDamaged()) {
			damageValue = a1->getDamageValue();
			maxDamage = a1->getMaxDamage();
			v8 = floorf(13.5 - (float)((float)((float)damageValue * 13.0) / (float)maxDamage));
			v9 = a1->getDamageValue();
			v10 = a1->getMaxDamage();
			v11 = a3 + 13.0;
			v12 = a2 + 2.0;
			v13 = (int32_t)floorf(255.5 - (float)((float)((float)v9 * 255.0) / (float)v10));
			v14 = 255 - v13;
			v15 = (v13 << 8) | ((255 - v13) << 16);
			ItemRenderer::fillRect(Tesselator::instance, v12, v11, 13.0, 1.0, 0);
			ItemRenderer::fillRect(Tesselator::instance, v12, v11, 12.0, 1.0, ((v14 / 4) << 16) | 0x3F00);
			ItemRenderer::fillRect(Tesselator::instance, v12, v11, v8, 1.0, v15);
			glColor4f(1.0, 1.0, 1.0, 1.0);
		}
	}
}
void ItemRenderer::renderGuiItemInChunk(ItemRenderChunkType a1, Textures* a2, const ItemInstance* a3, float a4, float a5, float a6, float a7, float a8) {
	Tile* tileClass; // r4
	float v13; // s14
	float v14; // s15
	TileRenderer* v15; // r7
	int32_t v19; // r4

	if(a3) {
		tileClass = a3->tileClass;
		if(!tileClass || (!TileRenderer::canRender(tileClass->getRenderShape()))) {
			if(!a3->itemClass) {
				return;
			}
			if(a1 == IRCT_THREE) {
				if(tileClass) {
LABEL_19:
					v19 = tileClass->getColor(a3->getAuxValue());
LABEL_21:
					ItemRenderer::iconBlit(a4, a5, *a3->getIcon(0, 1), 16.0, 16.0, a6, 1.0, v19, 1.0);
					return;
				}
			} else {
				if(a1 == IRCT_NULL) {
					return;
				}
				if(tileClass) {
					if(a1 == IRCT_TWO) {
						return;
					}
					goto LABEL_19;
				}
				if(a1 == IRCT_ONE) {
					return;
				}
			}
			v19 = -1;
			goto LABEL_21;
		}
		if(a1 == IRCT_NULL || a1 == IRCT_THREE) {
			v13 = a4 + (float)((float)((float)(a8 - 1.0) * -6.0) + 1.0);
			v14 = a5 + (float)((float)((float)(a8 - 1.0) * 4.0) + 13.0);
			Tesselator::instance.offset({v13, v14, -10.0});
			Tesselator::instance.scale3d(a8 * 9.0, a8 * 9.0, a8 * 9.0);
			Tesselator::instance.tilt();
			ItemRenderer::tileRenderer->renderGuiTile(tileClass, a3->getAuxValue(), a6, a7);
			Tesselator::instance.resetScale();
			Tesselator::instance.resetTilt();
			Tesselator::instance.offset({0, 0, 0});
		}
	}
}
void ItemRenderer::renderGuiItemNew(Textures* a1, const ItemInstance* a2, int32_t a3, float a4, float a5, float a6, float a7, float a8) {
	Tile* tileClass; // r4
	int32_t aux; // r0
	int32_t v16; // r4
	Item* itemClass; // r1

	tileClass = a2->tileClass;
	if(tileClass && (TileRenderer::canRender(tileClass->getRenderShape()))) {
		a1->loadAndBindTexture("terrain-atlas.tga");
		ItemRenderer::renderGuiItemInChunk(IRCT_THREE, a1, (ItemInstance*)a2, a4, a5, a7, a6, a8);
	} else {
		itemClass = a2->itemClass;
		if(itemClass) {
			if(tileClass) {
				a1->loadAndBindTexture("terrain-atlas.tga");
				v16 = tileClass->getColor(a2->getAuxValue());
			} else {
				a1->loadAndBindTexture(itemClass->itemTexture);
				v16 = -1;
			}
			ItemRenderer::iconBlit(a4 - 1.0, a5 + 1.0, *a2->getIcon(a3, 0), 16.0, 16.0, a7, 1.0, v16, a8);
		}
	}
}
void ItemRenderer::teardown_static() {
	if(ItemRenderer::tileRenderer) {
		delete ItemRenderer::tileRenderer;
		ItemRenderer::tileRenderer = 0;
	}
}

ItemRenderer::~ItemRenderer() {
}
void ItemRenderer::render(Entity* e_, float x, float y, float z, float a6, float a7) {
	ItemEntity* e = (ItemEntity*)e_;
	ItemInstance* p_itemInstance; // r9
	float v13;					  // s17
	float hoverStart;			  // s16
	int32_t count;					  // r3
	int32_t v16;					  // r8
	Tile* tileClass;			  // r7
	int32_t v18;					  // r0
	int32_t v19;					  // r6
	float* v20;					  // r5
	TextureUVCoordinateSet* Icon; // r0
	float minX;					  // s18
	float minY;					  // s17
	float maxX;					  // s19
	float maxY;					  // s20
	float v26;					  // s12
	bool_t v27;					  // fzf
	float v28;					  // s13
	float v29;					  // s14
	float* v30;					  // r9
	float v31;					  // s12
	float v32;					  // s13
	float v33;					  // s14
	int32_t v34;					  // r11
	float v35;					  // s16
	float v36;					  // s16

	p_itemInstance = &e->itemInstance;
	e->setupLighting(this->isFancy(), a7);
	glPushMatrix();
	v13 = (float)e->field_130 + a7;
	hoverStart = e->hoverStart;
	count = e->itemInstance.count;
	if(count > 20) {
		v16 = 4;
	} else if(count > 5) {
		v16 = 3;
	} else if(count <= 1) {
		v16 = 1;
	} else {
		v16 = 2;
	}
	glTranslatef(x, y + (float)((float)(Mth::sin((float)((float)(v13 / 10.0) + hoverStart)) * 0.1) + 0.1), z);
	tileClass = e->itemInstance.tileClass;
	if(tileClass && (v18 = tileClass->getRenderShape(), TileRenderer::canRender(v18))) {
		v19 = 0;
		glRotatef((float)((float)(v13 / 20.0) + hoverStart) * 57.296, 0.0, 1.0, 0.0);
		v35 = 0.5;
		this->bindTexture("terrain-atlas.tga");
		if((uint32_t)(tileClass->getRenderShape() - 1) >= 2) {
			v35 = 0.25;
		}
		glScalef(v35, v35, v35);
		v36 = 0.2 / v35;
		v20 = &ItemRenderer::rndFloats[0];
		do {
			glPushMatrix();
			if(v19) {
				glTranslatef(v36 * v20[0], v36 * v20[1], v36 * v20[2]);
			}
			++v19;
			v20 += 3;
			EntityRenderer::entityRenderDispatcher->itemInHandRenderer->renderItem(0, p_itemInstance);
			glPopMatrix();
		} while(v19 < v16);
	} else if(e->itemInstance.isValid) {
		v34 = 0;
		Icon = p_itemInstance->getIcon(0, 0);
		minX = Icon->minX;
		minY = Icon->minY;
		maxX = Icon->maxX;
		maxY = Icon->maxY;
		Tesselator::instance.begin(4 * v16);
		Tesselator::instance.normal(Vec3::UNIT_Z.x, Vec3::UNIT_Z.y, Vec3::UNIT_Z.z);
		v30 = &ItemRenderer::rndFloats[3];
		while(1) {
			Tesselator::instance.vertexUV(-0.5, -0.25, 0.0, minX, maxY);
			++v34;
			Tesselator::instance.vertexUV(0.5, -0.25, 0.0, maxX, maxY);
			Tesselator::instance.vertexUV(0.5, 0.75, 0.0, maxX, minY);
			Tesselator::instance.vertexUV(-0.5, 0.75, 0.0, minX, minY);
			if(v34 >= v16) {
				break;
			}
			v26 = v30[0];
			v27 = v30[0] == 0.0;
			v28 = v30[1];
			v29 = v30[2];
			v30 += 3;
			if(v27) {
				v26 = 0.0;
			}
			v31 = v26 * 0.3;
			if(v28 == 0.0) {
				v28 = 0.0;
			}
			v32 = v28 * 0.3;
			if(v29 == 0.0) {
				v29 = 0.0;
			}
			v33 = v29 * 0.3;
			if(v31 == 0.0) {
				v31 = 0.0;
			}
			if(v32 == 0.0) {
				v32 = 0.0;
			}
			if(v33 == 0.0) {
				v33 = 0.0;
			}
			Tesselator::instance.offset({v31, v32, v33});
		}
		if(tileClass) {
			this->bindTexture("terrain-atlas.tga");
		} else {
			this->bindTexture(e->itemInstance.itemClass->itemTexture);
		}
		glEnable(0xBC0u);
		glScalef(0.5, 0.5, 0.5);
		glRotatef(180.0 - EntityRenderer::entityRenderDispatcher->field_14, 0.0, 1.0, 0.0);
		Tesselator::instance.draw(0);
		Tesselator::instance.offset(Vec3::ZERO);
		glDisable(0xBC0u);
	}
	glPopMatrix();
}
