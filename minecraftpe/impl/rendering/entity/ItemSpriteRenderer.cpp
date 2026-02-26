#include <rendering/entity/ItemSpriteRenderer.hpp>
#include <item/Item.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/EntityRenderDispatcher.hpp>

ItemSpriteRenderer::ItemSpriteRenderer(Item* a2)
	: meshBuffer() {
	this->item = a2;
	this->textureFile = "";
	AppPlatform::_singleton->addListener(this, 1.0);
}

ItemSpriteRenderer::~ItemSpriteRenderer() {
	AppPlatform::_singleton->removeListener(this);
}
void ItemSpriteRenderer::render(Entity* e, float x, float y, float z, float a6, float a7) {
	TextureUVCoordinateSet* v11; // r5
	float v12;					 // s16
	float v13;					 // s17
	float v14;					 // r11
	float v15;					 // s18

	if(!this->meshBuffer.arrayBuffer || this->meshBuffer.arraysCount <= 3 || !this->meshBuffer.drawMode || !this->meshBuffer.vertexFormat) {
		v11 = this->item->getIcon(0, 0, 0);
		this->textureFile = this->item->itemTexture;
		v12 = v11->minX;
		v13 = v11->maxX;
		v14 = v11->minY;
		v15 = v11->maxY;
		Tesselator::instance.begin(4);
		Tesselator::instance.normal(Vec3::UNIT_Z.x, Vec3::UNIT_Z.y, Vec3::UNIT_Z.z);
		Tesselator::instance.vertexUV(-0.5, -0.25, 0.0, v12, v15);
		Tesselator::instance.vertexUV(0.5, -0.25, 0.0, v13, v15);
		Tesselator::instance.vertexUV(0.5, 0.75, 0.0, v13, v14);
		Tesselator::instance.vertexUV(-0.5, 0.75, 0.0, v12, v14);
		this->meshBuffer = Tesselator::instance.end();
	}
	glEnable(0xBC0u);
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(0.5, 0.5, 0.5);
	this->bindTexture(this->textureFile);
	glRotatef(180.0 - EntityRenderer::entityRenderDispatcher->field_14, 0.0, 1.0, 0.0);
	glRotatef(-EntityRenderer::entityRenderDispatcher->field_18, 1.0, 0.0, 0.0);
	this->meshBuffer.render();
	glPopMatrix();
	glDisable(0xBC0u);
}
void ItemSpriteRenderer::onAppSuspended() {
}
