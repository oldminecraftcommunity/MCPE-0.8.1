#include <rendering/ItemInHandRenderer.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/EntityTileRenderer.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/Textures.hpp>
#include <rendering/entity/HumanoidMobRenderer.hpp>
#include <rendering/states/DisableState.hpp>
#include <rendering/states/EnableState.hpp>
#include <tile/Tile.hpp>
#include <utils.h>
#include <rendering/TextureTesselator.hpp>

ItemInHandRenderer::ItemInHandRenderer(struct Minecraft* a2)
	: field_4(0, 1, 0)
	, tileRenderer(0) {
	this->minecraft = a2;
	this->field_1C = 0;
	this->field_20 = 0;
	AppPlatform::_singleton->addListener(this, 1.0);
}
int32_t ItemInHandRenderer::_getFrameID(struct Mob* a2, ItemInstance* a3) {
	int32_t v7;
	if(a3->isStackedByData()) {
		v7 = (a3->getId() | ((uint16_t)a3->getAuxValue()) << 12);
	} else {
		v7 = a3->getId() | 0;
	}
	if(a2) {
		v7 |= a2->getEntityTypeId() << 16;					 //byte2
		v7 |= a3->itemClass->getAnimationFrameFor(a2) << 24; //hibyte
	}
	return v7;
}
void ItemInHandRenderer::itemPlaced() {
	this->field_1C = 0;
}
void ItemInHandRenderer::itemUsed() {
	this->field_1C = 0;
}

