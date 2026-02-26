#include <rendering/entity/ArrowRenderer.hpp>
#include <rendering/Tesselator.hpp>
#include <entity/Arrow.hpp>
#include <math/Mth.hpp>
ArrowRenderer::ArrowRenderer()
	: EntityRenderer()
	, field_8() {
	AppPlatform::_singleton->addListener(this, 1);
}
ArrowRenderer::~ArrowRenderer() {
	AppPlatform::_singleton->removeListener(this);
}
void ArrowRenderer::render(Entity* e, float x, float y, float z, float a6, float a7) {
	float v12; // s16

	if(!this->field_8.arrayBuffer || this->field_8.arraysCount <= 3 || !this->field_8.drawMode || !this->field_8.vertexFormat) {
		Tesselator::instance.begin(12);
		Tesselator::instance.normal(Vec3::UNIT_X);
		Tesselator::instance.vertexUV(-7.0, -2.0, -2.0, 0.0, 0.15625);
		Tesselator::instance.vertexUV(-7.0, -2.0, 2.0, 0.15625, 0.15625);
		Tesselator::instance.vertexUV(-7.0, 2.0, 2.0, 0.15625, 0.3125);
		Tesselator::instance.vertexUV(-7.0, 2.0, -2.0, 0.0, 0.3125);
		Tesselator::instance.normal(Vec3::UNIT_Z);
		Tesselator::instance.vertexUV(-8.0, -2.0, 0.0, 0.0, 0.0);
		Tesselator::instance.vertexUV(8.0, -2.0, 0.0, 0.5, 0.0);
		Tesselator::instance.vertexUV(8.0, 2.0, 0.0, 0.5, 0.15625);
		Tesselator::instance.vertexUV(-8.0, 2.0, 0.0, 0.0, 0.15625);
		Tesselator::instance.normal(Vec3::UNIT_Y);
		Tesselator::instance.vertexUV(-8.0, 0.0, -2.0, 0.0, 0.0);
		Tesselator::instance.vertexUV(8.0, 0.0, -2.0, 0.5, 0.0);
		Tesselator::instance.vertexUV(8.0, 0.0, 2.0, 0.5, 0.15625);
		Tesselator::instance.vertexUV(-8.0, 0.0, 2.0, 0.0, 0.15625);
		this->field_8 = Tesselator::instance.end();
	}
	e->setupLighting(this->isFancy(), a7);
	this->bindTexture("item/arrows.png");
	glPushMatrix();
	glEnable(0xBC0u);
	glDisable(0xB44u);
	glLightModelf(0xB52u, 1.0);
	glTranslatef(x, y, z);
	glRotatef((float)(e->prevYaw + (float)((float)(e->yaw - e->prevYaw) * a7)) - 90.0, 0.0, 1.0, 0.0);
	glRotatef(e->prevPitch + (float)((float)(e->pitch - e->prevPitch) * a7), 0.0, 0.0, 1.0);
	v12 = (float)((Arrow*)e)->shake - a7;
	if(v12 > 0.0) {
		glRotatef(-(float)(Mth::sin(v12 * 3.0) * v12), 0.0, 0.0, 1.0);
	}
	glRotatef(45.0, 1.0, 0.0, 0.0);
	glScalef(0.05625, 0.05625, 0.05625);
	glTranslatef(-4.0, 0.0, 0.0);
	this->field_8.render();
	glLightModelf(0xB52u, 0.0);
	glEnable(0xB44u);
	glDisable(0xBC0u);
	glPopMatrix();
}
void ArrowRenderer::onAppSuspended() {
	this->field_8.reset();
}
