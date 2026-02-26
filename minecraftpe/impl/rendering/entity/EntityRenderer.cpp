#include <rendering/entity/EntityRenderer.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/Textures.hpp>
#include <Options.hpp>
#include <entity/particles/Particle.hpp>
#include <GL/gl.h>
#include <rendering/Tesselator.hpp>
#include <level/Level.hpp>

EntityRenderDispatcher* EntityRenderer::entityRenderDispatcher;

EntityRenderer::EntityRenderer() {
}
void EntityRenderer::bindTexture(const std::string& a2) {
	EntityRenderer::entityRenderDispatcher->textures->loadAndBindTexture(a2);
}
Font* EntityRenderer::getFont() {
	return EntityRenderer::entityRenderDispatcher->getFont();
}
void EntityRenderer::init(EntityRenderDispatcher* a2) {
	EntityRenderer::entityRenderDispatcher = a2;
}
bool_t EntityRenderer::isFancy() {
	return EntityRenderer::entityRenderDispatcher->options->graphics;
}
void EntityRenderer::render(const AABB& bb, float x, float y, float z) {
	glDisable(0xDE1u);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	Tesselator::instance.begin(24);
	Tesselator::instance.offset(x, y, z);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.maxZ);
	Tesselator::instance.offset(0.0, 0.0, 0.0);
	Tesselator::instance.draw(1);
	glEnable(0xDE1u);
}
static int32_t _dword_D6E08228 = 0;
void EntityRenderer::renderFlame(Entity* e, float x, float y, float z, float){
	float xx;	   // r5
	float zz;	   // r6
	float v9;	   // s12
	Particle* v10; // r0
	float motionX; // s14
	Particle* v12; // r0

	Vec3 a3 = e->getRandomPointInAABB(e->level->random);
	xx = a3.x;
	zz = a3.z;
	if((_dword_D6E08228 & 1) != 0) {
		v9 = 1.0;
		if(a3.y >= e->posY) {
			v9 = 0.0;
		}
		v10 = e->level->addParticle(PT_SMOKE, a3.x, a3.y + v9, a3.z, e->motionX * 0.5, 0.0, e->motionZ * 0.5, 250);
		if(v10) {
			v10->maxAliveTime /= 2;
		}
	}
	if(++_dword_D6E08228 == 10) {
		motionX = e->motionX;
		_dword_D6E08228 = 0;
		v12 = e->level->addParticle(PT_MOB_FLAME, xx, e->boundingBox.minY, zz, motionX * 0.5, 0.0, e->motionZ * 0.5, 0);
		if(v12) {
			v12->setEntity(e);
		}
	}
}
void EntityRenderer::renderFlat(const AABB& bb){
	Tesselator::instance.begin(24);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.minX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.minX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.minZ);
	Tesselator::instance.vertex(bb.maxX, bb.maxY, bb.maxZ);
	Tesselator::instance.vertex(bb.maxX, bb.minY, bb.maxZ);
	Tesselator::instance.draw(1);
}

EntityRenderer::~EntityRenderer() {
}
void EntityRenderer::postRender(Entity* a2, float a3, float a4, float a5, float a6, float a7) {
	if(a2->isOnFire()) {
		this->renderFlame(a2, a3, a4, a5, a7);
	}
}
void EntityRenderer::renderName(Entity*, float) {
}
