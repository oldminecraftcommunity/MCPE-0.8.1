#include <rendering/entity/PaintingRenderer.hpp>
#include <entity/Painting.hpp>
#include <rendering/Tesselator.hpp>
#include <Motive.hpp>

MeshBuffer PaintingRenderer::_buildPainting(int32_t a2, int32_t a3, int32_t a4, int32_t a5) {
	float x = -a2 * 0.5f;
	float y = -a3 * 0.5f;
	Tesselator::instance.begin(0);
	int v23 = a4 + a2;
	for(int v8 = 0; v8 < a2 / 16; ++v8){
		int xStart = 16 * v8;
		int xEnd = 16 * (v8 + 1);
		int v21 = v23 - 16;
		int v16 = a5 + a3;
		for(int v17 = 0; v17 < a3 / 16; ++v17){
			int v18 = v16 - 16;
			float v12 = y + (float)(16 * (v17 + 1));
			float v14 = y + (float)(16 * ((v17 + 1) + 0xFFFFFFF));
			Tesselator::instance.normal(Vec3::NEG_UNIT_Z);
			Tesselator::instance.vertexUV(x + xEnd, v14, -0.5f, v21 * 0.0039062f, v16 * 0.0039062f);
			Tesselator::instance.vertexUV(x + xStart, v14, -0.5f, v23 * 0.0039062f, v16 * 0.0039062f);
			Tesselator::instance.vertexUV(x + xStart, v12, -0.5f, v23 * 0.0039062f, v18 * 0.0039062f);
			Tesselator::instance.vertexUV(x + xEnd, v12, -0.5f, v21 * 0.0039062f, v18 * 0.0039062f);
			Tesselator::instance.normal(Vec3::UNIT_Z);
			Tesselator::instance.vertexUV(x + xEnd, v12, 0.5f, 0.75f, 0.0f);
			Tesselator::instance.vertexUV(x + xStart, v12, 0.5f, 0.8125f, 0.0f);
			Tesselator::instance.vertexUV(x + xStart, v14, 0.5f, 0.8125f, 0.0625f);
			Tesselator::instance.vertexUV(x + xEnd, v14, 0.5f, 0.75f, 0.0625f);
			Tesselator::instance.normal(Vec3::UNIT_Y);
			Tesselator::instance.vertexUV(x + xEnd, v12, -0.5f, 0.75f, 0.0019531f);
			Tesselator::instance.vertexUV(x + xStart, v12, -0.5f, 0.8125f, 0.0019531f);
			Tesselator::instance.vertexUV(x + xStart, v12, 0.5f, 0.8125f, 0.0019531f);
			Tesselator::instance.vertexUV(x + xEnd, v12, 0.5f, 0.75f, 0.0019531f);
			Tesselator::instance.normal(Vec3::NEG_UNIT_Y);
			Tesselator::instance.vertexUV(x + xEnd, v14, 0.5f, 0.75f, 0.0019531f);
			Tesselator::instance.vertexUV(x + xStart, v14, 0.5f, 0.8125f, 0.0019531f);
			Tesselator::instance.vertexUV(x + xStart, v14, -0.5f, 0.8125f, 0.0019531f);
			Tesselator::instance.vertexUV(x + xEnd, v14, -0.5f, 0.75f, 0.0019531f);
			Tesselator::instance.normal(Vec3::UNIT_X);
			Tesselator::instance.vertexUV(x + xEnd, v12, 0.5f, 0.75195f, 0.0f);
			Tesselator::instance.vertexUV(x + xEnd, v14, 0.5f, 0.75195f, 0.0625f);
			Tesselator::instance.vertexUV(x + xEnd, v14, -0.5f, 0.75195f, 0.0625f);
			Tesselator::instance.vertexUV(x + xEnd, v12, -0.5f, 0.75195f, 0.0f);
			Tesselator::instance.normal(Vec3::NEG_UNIT_X);
			Tesselator::instance.vertexUV(x + xStart, v12, -0.5f, 0.75195f, 0.0f);
			Tesselator::instance.vertexUV(x + xStart, v14, -0.5f, 0.75195f, 0.0625f);
			Tesselator::instance.vertexUV(x + xStart, v14, 0.5f, 0.75195f, 0.0625f);
			Tesselator::instance.vertexUV(x + xStart, v12, 0.5f, 0.75195f, 0.0f);
			v16 = v18;
		}
		v23 -= 16;
	}
	return Tesselator::instance.end();
}
MeshBuffer* PaintingRenderer::_getMesh(const Motive* a2) {
	auto&& p = this->motives.find(a2);
	if(p == this->motives.end()) {
		return &(this->motives[a2] = this->_buildPainting(a2->w, a2->h, a2->uo, a2->vo)); //TODO check
	}
	return &p->second;
}

void PaintingRenderer::render(Entity* e_, float x, float y, float z, float angle, float a7) {
	Painting* e = (Painting*)e_;
	MeshBuffer* mesh = this->_getMesh(e->motive);
	e->setupLighting(this->isFancy(), a7);
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	this->bindTexture("art/kz.png");
	glScalef(0.0625f, 0.0625f, 0.0625f);
	mesh->render();
	glPopMatrix();
}