RenderCall* ItemInHandRenderer::rebuildItem(struct Mob* a2, ItemInstance& a3) {
	//TODO check
	int fid = this->_getFrameID(a2, &a3);
	RenderCall* v7 = new RenderCall();
	auto&& p = this->field_90.find(fid);
	if(p == this->field_90.end()) {
		this->field_90.insert({fid, std::unique_ptr<RenderCall>()});
	}
	p = this->field_90.find(fid);
	p->second.reset(v7); //TODO check

	if(a3.tileClass) {
		int v12 = a3.tileClass->getRenderShape();
		if(TileRenderer::canRender(v12) && a3.tileClass->getRenderShape() != 22) {
			Tesselator::instance.begin(0);
			Tesselator::instance.voidBeginAndEndCalls(1);
			this->tileRenderer.renderTile(a3.tileClass, a3.getAuxValue(), 1);
			Tesselator::instance.voidBeginAndEndCalls(0);
			v7->field_4 = Tesselator::instance.end();
			v7->field_2C = "terrain-atlas.tga";
			v7->field_30 = 0;
			v7->field_0 = a3.getId();
			int v24 = a3.tileClass->getRenderLayer();
			if(v24 != 1) {
				if(!a3.tileClass->goodGraphics) {
					v7->field_31 = 0;
					v7->field_32 = a3.itemClass->isEmissive(a3.getAuxValue());
					return v7;
				}
				if(v24 != 3) {
					v7->field_31 = 0;
					v7->field_32 = a3.itemClass->isEmissive(a3.getAuxValue());
					return v7;
				}
			}
			v7->field_31 = 1;
			v7->field_32 = a3.itemClass->isEmissive(a3.getAuxValue());
			return v7;
		}
	}
	int v25 = a3.getId();
	v7->field_30 = 1;
	v7->field_0 = v25;
	if(a3.tileClass) {
		v7->field_2C = "terrain-atlas.tga";
	} else {
		v7->field_2C = a3.itemClass->itemTexture;
	}
	TextureUVCoordinateSet* icon;
	if(a2) {
		icon = a2->getItemInHandIcon(&a3, 0);
	} else {
		icon = a3.getIcon(0, 0);
	}


	float width = icon->width;
	float v16 = width * icon->minX;
	int v17 = (int)(float)(width * icon->maxX);
	float height = icon->height;
	float v19 = height * icon->minY;
	int v20 = (int)(float)(height * icon->maxY);
	TextureData* td = this->minecraft->texturesPtr->loadAndGetTextureData(v7->field_2C);

	TextureTesselator textes(td, (int)v16, (int)v19, v17, v20, Vec3(0, 0, 0), Color4::BLACK, Color4::WHITE);
	v7->field_4 = textes.tesselate();

	v7->field_32 = a3.itemClass->isEmissive(a3.getAuxValue());
	return v7;
}
void ItemInHandRenderer::render(float a2) {
	Mob* player;			  // r4
	float v6;				  // s23
	int v7;					  // r0
	bool_t v8;				  // r8
	float v9;				  // s16
	float v10;				  // s16
	float v11;				  // s25
	float v12;				  // s19
	float v13;				  // s17
	float v14;				  // s19
	float v15;				  // s12
	float v16;				  // s15
	float v17;				  // s16
	float v18;				  // s11
	float v19;				  // s15
	float v20;				  // r0
	float v21;				  // s17
	int maxUseDuration;		  // r6
	float v23;				  // s18
	float v24;				  // s17
	float v25;				  // r0
	float TimeS;			  // s15
	float v27;				  // s13
	float v28;				  // s25
	double v29;				  // d8
	float v30;				  // s18
	float v31;				  // s26
	float v32;				  // s25
	float v33;				  // s18
	float v34;				  // s15
	float v35;				  // r0
	EntityRenderer* renderer; // r4
	float v39;				  // s19

	glPushMatrix();
	player = (Mob*)this->minecraft->player;
	v6 = this->field_20 + (float)((float)(this->field_1C - this->field_20) * a2);
	if(!this->field_4.itemClass) {
		v28 = this->minecraft->player->getAttackAnim(a2);
		v29 = v28;
		v30 = sqrt(v28);
		v31 = Mth::sin((float)(v28 * v28) * 3.1416);
		v32 = Mth::sin(v28 * 3.1416);
		v33 = Mth::sin(v30 * 3.1416);
		v34 = sqrt(v29);
		v35 = Mth::sin((float)(v34 * 3.1416) + (float)(v34 * 3.1416));
		glTranslatef(-(float)(v33 * 0.3), v35 * 0.4, -(float)(v32 * 0.4));
		glTranslatef(0.64, -0.6 - (float)((float)(1.0 - v6) * 0.6), -0.72);
		glRotatef(45.0, 0.0, 1.0, 0.0);
		glRotatef(v33 * 70.0, 0.0, 1.0, 0.0);
		glRotatef(-(float)(v31 * 20.0), 0.0, 0.0, 1.0);
		this->minecraft->texturesPtr->loadAndBindTexture("mob/char.png");
		glTranslatef(-1.0, 3.6, 3.5);
		glRotatef(120.0, 0.0, 0.0, 1.0);
		glRotatef(200.0, 1.0, 0.0, 0.0);
		glRotatef(-135.0, 0.0, 1.0, 0.0);
		glScalef(1.0, 1.0, 1.0);
		glTranslatef(5.6, 0.0, 0.0);
		renderer = EntityRenderDispatcher::getInstance()->getRenderer(this->minecraft->player);
		glScalef(1.0, 1.0, 1.0);
		((HumanoidMobRenderer*)renderer)->renderHand();
		goto LABEL_28;
	}
	v7 = this->minecraft->player->getUseItemDuration();
	v8 = v7 > 0;
	if(Item::bow == this->field_4.itemClass && Item::bow) {
		if(v7 <= 0) {
LABEL_29:
			v39 = player->getAttackAnim(a2);
			goto LABEL_7;
		}
	} else if(v7 <= 0 || !this->field_4.getUseAnimation()) {
		goto LABEL_29;
	}
	v39 = 0.0;
LABEL_7:
	v9 = sqrt(v39);
	v10 = v9 * 3.1416;
	v11 = Mth::sin((float)(v39 * v39) * 3.1416);
	v12 = Mth::sin(v39 * 3.1416);
	v13 = Mth::sin(v10);
	if(v8) {
		if((unsigned int)(this->field_4.getUseAnimation() - 1) <= 1) {
			v14 = (float)((float)player->getUseItemDuration() - a2) + 1.0;
			v15 = 1.0 - (float)(v14 / (float)this->field_4.getMaxUseDuration());
			v16 = (float)((float)(1.0 - v15) * (float)(1.0 - v15)) * (float)(1.0 - v15);
			v17 = 1.0 - (float)((float)((float)((float)(v16 * v16) * v16) * (float)((float)(v16 * v16) * v16)) * (float)((float)(v16 * v16) * v16));
			v18 = fabsf(Mth::cos((float)((float)(v14 * 0.25) * 3.1416)) * 0.1);
			if(v15 > 0.2) {
				v19 = 1.0;
			} else {
				v19 = 0.0;
			}
			glTranslatef(0.0, v18 * v19, 0.0);
			glTranslatef(v17 * 0.6, -(float)(v17 * 0.5), 0.0);
			glRotatef(v17 * 90.0, 0.0, 1.0, 0.0);
			glRotatef(v17 * 10.0, 1.0, 0.0, 0.0);
			glRotatef(v17 * 30.0, 0.0, 0.0, 1.0);
		}
	} else {
		v20 = Mth::sin(v10 + v10);
		glTranslatef(-(float)(v13 * 0.4), v20 * 0.2, -(float)(v12 * 0.2));
	}
	glTranslatef(0.56, -0.52 - (float)((float)(1.0 - v6) * 0.6), -0.72);
	glRotatef(45.0, 0.0, 1.0, 0.0);
	v21 = -v13;
	glRotatef(-(float)(v11 * 20.0), 0.0, 1.0, 0.0);
	glRotatef(v21 * 20.0, 0.0, 0.0, 1.0);
	glRotatef(v21 * 80.0, 1.0, 0.0, 0.0);
	glScalef(0.4, 0.4, 0.4);
	if(player->getUseItemDuration() <= 0 || this->field_4.getUseAnimation() != 4) {
		goto LABEL_22;
	}
	glRotatef(-18.0, 0.0, 0.0, 1.0);
	glRotatef(-12.0, 0.0, 1.0, 0.0);
	glRotatef(-8.0, 1.0, 0.0, 0.0);
	glTranslatef(-0.9, 0.2, 0.0);
	maxUseDuration = this->field_4.getMaxUseDuration();
	v23 = (float)maxUseDuration - (float)((float)((float)player->getUseItemDuration() - a2) + 1.0);
	v24 = (float)((float)((float)(v23 / 20.0) + (float)(v23 / 20.0)) + (float)((float)(v23 / 20.0) * (float)(v23 / 20.0))) / 3.0;
	if(v24 > 1.0) {
		v24 = 1.0;
LABEL_20:
		v25 = Mth::sin((float)(v23 - 0.1) * 1.3);
		glTranslatef(0.0, (float)(v25 * 0.01) * (float)(v24 - 0.1), 0.0);
		goto LABEL_21;
	}
	if(v24 > 0.1) {
		goto LABEL_20;
	}
LABEL_21:
	glTranslatef(0.0, 0.0, v24 * 0.1);
	glRotatef(-335.0, 0.0, 0.0, 1.0);
	glRotatef(-50.0, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.5, 0.0);
	glScalef(1.0, 1.0, (float)(v24 * 0.2) + 1.0);
	glTranslatef(0.0, -0.5, 0.0);
	glRotatef(50.0, 0.0, 1.0, 0.0);
	glRotatef(335.0, 0.0, 0.0, 1.0);
LABEL_22:
	if(this->field_4.itemClass->isMirroredArt()) {
		glRotatef(180.0, 0.0, 1.0, 0.0);
	}
	if(this->minecraft->options.viewBobbing) {
		TimeS = getTimeS();
		v27 = sinf(TimeS + TimeS);
		glTranslatef(0.0, v27 * 0.011, 0.0);
		glRotatef((float)((float)(v27 * 0.011) * 360.0) * 0.075, 1.0, 0.0, 0.0);
	}
	this->renderItem(player, &this->field_4);
LABEL_28:
	glPopMatrix();
}
void ItemInHandRenderer::renderFire(float a2) {
	int32_t v2;	  // r6
	float minX;	  // r9
	float maxX;	  // r8
	float minY;	  // r5
	float maxY;	  // r10
	int32_t v7;	  // r3
	float width;  // [sp+18h] [bp-30h]
	float height; // [sp+1Ch] [bp-2Ch]

	glColor4f(1.0, 1.0, 1.0, 0.9);
	v2 = 1;
	do {
		glPushMatrix();
		minX = Tile::fire->textureUV.minX;
		maxX = Tile::fire->textureUV.maxX;
		width = Tile::fire->textureUV.width;
		height = Tile::fire->textureUV.height;
		minY = Tile::fire->textureUV.minY;
		maxY = Tile::fire->textureUV.maxY;
		glTranslatef((float)v2 * 0.24, -0.3, 0.0);
		v7 = -v2;
		v2 -= 2;
		glRotatef((float)v7 * 10.0, 0.0, 1.0, 0.0);
		Tesselator::instance.begin(4);
		Tesselator::instance.vertexUV(-0.5, -0.5, -0.5, maxX, maxY);
		Tesselator::instance.vertexUV(0.5, -0.5, -0.5, minX, maxY);
		Tesselator::instance.vertexUV(0.5, 0.5, -0.5, minX, minY);
		Tesselator::instance.vertexUV(-0.5, 0.5, -0.5, maxX, minY);
		Tesselator::instance.draw(1);
		glPopMatrix();
	} while(v2 != -3);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}
