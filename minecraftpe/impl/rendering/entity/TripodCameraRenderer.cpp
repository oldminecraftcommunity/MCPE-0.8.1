#include <rendering/entity/TripodCameraRenderer.hpp>
#include <entity/TripodCamera.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>
#include <rendering/model/ModelPart.hpp>
#include <unigl.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <Minecraft.hpp>
#include <math/Mth.hpp>

TripodCameraRenderer::TripodCameraRenderer()
	: tileRenderer(0)
	, tile(0, "dirt", Material::plant)
	, field_F0(0, 0, 64, 32) {
	this->field_F0.addBox(-4.0, -4.0, -6.0, 8, 8, 10);
	this->field_F0.yOffset = 11.0;
}
float TripodCameraRenderer::getFlashTime(const TripodCamera* ent, float a2) {
	if(ent->field_C70 > 7) return -1.0f;
	if(ent->field_C70 < 0) return -1.0f;

	return (ent->field_C70 - a2) * 0.125f;
}

void TripodCameraRenderer::render(Entity* a2, float x, float y, float z, float a6, float a7) {
	glPushMatrix();
	glTranslatef(x, y, z);
	this->field_F0.xRotAngle = Mth::deg2rad((a2->pitch * 0.5f) + 180.0f);
	this->field_F0.yRotAngle = -Mth::deg2rad(a2->yaw);
	Tesselator::instance.color(1.0f, 1.0f, 1.0f);
	this->bindTexture("items-opaque.png");
	Tesselator::instance.begin(0);
	this->tileRenderer.tesselateCrossTexture(&this->tile, 0, -0.5f, -0.5f, -0.5f);
	Tesselator::instance.draw(1);
	this->bindTexture("item/camera.png");
	this->field_F0.render(0.0625f);
	Entity* entity = EntityRenderer::entityRenderDispatcher->minecraft->selectedObject.entity;
	float flashTime = TripodCameraRenderer::getFlashTime((TripodCamera*)a2, a7);
	if(flashTime >= 0.0) {
		float v15 = sin(flashTime * 6.283f);
		glColor4f(1.0f, 1.0f, 1.0f, v15);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}
	if(entity == a2) {
		glDisable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
		glColor4f(0.5f, 0.5f, 0.5f, 0.5f);
		this->field_F0.renderHorrible(0.0625f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
	}
	glPopMatrix();
}
