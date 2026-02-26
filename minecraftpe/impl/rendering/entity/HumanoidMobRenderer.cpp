#include <rendering/entity/HumanoidMobRenderer.hpp>
#include <entity/Mob.hpp>
#include <item/Item.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/ItemInHandRenderer.hpp>
#include <rendering/TileRenderer.hpp>
#include <rendering/model/HumanoidModel.hpp>
#include <tile/Tile.hpp>

HumanoidMobRenderer::HumanoidMobRenderer(HumanoidModel* a2, float a3)
	: MobRenderer(a2, a3) {
	this->hmodel = a2;
}
void HumanoidMobRenderer::renderHand() {
	this->hmodel->field_0 = 0.0;
	this->hmodel->setupAnim(0.0, 0.0, 0.0, 0.0, 0.0, 0.0625);
	glEnableClientState(0x8078u);
	this->hmodel->rightArmModel.render(0.0625);
	glDisableClientState(0x8078u);
}

HumanoidMobRenderer::~HumanoidMobRenderer() {
}
void HumanoidMobRenderer::render(Entity* a2_, float a3, float a4, float a5, float a6, float a7) {
	Mob* a2 = (Mob*)a2_;
	if(a2->getCarriedItem()) {
		this->hmodel->field_319 = 1;
	}
	this->hmodel->field_31A = a2->isSneaking();
	MobRenderer::render(a2, a3, a4, a5, a6, a7);
	this->hmodel->field_319 = 0;
}
void HumanoidMobRenderer::additionalRendering(Mob* a2, float a3) {
	ItemInstance* v5; // r0
	ItemInstance* v6; // r4
	int32_t v9;			  // r0
	float v10;		  // r0
	float v11;		  // r0
	float v12;		  // r2
	float v13;		  // r3

	v5 = (ItemInstance*)a2->getCarriedItem();
	v6 = v5;
	if(v5 && v5->count > 0) {
		glPushMatrix();
		this->hmodel->rightArmModel.translateTo(0.0625);
		glTranslatef(-0.0625, 0.4375, 0.0625);
		if(v6->tileClass) {
			v9 = v6->tileClass->getRenderShape();
			if(TileRenderer::canRender(v9)) {
				glTranslatef(0.0, 0.1875, -0.3125);
				glRotatef(200.0, 1.0, 0.0, 0.0);
				glRotatef(45.0, 0.0, 1.0, 0.0);
				glScalef(0.375, 0.375, 0.375);
				goto LABEL_11;
			}
		}
		if(v6->itemClass == Item::bow) {
			glTranslatef(0.2, 0.125, -0.3875);
			glRotatef(-180.0, 1.0, 0.0, 0.0);
			glRotatef(10.0, 0.0, 1.0, 0.0);
			glScalef(0.625, 0.625, 0.625);
			v10 = -100.0;
		} else {
			if(!v6->itemClass->isHandEquipped()) {
				glTranslatef(0.25, 0.1875, -0.1875);
				glScalef(0.375, 0.375, 0.375);
				glRotatef(60.0, 0.0, 0.0, 1.0);
				glRotatef(-90.0, 1.0, 0.0, 0.0);
				v11 = 20.0;
				v13 = 1.0;
				v12 = 0.0;
				goto LABEL_10;
			}
			glRotatef(180.0, 0.0, 1.0, 0.0);
			glTranslatef(0.1, 0.265, 0.0);
			glScalef(0.625, 0.625, 0.625);
			v10 = 80.0;
		}
		glRotatef(v10, 1.0, 0.0, 0.0);
		v11 = 45.0;
		v12 = 1.0;
		v13 = 0.0;
LABEL_10:
		glRotatef(v11, 0.0, v12, v13);
LABEL_11:
		EntityRenderer::entityRenderDispatcher->itemInHandRenderer->renderItem(a2, v6);
		glPopMatrix();
	}
}
