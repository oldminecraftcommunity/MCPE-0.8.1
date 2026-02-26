#include <rendering/entity/MobRenderer.hpp>
#include <Minecraft.hpp>
#include <entity/Mob.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/model/Model.hpp>
#include <rendering/states/DisableState.hpp>
int8_t MobRenderer::menuMode = 0;

MobRenderer::MobRenderer(Model* a2, float a3) {
	this->model = a2;
	this->armorModel = 0;
}
void MobRenderer::_renderColorOverlay(Mob* a2, const Color4& a3, float a4) {
	int32_t i;		   // r6
	Model* armorModel; // r3

	glColor4f(a3.r, a3.g, a3.b, a3.a);
	this->model->render(a2, this->field_8, this->field_C, this->field_10, this->field_14 - this->field_18, this->field_1C, this->field_20);
	for(i = 0; i != 4; ++i) {
		if(this->prepareArmor(a2, i, a4) >= 0) {
			glColor4f(a3.r, a3.g, a3.b, a3.a);
			this->armorModel->prepareMobModel(a2, this->field_8, this->field_C, a4);
			armorModel = this->armorModel;

			{
				DisableState(armorModel->field_5 && this->isFancy() ? 2896 : 0);

				this->armorModel->render(a2, this->field_8, this->field_C, this->field_10, this->field_14 - this->field_18, this->field_1C, this->field_20);
				//~
			}
		}
	}
}
Model* MobRenderer::getArmor() {
	return this->armorModel;
}
void MobRenderer::setArmor(Model* a2) {
	this->armorModel = a2;
}