void ItemInHandRenderer::renderItem(struct Mob* a2, ItemInstance* a3) {
	Tile* tileClass;	  // r4
	RenderCall* v7;		  // r4
	int graphics;		  // r7
	Minecraft* minecraft; // r3
	GLenum v12;			  // r0
	unsigned int frameId; // r0

	tileClass = a3->tileClass;
	if(tileClass && tileClass->getRenderShape() == 22) {
		EntityTileRenderer::instance->render(tileClass, a3->getAuxValue(), 1.0);
	} else {
		frameId = this->_getFrameID(a2, a3);
		auto&& p = this->field_90.find(frameId);
		if(p == this->field_90.end()) {
			this->rebuildItem(a2, *a3); //TODO check
			p = this->field_90.find(frameId);
		}
		v7 = p->second.get();
		glPushMatrix();
		if(v7->field_30) {
			glScalef(1.5, 1.5, 1.5);
			glRotatef(50.0, 0.0, 1.0, 0.0);
			glRotatef(335.0, 0.0, 0.0, 1.0);
			glTranslatef(0.075, -0.245, -0.1);
			glScalef(0.0625, 0.0625, 0.0625);
			glRotatef(90.0, 0.0, 0.0, 1.0);
			glRotatef(90.0, 1.0, 0.0, 0.0);
			glRotatef(-180.0, 1.0, 0.0, 0.0);
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			glTranslatef(0.0, 0.0, -16.0);
		}
		this->minecraft->texturesPtr->loadAndBindTexture(v7->field_2C);

		{
			EnableState v8(v7->field_31 ? GL_ALPHA_TEST : 0);
			DisableState v18(v7->field_31 ? GL_CULL_FACE : 0);
			graphics = v7->field_31;
			if(v7->field_31) {
				minecraft = this->minecraft;
				graphics = minecraft->options.graphics;
				if(minecraft->options.graphics) {
					glLightModelf(0xB52u, 1.0);
					graphics = 1;
				}
			}
			if(v7->field_32 && this->minecraft->options.graphics) {
				v12 = 2896;
			} else {
				v12 = 0;
			}
			DisableState v19(v12);
			v7->field_4.render();
			if(graphics) {
				glLightModelf(0xB52u, 0.0);
			}
		}

		glPopMatrix();
	}
}
void ItemInHandRenderer::renderScreenEffect(float a2) {
	Minecraft* minecraft; // r2
	Player* player;		  // r3
	float v7;			  // s15
	int32_t v9;			  // r6
	bool_t v10;			  // fnf
	float v11;			  // s15
	int32_t v12;		  // r5
	bool_t v13;			  // fnf
	float v14;			  // s15
	int32_t v15;		  // r3
	Tile* v16;			  // r0
	int32_t v18;		  // [sp+4h] [bp-2Ch]

	if(this->minecraft->player->isOnFire()) {
		this->minecraft->texturesPtr->loadAndBindTexture("terrain-atlas.tga");
		this->renderFire(a2);
	}
	if(this->minecraft->player->isInWall()) {
		minecraft = this->minecraft;
		player = minecraft->player;
		v7 = player->posX;
		v9 = (int32_t)v7;
		v10 = v7 < (float)(int32_t)v7;
		v11 = player->posY;
		v12 = (int32_t)v11;
		if(v10) {
			--v9;
		}
		v13 = v11 < (float)(int32_t)v11;
		v14 = player->posZ;
		v15 = (int32_t)v14;
		if(v13) {
			--v12;
		}
		if(v14 < (float)(int32_t)v14) {
			--v15;
		}
		v18 = v15;
		minecraft->texturesPtr->loadAndBindTexture("terrain-atlas.tga");
		v16 = Tile::tiles[this->minecraft->level->getTile(v9, v12, v18)];
		if(v16) {
			this->renderTex(a2, *v16->getTexture(2));
		}
	}
}
void ItemInHandRenderer::renderTex(float a2, const TextureUVCoordinateSet& a3) {
	struct xy
	{
		float x, y, z;
	};
	DisableState v12(GL_BLEND);
	glDepthFunc(GL_ALWAYS);
	glColor4f(0.3, 0.3, 0.3, 0.5);
	float minX = a3.minX;
	float minY = a3.minY;
	float maxX = a3.maxX + 0.0;
	float maxY = a3.maxY + 0.0;

	Tesselator::instance.begin(16);
	for(auto&& p: {xy{-1.0f, -1.0f, 0.0f}, xy{0.0f, -1.0f, 0.0f}, xy{0.0f, 0.0f, 0.0f}, xy{-1.0f, 0.0f, 0.0f}}) {
		Tesselator::instance.vertexUV(p.x + 0.0, p.y + 0.0, -0.5, maxX, maxY);
		Tesselator::instance.vertexUV(p.x + 1.0, p.y + 0.0, -0.5, minX, maxY);
		Tesselator::instance.vertexUV(p.x + 1.0, p.y + 1.0, -0.5, minX, minY);
		Tesselator::instance.vertexUV(p.x + 0.0, p.y + 1.0, -0.5, maxX, minY);
	}
	Tesselator::instance.draw(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glDepthFunc(GL_LEQUAL);
}
void ItemInHandRenderer::renderWater(float a2) {
	float v3;			 // r0
	LocalPlayer* player; // r3
	float v5;			 // s18
	float v6;			 // s16
	float v7;			 // s17
	float v8;			 // s18
	float v9;			 // s16

	v3 = this->minecraft->player->getBrightness(a2);
	glColor4f(v3, v3, v3, 0.5);
	glPushMatrix();
	player = this->minecraft->player;
	v5 = -(float)(player->yaw * 0.015625);
	v6 = player->pitch * 0.015625;
	Tesselator::instance.begin(4);
	v7 = v5 + 4.0;
	Tesselator::instance.vertexUV(-1.0, -1.0, -0.5, v5 + 4.0, v6 + 4.0);
	v8 = v5 + 0.0;
	Tesselator::instance.vertexUV(1.0, -1.0, -0.5, v8, v6 + 4.0);
	v9 = v6 + 0.0;
	Tesselator::instance.vertexUV(1.0, 1.0, -0.5, v8, v9);
	Tesselator::instance.vertexUV(-1.0, 1.0, -0.5, v7, v9);
	Tesselator::instance.draw(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glPopMatrix();
}
void ItemInHandRenderer::tick() {
	ItemInstance* sel; // r0
	float v11;		   // s14
	float v12;		   // s15

	this->field_20 = this->field_1C;
	sel = this->minecraft->player->inventory->getSelected();
	if(sel && sel->count > 0) {
		this->field_4 = *sel;
	} else {
		this->field_4 = ItemInstance();
	}
	v11 = this->field_1C;
	v12 = 1.0 - v11;
	if((float)(1.0 - v11) < -0.4) {
		v12 = -0.4;
	} else if(v12 > 0.4) {
		v12 = 0.4;
	}
	this->field_1C = v11 + v12;
}

ItemInHandRenderer::~ItemInHandRenderer() {
	AppPlatform::_singleton->removeListener(this);
}
void ItemInHandRenderer::onAppSuspended() {
	this->field_90.clear();
	//TODO do something with field_90: (i+8) = -1
}
