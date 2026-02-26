#include <rendering/TextureTesselator.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/textures/TextureData.hpp>

TextureTesselator::TextureTesselator(TextureData* td, int32_t txmin, int32_t tymin, int32_t txmax, int32_t tymax, Vec3 f10, Color4 f1C, Color4 f2C)
	: field_1C(Color4::BLACK)
	, field_2C(Color4::WHITE) {
	this->texXMin = txmin;
	this->texYMin = tymin;
	this->texXMax = txmax;
	this->texYMax = tymax;
	this->textureData = td;
	this->field_10 = f10;
	this->field_1C = f1C;
	this->field_2C = f2C;
}
MeshBuffer TextureTesselator::tesselate() {
	bool v3;				  // r3
	float v4;				  // s17
	int texXMin;			  // r7
	float v6;				  // s16
	int width;				  // r10
	TextureData* textureData; // r2
	int v9;					  // r8
	int v10;				  // r11
	uint8_t* v11;			  // r10
	int texYMin;			  // r9
	int texYMax;			  // r3
	float v14;				  // s17
	float v15;				  // s16
	int v16;				  // r10
	const uint8_t* v17;		  // r2
	TextureData* v18;		  // r11
	int v19;				  // r3
	int v20;				  // r0
	uint8_t* v21;			  // r11
	int v22;				  // r7
	Vec3* v23;				  // r1
	int v24;				  // r8
	float v25;				  // s17
	int v26;				  // r7
	float v27;				  // s16
	int v28;				  // r2
	const uint8_t* v29;		  // r11
	TextureData* v30;		  // r10
	int v31;				  // r1
	int v32;				  // r3
	uint8_t* v33;			  // r10
	int v34;				  // r9
	Vec3* v35;				  // r2
	int texXMax;			  // [sp+18h] [bp-50h]
	int v39[17];			  // [sp+24h] [bp-44h] BYREF

	v3 = this->field_10.x != 0.0 || this->field_10.y != 0.0 || this->field_10.z != 0.0;
	this->field_40 = v3;
	v4 = 0.0;
	Tesselator::instance.begin(4, 0);
	v39[0] = 0;
	texXMin = this->texXMin;
	++this->texXMax;
	++this->texYMax;
	while(1) {
		texYMin = this->texYMin;
		if(texXMin >= this->texXMax) {
			break;
		}
		v6 = 0.0;
		while(1) {
			texYMax = this->texYMax;
			if(texYMin >= texYMax) {
				break;
			}
			width = this->textureData->width;
			textureData = this->textureData;
			v9 = (texXMin % width + width) % width;
			v10 = (texYMin % textureData->height + textureData->height) % textureData->height;
			v11 = (uint8_t*)&textureData->pixels[4 * v9 + 4 * width * v10];
			if(v11[3] > 9u && texXMin != texYMax) {
				this->_addLighting(Vec3::NEG_UNIT_Y, v11, v9, v10);
				Tesselator::instance.vertex(v4 + 1.0, 0.0, v6);
				Tesselator::instance.vertex(v4 + 1.0, 0.0, v6 + 1.0);
				Tesselator::instance.vertex(v4, 0.0, v6 + 1.0);
				Tesselator::instance.vertex(v4, 0.0, v6);
				Tesselator::instance.quad(0);
				this->_addLighting(Vec3::UNIT_Y, v11, v9, v10);
				Tesselator::instance.vertex(v4, 1.0, v6);
				Tesselator::instance.vertex(v4, 1.0, v6 + 1.0);
				Tesselator::instance.vertex(v4 + 1.0, 1.0, v6 + 1.0);
				Tesselator::instance.vertex(v4 + 1.0, 1.0, v6);
				Tesselator::instance.quad(0);
			}
			v6 = v6 + 1.0;
			++texYMin;
		}
		v4 = v4 + 1.0;
		++texXMin;
	}
	v14 = 0.0;
LABEL_24:
	v24 = this->texXMin;
	if(texYMin <= this->texYMax) {
		v15 = 0.0;
		v16 = 1;
		v17 = (const uint8_t*)v39;
		while(1) {
			texXMax = this->texXMax;
			if(v24 > texXMax) {
				v14 = v14 + 1.0;
				++texYMin;
				goto LABEL_24;
			}
			v18 = this->textureData;
			v19 = (v24 % v18->width + v18->width) % v18->width;
			v20 = (texYMin % v18->height + v18->height) % v18->height;
			v21 = (uint8_t*)&v18->pixels[4 * v19 + 4 * v18->width * v20];
			if(v21[3] > 9u) {
				break;
			}
			if(v16 != 1) {
				v22 = 1;
				goto LABEL_38;
			}
			v22 = 1;
LABEL_21:
			v15 = v15 + 1.0;
			++v24;
			v17 = v21;
			v16 = v22;
		}
		v22 = v24 == texXMax;
		if(v22 == v16) {
			goto LABEL_21;
		}
		if(v24 == texXMax) {
LABEL_38:
			v23 = &Vec3::UNIT_X;
		} else {
			v23 = &Vec3::NEG_UNIT_X;
			v17 = v21;
		}
		this->_addLighting(*v23, v17, v19, v20);
		Tesselator::instance.vertex(v15, 0.0, v14);
		Tesselator::instance.vertex(v15, 0.0, v14 + 1.0);
		Tesselator::instance.vertex(v15, 1.0, v14 + 1.0);
		Tesselator::instance.vertex(v15, 1.0, v14);
		Tesselator::instance.quad(v22);
		goto LABEL_21;
	}
	v25 = 0.0;
	while(v24 < this->texXMax) {
		v26 = this->texYMin;
		v27 = 0.0;
		v28 = 1;
		v29 = (const uint8_t*)v39;
		while(v26 < this->texYMax) {
			v30 = this->textureData;
			v31 = (v26 % v30->height + v30->height) % v30->height;
			v32 = (v24 % v30->width + v30->width) % v30->width;
			v33 = (uint8_t*)&v30->pixels[4 * v32 + 4 * v30->width * v31];
			v34 = v33[3] <= 9u;
			if(v34 != v28) {
				if(v33[3] <= 9u) {
					v35 = &Vec3::UNIT_Z;
				} else {
					v29 = v33;
					v35 = &Vec3::NEG_UNIT_Z;
				}
				this->_addLighting(*v35, v29, v32, v31);
				Tesselator::instance.vertex(v25, 1.0, v27);
				Tesselator::instance.vertex(v25 + 1.0, 1.0, v27);
				Tesselator::instance.vertex(v25 + 1.0, 0.0, v27);
				Tesselator::instance.vertex(v25, 0.0, v27);
				Tesselator::instance.quad(v34);
			}
			v27 = v27 + 1.0;
			++v26;
			v29 = v33;
			v28 = v34;
		}
		v25 = v25 + 1.0;
		++v24;
	}
	return Tesselator::instance.end();
}