MobRenderer::~MobRenderer() {
	if(this->model) delete this->model;
}
void MobRenderer::render(Entity* a2_, float a3, float a4, float a5, float a6, float a7) {
	Model* model;	   // r7
	Model* v12;		   // r7
	Model* v13;		   // r7
	Model* armorModel; // r3
	float v15;		   // s17
	float v16;		   // s17
	float v17;		   // s15
	float v18;		   // s14
	bool_t graphics;   // r8
	float v20;		   // r7
	float v21;		   // r0
	int32_t i;		   // r6
	GLenum v25;		   // r0
	GLenum v26;		   // r10
	int32_t v27;	   // r0
	int32_t hurtTime;  // r3
	bool_t v29;		   // r6
	float v30;		   // r0
	Mob* ridingAt;	   // r3
	float v32;		   // s17
	float v33;		   // s17
	float v34;		   // s15
	float v35;		   // r0
	Mob* a2 = (Mob*)a2_;

	glPushMatrix();
	model = this->model;
	model->field_0 = this->getAttackAnim(a2, a7);
	v12 = this->model;
	v12->field_4 = a2->isRiding();
	v13 = this->model;
	v13->field_14 = a2->isBaby();
	armorModel = this->armorModel;
	if(armorModel) {
		armorModel->field_4 = this->model->field_4;
		this->armorModel->field_14 = this->model->field_14;
		this->armorModel->field_0 = this->model->field_0;
	}
	v15 = a2->field_128;
	this->field_18 = v15 + (float)(a7 * Mth::wrapDegrees(a2->field_124 - v15));
	v16 = a2->field_130;
	this->field_14 = v16 + (float)(a7 * Mth::wrapDegrees(a2->headYaw - v16));
	if(a2->isRiding()) {
		if(a2->ridingAt->isMob()) {
			ridingAt = (Mob*)a2->ridingAt;
			v32 = ridingAt->field_128;
			v33 = v32 + (float)(a7 * Mth::wrapDegrees(ridingAt->field_124 - v32));
			v34 = this->field_14 - v33;
			this->field_18 = v33;
			v35 = Mth::wrapDegrees(v34);
			v17 = v35;
			if(v35 < -85.0) {
				v17 = -85.0;
			} else if(v35 >= 85.0) {
				v17 = 85.0;
			}
			v18 = this->field_14 - v17;
			if((float)(v17 * v17) > 2500.0) {
				v18 = v18 + (float)(v17 * 0.2);
			}
			this->field_18 = v18;
		}
	}
	this->field_1C = a2->prevPitch + (float)((float)(a2->pitch - a2->prevPitch) * a7);
	graphics = EntityRenderer::entityRenderDispatcher->minecraft->options.graphics;
	if(MobRenderer::menuMode) {
		v20 = 1.0;
	} else {
		v20 = a2->setupLighting(EntityRenderer::entityRenderDispatcher->minecraft->options.graphics, a7);
	}
	this->setupPosition(a2, a3, a4 - a2->ridingHeight, a5);
	v21 = this->getBob(a2, a7);
	this->field_10 = v21;
	this->setupRotations(a2, v21, this->field_18, a7);
	this->field_20 = 0.0625;
	glScalef(-1.0, -1.0, 1.0);
	this->scale(a2, a7);
	glTranslatef(0.0, (float)(this->field_20 * -24.0) - 0.0078125, 0.0);
	this->field_C = a2->field_168 + (float)((float)(a2->field_16C - a2->field_168) * a7);
	this->field_8 = a2->field_170 - (float)((float)(1.0 - a7) * a2->field_16C);
	if(a2->isBaby()) {
		this->field_8 = this->field_8 * 3.0;
	}
	if(this->field_C > 1.0) {
		this->field_C = 1.0;
	}
	this->bindTexture(*a2->getTexture());
	this->model->prepareMobModel(a2, this->field_8, this->field_C, a7);
	this->model->render(a2, this->field_8, this->field_C, this->field_10, this->field_14 - this->field_18, this->field_1C, this->field_20);
	for(i = 0; i != 4; ++i) {
		if(this->prepareArmor(a2, i, a7) >= 0) {
			this->armorModel->prepareMobModel(a2, this->field_8, this->field_C, a7);
			v25 = this->getArmorTransparencyMode();
			v26 = v25;
			if(v25) {
				glEnable(v25);
			}
			if(this->armorModel->field_5) {
				if(graphics) {
					Color4 params(10, 10, 1, 10);
					glLightfv(0x4000u, 0x1200u, &params.r);
				}
			}
			this->armorModel->render(a2, this->field_8, this->field_C, this->field_10, this->field_14 - this->field_18, this->field_1C, this->field_20);
			if(this->armorModel->field_5) {
				if(graphics) {
					a2->setupLighting(1, a7);
				}
			}
			if(v26) {
				glDisable(v26);
			}
		}
	}
	this->additionalRendering(a2, a7);
	v27 = this->getOverlayColor(a2, v20, a7);
	Color4 v39((float)((v27 & 0xff0000) >> 16) / 255.0, (float)((v27 & 0xff00) >> 8) / 255.0, (float)(v27 & 0xff) / 255.0, (float)(v27 >> 24) / 255.0);
	hurtTime = a2->hurtTime;
	if(hurtTime > 0) {
		v29 = 1;
		goto LABEL_50;
	}
	v29 = a2->deathTime > 0;
	if((float)((float)(v27 >> 24) / 255.0) > 0.0 || a2->deathTime > 0 || a2->isOnFire()) {
LABEL_50:
		glEnable(0xBE2u);
		DisableState v37(0xDE1);
		DisableState v38(this->isFancy() ? 0xB50 : 0);

		glDepthFunc(0x202u);
		if(a2->isOnFire()) {
			v30 = powf((float)((float)a2->fire / 100.0) * 0.5, 0.3);
			Color4 params(0.8, 0.256, 0.0, (float)((float)(v30 + 0.25) + 0.1) * 0.6);
			this->_renderColorOverlay(a2, params, a7);
		} else {
			if(!v29) {
LABEL_43:
				if(v39.a > 0.0) {
					this->_renderColorOverlay(a2, v39, a7);
				}

				goto LABEL_46;
			}
			Color4 params(v20, 0, 0, 0.6);
			this->_renderColorOverlay(a2, params, a7);
		}
		goto LABEL_43;
LABEL_46:
		glDepthFunc(0x203u);
		//DisableState::~DisableState((DisableState*)&v38);
		//DisableState::~DisableState((DisableState*)&v37);
		glDisable(0xBE2u);
		//~DisableState(v38), v37, 0xbe2
	}
	glPopMatrix();
}
int32_t MobRenderer::prepareArmor(Mob*, int32_t, float) {
	return -1;
}
void MobRenderer::setupPosition(Entity*, float a3, float a4, float a5) {
	glTranslatef(a3, a4, a5);
}
void MobRenderer::setupRotations(Entity* a2_, float a3, float a4, float a5) {
	int32_t deathTime; // r3
	float v8;		   // s17
	float v9;		   // r0
	Mob* a2 = (Mob*)a2_;

	glRotatef(180.0 - a4, 0.0, 1.0, 0.0);
	deathTime = a2->deathTime;
	if(deathTime > 0) {
		v8 = sqrt((float)((float)((float)((float)((float)deathTime + a5) - 1.0) / 20.0) * 1.6));
		if(v8 > 1.0) {
			v8 = 1.0;
		}
		v9 = v8 * this->getFlipDegrees(a2);
		glRotatef(v9, 0.0, 0.0, 1.0);
	}
}
float MobRenderer::getAttackAnim(Mob* a2, float a3) {
	return a2->getAttackAnim(a3);
}
float MobRenderer::getBob(Mob* a2, float a3) {
	return (float)a2->field_D8 + a3;
}
float MobRenderer::getFlipDegrees(Mob*) {
	return 90;
}
int32_t MobRenderer::getOverlayColor(Mob*, float, float) {
	return 0;
}
void MobRenderer::scale(Mob*, float) {
}
void MobRenderer::additionalRendering(Mob*, float) {
}
int32_t MobRenderer::getArmorTransparencyMode() {
	return 3042;
}
