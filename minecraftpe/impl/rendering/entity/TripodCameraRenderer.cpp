#include <rendering/entity/TripodCameraRenderer.hpp>
#include <entity/TripodCamera.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>
#include <rendering/model/ModelPart.hpp>
#include <GL/gl.h>
#include <rendering/Tesselator.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <Minecraft.hpp>

TripodCameraRenderer::TripodCameraRenderer()
	: tileRenderer(0)
	, tile(0, "dirt", Material::plant)
	, field_F0(0, 0, 64, 32) {
	this->field_F0.addBox(-4.0, -4.0, -6.0, 8, 8, 10);
	this->field_F0.yOffset = 11.0;
}
float TripodCameraRenderer::getFlashTime(const TripodCamera* a1, float a2){
	int32_t v2; // r3
	int32_t v3; // s13

	v2 = a1->field_C70;
	if ( v2 > 7 || v2 < 0 )
	{
		return -1.0;
	}
	v3 = a1->field_C70;
	return (float)((float)v2 - a2) * 0.125;
}

TripodCameraRenderer::~TripodCameraRenderer(){

}
void TripodCameraRenderer::render(Entity* a2, float x, float y, float z, float a6, float a7) {
	Entity* entity;	 // r6
	float flashTime; // r0
	float v15;		 // s15

	glPushMatrix();
	glTranslatef(x, y, z);
	this->field_F0.xRotAngle = 0.017453 * (float)((float)(a2->pitch * 0.5) + 180.0);
	this->field_F0.yRotAngle = -(float)(0.017453 * a2->yaw);
	Tesselator::instance.color((float)1.0, 1.0, 1.0);
	this->bindTexture("items-opaque.png");
	Tesselator::instance.begin(0);
	this->tileRenderer.tesselateCrossTexture(&this->tile, 0, -0.5, -0.5, -0.5);
	Tesselator::instance.draw(1);
	this->bindTexture("item/camera.png");
	this->field_F0.render(0.0625);
	entity = EntityRenderer::entityRenderDispatcher->minecraft->selectedObject.entity;
	flashTime = TripodCameraRenderer::getFlashTime((TripodCamera*)a2, a7);
	if(flashTime >= 0.0) {
		v15 = sin((float)(flashTime * 6.283));
		glColor4f(1.0, 1.0, 1.0, v15);
		glColor4f(1.0, 1.0, 1.0, 1.0);
	}
	if(entity == a2) {
		glDisable(0xDE1u);
		glBlendFunc(0x302u, 0x304u);
		glColor4f(0.5, 0.5, 0.5, 0.5);
		this->field_F0.renderHorrible(0.0625);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBlendFunc(0x302u, 0x303u);
		glEnable(0xDE1u);
	}
	glPopMatrix();
}