void TextureTesselator::_addLighting(const Vec3& a2, const uint8_t* a3, int32_t a4, int32_t a5) {
	int v8;	   // r7
	float v9;  // s16
	float v10; // s13
	float v11; // s14
	float v12; // s15

	v8 = a5;
	if(this->field_40) {
		v9 = (float)((float)((float)((float)(this->field_10.y * a2.y) + (float)(this->field_10.x * a2.x)) + (float)(this->field_10.z * a2.z)) + 1.0) * 0.5;
		v10 = v9 + this->field_1C.r;
		v11 = v9 + this->field_1C.g;
		v12 = v9 + this->field_1C.b;
		if(v10 > 1.0) {
			v10 = 1.0;
		} else if(v10 <= 0.0) {
			v10 = 0.0;
		}
		if(v11 > 1.0) {
			v11 = 1.0;
		} else if(v11 <= 0.0) {
			v11 = 0.0;
		}
		if(v12 > 1.0) {
			v12 = 1.0;
		} else if(v12 <= 0.0) {
			v12 = 0.0;
		}
		Tesselator::instance.color((float)((float)((float)*a3 * v10) / 255.0) * this->field_2C.r, (float)((float)((float)a3[1] * v11) / 255.0) * this->field_2C.g, (float)((float)((float)a3[2] * v12) / 255.0) * this->field_2C.b, (float)((float)a3[3] / 255.0) * this->field_2C.a);
	} else {
		Tesselator::instance.normal(a2.x, a2.y, a2.z);
		if(a2.x <= 0.0) {
			if(a2.z > 0.0) {
				v8 = a5 - 1;
			}
		} else {
			--a4;
		}
		Tesselator::instance.tex((float)((float)a4 + 0.5) / (float)this->textureData->width, (float)((float)v8 + 0.5) / (float)this->textureData->height);
	}
}
