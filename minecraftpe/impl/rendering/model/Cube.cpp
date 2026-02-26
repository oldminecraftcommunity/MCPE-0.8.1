#include <rendering/model/Cube.hpp>
#include <rendering/model/ModelPart.hpp>

Cube::Cube(struct ModelPart* a2, int32_t a3, int32_t a4, float a5, float a6, float a7, int32_t a8, int32_t a9, int32_t a10, float a11) {
	for(VertexPT& v: this->field_0) {
		v.vec.x = 0;
		v.vec.y = 0;
		v.vec.z = 0;
	}
	this->field_29C = a5;
	this->field_2A0 = a6;
	this->field_2A4 = a7;
	this->id = "";
	float v17 = a5 + (float)a8;
	float v18 = a6 + (float)a9;
	this->field_2A8 = v17;
	float v19 = a7 + (float)a10;
	this->field_2AC = v18;
	this->field_2B0 = v19;
	float v20 = a5 - a11;
	float v21 = a6 - a11;
	float v22 = a7 - a11;
	float v23 = v17 + a11;
	float v24 = v18 + a11;
	float v25 = v19 + a11;
	if(!a2->mirror) {
		float v26 = v23;
		v23 = a5 - a11;
		v20 = v26;
	}
	this->field_0[0].vec = Vec3(v23, v21, v22);
	this->field_0[0].u = 0;
	this->field_0[0].v = 0;

	this->field_0[1].vec = Vec3(v20, v21, v22);
	this->field_0[1].u = 0;
	this->field_0[1].v = 8;

	this->field_0[2].vec = Vec3(v20, v24, v22);
	this->field_0[2].u = 8;
	this->field_0[2].v = 8;

	this->field_0[3].vec = Vec3(v23, v24, v22);
	this->field_0[3].u = 8;
	this->field_0[3].v = 0;

	this->field_0[4].vec = Vec3(v23, v21, v25);
	this->field_0[4].u = 0;
	this->field_0[4].v = 0;

	this->field_0[5].vec = Vec3(v20, v21, v25);
	this->field_0[5].u = 0;
	this->field_0[5].v = 8;

	this->field_0[6].vec = Vec3(v20, v24, v25);
	this->field_0[6].u = 8;
	this->field_0[6].v = 8;

	this->field_0[7].vec = Vec3(v23, v24, v25);
	this->field_0[7].u = 8;
	this->field_0[7].v = 0;
	int32_t texWidth = (int32_t)a2->texWidth;
	int32_t v44 = a3 + a10 + a8;
	int32_t v45 = a4 + a10;
	int32_t texHeight = (int32_t)a2->texHeight;
	this->quads[0] = PolygonQuad(&this->field_0[5], &this->field_0[1], &this->field_0[2], &this->field_0[6], v44, v45, v44 + a10, v45 + a9, texWidth, texHeight);
	this->quads[1] = PolygonQuad(&this->field_0[0], &this->field_0[4], &this->field_0[7], &this->field_0[3], a3, v45, a3 + a10, v45 + a9, texWidth, texHeight);
	this->quads[2] = PolygonQuad(&this->field_0[5], &this->field_0[4], &this->field_0[0], &this->field_0[1], a3 + a10, a4, v44, a4 + a10, texWidth, texHeight);
	this->quads[3] = PolygonQuad(&this->field_0[2], &this->field_0[3], &this->field_0[7], &this->field_0[6], v44, a4 + a10, v44 + a8, a4, texWidth, texHeight);
	this->quads[4] = PolygonQuad(&this->field_0[1], &this->field_0[0], &this->field_0[3], &this->field_0[2], a3 + a10, v45, v44, v45 + a9, texWidth, texHeight);
	this->quads[5] = PolygonQuad(&this->field_0[4], &this->field_0[5], &this->field_0[6], &this->field_0[7], v44 + a10, v45, v44 + a10 + a8, v45 + a9, texWidth, texHeight);
	if(a2->mirror) {
		for(int32_t i = 0; i != 6; ++i) {
			this->quads[i].mirror();
		}
	}
}
void Cube::compile(struct Tesselator& a2, float a3) {
	for(int32_t i = 0; i != 6; ++i) {
		this->quads[i].render(a2, a3, -1);
	}
}
Cube* Cube::setId(const std::string& a2) {
	this->id = a2;
	return this;
}
