#include <rendering/VertexPT.hpp>

VertexPT::VertexPT(const VertexPT &vv, float u, float v){
	this->vec.x = 0;
	this->vec.y = 0;
	this->vec.z = 0;

	this->u = u;
	this->v = v;
	this->vec.x = vv.vec.x;
	this->vec.y = vv.vec.y;
	this->vec.z = vv.vec.z;
}

//XXX doesnt exist in mcpe?
VertexPT::VertexPT(){
	this->u = 0;
	this->v = 0;
}
