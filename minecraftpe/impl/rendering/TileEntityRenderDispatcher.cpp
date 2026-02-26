#include <rendering/TileEntityRenderDispatcher.hpp>
#include <entity/Mob.hpp>
#include <rendering/tileentity/TileEntityRenderer.hpp>
#include <tile/entity/TileEntity.hpp>
#include <level/Level.hpp>
#include <GL/gl.h>
#include <Minecraft.hpp>
#include <rendering/tileentity/ChestRenderer.hpp>
#include <rendering/tileentity/SignRenderer.hpp>

TileEntityRenderDispatcher::TileEntityRenderDispatcher() {
	this->textures = 0;
	this->level = 0; //TODO this thing is not here
	this->rednerers.insert({TER_CHEST, new ChestRenderer()});
	this->rednerers.insert({TER_SIGN, new SignRenderer()});
	for(auto& r: this->rednerers) {
		r.second->init(this);
	}

}
void TileEntityRenderDispatcher::destroy() {
	if(TileEntityRenderDispatcher::instance) {
		delete TileEntityRenderDispatcher::instance;
		TileEntityRenderDispatcher::instance = 0;
	}
}
float TileEntityRenderDispatcher::distanceToSqr(float x, float y, float z) {
	return (float)((float)((float)(y - this->camY) * (float)(y - this->camY)) + (float)((float)(x - this->camX) * (float)(x - this->camX))) + (float)((float)(z - this->camZ) * (float)(z - this->camZ));
}
Font* TileEntityRenderDispatcher::getFont() {
	return this->font;
}

TileEntityRenderDispatcher* TileEntityRenderDispatcher::instance = 0;
float TileEntityRenderDispatcher::xOff = 0;
float TileEntityRenderDispatcher::yOff = 0;
float TileEntityRenderDispatcher::zOff = 0;
TileEntityRenderDispatcher* TileEntityRenderDispatcher::getInstance() {
	if(!TileEntityRenderDispatcher::instance) {
		TileEntityRenderDispatcher::instance = new TileEntityRenderDispatcher();
	}
	return TileEntityRenderDispatcher::instance;
}

TileEntityRenderer* TileEntityRenderDispatcher::getRenderer(TileEntity* a2) {
	return this->getRenderer(a2->renderId);
}
TileEntityRenderer* TileEntityRenderDispatcher::getRenderer(TileEntityRendererId id) {
	auto&& p = this->rednerers.find(id);
	if(p != this->rednerers.end()) {
		return p->second;
	}
	return 0;
}
void TileEntityRenderDispatcher::prepare(Level* a2, Textures* a3, Font* a4, Mob* a5, float a6) {
	if(this->level != a2) {
		this->setLevel(a2);
	}
	this->textures = a3;
	this->cameraMaybe = a5;
	this->font = a4;
	this->camYaw = a5->prevYaw + (float)((float)(a5->yaw - a5->prevYaw) * a6);
	this->camPitch = a5->prevPitch + (float)((float)(a5->pitch - a5->prevPitch) * a6);
	this->camX = a5->prevPosX + (float)((float)(a5->posX - a5->prevPosX) * a6);
	this->camY = a5->prevPosY + (float)((float)(a5->posY - a5->prevPosY) * a6);
	this->camZ = a5->prevPosZ + (float)((float)(a5->posZ - a5->prevPosZ) * a6);
}
void TileEntityRenderDispatcher::render(TileEntity* a2, float a3) {
	float v6; // r0

	if(a2->distanceToSqr(this->camX, this->camY, this->camZ) < 4096.0) {
		v6 = this->level->getBrightness(a2->posX, a2->posY, a2->posZ);
		glColor4f(v6, v6, v6, 1.0);
		this->render(a2, (float)a2->posX - TileEntityRenderDispatcher::xOff, (float)a2->posY - TileEntityRenderDispatcher::yOff, (float)a2->posZ - TileEntityRenderDispatcher::zOff, a3);
	}
}
void TileEntityRenderDispatcher::render(TileEntity* a2, float x, float y, float z, float a6) {
	TileEntityRenderer* renderer; // r0

	renderer = this->getRenderer(a2);
	if(renderer) {
		renderer->render(a2, x, y, z, a6, this->minecraft->options.graphics);
	}
}
void TileEntityRenderDispatcher::setLevel(Level* a2) {
	this->level = a2;
	for(auto& r: this->rednerers) {
		if(r.second) {
			r.second->onNewLevel(a2);
		}
	}
}
TileEntityRenderDispatcher::~TileEntityRenderDispatcher() {
}
