#include <rendering/PolygonQuad.hpp>
#include <rendering/Tesselator.hpp>

PolygonQuad::PolygonQuad(VertexPT* v1, VertexPT* v2, VertexPT* v3, VertexPT* v4){
	this->flipnormal = 0;
	this->verticies[0] = *v1;
	this->verticies[1] = *v2;
	this->verticies[2] = *v3;
	this->verticies[3] = *v4;
}

PolygonQuad::PolygonQuad(VertexPT* v1, VertexPT* v2, VertexPT* v3, VertexPT* v4, int32_t a, int32_t b, int32_t c, int32_t d, int32_t texWidth, int32_t texHeight){
	float tw = (float) texWidth, th = (float) texHeight;

	this->flipnormal = 0;
	VertexPT p1(*v1, (float)c / tw, ((float)b / th) + 0.0f);
	this->verticies[0] = p1;

	float af = ((float)a / tw) + 0.0f;
	VertexPT p2(*v2, af, ((float)b / th) + 0.0f);
	this->verticies[1] = p2;

	float df = (float)d / th;
	VertexPT p3(*v3, af, df);
	this->verticies[2] = p3;

	VertexPT p4(*v4, (float)c / tw, df);
	this->verticies[3] = p4;
}

PolygonQuad::PolygonQuad(VertexPT* v1, VertexPT* v2, VertexPT* v3, VertexPT* v4, float a, float b, float c, float d){
	this->flipnormal = 0;
	//seems like it does this instead of this->verticies[] = VertexPT(...) based on stack size~
	VertexPT p1(*v1, c, b);
	this->verticies[0] = p1;
	VertexPT p2(*v2, a, b);
	this->verticies[1] = p2;
	VertexPT p3(*v3, a, d);
	this->verticies[2] = p3;
	VertexPT p4(*v4, c, d);
	this->verticies[3] = p4;
}

void PolygonQuad::mirror(void){
	for(int i = 0; i < 2; ++i) {
		VertexPT sav = this->verticies[i];
		this->verticies[i] = this->verticies[3 - i];
		this->verticies[3 - i] = sav;
	}
}

void PolygonQuad::render(Tesselator& a2, float a3, int32_t a4){
	Vec3 diff01 = this->verticies[0].vec.sub(this->verticies[1].vec);
	Vec3 diff03 = this->verticies[0].vec.sub(this->verticies[3].vec);
	Vec3 v15 = Vec3(
		diff01.y * diff03.z - diff01.z * diff03.y,
		diff01.z * diff03.x - diff01.x * diff03.z,
		diff01.x * diff03.y - diff01.y * diff03.x
	).normalized();

	a2.normal(v15.x, v15.y, v15.z);
	for(int32_t v23 = 0; v23 != 4; ++v23){
		VertexPT* v = &this->verticies[v23];
		a2.vertexUV(a3*v->vec.x, a3*v->vec.y, a3*v->vec.z, v->u, v->v);
	}
}

void PolygonQuad::flipNormal(void){
	this->flipnormal = 1;
}
