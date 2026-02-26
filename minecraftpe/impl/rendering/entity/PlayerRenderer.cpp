#include <rendering/entity/PlayerRenderer.hpp>
#include <rendering/model/HumanoidModel.hpp>
#include <entity/Player.hpp>
#include <item/ArmorItem.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/Font.hpp>
#include <rendering/Tesselator.hpp>

PlayerRenderer::PlayerRenderer(HumanoidModel* a2, float a3)
	: HumanoidMobRenderer(a2, a3) {
	this->hmodel1 = new HumanoidModel(1.0, 0.0);
	this->hmodel2 = new HumanoidModel(0.5, 0.0);
}

PlayerRenderer::~PlayerRenderer() {
	if(this->hmodel1) delete this->hmodel1;
	if(this->hmodel2) delete this->hmodel2;
}

static std::string _dword_D6E083C8_armorTextures[] = {"armor/cloth_1.png", "armor/cloth_2.png", "armor/chain_1.png", "armor/chain_2.png", "armor/iron_1.png", "armor/iron_2.png", "armor/diamond_1.png", "armor/diamond_2.png", "armor/gold_1.png", "armor/gold_2.png"};

void PlayerRenderer::renderName(Entity* a2_, float a3) {
	Player* a2 = (Player*)a2_;
	Mob* cameraEntity; // r1
	float v7;		   // s19
	float v8;		   // s18
	float v9;		   // s17
	Font* font;		   // r7
	int32_t v11;	   // kr00_4
	float v12;		   // s16

	cameraEntity = EntityRenderer::entityRenderDispatcher->cameraEntity;
	if(a2 != cameraEntity && a2->distanceToSqr(cameraEntity) <= 1024.0) {
		v7 = (float)(a2->prevPosX + (float)((float)(a2->posX - a2->prevPosX) * a3)) - EntityRenderDispatcher::xOff;
		v8 = (float)(a2->prevPosY + (float)((float)(a2->posY - a2->prevPosY) * a3)) - EntityRenderDispatcher::yOff;
		v9 = (float)(a2->prevPosZ + (float)((float)(a2->posZ - a2->prevPosZ) * a3)) - EntityRenderDispatcher::zOff;
		font = this->getFont();
		glPushMatrix();
		glTranslatef(v7 + 0.0, v8 + 1.0, v9);
		glRotatef(-EntityRenderer::entityRenderDispatcher->field_14, 0.0, 1.0, 0.0);
		glRotatef(EntityRenderer::entityRenderDispatcher->field_18, 1.0, 0.0, 0.0);
		glScalef(-0.026667, -0.026667, 0.026667);
		glDisable(0xDE1u);
		Tesselator::instance.begin(4);
		v11 = font->width(a2->username);
		Tesselator::instance.color((float)0.0, 0.0, 0.0, 0.25);
		Tesselator::instance.vertex((float) - (float)(v11 / 2) - 1.0, -1.0, 0.0);
		Tesselator::instance.vertex((float) - (float)(v11 / 2) - 1.0, 8.0, 0.0);
		Tesselator::instance.vertex((float)(v11 / 2) + 1.0, 8.0, 0.0);
		Tesselator::instance.vertex((float)(v11 / 2) + 1.0, -1.0, 0.0);
		Tesselator::instance.draw(1);
		glEnable(0xDE1u);
		v12 = (float)font->width(a2->username) * -0.5;
		font->draw(a2->username, v12, 0.0, 553648127);
		font->draw(a2->username, v12, 0.0, -1);
		glPopMatrix();
	}
}
int32_t PlayerRenderer::prepareArmor(Mob* a2_, int32_t armour, float a4) {
	Player* a2 = (Player*)a2_;
	ItemInstance* armor;	// r4
	HumanoidModel* hmodel2; // r4
	bool_t v9;				// r3
	bool_t v10;				// r5

	armor = a2->getArmor(armour);
	if(!ItemInstance::isArmorItem(armor)) {
		return -1;
	}
	this->bindTexture(_dword_D6E083C8_armorTextures[2 * ((ArmorItem*)armor->itemClass)->field_50 + (armour == 2)]);
	if(armour == 2) {
		hmodel2 = this->hmodel2;
	} else {
		hmodel2 = this->hmodel1;
	}
	hmodel2->headModel.field_1D = armour == 0;
	hmodel2->bodyModel.field_1D = (uint32_t)(armour - 1) <= 1;
	v9 = armour == 1;
	hmodel2->rightArmModel.field_1D = armour == 1;
	v10 = (uint32_t)(armour - 2) <= 1;
	hmodel2->leftArmModel.field_1D = v9;
	hmodel2->rightLegModel.field_1D = v10;
	hmodel2->leftLegModel.field_1D = v10;
	this->setArmor(hmodel2);
	hmodel2->field_4 = a2->isRiding();
	return 1;
}
void PlayerRenderer::setupPosition(Entity* a2_, float a3, float a4, float a5) {
	Player* a2 = (Player*)a2_;
	float v11, v12;
	if(a2->isAlive() && a2->isSleeping()) {
		v11 = a3 + a2->field_CC4;
		v12 = a4 + a2->field_CC8;
		a5 = a5 + a2->field_CCC;
	} else {
		v11 = a3;
		v12 = a4;
	}
	MobRenderer::setupPosition(a2, v11, v12, a5);
}
void PlayerRenderer::setupRotations(Entity* a2_, float a3, float a4, float a5) {
	Player* a2 = (Player*)a2_;
	float sleepRot, v10;
	if(a2->isAlive() && a2->isSleeping()) {
		sleepRot = a2->getSleepRotation();
		glRotatef(sleepRot, 0.0, 1.0, 0.0);
		v10 = this->getFlipDegrees(a2);
		glRotatef(v10, 0.0, 0.0, 1.0);
		glRotatef(270.0, 0.0, 1.0, 0.0);
	} else {
		MobRenderer::setupRotations(a2, a3, a4, a5);
	}
}
int32_t PlayerRenderer::getArmorTransparencyMode() {
	return 3008;
}
