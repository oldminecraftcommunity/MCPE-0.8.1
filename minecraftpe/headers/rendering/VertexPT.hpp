#pragma once
#include <math/Vec3.hpp>
struct VertexPT{
	Vec3 vec;
	float u, v;

	VertexPT(){
	}
	VertexPT(const VertexPT &vv, float u, float v){
		this->vec = vv.vec;
		this->u = u;
		this->v = v;
	}
};
