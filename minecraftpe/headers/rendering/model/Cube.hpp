#pragma once
#include <rendering/PolygonQuad.hpp>
#include <rendering/VertexPT.hpp>
#include <string>

struct Cube
{
	VertexPT field_0[8];
	PolygonQuad quads[6];
	std::string id;
	float field_29C, field_2A0, field_2A4;
	float field_2A8, field_2AC, field_2B0;

	Cube(struct ModelPart*, int32_t, int32_t, float, float, float, int32_t, int32_t, int32_t, float);
	void compile(struct Tesselator&, float);
	Cube* setId(const std::string&);
};
