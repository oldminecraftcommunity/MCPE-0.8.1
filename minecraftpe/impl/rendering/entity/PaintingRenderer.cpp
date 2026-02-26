#include <rendering/entity/PaintingRenderer.hpp>
#include <entity/Painting.hpp>
#include <rendering/Tesselator.hpp>
#include <Motive.hpp>

MeshBuffer PaintingRenderer::_buildPainting(int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
	int32_t v8; // r11
	float v9; // s27
	float v10; // s28
	int32_t v11; // r12
	float v12; // r5
	int32_t v13; // s14
	float v14; // r7
	float v15; // s30
	int32_t v16; // r3
	int32_t v17; // r12
	int32_t v18; // s22
	int32_t v19; // s23
	int32_t v20; // s24
	int32_t v21; // s21
	int32_t v22; // [sp+Ch] [bp-7Ch]
	int32_t v23; // [sp+10h] [bp-78h]
	int32_t v25; // [sp+18h] [bp-70h]

	v8 = 0;
	v9 = (float)-a2 * 0.5;
	v10 = (float)-a3 * 0.5;
	Tesselator::instance.begin(0);
	v25 = a2 / 16;
	v23 = a4 + a2;
	while(v8 < v25) {
		v17 = 0;
		v19 = 16 * v8;
		v20 = 16 * (v8 + 1);
		v21 = v23 - 16;
		v16 = a5 + a3;
		while(1) {
			v18 = v16 - 16;
			if(v17 >= a3 / 16) {
				break;
			}
			v11 = v17 + 1;
			v12 = v10 + (float)(16 * v11);
			v13 = v16;
			v22 = v11;
			v14 = v10 + (float)(16 * (v11 + 0xFFFFFFF));
			Tesselator::instance.normal(Vec3::NEG_UNIT_Z);
			v15 = (float)v23 * 0.0039062;
			Tesselator::instance.vertexUV(v9 + (float)v20, v14, -0.5, (float)v21 * 0.0039062, (float)v13 * 0.0039062);
			Tesselator::instance.vertexUV(v9 + (float)v19, v14, -0.5, v15, (float)v13 * 0.0039062);
			Tesselator::instance.vertexUV(v9 + (float)v19, v12, -0.5, v15, (float)v18 * 0.0039062);
			Tesselator::instance.vertexUV(v9 + (float)v20, v12, -0.5, (float)v21 * 0.0039062, (float)v18 * 0.0039062);
			Tesselator::instance.normal(Vec3::UNIT_Z);
			Tesselator::instance.vertexUV(v9 + (float)v20, v12, 0.5, 0.75, 0.0);
			Tesselator::instance.vertexUV(v9 + (float)v19, v12, 0.5, 0.8125, 0.0);
			Tesselator::instance.vertexUV(v9 + (float)v19, v14, 0.5, 0.8125, 0.0625);
			Tesselator::instance.vertexUV(v9 + (float)v20, v14, 0.5, 0.75, 0.0625);
			Tesselator::instance.normal(Vec3::UNIT_Y);
			Tesselator::instance.vertexUV(v9 + (float)v20, v12, -0.5, 0.75, 0.0019531);
			Tesselator::instance.vertexUV(v9 + (float)v19, v12, -0.5, 0.8125, 0.0019531);
			Tesselator::instance.vertexUV(v9 + (float)v19, v12, 0.5, 0.8125, 0.0019531);
			Tesselator::instance.vertexUV(v9 + (float)v20, v12, 0.5, 0.75, 0.0019531);
			Tesselator::instance.normal(Vec3::NEG_UNIT_Y);
			Tesselator::instance.vertexUV(v9 + (float)v20, v14, 0.5, 0.75, 0.0019531);
			Tesselator::instance.vertexUV(v9 + (float)v19, v14, 0.5, 0.8125, 0.0019531);
			Tesselator::instance.vertexUV(v9 + (float)v19, v14, -0.5, 0.8125, 0.0019531);
			Tesselator::instance.vertexUV(v9 + (float)v20, v14, -0.5, 0.75, 0.0019531);
			Tesselator::instance.normal(Vec3::UNIT_X);
			Tesselator::instance.vertexUV(v9 + (float)v20, v12, 0.5, 0.75195, 0.0);
			Tesselator::instance.vertexUV(v9 + (float)v20, v14, 0.5, 0.75195, 0.0625);
			Tesselator::instance.vertexUV(v9 + (float)v20, v14, -0.5, 0.75195, 0.0625);
			Tesselator::instance.vertexUV(v9 + (float)v20, v12, -0.5, 0.75195, 0.0);
			Tesselator::instance.normal(Vec3::NEG_UNIT_X);
			Tesselator::instance.vertexUV(v9 + (float)v19, v12, -0.5, 0.75195, 0.0);
			Tesselator::instance.vertexUV(v9 + (float)v19, v14, -0.5, 0.75195, 0.0625);
			Tesselator::instance.vertexUV(v9 + (float)v19, v14, 0.5, 0.75195, 0.0625);
			Tesselator::instance.vertexUV(v9 + (float)v19, v12, 0.5, 0.75195, 0.0);
			v16 = v18;
			v17 = v22;
		}
		++v8;
		v23 -= 16;
	}
	return Tesselator::instance.end();
}
MeshBuffer* PaintingRenderer::_getMesh(const Motive* a2) {
	auto&& p = this->motives.find(a2);
	if(p != this->motives.end()) {
		return &p->second;
	}
	return &this->motives.insert({a2, this->_buildPainting(a2->w, a2->h, a2->uo, a2->vo)}).first->second;
}

PaintingRenderer::~PaintingRenderer() {
	AppPlatform::_singleton->removeListener(this);
}
void PaintingRenderer::render(Entity* e_, float x, float y, float z, float angle, float a7) {
	Painting* e = (Painting*)e_;
	MeshBuffer* mesh; // r6

	mesh = this->_getMesh(e->motive);
	e->setupLighting(this->isFancy(), a7);
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, 0.0, 1.0, 0.0);
	this->bindTexture("art/kz.png");
	glScalef(0.0625, 0.0625, 0.0625);
	mesh->render();
	glPopMatrix();
}
void PaintingRenderer::onAppSuspended() {
	this->motives.clear();
}
