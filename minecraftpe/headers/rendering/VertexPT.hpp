#pragma once
#include <_types.h>
#include <math/Vec3.hpp>
struct VertexPT{
	Vec3 vec = Vec3::ZERO;
	float u, v;

	VertexPT();
	VertexPT(const VertexPT&, float, float);
};
