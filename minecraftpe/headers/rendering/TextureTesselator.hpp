#pragma once
#include <util/Color4.hpp>
#include <math/Vec3.hpp>
#include <rendering/MeshBuffer.hpp>

struct TextureData;
struct TextureTesselator
{
	int32_t texXMin, texYMin, texXMax, texYMax;
	Vec3 field_10;
	Color4 field_1C, field_2C;
	TextureData* textureData;
	int8_t field_40, field_41, field_42, field_43;

	TextureTesselator(TextureData* td, int32_t txmin, int32_t tymin, int32_t txmax, int32_t tymax, Vec3 f10, Color4 f1C, Color4 f2C);
	/*
	 * 	textes.texXMin = v11 - 32;
		textes.texYMin = v12 - 32;
		textes.texXMax = v11 + 32;
		textes.texYMax = v12 + 32;
		textes.field_10.x = textes.field_10.y = textes.field_10.z = 0;
		textes.field_1C = Color4::BLACK;
		textes.textureData = td;
		textes.field_2C = Color4::WHITE;
		textes.field_10 = Vec3(0, 0.70711, 0.70711);
		textes.field_1C.a = 1.0;
		textes.field_1C.r = 0.6;
		textes.field_1C.g = 0.6;
		textes.field_1C.b = 0.6;
		textes.field_2C = v30;
	 *
	 * */
	MeshBuffer tesselate();
	void _addLighting(const Vec3&, const uint8_t*, int32_t, int32_t);

};
