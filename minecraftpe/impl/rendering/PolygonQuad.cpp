#include <rendering/PolygonQuad.hpp>
#include <rendering/Tesselator.hpp>
PolygonQuad::PolygonQuad(){
	for(int i = 0; i < 4; ++i){
		this->verticies[i].vec.x = 0;
		this->verticies[i].vec.y = 0;
		this->verticies[i].vec.z = 0;
	}
}
PolygonQuad::PolygonQuad(VertexPT* v1, VertexPT* v2, VertexPT* v3, VertexPT* v4){
	for(int i = 0; i < 4; ++i){
		this->verticies[i].vec.x = 0;
		this->verticies[i].vec.y = 0;
		this->verticies[i].vec.z = 0;
	}
	this->flipnormal = 0;
	this->verticies[0] = *v1;
	this->verticies[1] = *v2;
	this->verticies[2] = *v3;
	this->verticies[3] = *v4;
}

PolygonQuad::PolygonQuad(VertexPT* v1, VertexPT* v2, VertexPT* v3, VertexPT* v4, float a, float b, float c, float d){

	for(int i = 0; i < 4; ++i){
		this->verticies[i].vec.x = 0;
		this->verticies[i].vec.y = 0;
		this->verticies[i].vec.z = 0;
	}

	this->flipnormal = 0;

	{
		VertexPT vec(*v1, c, b);
		this->verticies[0] = vec;
	}
	{
		VertexPT vec(*v2, a, b);
		this->verticies[1] = vec;
	}
	{
		VertexPT vec(*v3, a, d);
		this->verticies[2] = vec;
	}
	{
		VertexPT vec(*v4, c, d);
		this->verticies[3] = vec;
	}
}

PolygonQuad::PolygonQuad(VertexPT* v1, VertexPT* v2, VertexPT* v3, VertexPT* v4, int32_t a, int32_t b, int32_t c, int32_t d, int32_t texWidth, int32_t texHeight){

	for(int32_t i = 0; i < 4; ++i){
		this->verticies[i].vec.x = 0;
		this->verticies[i].vec.y = 0;
		this->verticies[i].vec.z = 0;
	}
	float tw = (float) texWidth, th = (float) texHeight;

	this->flipnormal = 0;

	{
		VertexPT vec(*v1, (float)c / tw, ((float)b / th) + 0.0f);
		this->verticies[0] = vec;
	}

	float af = ((float)a / tw) + 0.0f;
	{
		VertexPT vec(*v2, af, ((float)b / th) + 0.0f);
		this->verticies[1] = vec;
	}

	float df = (float)d / th;
	{
		VertexPT vec(*v3, af, df);
		this->verticies[2] = vec;
	}
	{
		VertexPT vec(*v4, (float)c / tw, df);
		this->verticies[3] = vec;
	}
}


void PolygonQuad::flipNormal(void){
	this->flipnormal = 1;
}

void PolygonQuad::mirror(void){
	//XXX uses loops
	VertexPT v1 = this->verticies[0], v2 = this->verticies[1], v3 = this->verticies[2], v4 = this->verticies[3];
	this->verticies[3] = v1;
	this->verticies[2] = v2;
	this->verticies[1] = v3;
	this->verticies[0] = v4;
}

void PolygonQuad::render(Tesselator& a2, float a3, int32_t a4){
	float diffX01 = this->verticies[0].vec.x - this->verticies[1].vec.x;
	float diffY01 = this->verticies[0].vec.y - this->verticies[1].vec.y;
	float diffZ01 = this->verticies[0].vec.z - this->verticies[1].vec.z;
	float diffX03 = this->verticies[0].vec.x - this->verticies[3].vec.x;
	float diffY03 = this->verticies[0].vec.y - this->verticies[3].vec.y;
	float diffZ03 = this->verticies[0].vec.z - this->verticies[3].vec.z;
	//useless but libminecraftpe.so has this for some reason?
	if(diffX01 == 0) diffX01 = 0;
	if(diffY01 == 0) diffY01 = 0;
	if(diffZ01 == 0) diffZ01 = 0;
	if(diffX03 == 0) diffX03 = 0;
	if(diffY03 == 0) diffY03 = 0;
	if(diffZ03 == 0) diffZ03 = 0;

	float v15 = (diffY01*diffZ03) - (diffZ01*diffY03);
	float v16 = (diffZ01*diffX03) - (diffX01*diffZ03);
	float v18 = (diffX01*diffY03) - (diffY01*diffX03);
	if(v15 == 0) v15 = 0;
	if(v16 == 0) v16 = 0;
	if(v18 == 0) v18 = 0;

	float v19 = sqrt(v16*v16 + v15*v15 + v18*v18);
	float xCoord, yCoord, zCoord;
	if(v19 >= 0.0001){
		xCoord = v15/v19;
		yCoord = v16/v19;
		zCoord = v18/v19;
		if(xCoord == 0) xCoord = 0;
		if(yCoord == 0) yCoord = 0;
		if(zCoord == 0) zCoord = 0;
	}else{
		xCoord = Vec3::ZERO.x;
		yCoord = Vec3::ZERO.y;
		zCoord = Vec3::ZERO.z;
	}
	a2.normal(xCoord, yCoord, zCoord);
	for(int32_t v23 = 0; v23 != 4; ++v23){
		VertexPT* v = &this->verticies[v23];
		a2.vertexUV(a3*v->vec.x, a3*v->vec.y, a3*v->vec.z, v->u, v->v);
	}

}
