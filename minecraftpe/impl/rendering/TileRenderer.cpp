#include <rendering/TileRenderer.hpp>
#include <level/Level.hpp>
#include <level/LevelSource.hpp>
#include <math/Direction.hpp>
#include <math/Mth.hpp>
#include <rendering/Tesselator.hpp>
#include <tile/BaseRailTile.hpp>
#include <tile/BedTile.hpp>
#include <tile/FenceGateTile.hpp>
#include <tile/FenceTile.hpp>
#include <tile/FireTile.hpp>
#include <tile/LiquidTile.hpp>
#include <tile/StairTile.hpp>
#include <tile/StemTile.hpp>
#include <tile/ThinFenceTile.hpp>
#include <tile/Tile.hpp>
#include <tile/WallTile.hpp>
#include <tile/material/Material.hpp>
#include <rendering/EntityTileRenderer.hpp>
#include <tile/entity/ChestTileEntity.hpp>

void TileRenderer::_randomizeFaceDirection(Tile* a2, int32_t face, float a4, float a5, float a6) {
	if(((a2->field_5C >> face) & 1) != 0) {
		if(this->randomizeFace[face] == 0) {
			int v7 = (int32_t)a5 ^ ((int32_t)a4 * 0x2FC20F) ^ ((int32_t)a6 * 0x6EBFFF5);
			this->randomizeFace[face] = ((uint32_t)(11 * v7 + 0x285B825 * v7 * v7) >> 24) & 3;
		}
	}
}
bool_t TileRenderer::canRender(int32_t a1) {
	return !a1 || a1 == 13 || a1 == 10 || a1 == 11 || a1 == 21 || a1 == 32 || a1 == 22 || a1 == 31;
}

TileRenderer::TileRenderer(struct LevelSource* a2) :
	field_0(0), levelSource(a2), hasUVCoords(0),
	field_8(),
	field_21(0), disableCulling(0), enableAO(0), randomizeFace{0}
{
}
float TileRenderer::getWaterHeight(int32_t x, int32_t y, int32_t z, const struct Material* mat) {

	float v5 = 0.0f;
	int v6 = 0;
	int v11 = 0;
	for(int i = 0; i < 4; ++i){
		int xx = x - (i & 1);
		int zz = z - (i >> 1);
		if(this->levelSource->getMaterial(xx, y+1, zz) != mat){
			Material* v12 = this->levelSource->getMaterial(xx, y, zz);
			if(v12 == mat){
				int32_t data = this->levelSource->getData(x - (i & 1), y, z - (i >> 1));
				if(data > 7 || data == 0) {
					v5 = v5 + 1.1111f;
					v11 += 10;
					if(data > 7) {
						data = 0;
					}
				}
				v5 = v5 + (data + 1) / 9.0f;
				v11 += 1;
			}else if(!v12->isSolid()){
				v5 += 1.0f;
				v11 += 1;
			}
		}else{
			return 1.0f;
		}
	}

	return 1.0f - (v5 / v11);
}
void TileRenderer::renderEast(Tile* a2, float a3, float a4, float a5, const struct TextureUVCoordinateSet& _a6) {
	float minX;	 // s16
	float maxX;	 // s18
	float v13;	 // s14
	float maxZ;	 // s11
	float minZ;	 // s10
	float maxY;	 // s12
	float v17;	 // s17
	float minY;	 // s19
	float v19;	 // s15
	float v20;	 // s14
	float v21;	 // s13
	float v22;	 // s9
	float v23;	 // s15
	int32_t v24; // r3
	float v25;	 // s14
	float v26;	 // s20
	float v27;	 // s15
	float v28;	 // s20
	float v29;	 // s22
	float v30;	 // s23
	float v31;	 // s21
	float v32;	 // s21
	float v33;	 // s17
	float v34;	 // s15
	float v35;	 // s14
	float v36;	 // s18
	float v37;	 // s15
	float v38;	 // s17
	float v39;	 // s15
	float v40;	 // r6
	float v41;	 // s27
	float v42;	 // s26
	float v43;	 // s25
	float v44;	 // s24
	TextureUVCoordinateSet* a6 = (TextureUVCoordinateSet*)&_a6;
	if(this->hasUVCoords) {
		a6 = &this->field_8;
	}
	minX = a6->minX;
	maxX = a6->maxX;
	v13 = maxX - a6->minX;
	maxZ = a2->maxZ;
	minZ = a2->minZ;
	maxY = a2->maxY;
	v17 = a6->maxY;
	minY = a6->minY;
	v19 = a6->minX + (float)(minZ * v13);
	v20 = a6->minX + (float)(maxZ * v13);
	v21 = a2->minY;
	if(this->field_21) {
		v22 = v19;
		v19 = v20;
		v20 = v22;
	}
	if(minZ >= 0.0f && maxZ <= 1.0f) {
		maxX = v20;
		minX = v19;
	}
	if(v21 >= 0.0f && maxY <= 1.0f) {
		v23 = v17 - minY;
		v17 = v17 - (float)(v21 * (float)(v17 - minY));
		minY = a6->maxY - (float)(maxY * v23);
	}
	this->_randomizeFaceDirection(a2, 5, a3, a4, a5);
	v24 = this->randomizeFace[5];
	if(v24 == 2) {
		v25 = a6->maxX - a6->minX;
		v26 = a6->maxY;
		minX = a6->minX + (float)(v25 * a2->minY);
		v27 = v26 - a6->minY;
		maxX = a6->minX + (float)(v25 * a2->maxY);
		v28 = v26 - (float)(v27 * a2->minZ);
		v29 = a6->maxY - (float)(v27 * a2->maxZ);
		v30 = maxX;
		v31 = minX;
		v17 = v28;
		minY = v29;
	} else if(v24 == 1) {
		v32 = a6->maxX;
		v33 = a6->minY;
		v34 = v32 - a6->minX;
		v35 = a6->maxY - v33;
		minY = v33 + (float)(v35 * a2->maxZ);
		v17 = v33 + (float)(v35 * a2->minZ);
		v30 = v32 - (float)(v34 * a2->maxY);
		v31 = v32 - (float)(v34 * a2->minY);
		v29 = a6->minY + (float)(v35 * a2->maxZ);
		v28 = v17;
		maxX = a6->maxX - (float)(v34 * a2->maxY);
		minX = v31;
	} else {
		if(v24 == 3) {
			v36 = a6->maxX;
			v37 = v36 - a6->minX;
			v38 = a6->minY;
			minX = v36 - (float)(v37 * a2->minZ);
			maxX = v36 - (float)(v37 * a2->maxZ);
			v39 = a6->maxY - v38;
			minY = v38 + (float)(v39 * a2->maxY);
			v17 = v38 + (float)(v39 * a2->minY);
		}
		v29 = v17;
		v28 = minY;
		v30 = minX;
		v31 = maxX;
	}
	v40 = a3 + a2->maxX;
	v41 = a4 + a2->minY;
	v42 = a5 + a2->minZ;
	v43 = a4 + a2->maxY;
	v44 = a5 + a2->maxZ;
	if(this->field_0) {
		Tesselator::instance.normal(Vec3::UNIT_X);
	}
	if (this->enableAO){
		Tesselator::instance.color(this->redXeYs, this->greenXeYs, this->blueXeYs);
		Tesselator::instance.vertexUV(v40, v41, v44, v30, v29);
		Tesselator::instance.color(this->redXsYs, this->greenXsYs, this->blueXsYs);
		Tesselator::instance.vertexUV(v40, v41, v42, maxX, v17);
		Tesselator::instance.color(this->redXsYe, this->greenXsYe, this->blueXsYe);
		Tesselator::instance.vertexUV(v40, v43, v42, v31, v28);
		Tesselator::instance.color(this->redXeYe, this->greenXeYe, this->blueXeYe);
	}else{
		Tesselator::instance.vertexUV(v40, v41, v44, v30, v29);
		Tesselator::instance.vertexUV(v40, v41, v42, maxX, v17);
		Tesselator::instance.vertexUV(v40, v43, v42, v31, v28);
	}
	Tesselator::instance.vertexUV(v40, v43, v44, minX, minY);
}
void TileRenderer::renderFaceDown(Tile* a2, float a3, float a4, float a5, const struct TextureUVCoordinateSet& _a6) {
	float minX;	 // s12
	float v12;	 // s17
	float maxX;	 // s19
	float v14;	 // s11
	float minZ;	 // s14
	float minY;	 // s16
	float maxY;	 // s18
	float maxZ;	 // s13
	float v19;	 // s15
	float v20;	 // s15
	int32_t v21; // r3
	float v22;	 // s14
	float v23;	 // s20
	float v24;	 // s15
	float v25;	 // s20
	float v26;	 // s22
	float v27;	 // s23
	float v28;	 // s21
	float v29;	 // s21
	float v30;	 // s18
	float v31;	 // s15
	float v32;	 // s14
	float v33;	 // s19
	float v34;	 // s15
	float v35;	 // s18
	float v36;	 // s15
	float v37;	 // s27
	float v38;	 // s25
	float v39;	 // r6
	float v40;	 // s26
	float v41;	 // s24
	TextureUVCoordinateSet* a6 = (TextureUVCoordinateSet*)&_a6;
	if(this->hasUVCoords) {
		a6 = &this->field_8;
	}
	minX = a2->minX;
	v12 = a6->minX;
	maxX = a6->maxX;
	v14 = a2->maxX;
	minZ = a2->minZ;
	minY = a6->minY;
	maxY = a6->maxY;
	maxZ = a2->maxZ;
	if(minX >= 0.0f && v14 <= 1.0f) {
		v19 = maxX - v12;
		v12 = v12 + (float)(minX * (float)(maxX - v12));
		maxX = a6->minX + (float)(v14 * v19);
	}
	if(minZ >= 0.0f && maxZ <= 1.0f) {
		v20 = maxY - minY;
		minY = minY + (float)(minZ * (float)(maxY - minY));
		maxY = a6->minY + (float)(maxZ * v20);
	}
	this->_randomizeFaceDirection(a2, 0, a3, a4, a5);
	v21 = this->randomizeFace[0];
	if(v21 == 2) {
		v22 = a6->maxX - a6->minX;
		v23 = a6->maxY;
		v12 = a6->minX + (float)(v22 * a2->minZ);
		v24 = v23 - a6->minY;
		maxX = a6->minX + (float)(v22 * a2->maxZ);
		v25 = v23 - (float)(v24 * a2->maxX);
		v26 = a6->maxY - (float)(v24 * a2->minX);
		v27 = maxX;
		v28 = v12;
		maxY = v25;
		minY = v26;
	} else if(v21 == 1) {
		v29 = a6->maxX;
		v30 = a6->minY;
		v31 = v29 - a6->minX;
		v32 = a6->maxY - v30;
		minY = v30 + (float)(v32 * a2->minX);
		maxY = v30 + (float)(v32 * a2->maxX);
		v27 = v29 - (float)(v31 * a2->maxZ);
		v28 = v29 - (float)(v31 * a2->minZ);
		v26 = a6->minY + (float)(v32 * a2->minX);
		v25 = maxY;
		maxX = a6->maxX - (float)(v31 * a2->maxZ);
		v12 = v28;
	} else {
		if(v21 == 3) {
			v33 = a6->maxX;
			v34 = v33 - a6->minX;
			v35 = a6->maxY;
			v12 = v33 - (float)(v34 * a2->minX);
			maxX = v33 - (float)(v34 * a2->maxX);
			v36 = v35 - a6->minY;
			minY = v35 - (float)(v36 * a2->minZ);
			maxY = v35 - (float)(v36 * a2->maxZ);
		}
		v26 = maxY;
		v25 = minY;
		v27 = v12;
		v28 = maxX;
	}
	v37 = a3 + a2->minX;
	v38 = a3 + a2->maxX;
	v39 = a4 + a2->minY;
	v40 = a5 + a2->minZ;
	v41 = a5 + a2->maxZ;
	if(this->field_0) {
		Tesselator::instance.normal(Vec3::NEG_UNIT_Y);
	}
	if(this->enableAO) {
		//rgby
		Tesselator::instance.color(this->redXeYs, this->greenXeYs, this->blueXeYs);
		Tesselator::instance.vertexUV(v37, v39, v41, v27, v26);
		Tesselator::instance.color(this->redXsYs, this->greenXsYs, this->blueXsYs);
		Tesselator::instance.vertexUV(v37, v39, v40, v12, minY);
		Tesselator::instance.color(this->redXsYe, this->greenXsYe, this->blueXsYe);
		Tesselator::instance.vertexUV(v38, v39, v40, v28, v25);
		Tesselator::instance.color(this->redXeYe, this->greenXeYe, this->blueXeYe);
	} else {
		Tesselator::instance.vertexUV(v37, v39, v41, v27, v26);
		Tesselator::instance.vertexUV(v37, v39, v40, v12, minY);
		Tesselator::instance.vertexUV(v38, v39, v40, v28, v25);
	}
	Tesselator::instance.vertexUV(v38, v39, v41, maxX, maxY);
}
void TileRenderer::renderFaceUp(Tile* a2, float a3, float a4, float a5, const struct TextureUVCoordinateSet& _a6) {
	float minX;	 // s12
	float v12;	 // s17
	float maxX;	 // s19
	float v14;	 // s11
	float minZ;	 // s14
	float minY;	 // s16
	float maxY;	 // s18
	float maxZ;	 // s13
	float v19;	 // s15
	float v20;	 // s15
	int32_t v21; // r3
	float v22;	 // s14
	float v23;	 // s22
	float v24;	 // s15
	float v25;	 // s22
	float v26;	 // s20
	float v27;	 // s21
	float v28;	 // s23
	float v29;	 // s23
	float v30;	 // s18
	float v31;	 // s15
	float v32;	 // s14
	float v33;	 // s19
	float v34;	 // s15
	float v35;	 // s18
	float v36;	 // s15
	float v37;	 // s25
	float v38;	 // r6
	float v39;	 // s27
	float v40;	 // s26
	float v41;	 // s24
	TextureUVCoordinateSet* a6 = (TextureUVCoordinateSet*)&_a6;
	if(this->hasUVCoords) {
		a6 = &this->field_8;
	}
	minX = a2->minX;
	v12 = a6->minX;
	maxX = a6->maxX;
	v14 = a2->maxX;
	minZ = a2->minZ;
	minY = a6->minY;
	maxY = a6->maxY;
	maxZ = a2->maxZ;
	if(minX >= 0.0f && v14 <= 1.0f) {
		v19 = maxX - v12;
		v12 = v12 + (float)(minX * (float)(maxX - v12));
		maxX = a6->minX + (float)(v14 * v19);
	}
	if(minZ >= 0.0f && maxZ <= 1.0f) {
		v20 = maxY - minY;
		minY = minY + (float)(minZ * (float)(maxY - minY));
		maxY = a6->minY + (float)(maxZ * v20);
	}
	this->_randomizeFaceDirection(a2, 1, a3, a4, a5);
	v21 = this->randomizeFace[1];
	if(v21 == 1) {
		v22 = a6->maxX - a6->minX;
		v23 = a6->maxY;
		v12 = a6->minX + (float)(v22 * a2->minZ);
		v24 = v23 - a6->minY;
		maxX = a6->minX + (float)(v22 * a2->maxZ);
		v25 = v23 - (float)(v24 * a2->maxX);
		v26 = a6->maxY - (float)(v24 * a2->minX);
		v27 = maxX;
		v28 = v12;
		maxY = v25;
		minY = v26;
	} else if(v21 == 2) {
		v29 = a6->maxX;
		v30 = a6->minY;
		v31 = v29 - a6->minX;
		v32 = a6->maxY - v30;
		minY = v30 + (float)(v32 * a2->minX);
		maxY = v30 + (float)(v32 * a2->maxX);
		v27 = v29 - (float)(v31 * a2->maxZ);
		v28 = v29 - (float)(v31 * a2->minZ);
		v26 = a6->minY + (float)(v32 * a2->minX);
		v25 = maxY;
		maxX = a6->maxX - (float)(v31 * a2->maxZ);
		v12 = v28;
	} else {
		if(v21 == 3) {
			v33 = a6->maxX;
			v34 = v33 - a6->minX;
			v35 = a6->maxY;
			v12 = v33 - (float)(v34 * a2->minX);
			maxX = v33 - (float)(v34 * a2->maxX);
			v36 = v35 - a6->minY;
			minY = v35 - (float)(v36 * a2->minZ);
			maxY = v35 - (float)(v36 * a2->maxZ);
		}
		v26 = maxY;
		v25 = minY;
		v27 = v12;
		v28 = maxX;
	}
	v37 = a3 + a2->minX;
	v38 = a4 + a2->maxY;
	v39 = a3 + a2->maxX;
	v40 = a5 + a2->minZ;
	v41 = a5 + a2->maxZ;
	if(this->field_0) {
		Tesselator::instance.normal(Vec3::UNIT_Y);
	}

	if(this->enableAO) {
		Tesselator::instance.color(this->redXeYs, this->greenXeYs, this->blueXeYs);
		Tesselator::instance.vertexUV(v39, v38, v41, maxX, maxY);
		Tesselator::instance.color(this->redXsYs, this->greenXsYs, this->blueXsYs);
		Tesselator::instance.vertexUV(v39, v38, v40, v28, v25);
		Tesselator::instance.color(this->redXsYe, this->greenXsYe, this->blueXsYe);
		Tesselator::instance.vertexUV(v37, v38, v40, v12, minY);
		Tesselator::instance.color(this->redXeYe, this->greenXeYe, this->blueXeYe);
	} else {
		Tesselator::instance.vertexUV(v39, v38, v41, maxX, maxY);
		Tesselator::instance.vertexUV(v39, v38, v40, v28, v25);
		Tesselator::instance.vertexUV(v37, v38, v40, v12, minY);
	}
	Tesselator::instance.vertexUV(v37, v38, v41, v27, v26);
}

void TileRenderer::renderGuiTile(Tile* tile, int32_t a3, float a4, float a5) {
	int32_t v5;						   // r8
	int8_t v6;						   // r9
	int32_t v11;					   // r0
	int32_t v12;					   // r10
	const TextureUVCoordinateSet* v13; // r0
	const TextureUVCoordinateSet* v14; // r0
	int32_t v15;					   // r1
	const TextureUVCoordinateSet* v16; // r0
	const TextureUVCoordinateSet* v17; // r0
	const TextureUVCoordinateSet* v18; // r0
	const TextureUVCoordinateSet* v19; // r0
	const TextureUVCoordinateSet* v20; // r0
	const TextureUVCoordinateSet* v22; // r0
	const TextureUVCoordinateSet* v23; // r0
	const TextureUVCoordinateSet* v24; // r0
	const TextureUVCoordinateSet* v25; // r0
	const TextureUVCoordinateSet* v26; // r0
	const TextureUVCoordinateSet* v27; // r0
	const TextureUVCoordinateSet* v28; // r0
	const TextureUVCoordinateSet* v29; // r0
	const TextureUVCoordinateSet* v30; // r0
	const TextureUVCoordinateSet* v31; // r0
	const TextureUVCoordinateSet* v33; // r0
	const TextureUVCoordinateSet* v34; // r0
	const TextureUVCoordinateSet* v35; // r0
	const TextureUVCoordinateSet* v36; // r0
	const TextureUVCoordinateSet* v37; // r0
	float v38;						   // s15
	Tile* v39;						   // r0
	float v40;						   // s14
	float v42;						   // r1
	const TextureUVCoordinateSet* v43; // r0
	const TextureUVCoordinateSet* v44; // r0
	const TextureUVCoordinateSet* v45; // r0
	const TextureUVCoordinateSet* v46; // r0
	const TextureUVCoordinateSet* v47; // r0
	float v48;						   // [sp+0h] [bp-68h]
	TextureUVCoordinateSet v49;		   // [sp+4h] [bp-64h]
	TextureUVCoordinateSet v50;		   // [sp+4h] [bp-64h]
	TextureUVCoordinateSet v51;		   // [sp+4h] [bp-64h]
	TextureUVCoordinateSet v52;		   // [sp+4h] [bp-64h]
	TextureUVCoordinateSet v53;		   // [sp+4h] [bp-64h]
	float v54;						   // [sp+4h] [bp-64h]
	TextureUVCoordinateSet v55;		   // [sp+4h] [bp-64h]
	float v56;						   // [sp+8h] [bp-60h]

	v5 = 0;
	v6 = this->field_0;
	this->field_0 = 0;
	v11 = tile->getRenderShape();
	v12 = v11;
	if(!v11 || v11 == 31 || tile == (Tile*)Tile::chest) {
		tile->updateDefaultShape();
		Tesselator::instance.begin(7, 24);
		Tesselator::instance.color(a4, a4, a4, a5);
		v13 = tile->getCarriedTexture(1, a3);
		TileRenderer::renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v13);
		Tesselator::instance.color(a4 * 0.5f, a4 * 0.5f, a4 * 0.5f, a5);
		v49 = *tile->getCarriedTexture(3, a3);
		TileRenderer::renderSouth(tile, 0.0f, 0.0f, 0.0f, v49);
		Tesselator::instance.color(a4 * 0.73f, a4 * 0.73f, a4 * 0.73f, a5);
		v14 = tile->getCarriedTexture(4, a3);
		TileRenderer::renderWest(tile, 0.0f, 0.0f, 0.0f, *v14);
LABEL_10:
		v15 = 1;
		goto LABEL_7;
	}
	switch(v11) {
		case 1:
			Tesselator::instance.begin(8);
			Tesselator::instance.color(a4, a4, a4, a5);
			this->tesselateCrossTexture(tile, a3, -0.5f, -0.5f, -0.5f);
			v15 = v12;
LABEL_7:
			Tesselator::instance.draw(v15);
			break;
		case 13:
			tile->updateDefaultShape();
			Tesselator::instance.begin(24);
			Tesselator::instance.color(a4, a4, a4, a5);
			v16 = tile->getTexture(0);
			this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v16);
			v17 = tile->getTexture(1);
			this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v17);
			Tesselator::instance.color(a4 * 0.5f, a4 * 0.5f, a4 * 0.5f, a5);
			v18 = tile->getTexture(2);
			this->renderNorth(tile, 0.0f, 0.0f, 0.0625f, *v18);
			v50 = *tile->getTexture(3);
			this->renderSouth(tile, 0.0f, 0.0f, -0.0625f, v50);
			Tesselator::instance.color(a4 * 0.73f, a4 * 0.73f, a4 * 0.73f, a5);
			v19 = tile->getTexture(4);
			this->renderWest(tile, 0.0625f, 0.0f, 0.0f, *v19);
			v20 = tile->getTexture(5);
			this->renderEast(tile, -0.0625f, 0.0f, 0.0f, *v20);
			goto LABEL_10;
		case 10:
			Tesselator::instance.begin(48);
			do {
				if(v5) {
					tile->setShape(0.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f);
				} else {
					tile->setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f);
				}
				Tesselator::instance.color(a4, a4, a4, a5);
				++v5;
				v22 = tile->getTexture(0);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v22);
				v23 = tile->getTexture(1);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v23);
				Tesselator::instance.color(a4 * 0.5f, a4 * 0.5f, a4 * 0.5f, a5);
				v24 = tile->getTexture(2);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v24);
				v51 = *tile->getTexture(3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v51);
				Tesselator::instance.color(a4 * 0.73f, a4 * 0.73f, a4 * 0.73f, a5);
				v25 = tile->getTexture(4);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v25);
				v26 = tile->getTexture(5);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v26);
			} while(v5 != 2);
			goto LABEL_10;
		case 11:
			Tesselator::instance.begin(96);
			do {
				if(v5) {
					switch(v5) {
						case 1:
							tile->setShape(0.375f, 0.0f, 0.75f, 0.625f, 1.0f, 1.0f);
							break;
						case 2:
							tile->setShape(0.4375f, 0.8125f, -0.125f, 0.5625f, 0.9375f, 1.125f);
							break;
						case 3:
							tile->setShape(0.4375f, 0.3125f, -0.125f, 0.5625f, 0.4375f, 1.125f);
							break;
					}
				} else {
					tile->setShape(0.375f, 0.0f, 0.0f, 0.625f, 1.0f, 0.25f);
				}
				Tesselator::instance.color(a4, a4, a4, a5);
				++v5;
				v27 = tile->getTexture(0);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v27);
				v28 = tile->getTexture(1);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v28);
				Tesselator::instance.color(a4 * 0.5f, a4 * 0.5f, a4 * 0.5f, a5);
				v29 = tile->getTexture(2);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v29);
				v52 = *tile->getTexture(3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v52);
				Tesselator::instance.color(a4 * 0.73f, a4 * 0.73f, a4 * 0.73f, a5);
				v30 = tile->getTexture(4);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v30);
				v31 = tile->getTexture(5);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v31);
			} while(v5 != 4);
LABEL_28:
			Tesselator::instance.draw(1);
			tile->setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 21:
			Tesselator::instance.begin(72);
			do {
				if(v5) {
					if(v5 == 1) {
						tile->setShape(0.4375f, 0.3f, 0.875f, 0.5625f, 1.0f, 1.0f);
					} else {
						tile->setShape(0.4375f, 0.5f, 0.0f, 0.5625f, 0.9375f, 1.0f);
					}
				} else {
					tile->setShape(0.4375f, 0.3f, 0.0f, 0.5625f, 1.0f, 0.125f);
				}
				Tesselator::instance.color(a4, a4, a4, a5);
				++v5;
				v33 = tile->getTexture(0);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v33);
				v34 = tile->getTexture(1);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v34);
				Tesselator::instance.color(a4 * 0.5f, a4 * 0.5f, a4 * 0.5f, a5);
				v35 = tile->getTexture(2);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v35);
				v53 = *tile->getTexture(3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v53);
				Tesselator::instance.color(a4 * 0.73f, a4 * 0.73f, a4 * 0.73f, a5);
				v36 = tile->getTexture(4);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v36);
				v37 = tile->getTexture(5);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v37);
			} while(v5 != 3);
			goto LABEL_28;
		case 32:
			Tesselator::instance.begin(96);
			while(v5) {
				if(v5 != 1) {
					if(v5 == 2) {
						v39 = tile;
						v40 = 0.25f + 0.0f;
						v38 = 0.1875f;
						v48 = 0.5f;
						v54 = 0.8125f;
						v56 = 0.1875f + 0.5f;
					} else {
						v38 = 0.25f;
						v39 = tile;
						v48 = 0.25f + 0.0f;
						v54 = 1.0f;
						v56 = 0.25f + 0.5f;
						v40 = 0.0f - 0.25f;
					}
					goto LABEL_48;
				}
				v39 = tile;
				v42 = 0.5f;
				v38 = 0.1875f;
				v48 = 1.0f - 0.25f;
				v54 = 0.8125f;
				v56 = 0.1875f + 0.5f;
LABEL_49:
				++v5;
				v39->setShape(v42, 0.0f, 0.5f - v38, v48, v54, v56);
				Tesselator::instance.color(a4, a4, a4, a5);
				v43 = tile->getTexture(0, a3);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v43);
				v44 = tile->getTexture(1, a3);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v44);
				Tesselator::instance.color(a4 * 0.5f, a4 * 0.5f, a4 * 0.5f, a5);
				v45 = tile->getTexture(2, a3);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v45);
				v55 = *tile->getTexture(3, a3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v55);
				Tesselator::instance.color(a4 * 0.73f, a4 * 0.73f, a4 * 0.73f, a5);
				v46 = tile->getTexture(4, a3);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v46);
				v47 = tile->getTexture(5, a3);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v47);
				if(v5 == 4) {
					goto LABEL_28;
				}
			}
			v38 = 0.25f;
			v39 = tile;
			v48 = 0.25f + 1.0f;
			v54 = 1.0f;
			v56 = 0.25f + 0.5f;
			v40 = 1.0f - 0.25f;
LABEL_48:
			v42 = v40;
			goto LABEL_49;
		case 22:
			EntityTileRenderer::instance->render(tile, a3, 1.0f);
			break;
	}
	this->field_0 = v6;
}
void TileRenderer::renderNorth(Tile* a2, float a3, float a4, float a5, const struct TextureUVCoordinateSet& _a6) {
	float minX;	 // s16
	float maxX;	 // s18
	float v13;	 // s14
	float v14;	 // s11
	float v15;	 // s10
	float maxY;	 // s12
	float v17;	 // s17
	float minY;	 // s19
	float v19;	 // s15
	float v20;	 // s14
	float v21;	 // s13
	float v22;	 // s9
	float v23;	 // s15
	int32_t v24; // r3
	float v25;	 // s14
	float v26;	 // s22
	float v27;	 // s15
	float v28;	 // s22
	float v29;	 // s20
	float v30;	 // s21
	float v31;	 // s23
	float v32;	 // s23
	float v33;	 // s17
	float v34;	 // s15
	float v35;	 // s14
	float v36;	 // s18
	float v37;	 // s15
	float v38;	 // s17
	float v39;	 // s15
	float v40;	 // s25
	float v41;	 // s26
	float v42;	 // s24
	float v43;	 // s27
	float v44;	 // s15
	TextureUVCoordinateSet* a6 = (TextureUVCoordinateSet*)&_a6;
	if(this->hasUVCoords) {
		a6 = &this->field_8;
	}
	minX = a6->minX;
	maxX = a6->maxX;
	v13 = maxX - a6->minX;
	v14 = a2->maxX;
	v15 = a2->minX;
	maxY = a2->maxY;
	v17 = a6->maxY;
	minY = a6->minY;
	v19 = a6->minX + (float)(v15 * v13);
	v20 = a6->minX + (float)(v14 * v13);
	v21 = a2->minY;
	if(this->field_21) {
		v22 = v19;
		v19 = v20;
		v20 = v22;
	}
	if(v15 >= 0.0f && v14 <= 1.0f) {
		maxX = v20;
		minX = v19;
	}
	if(v21 >= 0.0f && maxY <= 1.0f) {
		v23 = v17 - minY;
		v17 = v17 - (float)(v21 * (float)(v17 - minY));
		minY = a6->maxY - (float)(maxY * v23);
	}
	this->_randomizeFaceDirection(a2, 2, a3, a4, a5);
	v24 = this->randomizeFace[2];
	if(v24 == 2) {
		v25 = a6->maxX - a6->minX;
		v26 = a6->maxY;
		minX = a6->minX + (float)(v25 * a2->minY);
		v27 = v26 - a6->minY;
		maxX = a6->minX + (float)(v25 * a2->maxY);
		v28 = v26 - (float)(v27 * a2->minX);
		v29 = a6->maxY - (float)(v27 * a2->maxX);
		v30 = maxX;
		v31 = minX;
		v17 = v28;
		minY = v29;
	} else if(v24 == 1) {
		v32 = a6->maxX;
		v33 = a6->minY;
		v34 = v32 - a6->minX;
		v35 = a6->maxY - v33;
		minY = v33 + (float)(v35 * a2->maxX);
		v17 = v33 + (float)(v35 * a2->minX);
		v30 = v32 - (float)(v34 * a2->maxY);
		v31 = v32 - (float)(v34 * a2->minY);
		v29 = a6->minY + (float)(v35 * a2->maxX);
		v28 = v17;
		maxX = a6->maxX - (float)(v34 * a2->maxY);
		minX = v31;
	} else {
		if(v24 == 3) {
			v36 = a6->maxX;
			v37 = v36 - a6->minX;
			v38 = a6->minY;
			minX = v36 - (float)(v37 * a2->minX);
			maxX = v36 - (float)(v37 * a2->maxX);
			v39 = a6->maxY - v38;
			minY = v38 + (float)(v39 * a2->maxY);
			v17 = v38 + (float)(v39 * a2->minY);
		}
		v29 = v17;
		v28 = minY;
		v30 = minX;
		v31 = maxX;
	}
	v40 = a3 + a2->minX;
	v41 = a3 + a2->maxX;
	v42 = a4 + a2->minY;
	v43 = a4 + a2->maxY;
	v44 = a5 + a2->minZ;
	if(this->field_0) {
		Tesselator::instance.normal(Vec3::NEG_UNIT_Z);
	}
	if(this->enableAO) {
		Tesselator::instance.color(this->redXeYs, this->greenXeYs, this->blueXeYs);
		Tesselator::instance.vertexUV(v40, v43, v44, v31, v28);
		Tesselator::instance.color(this->redXsYs, this->greenXsYs, this->blueXsYs);
		Tesselator::instance.vertexUV(v41, v43, v44, minX, minY);
		Tesselator::instance.color(this->redXsYe, this->greenXsYe, this->blueXsYe);
		Tesselator::instance.vertexUV(v41, v42, v44, v30, v29);
		Tesselator::instance.color(this->redXeYe, this->greenXeYe, this->blueXeYe);
		Tesselator::instance.vertexUV(v40, v42, v44, maxX, v17);
	} else {
		Tesselator::instance.vertexUV(v40, v43, v44, v31, v28);
		Tesselator::instance.vertexUV(v41, v43, v44, minX, minY);
		Tesselator::instance.vertexUV(v41, v42, v44, v30, v29);
		Tesselator::instance.vertexUV(v40, v42, v44, maxX, v17);
	}
}
void TileRenderer::renderSouth(Tile* a2, float a3, float a4, float a5, const TextureUVCoordinateSet a6) { //mojang moment
	TextureUVCoordinateSet* v10;																		  // r6
	float minX;																							  // s16
	float maxX;																							  // s18
	float v13;																							  // s14
	float v14;																							  // s11
	float v15;																							  // s10
	float maxY;																							  // s12
	float v17;																							  // s17
	float minY;																							  // s19
	float v19;																							  // s15
	float v20;																							  // s14
	float v21;																							  // s13
	float v22;																							  // s9
	float v23;																							  // s15
	int32_t v24;																						  // r3
	float v25;																							  // s14
	float v26;																							  // s20
	float v27;																							  // s15
	float v28;																							  // s22
	float v29;																							  // s20
	float v30;																							  // s23
	float v31;																							  // s21
	float v32;																							  // s21
	float v33;																							  // s17
	float v34;																							  // s15
	float v35;																							  // s14
	float v36;																							  // s18
	float v37;																							  // s15
	float v38;																							  // s17
	float v39;																							  // s15
	float v40;																							  // s27
	float v41;																							  // s25
	float v42;																							  // s26
	float v43;																							  // s24
	float v44;																							  // s15

	if(this->hasUVCoords) {
		v10 = &this->field_8;
	} else {
		v10 = (TextureUVCoordinateSet*)&a6;
	}
	minX = v10->minX;
	maxX = v10->maxX;
	v13 = maxX - v10->minX;
	v14 = a2->maxX;
	v15 = a2->minX;
	maxY = a2->maxY;
	v17 = v10->maxY;
	minY = v10->minY;
	v19 = v10->minX + (float)(v15 * v13);
	v20 = v10->minX + (float)(v14 * v13);
	v21 = a2->minY;
	if(this->field_21) {
		v22 = v19;
		v19 = v20;
		v20 = v22;
	}
	if(v15 >= 0.0f && v14 <= 1.0f) {
		maxX = v20;
		minX = v19;
	}
	if(v21 >= 0.0f && maxY <= 1.0f) {
		v23 = v17 - minY;
		v17 = v17 - (float)(v21 * (float)(v17 - minY));
		minY = v10->maxY - (float)(maxY * v23);
	}
	this->_randomizeFaceDirection(a2, 3, a3, a4, a5);
	v24 = this->randomizeFace[3];
	if(v24 == 1) {
		v25 = v10->maxX - v10->minX;
		v26 = v10->maxY;
		minX = v10->minX + (float)(v25 * a2->minY);
		v27 = v26 - v10->minY;
		maxX = v10->minX + (float)(v25 * a2->maxY);
		v28 = v26 - (float)(v27 * a2->minX);
		v29 = v26 - (float)(v27 * a2->maxX);
		v30 = maxX;
		v31 = minX;
		v17 = v29;
		minY = v10->maxY - (float)(v27 * a2->minX);
	} else if(v24 == 2) {
		v32 = v10->maxX;
		v33 = v10->minY;
		v34 = v32 - v10->minX;
		v35 = v10->maxY - v33;
		minY = v33 + (float)(v35 * a2->minX);
		v17 = v33 + (float)(v35 * a2->maxX);
		v30 = v32 - (float)(v34 * a2->maxY);
		v31 = v32 - (float)(v34 * a2->minY);
		v28 = v10->minY + (float)(v35 * a2->minX);
		v29 = v17;
		maxX = v10->maxX - (float)(v34 * a2->maxY);
		minX = v31;
	} else {
		if(v24 == 3) {
			v36 = v10->maxX;
			v37 = v36 - v10->minX;
			v38 = v10->minY;
			minX = v36 - (float)(v37 * a2->minX);
			maxX = v36 - (float)(v37 * a2->maxX);
			v39 = v10->maxY - v38;
			minY = v38 + (float)(v39 * a2->maxY);
			v17 = v38 + (float)(v39 * a2->minY);
		}
		v28 = v17;
		v29 = minY;
		v30 = minX;
		v31 = maxX;
	}
	v40 = a3 + a2->minX;
	v41 = a3 + a2->maxX;
	v42 = a4 + a2->minY;
	v43 = a4 + a2->maxY;
	v44 = a5 + a2->maxZ;
	if(this->field_0) {
		Tesselator::instance.normal(Vec3::UNIT_Z);
	}
	if(this->enableAO) {
		Tesselator::instance.color(this->redXeYs, this->greenXeYs, this->blueXeYs);
		Tesselator::instance.vertexUV(v40, v43, v44, minX, minY);
		Tesselator::instance.color(this->redXsYs, this->greenXsYs, this->blueXsYs);
		Tesselator::instance.vertexUV(v40, v42, v44, v30, v28);
		Tesselator::instance.color(this->redXsYe, this->greenXsYe, this->blueXsYe);
		Tesselator::instance.vertexUV(v41, v42, v44, maxX, v17);
		Tesselator::instance.color(this->redXeYe, this->greenXeYe, this->blueXeYe);
	} else {
		Tesselator::instance.vertexUV(v40, v43, v44, minX, minY);
		Tesselator::instance.vertexUV(v40, v42, v44, v30, v28);
		Tesselator::instance.vertexUV(v41, v42, v44, maxX, v17);
	}
	Tesselator::instance.vertexUV(v41, v43, v44, v31, v29);
}

void TileRenderer::renderTile(Tile* tile, int32_t a3, bool_t a4) {
	int32_t v7;						   // r0
	const TextureUVCoordinateSet* v8;  // r0
	const TextureUVCoordinateSet* v9;  // r0
	const TextureUVCoordinateSet* v10; // r0
	const TextureUVCoordinateSet* v11; // r0
	const TextureUVCoordinateSet* v12; // r0
	const TextureUVCoordinateSet* v13; // r0
	const TextureUVCoordinateSet* v14; // r0
	const TextureUVCoordinateSet* v15; // r0
	const TextureUVCoordinateSet* v16; // r0
	const TextureUVCoordinateSet* v17; // r0
	int32_t v18;					   // r9
	//Tile_vt* vtable;				   // r3
	const TextureUVCoordinateSet* v20; // r0
	const TextureUVCoordinateSet* v21; // r0
	const TextureUVCoordinateSet* v22; // r0
	const TextureUVCoordinateSet* v23; // r0
	const TextureUVCoordinateSet* v24; // r0
	int32_t v25;					   // r8
	//Tile_vt* v26;					   // r3
	const TextureUVCoordinateSet* v27; // r0
	const TextureUVCoordinateSet* v28; // r0
	const TextureUVCoordinateSet* v29; // r0
	const TextureUVCoordinateSet* v30; // r0
	const TextureUVCoordinateSet* v31; // r0
	int32_t v32;					   // r8
	//Tile_vt* v33;					   // r3
	const TextureUVCoordinateSet* v34; // r0
	const TextureUVCoordinateSet* v35; // r0
	const TextureUVCoordinateSet* v36; // r0
	const TextureUVCoordinateSet* v37; // r0
	const TextureUVCoordinateSet* v38; // r0
	int32_t v39;					   // r8
	//Tile_vt* v40;					   // r2
	const TextureUVCoordinateSet* v41; // r0
	const TextureUVCoordinateSet* v42; // r0
	const TextureUVCoordinateSet* v43; // r0
	const TextureUVCoordinateSet* v44; // r0
	const TextureUVCoordinateSet* v45; // r0
	TextureUVCoordinateSet v46;		   // [sp+4h] [bp-54h]
	TextureUVCoordinateSet v47;		   // [sp+4h] [bp-54h]
	TextureUVCoordinateSet v48;		   // [sp+4h] [bp-54h]
	TextureUVCoordinateSet v49;		   // [sp+4h] [bp-54h]
	TextureUVCoordinateSet v50;		   // [sp+4h] [bp-54h]
	TextureUVCoordinateSet v51;		   // [sp+4h] [bp-54h]

	this->field_0 = a4;
	v7 = tile->getRenderShape();
	switch(v7) {
		case 0:
		case 31:
			tile->updateDefaultShape();
			Tesselator::instance.addOffset(-0.5f, -0.5f, -0.5f);
			Tesselator::instance.begin(24);
			Tesselator::instance.normal(Vec3::NEG_UNIT_Y);
			v8 = tile->getCarriedTexture(0, a3);
			this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v8);
			v9 = tile->getCarriedTexture(1, a3);
			this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v9);
			v10 = tile->getCarriedTexture(2, a3);
			this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v10);
			v46 = *tile->getCarriedTexture(3, a3);
			this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v46);
			v11 = tile->getCarriedTexture(4, a3);
			this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v11);
			v12 = tile->getCarriedTexture(5, a3);
			this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v12);
			Tesselator::instance.draw(0);
LABEL_21:
			Tesselator::instance.addOffset(0.5f, 0.5f, 0.5f);
			break;
		case 1:
			Tesselator::instance.begin(8);
			this->tesselateCrossTexture(tile, a3, -0.5f, -0.5f, -0.5f);
LABEL_8:
			Tesselator::instance.draw(0);
			break;
		case 19:
			Tesselator::instance.begin(8);
			tile->updateDefaultShape();
			this->tesselateStemTexture(tile, a3, tile->maxY, -0.5f, -0.5f, -0.5f);
			goto LABEL_8;
		case 13:
			tile->updateDefaultShape();
			Tesselator::instance.offset(-0.5f, -0.5f, -0.5f);
			Tesselator::instance.begin(24);
			v13 = tile->getTexture(0);
			this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v13);
			v14 = tile->getTexture(1);
			this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v14);
			Tesselator::instance.addOffset(0.0f, 0.0f, 0.0625f);
			v15 = tile->getTexture(2);
			this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v15);
			Tesselator::instance.addOffset(0.0f, 0.0f, -0.0625f);
			Tesselator::instance.addOffset(0.0f, 0.0f, -0.0625f);
			v47 = *tile->getTexture(3);
			this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v47);
			Tesselator::instance.addOffset(0.0f, 0.0f, 0.0625f);
			Tesselator::instance.addOffset(0.0625f, 0.0f, 0.0f);
			v16 = tile->getTexture(4);
			this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v16);
			Tesselator::instance.addOffset(-0.0625f, 0.0f, 0.0f);
			Tesselator::instance.addOffset(-0.0625f, 0.0f, 0.0f);
			v17 = tile->getTexture(5);
			this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v17);
			Tesselator::instance.addOffset(0.0625f, 0.0f, 0.0f);
			Tesselator::instance.draw(0);
			Tesselator::instance.offset(0.0f, 0.0f, 0.0f);
			break;
		case 6:
			Tesselator::instance.begin(0);
			Tesselator::instance.normal(0.0f, -1.0f, 0.0f);
			this->tesselateRowTexture(tile, a3, -0.5f, -0.5f, -0.5f);
			break;
		case 22:
			EntityTileRenderer::instance->render(tile, a3, 1.0f);
			break;
		case 10:
			v18 = 0;
			Tesselator::instance.addOffset(-0.5f, -0.5f, -0.5f);
			Tesselator::instance.begin(48);
			do {
				if(v18) {
					tile->setShape(0.0f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f);
				} else {
					tile->setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f);
				}
				++v18;
				v20 = tile->getTexture(0);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v20);
				v21 = tile->getTexture(1);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v21);
				v22 = tile->getTexture(2);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v22);
				v48 = *tile->getTexture(3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v48);
				v23 = tile->getTexture(4);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v23);
				v24 = tile->getTexture(5);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v24);
			} while(v18 != 2);
			Tesselator::instance.draw(0);
			goto LABEL_21;
		case 11:
			v25 = 0;
			Tesselator::instance.addOffset(-0.5f, -0.5f, -0.5f);
			Tesselator::instance.begin(96);
			do {
				//v26 = tile->vtable;
				if(v25) {
					switch(v25) {
						case 1:
							tile->setShape(0.375f, 0.0f, 0.75f, 0.625f, 1.0f, 1.0f);
							break;
						case 2:
							tile->setShape(0.4375f, 0.8125f, -0.125f, 0.5625f, 0.9375f, 1.125f);
							break;
						case 3:
							tile->setShape(0.4375f, 0.3125f, -0.125f, 0.5625f, 0.4375f, 1.125f);
							break;
					}
				} else {
					tile->setShape(0.375f, 0.0f, 0.0f, 0.625f, 1.0f, 0.25f);
				}
				++v25;
				v27 = tile->getTexture(0);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v27);
				v28 = tile->getTexture(1);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v28);
				v29 = tile->getTexture(2);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v29);
				v49 = *tile->getTexture(3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v49);
				v30 = tile->getTexture(4);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v30);
				v31 = tile->getTexture(5);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v31);
			} while(v25 != 4);
LABEL_42:
			Tesselator::instance.draw(0);
			Tesselator::instance.addOffset(0.5f, 0.5f, 0.5f);
			tile->setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
			break;
		case 21:
			v32 = 0;
			Tesselator::instance.addOffset(-0.5f, -0.5f, -0.5f);
			Tesselator::instance.begin(72);
			do {
				//v33 = tile->vtable;
				if(v32) {
					if(v32 == 1) {
						tile->setShape(0.4375f, 0.3f, 0.875f, 0.5625f, 1.0f, 1.0f);
					} else {
						tile->setShape(0.4375f, 0.5f, 0.125f, 0.5625f, 0.9375f, 0.875f);
					}
				} else {
					tile->setShape(0.4375f, 0.3f, 0.0f, 0.5625f, 1.0f, 0.125f);
				}
				++v32;
				v34 = tile->getTexture(0);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v34);
				v35 = tile->getTexture(1);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v35);
				v36 = tile->getTexture(2);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v36);
				v50 = *tile->getTexture(3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v50);
				v37 = tile->getTexture(4);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v37);
				v38 = tile->getTexture(5);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v38);
			} while(v32 != 3);
			goto LABEL_42;
		case 32:
			v39 = 0;
			Tesselator::instance.begin(96);
			do {
				if(v39) {
					if(v39 == 1) {
						tile->setShape(0.5f - 0.1875f, 0.0f, 0.5f, 0.1875f + 0.5f, 0.8125f, 1.0f - 0.25f);
					} else {
						//v40 = tile->vtable;
						if(v39 == 2) {
							tile->setShape(0.5f - 0.1875f, 0.0f, 0.25f + 0.0f, 0.1875f + 0.5f, 0.8125f, 0.5f);
						} else {
							tile->setShape(0.5f - 0.25f, 0.0f, 0.0f - 0.25f, 0.25f + 0.5f, 1.0f, 0.25f + 0.0f);
						}
					}
				} else {
					tile->setShape(0.5f - 0.25f, 0.0f, 1.0f - 0.25f, 0.25f + 0.5f, 1.0f, 0.25f + 1.0f);
				}
				++v39;
				v41 = tile->getTexture(0, a3);
				this->renderFaceUp(tile, 0.0f, 0.0f, 0.0f, *v41);
				v42 = tile->getTexture(1, a3);
				this->renderFaceDown(tile, 0.0f, 0.0f, 0.0f, *v42);
				v43 = tile->getTexture(2, a3);
				this->renderNorth(tile, 0.0f, 0.0f, 0.0f, *v43);
				v51 = *tile->getTexture(3, a3);
				this->renderSouth(tile, 0.0f, 0.0f, 0.0f, v51);
				v44 = tile->getTexture(4, a3);
				this->renderWest(tile, 0.0f, 0.0f, 0.0f, *v44);
				v45 = tile->getTexture(5, a3);
				this->renderEast(tile, 0.0f, 0.0f, 0.0f, *v45);
			} while(v39 != 4);
			Tesselator::instance.draw(0);
			tile->setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
			break;
	}
	this->field_0 = 0;
}
void TileRenderer::renderWest(Tile* a2, float a3, float a4, float a5, const struct TextureUVCoordinateSet& _a6) {
	float minX;	 // s16
	float maxX;	 // s18
	float v13;	 // s14
	float maxZ;	 // s11
	float minZ;	 // s10
	float maxY;	 // s12
	float v17;	 // s17
	float minY;	 // s19
	float v19;	 // s15
	float v20;	 // s14
	float v21;	 // s13
	float v22;	 // s9
	float v23;	 // s15
	int32_t v24; // r3
	float v25;	 // s14
	float v26;	 // s22
	float v27;	 // s15
	float v28;	 // s22
	float v29;	 // s20
	float v30;	 // s21
	float v31;	 // s23
	float v32;	 // s23
	float v33;	 // s17
	float v34;	 // s15
	float v35;	 // s14
	float v36;	 // s18
	float v37;	 // s15
	float v38;	 // s17
	float v39;	 // s15
	float v40;	 // r6
	float v41;	 // s25
	float v42;	 // s27
	float v43;	 // s26
	float v44;	 // s24
	TextureUVCoordinateSet* a6 = (TextureUVCoordinateSet*)&_a6;

	if(this->hasUVCoords) {
		a6 = &this->field_8;
	}
	minX = a6->minX;
	maxX = a6->maxX;
	v13 = maxX - a6->minX;
	maxZ = a2->maxZ;
	minZ = a2->minZ;
	maxY = a2->maxY;
	v17 = a6->maxY;
	minY = a6->minY;
	v19 = a6->minX + (float)(minZ * v13);
	v20 = a6->minX + (float)(maxZ * v13);
	v21 = a2->minY;
	if(this->field_21) {
		v22 = v19;
		v19 = v20;
		v20 = v22;
	}
	if(minZ >= 0.0f && maxZ <= 1.0f) {
		maxX = v20;
		minX = v19;
	}
	if(v21 >= 0.0f && maxY <= 1.0f) {
		v23 = v17 - minY;
		v17 = v17 - (float)(v21 * (float)(v17 - minY));
		minY = a6->maxY - (float)(maxY * v23);
	}
	this->_randomizeFaceDirection(a2, 4, a3, a4, a5);
	v24 = this->randomizeFace[4];
	if(v24 == 1) {
		v25 = a6->maxX - a6->minX;
		v26 = a6->maxY;
		minX = a6->minX + (float)(v25 * a2->minY);
		v27 = v26 - a6->minY;
		maxX = a6->minX + (float)(v25 * a2->maxY);
		v28 = v26 - (float)(v27 * a2->maxZ);
		v29 = a6->maxY - (float)(v27 * a2->minZ);
		v30 = maxX;
		v31 = minX;
		v17 = v28;
		minY = v29;
	} else if(v24 == 2) {
		v32 = a6->maxX;
		v33 = a6->minY;
		v34 = v32 - a6->minX;
		v35 = a6->maxY - v33;
		minY = v33 + (float)(v35 * a2->minZ);
		v17 = v33 + (float)(v35 * a2->maxZ);
		v30 = v32 - (float)(v34 * a2->maxY);
		v31 = v32 - (float)(v34 * a2->minY);
		v29 = a6->minY + (float)(v35 * a2->minZ);
		v28 = v17;
		maxX = a6->maxX - (float)(v34 * a2->maxY);
		minX = v31;
	} else {
		if(v24 == 3) {
			v36 = a6->maxX;
			v37 = v36 - a6->minX;
			v38 = a6->minY;
			minX = v36 - (float)(v37 * a2->minZ);
			maxX = v36 - (float)(v37 * a2->maxZ);
			v39 = a6->maxY - v38;
			minY = v38 + (float)(v39 * a2->maxY);
			v17 = v38 + (float)(v39 * a2->minY);
		}
		v29 = v17;
		v28 = minY;
		v30 = minX;
		v31 = maxX;
	}
	v40 = a3 + a2->minX;
	v41 = a4 + a2->minY;
	v42 = a4 + a2->maxY;
	v43 = a5 + a2->minZ;
	v44 = a5 + a2->maxZ;
	if(this->field_0) {
		Tesselator::instance.normal(Vec3::NEG_UNIT_X);
	}
	if(this->enableAO) {
		Tesselator::instance.color(this->redXeYs, this->greenXeYs, this->blueXeYs);
		Tesselator::instance.vertexUV(v40, v42, v44, v31, v28);
		Tesselator::instance.color(this->redXsYs, this->greenXsYs, this->blueXsYs);
		Tesselator::instance.vertexUV(v40, v42, v43, minX, minY);
		Tesselator::instance.color(this->redXsYe, this->greenXsYe, this->blueXsYe);
		Tesselator::instance.vertexUV(v40, v41, v43, v30, v29);
		Tesselator::instance.color(this->redXeYe, this->greenXeYe, this->blueXeYe);
	} else {
		Tesselator::instance.vertexUV(v40, v42, v44, v31, v28);
		Tesselator::instance.vertexUV(v40, v42, v43, minX, minY);
		Tesselator::instance.vertexUV(v40, v41, v43, v30, v29);
	}
	Tesselator::instance.vertexUV(v40, v41, v44, maxX, v17);
}

static int8_t _D67239E0[] = {5, 3, 4, 2};

bool_t TileRenderer::tesselateBedInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	uint32_t v9;					   // r0
	int32_t v10;					   // r10
	float v11;						   // s22
	const TextureUVCoordinateSet* v12;	   // r0
	float v13;						   // s16
	float maxX;						   // s21
	float v15;						   // r11
	float minY;						   // s25
	float minX;						   // s27
	float maxY;						   // s26
	float v19;						   // s18
	float v20;						   // s17
	float v21;						   // s20
	float v22;						   // s24
	float v23;						   // s23
	float v24;						   // s21
	float v25;						   // r0
	const TextureUVCoordinateSet* v26;	   // r0
	float v27;						   // s21
	float v28;						   // lr
	float v29;						   // s20
	float v30;						   // r1
	float v31;						   // r11
	float v32;						   // r3
	float v33;						   // s18
	float v34;						   // r2
	float v35;						   // s24
	float v36;						   // s25
	float v37;						   // s29
	float v38;						   // s27
	float v39;						   // s23
	float v40;						   // s26
	float v41;						   // s28
	float v42;						   // s27
	int32_t v43;					   // r11
	int32_t v44;					   // r10
	float v45;						   // s14
	const TextureUVCoordinateSet* v46; // r0
	float v47;						   // s14
	float v48;						   // s14
	const TextureUVCoordinateSet* v49; // r0
	float v50;						   // r0
	const TextureUVCoordinateSet* v51; // r0
	bool_t result;					   // r0
	TextureUVCoordinateSet v53;		   // [sp+4h] [bp-84h]
	bool_t isHeadPiece;				   // [sp+24h] [bp-64h]

	v9 = this->levelSource->getData(x, y, z);
	v10 = v9 & 3;
	isHeadPiece = BedTile::isHeadPiece(v9);
	v11 = tile->getBrightness(this->levelSource, x, y, z);
	Tesselator::instance.color((float)(v11 * 0.5f), v11 * 0.5f, v11 * 0.5f);
	v12 = tile->getTexture(this->levelSource, x, y, z, 0);
	v13 = (float)x;
	maxX = tile->maxX;
	v15 = v12->maxX;
	minY = v12->minY;
	minX = v12->minX;
	maxY = v12->maxY;
	v19 = (float)((float)y + tile->minY) + 0.1875f;
	v20 = (float)z;
	v21 = (float)z + tile->maxZ;
	v22 = (float)x + tile->minX;
	v23 = (float)z + tile->minZ;
	Tesselator::instance.vertexUV(v22, v19, v21, v12->minX, maxY);
	v24 = (float)x + maxX;
	Tesselator::instance.vertexUV(v22, v19, v23, minX, minY);
	Tesselator::instance.vertexUV(v24, v19, v23, v15, minY);
	Tesselator::instance.vertexUV(v24, v19, v21, v15, maxY);
	v25 = tile->getBrightness(this->levelSource, x, y + 1, z);
	Tesselator::instance.color(v25, v25, v25);
	v26 = tile->getTexture(this->levelSource, x, y, z, 1);
	v27 = v26->minX;
	v28 = v26->maxX;
	v29 = v26->minY;
	v30 = v26->maxY;
	switch(v10) {
		case 0:
			v31 = v26->minY;
			v32 = v26->maxY;
			v33 = v26->maxX;
			v34 = v33;
			v35 = v32;
LABEL_7:
			v36 = v27;
			goto LABEL_10;
		case 2:
			v32 = v26->minY;
			v31 = v26->maxY;
			v33 = v26->minX;
			v34 = v26->minX;
			v29 = v31;
			v27 = v26->maxX;
			v35 = v32;
			goto LABEL_7;
		case 3:
			v33 = v26->minX;
			v34 = v26->maxX;
			v31 = v26->minY;
			v32 = v31;
			v29 = v26->maxY;
			break;
		default:
			v31 = v26->maxY;
			v32 = v31;
			v33 = v26->maxX;
			v34 = v26->minX;
			break;
	}
	v35 = v29;
	v36 = v34;
	v27 = v33;
LABEL_10:
	v37 = v13 + tile->maxX;
	v38 = tile->minX;
	v39 = (float)y + tile->maxY;
	v40 = v20 + tile->maxZ;
	v41 = v20 + tile->minZ;
	Tesselator::instance.vertexUV(v37, v39, v40, v34, v32);
	v42 = v13 + v38;
	Tesselator::instance.vertexUV(v37, v39, v41, v36, v35);
	Tesselator::instance.vertexUV(v42, v39, v41, v27, v29);
	Tesselator::instance.vertexUV(v42, v39, v40, v33, v31);
	v43 = Direction::DIRECTION_FACING[v10];
	if(isHeadPiece) {
		v43 = Direction::DIRECTION_FACING[Direction::DIRECTION_OPPOSITE[v10]];
	}
	v44 = _D67239E0[v10];
	if(v43 == 2) {
		goto LABEL_18;
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z - 1, 2)) {
		v45 = tile->getBrightness(this->levelSource, x, y, z - 1);
		if(tile->minZ > 0.0f) {
			v45 = v11;
		}
		Tesselator::instance.color((float)(v45 * 0.8f), v45 * 0.8f, v45 * 0.8f);
		this->field_21 = v44 == 2;
		v46 = tile->getTexture(this->levelSource, x, y, z, 2);
		this->renderNorth(tile, (float)x, (float)y, (float)z, *v46);
	}
	if(v43 != 3) {
LABEL_18:
		if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z + 1, 3)) {
			v47 = tile->getBrightness(this->levelSource, x, y, z + 1);
			if(tile->maxZ < 1.0f) {
				v47 = v11;
			}
			Tesselator::instance.color((float)(v47 * 0.8f), v47 * 0.8f, v47 * 0.8f);
			this->field_21 = v44 == 3;
			v53 = *tile->getTexture(this->levelSource, x, y, z, 3);
			this->renderSouth(tile, (float)x, (float)y, (float)z, v53);
		}
		if(v43 == 4) {
			goto LABEL_40;
		}
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x - 1, y, z, 4)) {
		v48 = tile->getBrightness(this->levelSource, x - 1, y, z);
		if(tile->minX > 0.0f) {
			v48 = v11;
		}
		Tesselator::instance.color((float)(v48 * 0.6f), v48 * 0.6f, v48 * 0.6f);
		this->field_21 = v44 == 4;
		v49 = tile->getTexture(this->levelSource, x, y, z, 4);
		this->renderWest(tile, (float)x, (float)y, (float)z, *v49);
	}
	if(v43 != 5) {
LABEL_40:
		if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x + 1, y, z, 5)) {
			v50 = tile->getBrightness(this->levelSource, x + 1, y, z);
			if(tile->maxX >= 1.0f) {
				v11 = v50;
			}
			Tesselator::instance.color((float)(v11 * 0.6f), v11 * 0.6f, v11 * 0.6f);
			this->field_21 = v44 == 5;
			v51 = tile->getTexture(this->levelSource, x, y, z, 5);
			this->renderEast(tile, (float)x, (float)y, (float)z, *v51);
		}
	}
	result = 1;
	this->field_21 = 0;
	return result;
}
bool_t TileRenderer::tesselateBlockInWorld(Tile* a2, int32_t a3, int32_t a4, int32_t a5) {
	int32_t color = a2->getColor(this->levelSource, a3, a4, a5);
	return this->tesselateBlockInWorldWithAmbienceOcclusion(a2, a3, a4, a5, (float)((color & 0xff0000) >> 16) / 255, (float)((color & 0xff00) >> 8) / 255, (float)((color & 0xff)) / 255);
}
bool_t TileRenderer::tesselateBlockInWorld(Tile* tile, int32_t x, int32_t y, int32_t z, float r, float g, float b) {
	float v12;						   // s17
	float v13;						   // s19
	float v14;						   // s18
	bool_t v15;						   // r10
	float v16;						   // s16
	const TextureUVCoordinateSet* v17; // r0
	float v18;						   // s15
	const TextureUVCoordinateSet* v19; // r0
	float v20;						   // s15
	float v21;						   // s15
	const TextureUVCoordinateSet* v22; // r0
	float v23;						   // s15
	const TextureUVCoordinateSet* v24; // r0
	float v25;						   // r0
	const TextureUVCoordinateSet* v26; // r0
	float v27;						   // s20
	TextureUVCoordinateSet v29;		   // [sp+4h] [bp-5Ch]

	this->enableAO = 0;
	if(tile == Tile::grass) {
		v12 = 1.0f;
		v13 = 1.0f;
		v14 = 1.0f;
	} else {
		v12 = b;
		v13 = g;
		v14 = r;
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y - 1, z, 0)) {
		v15 = 1;
		v25 = tile->getBrightness(this->levelSource, x, y - 1, z);
		Tesselator::instance.color((float)(v25 * 0.5f) * v14, (float)(v25 * 0.5f) * v13, (float)(v25 * 0.5f) * v12);
		v26 = tile->getTexture(this->levelSource, x, y, z, 0);
		this->renderFaceDown(tile, (float)x, (float)y, (float)z, *v26);
	} else {
		v15 = 0;
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y + 1, z, 1)) {
		v27 = tile->getBrightness(this->levelSource, x, y + 1, z);
		if(tile->maxY == 1.0f || tile->material->isLiquid()) {
			v16 = -999.0f;
		} else {
			v16 = tile->getBrightness(this->levelSource, x, y, z);
			v27 = v16;
		}
		v15 = 1;
		Tesselator::instance.color(r * v27, g * v27, b * v27);
		v17 = tile->getTexture(this->levelSource, x, y, z, 1);
		this->renderFaceUp(tile, (float)x, (float)y, (float)z, *v17);
	} else {
		v16 = -999.0f;
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z - 1, 2)) {
		v18 = tile->getBrightness(this->levelSource, x, y, z - 1);
		if(tile->minZ > 0.0f) {
			if(v16 == -999.0f) {
				v16 = tile->getBrightness(this->levelSource, x, y, z);
			}
			v18 = v16;
		}
		v15 = 1;
		Tesselator::instance.color(v14 * (float)(v18 * 0.8f), v13 * (float)(v18 * 0.8f), v12 * (float)(v18 * 0.8f));
		v19 = tile->getTexture(this->levelSource, x, y, z, 2);
		this->renderNorth(tile, (float)x, (float)y, (float)z, *v19);
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z + 1, 3)) {
		v20 = tile->getBrightness(this->levelSource, x, y, z + 1);
		if(tile->maxZ < 1.0f) {
			if(v16 == -999.0f) {
				v16 = tile->getBrightness(this->levelSource, x, y, z);
			}
			v20 = v16;
		}
		v15 = 1;
		Tesselator::instance.color(v14 * (float)(v20 * 0.8f), v13 * (float)(v20 * 0.8f), v12 * (float)(v20 * 0.8f));
		v29 = *tile->getTexture(this->levelSource, x, y, z, 3);
		this->renderSouth(tile, (float)x, (float)y, (float)z, v29);
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x - 1, y, z, 4)) {
		v21 = tile->getBrightness(this->levelSource, x - 1, y, z);
		if(tile->minX > 0.0f) {
			if(v16 == -999.0f) {
				v16 = tile->getBrightness(this->levelSource, x, y, z);
			}
			v21 = v16;
		}
		v15 = 1;
		Tesselator::instance.color(v14 * (float)(v21 * 0.6f), v13 * (float)(v21 * 0.6f), v12 * (float)(v21 * 0.6f));
		v22 = tile->getTexture(this->levelSource, x, y, z, 4);
		this->renderWest(tile, (float)x, (float)y, (float)z, *v22);
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x + 1, y, z, 5)) {
		v23 = tile->getBrightness(this->levelSource, x + 1, y, z);
		if(tile->maxX < 1.0f) {
			if(v16 == -999.0f) {
				v23 = tile->getBrightness(this->levelSource, x, y, z);
			} else {
				v23 = v16;
			}
		}
		v15 = 1;
		Tesselator::instance.color(v14 * (float)(v23 * 0.6f), v13 * (float)(v23 * 0.6f), v12 * (float)(v23 * 0.6f));
		v24 = tile->getTexture(this->levelSource, x, y, z, 5);
		this->renderEast(tile, (float)x, (float)y, (float)z, *v24);
	}
	return v15;
}

bool_t TileRenderer::tesselateBlockInWorldWithAmbienceOcclusion(Tile* tile, int32_t x, int32_t y, int32_t z, float r, float g, float b) {

	bool renderedSomething = 0;
	this->enableAO = 1;
	bool dontApplyGrassColor = tile != Tile::grass;
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y - 1, z, 0)) {
		bool xp = Tile::translucent[this->levelSource->getTile(x + 1, y - 1, z)];
		bool xn = Tile::translucent[this->levelSource->getTile(x - 1, y - 1, z)];
		bool zp = Tile::translucent[this->levelSource->getTile(x, y - 1, z + 1)];
		bool zn = Tile::translucent[this->levelSource->getTile(x, y - 1, z - 1)];
		float b_xn = tile->getBrightness(this->levelSource, x - 1, y - 1, z);
		float b_zn = tile->getBrightness(this->levelSource, x, y - 1, z - 1);
		float b_zp = tile->getBrightness(this->levelSource, x, y - 1, z + 1);
		float b_xp = tile->getBrightness(this->levelSource, x + 1, y - 1, z);

		float v13 = zn || xn ? tile->getBrightness(this->levelSource, x - 1, y - 1, z - 1) : b_xn;
		float v14 = zp || xn ? tile->getBrightness(this->levelSource, x - 1, y - 1, z + 1) : b_xn;
		float v15 = zn || xp ? tile->getBrightness(this->levelSource, x + 1, y - 1, z - 1) : b_xp;
		float v16 = zp || xp ? tile->getBrightness(this->levelSource, x + 1, y - 1, z + 1) : b_xp;
		float v17 = tile->getBrightness(this->levelSource, x, y - 1, z);

		float v18 = (float)((float)((float)(v14 + b_xn) + b_zp) + v17) * 0.25f;
		float v19 = (float)((float)((float)(b_zp + v17) + v16) + b_xp) * 0.25f;
		float v20 = (float)((float)((float)(v17 + b_zn) + b_xp) + v15) * 0.25f;
		float v21 = (float)((float)((float)(b_xn + v13) + v17) + b_zn) * 0.25f;

		if(dontApplyGrassColor) {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = r * 0.5f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = g * 0.5f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = b * 0.5f;
		} else {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = 0.5f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = 0.5f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = 0.5f;
		}

		renderedSomething = 1;

		this->redXeYs = this->redXeYs * v18;
		this->greenXeYs = this->greenXeYs * v18;
		this->blueXeYs = this->blueXeYs * v18;

		this->redXsYs = this->redXsYs * v21;
		this->greenXsYs = this->greenXsYs * v21;
		this->blueXsYs = this->blueXsYs * v21;

		this->redXsYe = this->redXsYe * v20;
		this->greenXsYe = this->greenXsYe * v20;
		this->blueXsYe = this->blueXsYe * v20;

		this->redXeYe = this->redXeYe * v19;
		this->greenXeYe = this->greenXeYe * v19;
		this->blueXeYe = this->blueXeYe * v19;
		this->renderFaceDown(tile, (float)x, (float)y, (float)z, *tile->getTexture(this->levelSource, x, y, z, 0));
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y + 1, z, 1)) {
		bool xp = Tile::translucent[this->levelSource->getTile(x + 1, y + 1, z)];
		bool xn = Tile::translucent[this->levelSource->getTile(x - 1, y + 1, z)];
		bool zp = Tile::translucent[this->levelSource->getTile(x, y + 1, z + 1)];
		bool zn = Tile::translucent[this->levelSource->getTile(x, y + 1, z - 1)];
		float thick = tile->getThickness();
		float b_xn = tile->getBrightness(this->levelSource, x - 1, (thick <= 0.0f) + y, z);
		float b_xp = tile->getBrightness(this->levelSource, x + 1, (thick <= 0.0f) + y, z);
		float b_zn = tile->getBrightness(this->levelSource, x, (thick <= 0.0f) + y, z - 1);
		float b_zp = tile->getBrightness(this->levelSource, x, (thick <= 0.0f) + y, z + 1);

		float v29 = zn || xn ? tile->getBrightness(this->levelSource, x - 1, (thick <= 0.0f) + y, z - 1) : b_xn;
		float v30 = zn || xp ? tile->getBrightness(this->levelSource, x + 1, (thick <= 0.0f) + y, z - 1) : b_xp;
		float v31 = zp || xn ? tile->getBrightness(this->levelSource, x - 1, (thick <= 0.0f) + y, z + 1) : b_xn;
		float v32 = zp || xp ? tile->getBrightness(this->levelSource, x + 1, (thick <= 0.0f) + y, z + 1) : b_xp;
		float v33 = tile->getBrightness(this->levelSource, x, y + 1, z);

		renderedSomething = 1;
		float v36 = (float)((float)((float)(b_zp + v33) + v32) + b_xp) * 0.25f;
		float v37 = (float)((float)((float)(b_xn + v29) + v33) + b_zn) * 0.25f;
		float v38 = (float)((float)((float)(v33 + b_zn) + b_xp) + v30) * 0.25f;
		float v39 = (float)((float)((float)(v31 + b_xn) + b_zp) + v33) * 0.25f;

		this->redXeYs = r * v36;
		this->greenXeYs = g * v36;
		this->blueXeYs = b * v36;

		this->redXsYs = r * v38;
		this->greenXsYs = g * v38;
		this->blueXsYs = b * v38;

		this->redXsYe = r * v37;
		this->greenXsYe = g * v37;
		this->blueXsYe = b * v37;

		this->redXeYe = r * v39;
		this->greenXeYe = g * v39;
		this->blueXeYe = b * v39;

		this->renderFaceUp(tile, (float)x, (float)y, (float)z, *tile->getTexture(this->levelSource, x, y, z, 1));
	}

	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z - 1, 2)) {
		bool xp = Tile::translucent[this->levelSource->getTile(x + 1, y, z - 1)];
		bool xn = Tile::translucent[this->levelSource->getTile(x - 1, y, z - 1)];
		bool yp = Tile::translucent[this->levelSource->getTile(x, y + 1, z - 1)];
		bool yn = Tile::translucent[this->levelSource->getTile(x, y - 1, z - 1)];
		float b_xn = tile->getBrightness(this->levelSource, x - 1, y, z - 1);
		float b_yn = tile->getBrightness(this->levelSource, x, y - 1, z - 1);
		float b_yp = tile->getBrightness(this->levelSource, x, y + 1, z - 1);
		float b_xp = tile->getBrightness(this->levelSource, x + 1, y, z - 1);

		float v41 = xn || yn ? tile->getBrightness(this->levelSource, x - 1, y - 1, z - 1) : b_xn;
		float v42 = xn || yp ? tile->getBrightness(this->levelSource, x - 1, y + 1, z - 1) : b_xn;
		float v43 = xp || yn ? tile->getBrightness(this->levelSource, x + 1, y - 1, z - 1) : b_xp;
		float v44 = xp || yp ? tile->getBrightness(this->levelSource, x + 1, y + 1, z - 1) : b_xp;
		float v45 = tile->getBrightness(this->levelSource, x, y, z - 1);
		float v47 = (float)((float)((float)(b_xn + v42) + v45) + b_yp) * 0.25f;
		float v48 = (float)((float)((float)(v45 + b_yp) + b_xp) + v44) * 0.25f;
		float v49 = (float)((float)((float)(b_yn + v45) + v43) + b_xp) * 0.25f;
		float v50 = (float)((float)((float)(v41 + b_xn) + b_yn) + v45) * 0.25f;

		if(dontApplyGrassColor) {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = r * 0.8f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = g * 0.8f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = b * 0.8f;
		} else {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = 0.8f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = 0.8f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = 0.8f;
		}
		renderedSomething = 1;
		this->redXeYs = this->redXeYs * v47;
		this->greenXeYs = this->greenXeYs * v47;
		this->blueXeYs = this->blueXeYs * v47;

		this->redXsYs = this->redXsYs * v48;
		this->greenXsYs = this->greenXsYs * v48;
		this->blueXsYs = this->blueXsYs * v48;

		this->redXsYe = this->redXsYe * v49;
		this->greenXsYe = this->greenXsYe * v49;
		this->blueXsYe = this->blueXsYe * v49;

		this->redXeYe = this->redXeYe * v50;
		this->greenXeYe = this->greenXeYe * v50;
		this->blueXeYe = this->blueXeYe * v50;

		this->renderNorth(tile, (float)x, (float)y, (float)z, *tile->getTexture(this->levelSource, x, y, z, 2));
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z + 1, 3)) {
		bool xp = Tile::translucent[this->levelSource->getTile(x + 1, y, z + 1)];
		bool xn = Tile::translucent[this->levelSource->getTile(x - 1, y, z + 1)];
		bool yp = Tile::translucent[this->levelSource->getTile(x, y + 1, z + 1)];
		bool yn = Tile::translucent[this->levelSource->getTile(x, y - 1, z + 1)];
		float b_xn = tile->getBrightness(this->levelSource, x - 1, y, z + 1);
		float b_xp = tile->getBrightness(this->levelSource, x + 1, y, z + 1);
		float b_yn = tile->getBrightness(this->levelSource, x, y - 1, z + 1);
		float b_yp = tile->getBrightness(this->levelSource, x, y + 1, z + 1);

		float v57 = xn || yn ? tile->getBrightness(this->levelSource, x - 1, y - 1, z + 1) : b_xn;
		float v58 = xn || yp ? tile->getBrightness(this->levelSource, x - 1, y + 1, z + 1) : b_xn;
		float v59 = xp || yn ? tile->getBrightness(this->levelSource, x + 1, y - 1, z + 1) : b_xp;
		float v60 = xp || yp ? tile->getBrightness(this->levelSource, x + 1, y + 1, z + 1) : b_xp;
		float v61 = tile->getBrightness(this->levelSource, x, y, z + 1);

		float v63 = (float)((float)((float)(b_xn + v58) + v61) + b_yp) * 0.25f;
		float v64 = (float)((float)((float)(v61 + b_yp) + b_xp) + v60) * 0.25f;
		float v65 = (float)((float)((float)(b_yn + v61) + v59) + b_xp) * 0.25f;
		float v66 = (float)((float)((float)(v57 + b_xn) + b_yn) + v61) * 0.25f;
		if(dontApplyGrassColor) {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = r * 0.8f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = g * 0.8f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = b * 0.8f;
		} else {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = 0.8f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = 0.8f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = 0.8f;
		}

		renderedSomething = 1;
		this->redXeYs = this->redXeYs * v63;
		this->greenXeYs = this->greenXeYs * v63;
		this->blueXeYs = this->blueXeYs * v63;

		this->redXsYs = this->redXsYs * v66;
		this->greenXsYs = this->greenXsYs * v66;
		this->blueXsYs = this->blueXsYs * v66;

		this->redXsYe = this->redXsYe * v65;
		this->greenXsYe = this->greenXsYe * v65;
		this->blueXsYe = this->blueXsYe * v65;

		this->redXeYe = this->redXeYe * v64;
		this->greenXeYe = this->greenXeYe * v64;
		this->blueXeYe = this->blueXeYe * v64;

		this->renderSouth(tile, (float)x, (float)y, (float)z, *tile->getTexture(this->levelSource, x, y, z, 3));
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x - 1, y, z, 4)) {
		bool yp = Tile::translucent[this->levelSource->getTile(x - 1, y + 1, z)];
		bool yn = Tile::translucent[this->levelSource->getTile(x - 1, y - 1, z)];
		bool zn = Tile::translucent[this->levelSource->getTile(x - 1, y, z - 1)];
		bool zp = Tile::translucent[this->levelSource->getTile(x - 1, y, z + 1)];
		float b_yn = tile->getBrightness(this->levelSource, x - 1, y - 1, z);
		float b_zn = tile->getBrightness(this->levelSource, x - 1, y, z - 1);
		float b_zp = tile->getBrightness(this->levelSource, x - 1, y, z + 1);
		float b_yp = tile->getBrightness(this->levelSource, x - 1, y + 1, z);

		float v72 = zn || yn ? tile->getBrightness(this->levelSource, x - 1, y - 1, z - 1) : b_zn;
		float v73 = zp || yn ? tile->getBrightness(this->levelSource, x - 1, y - 1, z + 1) : b_zp;
		float v74 = zn || yp ? tile->getBrightness(this->levelSource, x - 1, y + 1, z - 1) : b_zn;
		float v75 = zp || yp ? tile->getBrightness(this->levelSource, x - 1, y + 1, z + 1) : b_zp;
		float v76 = tile->getBrightness(this->levelSource, x - 1, y, z);

		float v78 = (float)((float)((float)(b_yn + v73) + v76) + b_zp) * 0.25f;
		float v79 = (float)((float)((float)(v76 + b_zp) + b_yp) + v75) * 0.25f;
		float v80 = (float)((float)((float)(b_zn + v76) + v74) + b_yp) * 0.25f;
		float v81 = (float)((float)((float)(v72 + b_yn) + b_zn) + v76) * 0.25f;
		if(dontApplyGrassColor) {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = r * 0.6f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = g * 0.6f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = b * 0.6f;
		} else {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = 0.6f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = 0.6f;
			this->blueXeYs = this->blueXsYs = this->blueXsYe = this->blueXeYe = 0.6f;
		}
		renderedSomething = 1;
		this->redXeYs = this->redXeYs * v79;
		this->greenXeYs = this->greenXeYs * v79;
		this->blueXeYs = this->blueXeYs * v79;

		this->redXsYs = this->redXsYs * v80;
		this->greenXsYs = this->greenXsYs * v80;
		this->blueXsYs = this->blueXsYs * v80;

		this->redXsYe = this->redXsYe * v81;
		this->greenXsYe = this->greenXsYe * v81;
		this->blueXsYe = this->blueXsYe * v81;

		this->redXeYe = this->redXeYe * v78;
		this->greenXeYe = this->greenXeYe * v78;
		this->blueXeYe = this->blueXeYe * v78;

		this->renderWest(tile, (float)x, (float)y, (float)z, *tile->getTexture(this->levelSource, x, y, z, 4));
	}

	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x + 1, y, z, 5)) {
		bool yp = Tile::translucent[this->levelSource->getTile(x + 1, y + 1, z)];
		bool yn = Tile::translucent[this->levelSource->getTile(x + 1, y - 1, z)];
		bool zp = Tile::translucent[this->levelSource->getTile(x + 1, y, z + 1)];
		bool zn = Tile::translucent[this->levelSource->getTile(x + 1, y, z - 1)];
		float b_yn = tile->getBrightness(this->levelSource, x + 1, y - 1, z);
		float b_zn = tile->getBrightness(this->levelSource, x + 1, y, z - 1);
		float b_zp = tile->getBrightness(this->levelSource, x + 1, y, z + 1);
		float b_yp = tile->getBrightness(this->levelSource, x + 1, y + 1, z);

		float v88 = yn || zn ? tile->getBrightness(this->levelSource, x + 1, y - 1, z - 1) : b_zn;
		float v89 = yn || zp ? tile->getBrightness(this->levelSource, x + 1, y - 1, z + 1) : b_zp;
		float v90 = yp || zn ? tile->getBrightness(this->levelSource, x + 1, y + 1, z - 1) : b_zn;
		float v91 = yp || zp ? tile->getBrightness(this->levelSource, x + 1, y + 1, z + 1) : b_zp;
		float v92 = tile->getBrightness(this->levelSource, x + 1, y, z);

		float v93 = (float)((float)((float)(b_yn + v89) + v92) + b_zp) * 0.25f;
		float v94 = (float)((float)((float)(v92 + b_zp) + b_yp) + v91) * 0.25f;
		float v95 = (float)((float)((float)(b_zn + v92) + v90) + b_yp) * 0.25f;
		float v96 = (float)((float)((float)(v88 + b_yn) + b_zn) + v92) * 0.25f;
		if(dontApplyGrassColor) {
			this->redXeYe = this->redXsYe = this->redXsYs = this->redXeYs = r * 0.6f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = g * 0.6f;
			this->blueXeYe = this->blueXsYe = this->blueXsYs = this->blueXeYs = b * 0.6f;
		} else {
			this->redXeYe = this->redXsYe = this->redXsYs =this->redXeYs = 0.6f;
			this->greenXeYe = this->greenXsYe = this->greenXsYs = this->greenXeYs = 0.6f;
			this->blueXeYe = this->blueXsYe = this->blueXsYs = this->blueXeYs = 0.6f;
		}

		renderedSomething = 1;
		this->redXeYs = this->redXeYs * v93;
		this->greenXeYs = this->greenXeYs * v93;
		this->blueXeYs = this->blueXeYs * v93;

		this->redXsYs = this->redXsYs * v96;
		this->greenXsYs = this->greenXsYs * v96;
		this->blueXsYs = this->blueXsYs * v96;

		this->redXsYe = this->redXsYe * v95;
		this->greenXsYe = this->greenXsYe * v95;
		this->blueXsYe = this->blueXsYe * v95;

		this->redXeYe = this->redXeYe * v94;
		this->greenXeYe = this->greenXeYe * v94;
		this->blueXeYe = this->blueXeYe * v94;
		this->renderEast(tile, (float)x, (float)y, (float)z, *tile->getTexture(this->levelSource, x, y, z, 5));
	}

	this->enableAO = 0;
	this->randomizeFace[0] = this->randomizeFace[1] = this->randomizeFace[2] = this->randomizeFace[3] = this->randomizeFace[4] = this->randomizeFace[5] = 0;
	return renderedSomething;
}
bool_t TileRenderer::tesselateCactusInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	int32_t v9; // r0

	v9 = tile->getColor(this->levelSource, x, y, z);
	return this->tesselateCactusInWorld(tile, x, y, z, (float)((v9 & 0xff0000) >> 16) / 255.0f, (float)((v9 & 0xff00) >> 8) / 255.0f, (float)(v9 & 0xff) / 255.0f);
}
bool_t TileRenderer::tesselateCactusInWorld(Tile* tile, int32_t x, int32_t y, int32_t z, float r, float g, float b) {
	float v10;						   // s17
	float v13;						   // s16
	float v14;						   // s18
	float v15;						   // s29
	float v16;						   // s19
	float v17;						   // s26
	float v18;						   // s28
	float v19;						   // s25
	float v20;						   // s27
	float v21;						   // s24
	int32_t v22;					   // r10
	float v23;						   // s20
	const TextureUVCoordinateSet* v24; // r0
	float v25;						   // r0
	const TextureUVCoordinateSet* v26; // r0
	float v27;						   // s15
	const TextureUVCoordinateSet* v28; // r0
	float v29;						   // s15
	float v30;						   // s15
	const TextureUVCoordinateSet* v31; // r0
	float v32;						   // r0
	const TextureUVCoordinateSet* v33; // r0
	TextureUVCoordinateSet v35;		   // [sp+4h] [bp-7Ch]

	v10 = (float)x;
	v13 = (float)y;
	v14 = (float)z;
	v15 = r * 0.8f;
	v16 = tile->getBrightness(this->levelSource, x, y, z);
	v17 = r * 0.6f;
	v18 = g * 0.8f;
	v19 = g * 0.6f;
	v20 = b * 0.8f;
	v21 = b * 0.6f;
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y - 1, z, 0)) {
		v22 = 1;
		v25 = tile->getBrightness(this->levelSource, x, y - 1, z);
		Tesselator::instance.color((float)(r * 0.5f) * v25, (float)(g * 0.5f) * v25, (float)(b * 0.5f) * v25);
		v26 = tile->getTexture(this->levelSource, x, y, z, 0);
		this->renderFaceDown(tile, v10, v13, v14, *v26);
	} else {
		v22 = 0;
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y + 1, z, 1)) {
		v23 = tile->getBrightness(this->levelSource, x, y + 1, z);
		if(tile->maxY != 1.0f && !tile->material->isLiquid()) {
			v23 = v16;
		}
		v22 = 1;
		Tesselator::instance.color(r * v23, g * v23, b * v23);
		v24 = tile->getTexture(this->levelSource, x, y, z, 1);
		this->renderFaceUp(tile, v10, v13, v14, *v24);
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z - 1, 2)) {
		v27 = tile->getBrightness(this->levelSource, x, y, z - 1);
		if(tile->minZ > 0.0f) {
			v27 = v16;
		}
		Tesselator::instance.color(v15 * v27, v18 * v27, v20 * v27);
		Tesselator::instance.addOffset(0.0f, 0.0f, 0.0625f);
		v28 = tile->getTexture(this->levelSource, x, y, z, 2);
		this->renderNorth(tile, v10, v13, v14, *v28);
		v22 = 1;
		Tesselator::instance.addOffset(0.0f, 0.0f, -0.0625f);
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x, y, z + 1, 3)) {
		v29 = tile->getBrightness(this->levelSource, x, y, z + 1);
		if(tile->maxZ < 1.0f) {
			v29 = v16;
		}
		Tesselator::instance.color(v15 * v29, v18 * v29, v20 * v29);
		Tesselator::instance.addOffset(0.0f, 0.0f, -0.0625f);
		v35 = *tile->getTexture(this->levelSource, x, y, z, 3);
		this->renderSouth(tile, v10, v13, v14, v35);
		v22 = 1;
		Tesselator::instance.addOffset(0.0f, 0.0f, 0.0625f);
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x - 1, y, z, 4)) {
		v30 = tile->getBrightness(this->levelSource, x - 1, y, z);
		if(tile->minX > 0.0f) {
			v30 = v16;
		}
		Tesselator::instance.color(v17 * v30, v19 * v30, v21 * v30);
		Tesselator::instance.addOffset(0.0625f, 0.0f, 0.0f);
		v31 = tile->getTexture(this->levelSource, x, y, z, 4);
		this->renderWest(tile, v10, v13, v14, *v31);
		v22 = 1;
		Tesselator::instance.addOffset(-0.0625f, 0.0f, 0.0f);
	}
	if(this->disableCulling || tile->shouldRenderFace(this->levelSource, x + 1, y, z, 5)) {
		v22 = 1;
		v32 = tile->getBrightness(this->levelSource, x + 1, y, z);
		if(tile->maxX >= 1.0f) {
			v16 = v32;
		}
		Tesselator::instance.color(v17 * v16, v19 * v16, v21 * v16);
		Tesselator::instance.addOffset(-0.0625f, 0.0f, 0.0f);
		v33 = tile->getTexture(this->levelSource, x, y, z, 5);
		this->renderEast(tile, v10, v13, v14, *v33);
		Tesselator::instance.addOffset(0.0625f, 0.0f, 0.0f);
	}
	return v22;
}
bool_t TileRenderer::tesselateCrossInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	float v9;	  // s16
	int32_t v10;  // r0
	float v11;	  // s16
	float v12;	  // s18
	float v13;	  // s17
	uint32_t v14; // r3
	int32_t v15;  // s12
	int32_t v16;  // r2
	int32_t v17;  // r3
	float v18;	  // s12
	int32_t v19;  // r0

	v9 = tile->getBrightness(this->levelSource, x, y, z);
	v10 = tile->getColor(this->levelSource, x, y, z);
	Tesselator::instance.color(v9 * (float)((float)((v10 & 0xff0000) >> 16) / 255.0f), v9 * (float)((float)((v10 & 0xff00) >> 8) / 255.0f), v9 * (float)((float)(v10 & 0xff) / 255.0f));
	v11 = (float)x;
	v12 = (float)y;
	v13 = (float)z;
	if(tile == Tile::tallgrass || tile == Tile::flower || tile == Tile::rose) {
		v14 = 11 * ((0x2FC20F * x) ^ y ^ (0x6EBFFF5 * z)) + 0x285B825 * ((0x2FC20F * x) ^ y ^ (0x6EBFFF5 * z)) * ((0x2FC20F * x) ^ y ^ (0x6EBFFF5 * z));
		v15 = ((v14 & 0xffff0000) >> 16) /*HIWORD*/ & 0xF;
		v16 = (v14 >> 20) & 0xF;
		v17 = ((v14 & 0xff000000) >> 24) & 0xF;
		v11 = v11 + (float)((float)((float)((float)v15 / 15.0f) - 0.5f) * 0.35f);
		v18 = 0.1f;
		if(!Tile::flower) {
			v18 = 0.35f;
		}
		v12 = v12 + (float)((float)((float)((float)v16 / 15.0f) - 1.0f) * v18);
		v13 = v13 + (float)((float)((float)((float)v17 / 15.0f) - 0.5f) * 0.35f);
	}
	v19 = this->levelSource->getData(x, y, z);
	this->tesselateCrossTexture(tile, v19, v11, v12, v13);
	return 1;
}
void TileRenderer::tesselateCrossTexture(Tile* tile, int32_t d, float a4, float a5, float a6) {
	const TextureUVCoordinateSet* v7; // r0
	float maxX;					// s16
	float minY;					// r11
	float maxY;					// s17
	float minX;					// s18

	if(this->hasUVCoords) {
		v7 = &this->field_8;
	} else {
		v7 = tile->getTexture(0, d);
	}
	maxX = v7->maxX;
	minY = v7->minY;
	maxY = v7->maxY;
	minX = v7->minX;
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.45f, v7->minX, minY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.45f, minX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.45f, maxX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.45f, maxX, minY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.45f, minX, minY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.45f, minX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.45f, maxX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.45f, maxX, minY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.45f, minX, minY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.45f, minX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.45f, maxX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.45f, maxX, minY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.45f, minX, minY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) + 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.45f, minX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.45f, maxX, maxY);
	Tesselator::instance.vertexUV((float)(a4 + 0.5f) - 0.45f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.45f, maxX, minY);
}
bool_t TileRenderer::tesselateDoorInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	float v9;						   // s20
	float v10;						   // s15
	const TextureUVCoordinateSet* v11; // r0
	float v12;						   // s15
	const TextureUVCoordinateSet* v13; // r0
	float v14;						   // s14
	const TextureUVCoordinateSet* v15; // r0
	float v16;						   // s15
	float v17;						   // s15
	const TextureUVCoordinateSet* v18; // r0
	float v19;						   // r0
	const TextureUVCoordinateSet* v20; // r0
	TextureUVCoordinateSet v22;		   // [sp+4h] [bp-64h]

	v9 = tile->getBrightness(this->levelSource, x, y, z);
	v10 = tile->getBrightness(this->levelSource, x, y - 1, z);
	if(tile->minY > 0.0f) {
		v10 = v9;
	}
	if(Tile::lightEmission[tile->blockID] > 0) {
		v10 = 1.0f;
	}
	Tesselator::instance.color((float)(v10 * 0.5f), v10 * 0.5f, v10 * 0.5f);
	v11 = tile->getTexture(this->levelSource, x, y, z, 0);
	this->renderFaceDown(tile, (float)x, (float)y, (float)z, *v11);
	v12 = tile->getBrightness(this->levelSource, x, y + 1, z);
	if(tile->maxY < 1.0f) {
		v12 = v9;
	}
	if(Tile::lightEmission[tile->blockID] > 0) {
		v12 = 1.0f;
	}
	Tesselator::instance.color(v12, v12, v12);
	v13 = tile->getTexture(this->levelSource, x, y, z, 1);
	this->renderFaceUp(tile, (float)x, (float)y, (float)z, *v13);
	v14 = tile->getBrightness(this->levelSource, x, y, z - 1);
	if(tile->minZ > 0.0f) {
		v14 = v9;
	}
	if(Tile::lightEmission[tile->blockID] > 0) {
		v14 = 1.0f;
	}
	Tesselator::instance.color((float)(v14 * 0.8f), v14 * 0.8f, v14 * 0.8f);
	v15 = tile->getTexture(this->levelSource, x, y, z, 2);
	this->renderNorth(tile, (float)x, (float)y, (float)z, *v15);
	this->field_21 = 0;
	v16 = tile->getBrightness(this->levelSource, x, y, z + 1);
	if(tile->maxZ < 1.0f) {
		v16 = v9;
	}
	if(Tile::lightEmission[tile->blockID] > 0) {
		v16 = 1.0f;
	}
	Tesselator::instance.color((float)(v16 * 0.8f), v16 * 0.8f, v16 * 0.8f);
	v22 = *tile->getTexture(this->levelSource, x, y, z, 3);
	this->renderSouth(tile, (float)x, (float)y, (float)z, v22);
	this->field_21 = 0;
	v17 = tile->getBrightness(this->levelSource, x - 1, y, z);
	if(tile->minX > 0.0f) {
		v17 = v9;
	}
	if(Tile::lightEmission[tile->blockID] > 0) {
		v17 = 1.0f;
	}
	Tesselator::instance.color((float)(v17 * 0.6f), v17 * 0.6f, v17 * 0.6f);
	v18 = tile->getTexture(this->levelSource, x, y, z, 4);
	this->renderWest(tile, (float)x, (float)y, (float)z, *v18);
	this->field_21 = 0;
	v19 = tile->getBrightness(this->levelSource, x + 1, y, z);
	if(tile->maxX >= 1.0f) {
		v9 = v19;
	}
	if(Tile::lightEmission[tile->blockID] > 0) {
		v9 = 1.0f;
	}
	Tesselator::instance.color((float)(v9 * 0.6f), v9 * 0.6f, v9 * 0.6f);
	v20 = tile->getTexture(this->levelSource, x, y, z, 5);
	this->renderEast(tile, (float)x, (float)y, (float)z, *v20);
	this->field_21 = 0;
	return 1;
}
bool_t TileRenderer::tesselateFenceGateInWorld(FenceGateTile* tile, int32_t x, int32_t y, int32_t z) {
	char v9;	 // r0
	int32_t v11; // r10
	Tile* v13;	 // r0
	float v15;	 // r1
	float v16;	 // r3
	float v19;	 // [sp+0h] [bp-58h]
	float v20;	 // [sp+4h] [bp-54h]
	float v21;	 // [sp+8h] [bp-50h]
	int32_t v22; // [sp+14h] [bp-44h]

	v9 = this->levelSource->getData(x, y, z);
	v11 = v9 & 3;
	v22 = v9 & 4;
	if(v11 == 3 || v11 == 1) {
		tile->setShape(0.4375f, 0.3125f, 0.0f, 0.5625f, 1.0f, 0.125f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.4375f, 0.3125f, 0.875f, 0.5625f, 1.0f, 1.0f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		if(!v22) {
			if(v11 == 3 || v11 == 1) {
				tile->setShape(0.4375f, 0.375f, 0.375f, 0.5625f, 0.9375f, 0.5f);
				this->tesselateBlockInWorld((Tile*)tile, x, y, z);
				tile->setShape(0.4375f, 0.375f, 0.5f, 0.5625f, 0.9375f, 0.625f);
				this->tesselateBlockInWorld((Tile*)tile, x, y, z);
				tile->setShape(0.4375f, 0.375f, 0.625f, 0.5625f, 0.5625f, 0.875f);
				this->tesselateBlockInWorld((Tile*)tile, x, y, z);
				tile->setShape(0.4375f, 0.75f, 0.625f, 0.5625f, 0.9375f, 0.875f);
				this->tesselateBlockInWorld((Tile*)tile, x, y, z);
				tile->setShape(0.4375f, 0.375f, 0.125f, 0.5625f, 0.5625f, 0.375f);
				this->tesselateBlockInWorld((Tile*)tile, x, y, z);
				tile->setShape(0.4375f, 0.75f, 0.125f, 0.5625f, 0.9375f, 0.375f);
LABEL_21:
				this->tesselateBlockInWorld((Tile*)tile, x, y, z);
				goto LABEL_22;
			}
LABEL_10:
			tile->setShape(0.375f, 0.375f, 0.4375f, 0.5f, 0.9375f, 0.5625f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.5f, 0.375f, 0.4375f, 0.625f, 0.9375f, 0.5625f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.625f, 0.375f, 0.4375f, 0.875f, 0.5625f, 0.5625f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.625f, 0.75f, 0.4375f, 0.875f, 0.9375f, 0.5625f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.125f, 0.375f, 0.4375f, 0.375f, 0.5625f, 0.5625f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.125f, 0.75f, 0.4375f, 0.375f, 0.9375f, 0.5625f);
			goto LABEL_21;
		}
		if(v11 == 3) {
			tile->setShape(0.8125f, 0.375f, 0.0f, 0.9375f, 0.9375f, 0.125f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.8125f, 0.375f, 0.875f, 0.9375f, 0.9375f, 1.0f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.5625f, 0.375f, 0.0f, 0.8125f, 0.5625f, 0.125f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.5625f, 0.375f, 0.875f, 0.8125f, 0.5625f, 1.0f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.5625f, 0.75f, 0.0f, 0.8125f, 0.9375f, 0.125f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			v19 = 0.8125f;
			v21 = 1.0f;
			v20 = 0.9375f;
			v13 = (Tile*)tile;
			v15 = 0.5625f;
LABEL_15:
			v16 = 0.875f;
LABEL_20:
			v13->setShape(v15, 0.75f, v16, v19, v20, v21);
			goto LABEL_21;
		}
		if(v11 == 1) {
			tile->setShape(0.0625f, 0.375f, 0.0f, 0.1875f, 0.9375f, 0.125f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.0625f, 0.375f, 0.875f, 0.1875f, 0.9375f, 1.0f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.1875f, 0.375f, 0.0f, 0.4375f, 0.5625f, 0.125f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.1875f, 0.375f, 0.875f, 0.4375f, 0.5625f, 1.0f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			tile->setShape(0.1875f, 0.75f, 0.0f, 0.4375f, 0.9375f, 0.125f);
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
			v19 = 0.4375f;
			v20 = 0.9375f;
			v21 = 1.0f;
			v13 = (Tile*)tile;
			v15 = 0.1875f;
			goto LABEL_15;
		}
	} else {
		tile->setShape(0.0f, 0.3125f, 0.4375f, 0.125f, 1.0f, 0.5625f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.875f, 0.3125f, 0.4375f, 1.0f, 1.0f, 0.5625f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		if(!v22) {
			goto LABEL_10;
		}
	}

	if(!v11) {
		tile->setShape(0.0f, 0.375f, 0.8125f, 0.125f, 0.9375f, 0.9375f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.875f, 0.375f, 0.8125f, 1.0f, 0.9375f, 0.9375f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.0f, 0.375f, 0.5625f, 0.125f, 0.5625f, 0.8125f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.875f, 0.375f, 0.5625f, 1.0f, 0.5625f, 0.8125f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.0f, 0.75f, 0.5625f, 0.125f, 0.9375f, 0.8125f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.875f, 0.75f, 0.5625f, 1.0f, 0.9375f, 0.8125f);
		goto LABEL_21;
	}
	if(v11 == 2) {
		tile->setShape(0.0f, 0.375f, 0.0625f, 0.125f, 0.9375f, 0.1875f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.875f, 0.375f, 0.0625f, 1.0f, 0.9375f, 0.1875f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.0f, 0.375f, 0.1875f, 0.125f, 0.5625f, 0.4375f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.875f, 0.375f, 0.1875f, 1.0f, 0.5625f, 0.4375f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		tile->setShape(0.0f, 0.75f, 0.1875f, 0.125f, 0.9375f, 0.4375f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		v15 = 0.875f;
		v19 = 1.0f;
		v20 = 0.9375f;
		v13 = (Tile*)tile;
		v21 = 0.4375f;
		v16 = 0.1875f;
		goto LABEL_20;
	}
LABEL_22:
	tile->setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	return 1;
}
bool_t TileRenderer::tesselateFenceInWorld(FenceTile* tile, int32_t x, int32_t y, int32_t z) {
	bool_t v9;	 // r10
	bool_t v10;	 // r0
	int32_t v11; // r9
	int32_t v12; // r11
	float v13;	 // s14
	float v14;	 // s17
	float v15;	 // s18
	float v16;	 // r10
	bool_t v18;	 // [sp+14h] [bp-44h]
	bool_t v19;	 // [sp+1Ch] [bp-3Ch]

	tile->setShape(0.375f, 0.0f, 0.375f, 0.625f, 1.0f, 0.625f);
	this->tesselateBlockInWorld((Tile*)tile, x, y, z);
	v18 = tile->connectsTo((Level*)this->levelSource, x - 1, y, z);
	v19 = tile->connectsTo((Level*)this->levelSource, x + 1, y, z);
	v9 = tile->connectsTo((Level*)this->levelSource, x, y, z - 1);
	v10 = tile->connectsTo((Level*)this->levelSource, x, y, z + 1);
	v11 = v19;
	if(v18) {
		v11 = 1;
	}
	v12 = v9 || v10;
	if(!v11) {
		v11 = (uint8_t)v12 ^ 1;
	}
	if(v18) {
		v13 = 0.0f;
	} else {
		v13 = 0.4375f;
	}
	v14 = 1.0f;
	if(v19) {
		v15 = 1.0f;
	} else {
		v15 = 0.5625f;
	}
	if(v9) {
		v16 = 0.0f;
	} else {
		v16 = 0.4375f;
	}
	if(!v10) {
		v14 = 0.5625f;
	}
	if(v11) {
		tile->setShape(v13, 0.75f, 0.4375f, v15, 0.9375f, 0.5625f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
	}
	if(v12) {
		tile->setShape(0.4375f, 0.75f, v16, 0.5625f, 0.9375f, v14);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
	}
	if(v11) {
		tile->setShape(v13, 0.375f, 0.4375f, v15, 0.5625f, 0.5625f);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
	}
	if(v12) {
		tile->setShape(0.4375f, 0.375f, v16, 0.5625f, 0.5625f, v14);
		this->tesselateBlockInWorld((Tile*)tile, x, y, z);
	}
	tile->setShape(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	return 1;
}
bool_t TileRenderer::tesselateFireInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	const TextureUVCoordinateSet* v9;	 // r9
	const TextureUVCoordinateSet* v10; // r0
	float minX;					 // r5
	float minY;					 // s17
	float maxX;					 // s16
	float maxY;					 // s18
	const TextureUVCoordinateSet* v15; // r8
	float v16;					 // r3
	float v17;					 // s20
	float v18;					 // s20
	float v19;					 // s21
	float v20;					 // s20
	float v21;					 // s20
	int32_t v22;				 // s19
	float v23;					 // r5
	float v24;					 // s21
	float v25;					 // r10
	float v26;					 // r11
	float v27;					 // r7
	float v28;					 // s23
	float v29;					 // s23
	float v30;					 // s19
	float v31;					 // s20
	float v32;					 // s18
	float v33;					 // s23
	float v34;					 // s21
	float v35;					 // r7
	float v36;					 // r9
	float v37;					 // r6
	float v38;					 // r5
	float v39;					 // s21
	float v40;					 // s19
	float v41;					 // s17
	float v42;					 // s19
	float v43;					 // r7
	float v44;					 // r9
	float v45;					 // r6
	float v46;					 // r5
	float v47;					 // s20
	float v48;					 // s24
	float v49;					 // s21
	float v50;					 // s19
	float v51;					 // r11
	float v52;					 // r6
	float v53;					 // s19
	float v54;					 // s25
	float v55;					 // r7
	float v56;					 // r10
	float v57;					 // s19
	float v58;					 // s16
	float v59;					 // s18
	float v60;					 // s17
	float v61;					 // r8
	float v62;					 // r5
	float v63;					 // s26
	float v64;					 // s27
	float v65;					 // r1
	float v66;					 // s25
	float v67;					 // s21
	float v68;					 // s23
	float v69;					 // s24
	float v70;					 // s22
	float v71;					 // s20
	float v72;					 // r10
	float v73;					 // r11
	float v74;					 // s16
	float v75;					 // r9

	v9 = tile->getTexture(0);
	v10 = tile->getTexture(1);
	minX = v9->minX;
	minY = v9->minY;
	maxX = v9->maxX;
	maxY = v9->maxY;
	v15 = v10;
	Tesselator::instance.color(Color4::WHITE.r, Color4::WHITE.g, Color4::WHITE.b, Color4::WHITE.a);

	if(this->levelSource->isSolidBlockingTile(x, y - 1, z) || ((FireTile*)Tile::fire)->canBurn(this->levelSource, x, y - 1, z)) {
		v47 = (float)z + 0.5f;
		v48 = (float)x;
		v49 = (float)x + 0.5f;
		v50 = (float)y;
		v51 = (float)z + 1.0f;
		v52 = v50 + 1.4f;
		Tesselator::instance.vertexUV(v49 - 0.3f, v50 + 1.4f, v51, maxX, minY);
		v53 = v50 + 0.0f;
		Tesselator::instance.vertexUV(v49 + 0.2f, v53, v51, maxX, maxY);
		v54 = (float)z + 0.0f;
		v55 = v53;
		Tesselator::instance.vertexUV(v49 + 0.2f, v53, v54, minX, maxY);
		v56 = v54;
		Tesselator::instance.vertexUV(v49 - 0.3f, v52, v54, minX, minY);
		Tesselator::instance.vertexUV(v49 + 0.3f, v52, v54, maxX, minY);
		Tesselator::instance.vertexUV(v49 - 0.2f, v53, v54, maxX, maxY);
		Tesselator::instance.vertexUV(v49 - 0.2f, v53, v51, minX, maxY);
		Tesselator::instance.vertexUV(v49 + 0.3f, v52, v51, minX, minY);
		v57 = v15->minX;
		v58 = v15->minY;
		v59 = v15->maxY;
		v60 = v15->maxX;
		Tesselator::instance.vertexUV(v48 + 1.0f, v52, v47 + 0.3f, v60, v58);
		v61 = v48 + 1.0f;
		Tesselator::instance.vertexUV(v48 + 1.0f, v55, v47 - 0.2f, v60, v59);
		Tesselator::instance.vertexUV(v48 + 0.0f, v55, v47 - 0.2f, v57, v59);
		v62 = v48 + 0.0f;
		Tesselator::instance.vertexUV(v48 + 0.0f, v52, v47 + 0.3f, v57, v58);
		Tesselator::instance.vertexUV(v48 + 0.0f, v52, v47 - 0.3f, v60, v58);
		Tesselator::instance.vertexUV(v48 + 0.0f, v55, v47 + 0.2f, v60, v59);
		Tesselator::instance.vertexUV(v48 + 1.0f, v55, v47 + 0.2f, v57, v59);
		Tesselator::instance.vertexUV(v48 + 1.0f, v52, v47 - 0.3f, v57, v58);
		v63 = v49 - 0.4f;
		v64 = v49 - 0.5f;
		v65 = v49 - 0.4f;
		v66 = v49 + 0.5f;
		v67 = v49 + 0.4f;
		v68 = v47 - 0.4f;
		v69 = v47 - 0.5f;
		v70 = v47 + 0.5f;
		v71 = v47 + 0.4f;
		Tesselator::instance.vertexUV(v65, v52, (float)z + 0.0f, v57, v58);
		Tesselator::instance.vertexUV(v64, v55, v56, v57, v59);
		Tesselator::instance.vertexUV(v64, v55, v51, v60, v59);
		Tesselator::instance.vertexUV(v63, v52, v51, v60, v58);
		Tesselator::instance.vertexUV(v67, v52, v51, v57, v58);
		Tesselator::instance.vertexUV(v66, v55, v51, v57, v59);
		Tesselator::instance.vertexUV(v66, v55, v56, v60, v59);
		Tesselator::instance.vertexUV(v67, v52, v56, v60, v58);
		v72 = v9->minY;
		v73 = v9->maxX;
		v74 = v9->minX;
		v75 = v9->maxY;
		Tesselator::instance.vertexUV(v62, v52, v71, v74, v72);
		Tesselator::instance.vertexUV(v62, v55, v70, v74, v75);
		Tesselator::instance.vertexUV(v61, v55, v70, v73, v75);
		Tesselator::instance.vertexUV(v61, v52, v71, v73, v72);
		Tesselator::instance.vertexUV(v61, v52, v68, v74, v72);
		Tesselator::instance.vertexUV(v61, v55, v69, v74, v75);
		Tesselator::instance.vertexUV(v62, v55, v69, v73, v75);
		Tesselator::instance.vertexUV(v62, v52, v68, v73, v72);
	} else {
		if((((int8_t)x + (int8_t)y + (int8_t)z) & 1) != 0) {
			minX = v15->minX;
			minY = v15->minY;
			maxX = v15->maxX;
			maxY = v15->maxY;
		}
		if(((y / 2 + x / 2 + z / 2) & 1) != 0) {
			v16 = minX;
			minX = maxX;
			maxX = v16;
		}
		if(((FireTile*)Tile::fire)->canBurn(this->levelSource, x - 1, y, z)) {
			v17 = (float)z + 1.0f;
			Tesselator::instance.vertexUV((float)x + 0.2f, (float)((float)y + 1.4f) + 0.0625f, v17, maxX, minY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, v17, maxX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, (float)z + 0.0f, minX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.2f, (float)((float)y + 1.4f) + 0.0625f, (float)z + 0.0f, minX, minY);
			Tesselator::instance.vertexUV((float)x + 0.2f, (float)((float)y + 1.4f) + 0.0625f, (float)z + 0.0f, minX, minY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, (float)z + 0.0f, minX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, v17, maxX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.2f, (float)((float)y + 1.4f) + 0.0625f, v17, maxX, minY);
		}
		if(((FireTile*)Tile::fire)->canBurn(this->levelSource, x + 1, y, z)) {
			v18 = (float)x + 1.0f;
			v19 = (float)z + 0.0f;
			Tesselator::instance.vertexUV(v18 - 0.2f, (float)((float)y + 1.4f) + 0.0625f, v19, minX, minY);
			Tesselator::instance.vertexUV(v18, (float)y + 0.0625f, v19, minX, maxY);
			Tesselator::instance.vertexUV(v18, (float)y + 0.0625f, (float)z + 1.0f, maxX, maxY);
			Tesselator::instance.vertexUV(v18 - 0.2f, (float)((float)y + 1.4f) + 0.0625f, (float)z + 1.0f, maxX, minY);
			Tesselator::instance.vertexUV(v18 - 0.2f, (float)((float)y + 1.4f) + 0.0625f, (float)z + 1.0f, maxX, minY);
			Tesselator::instance.vertexUV(v18, (float)y + 0.0625f, (float)z + 1.0f, maxX, maxY);
			Tesselator::instance.vertexUV(v18, (float)y + 0.0625f, v19, minX, maxY);
			Tesselator::instance.vertexUV(v18 - 0.2f, (float)((float)y + 1.4f) + 0.0625f, v19, minX, minY);
		}
		if(((FireTile*)Tile::fire)->canBurn(this->levelSource, x, y, z - 1)) {
			v20 = (float)z + 0.2f;
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)((float)y + 1.4f) + 0.0625f, v20, maxX, minY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, (float)z + 0.0f, maxX, maxY);
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)y + 0.0625f, (float)z + 0.0f, minX, maxY);
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)((float)y + 1.4f) + 0.0625f, v20, minX, minY);
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)((float)y + 1.4f) + 0.0625f, v20, minX, minY);
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)y + 0.0625f, (float)z + 0.0f, minX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, (float)z + 0.0f, maxX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)((float)y + 1.4f) + 0.0625f, v20, maxX, minY);
		}
		if(((FireTile*)Tile::fire)->canBurn(this->levelSource, x, y, z + 1)) {
			v21 = (float)z + 1.0f;
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)((float)y + 1.4f) + 0.0625f, v21 - 0.2f, minX, minY);
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)y + 0.0625f, v21, minX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, v21, maxX, maxY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)((float)y + 1.4f) + 0.0625f, v21 - 0.2f, maxX, minY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)((float)y + 1.4f) + 0.0625f, v21 - 0.2f, maxX, minY);
			Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + 0.0625f, v21, maxX, maxY);
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)y + 0.0625f, v21, minX, maxY);
			Tesselator::instance.vertexUV((float)x + 1.0f, (float)((float)y + 1.4f) + 0.0625f, v21 - 0.2f, minX, minY);
		}
		v22 = y + 1;
		if(((FireTile*)Tile::fire)->canBurn(this->levelSource, x, y + 1, z)) {
			v23 = v9->minX;
			v24 = (float)z;
			v25 = v9->minY;
			v26 = v9->maxX;
			v27 = v9->maxY;
			v28 = (float)x;
			if((((int8_t)x + (int8_t)v22 + (int8_t)z) & 1) != 0) {
				v39 = v24 + 0.5f;
				v40 = (float)v22;
				v41 = v40 - 0.2f;
				Tesselator::instance.vertexUV(v28 + 0.0f, v40 - 0.2f, v39 + 0.5f, v9->maxX, v25);
				v42 = v40 + 0.0f;
				Tesselator::instance.vertexUV(v28 + 0.0f, v42, v39 - 0.5f, v26, v27);
				Tesselator::instance.vertexUV(v28 + 1.0f, v42, v39 - 0.5f, v23, v27);
				Tesselator::instance.vertexUV(v28 + 1.0f, v41, v39 + 0.5f, v23, v25);
				v43 = v15->minY;
				v44 = v15->maxX;
				v45 = v15->maxY;
				v46 = v15->minX;
				Tesselator::instance.vertexUV(v28 + 1.0f, v41, v39 - 0.5f, v44, v43);
				Tesselator::instance.vertexUV(v28 + 1.0f, v42, v39 + 0.5f, v44, v45);
				Tesselator::instance.vertexUV(v28 + 0.0f, v42, v39 + 0.5f, v46, v45);
				Tesselator::instance.vertexUV(v28 + 0.0f, v41, v39 - 0.5f, v46, v43);
			} else {
				v29 = v28 + 0.5f;
				v30 = (float)v22;
				v31 = v29 + 0.5f;
				v32 = v24 + 0.0f;
				v33 = v29 - 0.5f;
				Tesselator::instance.vertexUV(v33, v30 - 0.2f, v24 + 0.0f, v9->maxX, v25);
				Tesselator::instance.vertexUV(v31, v30 + 0.0f, v24 + 0.0f, v26, v27);
				v34 = v24 + 1.0f;
				Tesselator::instance.vertexUV(v31, v30 + 0.0f, v34, v23, v27);
				Tesselator::instance.vertexUV(v33, v30 - 0.2f, v34, v23, v25);
				v35 = v15->minY;
				v36 = v15->maxX;
				v37 = v15->maxY;
				v38 = v15->minX;
				Tesselator::instance.vertexUV(v31, v30 - 0.2f, v34, v36, v35);
				Tesselator::instance.vertexUV(v33, v30 + 0.0f, v34, v36, v37);
				Tesselator::instance.vertexUV(v33, v30 + 0.0f, v32, v38, v37);
				Tesselator::instance.vertexUV(v31, v30 - 0.2f, v32, v38, v35);
			}
		}
	}
	return 1;
}
bool_t TileRenderer::tesselateInWorld(Tile* a2, int32_t a3, int32_t a4, int32_t a5) {
	int32_t v9; // r9

	v9 = a2->getRenderShape();
	a2->updateShape(this->levelSource, a3, a4, a5);
	switch(v9) {
		case 0:
			return this->tesselateBlockInWorld(a2, a3, a4, a5);
		case 4:
			return this->tesselateWaterInWorld(a2, a3, a4, a5);
		case 13:
			return this->tesselateCactusInWorld(a2, a3, a4, a5);
		case 1:
			return this->tesselateCrossInWorld(a2, a3, a4, a5);
		case 19:
			return this->tesselateStemInWorld(a2, a3, a4, a5);
		case 6:
			return this->tesselateRowInWorld(a2, a3, a4, a5);
		case 2:
			return this->tesselateTorchInWorld(a2, a3, a4, a5);
		case 3:
			return this->tesselateFireInWorld(a2, a3, a4, a5);
		case 8:
			return this->tesselateLadderInWorld(a2, a3, a4, a5);
		case 7:
			return this->tesselateDoorInWorld(a2, a3, a4, a5);
		case 9:
			return this->tesselateRailInWorld((BaseRailTile*)a2, a3, a4, a5);
		case 10:
			return this->tesselateStairsInWorld((StairTile*)a2, a3, a4, a5);
		case 11:
			return this->tesselateFenceInWorld((FenceTile*)a2, a3, a4, a5);
		case 21:
			return this->tesselateFenceGateInWorld((FenceGateTile*)a2, a3, a4, a5);
		case 32:
			return this->tesselateWallInWorld((WallTile*)a2, a3, a4, a5);
		case 18:
			return this->tesselateThinFenceInWorld((ThinFenceTile*)a2, a3, a4, a5);
		case 31:
			return this->tesselateTreeInWorld(a2, a3, a4, a5);
		case 14:
			return this->tesselateBedInWorld(a2, a3, a4, a5);
	}
	return 0;
}
bool_t TileRenderer::tesselateInWorld(Tile* a2, int32_t a3, int32_t a4, int32_t a5, const struct TextureUVCoordinateSet& a6) {
	this->hasUVCoords = 1;
	this->field_8 = a6;
	bool_t result = this->tesselateInWorld(a2, a3, a4, a5);
	this->hasUVCoords = 0;
	return result;
}
bool_t TileRenderer::tesselateInWorldNoCulling(Tile* a2, int32_t a3, int32_t a4, int32_t a5) {
	this->disableCulling = 1;
	bool_t result = this->tesselateInWorld(a2, a3, a4, a5);
	this->disableCulling = 0;
	return result;
}
bool_t TileRenderer::tesselateLadderInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	const TextureUVCoordinateSet* v9; // r9
	float v10;					// r0
	float minX;					// r11
	float maxX;					// r8
	float minY;					// r7
	float maxY;					// r9
	int32_t v15;				// r0
	float v16;					// s16
	float v17;					// s18
	float v18;					// s17
	int32_t v19;				// s15
	int32_t v20;				// r5
	float v21;					// r1
	float v22;					// r2
	float v23;					// r3
	int32_t v24;				// s15
	int32_t v25;				// r5
	float v26;					// s17
	float v27;					// s16
	float v28;					// s18
	float v30;					// [sp+0h] [bp-48h]
	float v31;					// [sp+4h] [bp-44h]

	if(this->hasUVCoords) {
		v9 = &this->field_8;
	} else {
		v9 = tile->getTexture(0);
	}
	v10 = tile->getBrightness(this->levelSource, x, y, z);
	Tesselator::instance.color(v10, v10, v10);
	minX = v9->minX;
	maxX = v9->maxX;
	minY = v9->minY;
	maxY = v9->maxY;
	v15 = this->levelSource->getData(x, y, z);
	switch(v15) {
		case 5:
			v16 = (float)x + 0.05f;
			v17 = (float)(y + 1) + 0.0f;
			Tesselator::instance.vertexUV(v16, v17, (float)(z + 1) + 0.0f, minX, minY);
			Tesselator::instance.vertexUV(v16, (float)y, (float)(z + 1) + 0.0f, minX, maxY);
			v18 = (float)z;
			Tesselator::instance.vertexUV(v16, (float)y, (float)z, maxX, maxY);
			v30 = maxX;
			v31 = minY;
LABEL_8:
			v21 = v16;
			v22 = v17;
			v23 = v18;
LABEL_14:
			Tesselator::instance.vertexUV(v21, v22, v23, v30, v31);
			return 1;
		case 4:
			v16 = (float)(x + 1) - 0.05f;
			v19 = y;
			v20 = y + 1;
			v17 = (float)v19;
			Tesselator::instance.vertexUV(v16, (float)v19, (float)(z + 1) + 0.0f, maxX, maxY);
			Tesselator::instance.vertexUV(v16, (float)v20 + 0.0f, (float)(z + 1) + 0.0f, maxX, minY);
			v18 = (float)z;
			Tesselator::instance.vertexUV(v16, (float)v20 + 0.0f, (float)z, minX, minY);
			v30 = minX;
			v31 = maxY;
			goto LABEL_8;
		case 3:
			v24 = y;
			v25 = y + 1;
			v26 = (float)v24;
			v27 = (float)z + 0.05f;
			Tesselator::instance.vertexUV((float)(x + 1) + 0.0f, (float)v24, v27, maxX, maxY);
			Tesselator::instance.vertexUV((float)(x + 1) + 0.0f, (float)v25 + 0.0f, v27, maxX, minY);
			v28 = (float)x;
			Tesselator::instance.vertexUV((float)x, (float)v25 + 0.0f, v27, minX, minY);
			v30 = minX;
			v31 = maxY;
LABEL_13:
			v21 = v28;
			v22 = v26;
			v23 = v27;
			goto LABEL_14;
		case 2:
			v26 = (float)(y + 1) + 0.0f;
			v27 = (float)(z + 1) - 0.05f;
			Tesselator::instance.vertexUV((float)(x + 1) + 0.0f, v26, v27, minX, minY);
			Tesselator::instance.vertexUV((float)(x + 1) + 0.0f, (float)y, v27, minX, maxY);
			v28 = (float)x;
			Tesselator::instance.vertexUV((float)x, (float)y, v27, maxX, maxY);
			v30 = maxX;
			v31 = minY;
			goto LABEL_13;
	}
	return 1;
}
bool_t TileRenderer::tesselateRailInWorld(BaseRailTile* tile, int32_t x, int32_t y, int32_t z) {
	int32_t v9;					 // r5
	TextureUVCoordinateSet* v10; // r0
	float* p_width;				 // r6
	float width;				 // r0
	float v13;					 // r0
	float v14;					 // s18
	float v15;					 // s20
	float v16;					 // s17
	float v17;					 // s16
	float v18;					 // s19
	float v19;					 // r4
	bool_t v20;					 // zf
	float v21;					 // r9
	float v22;					 // r7
	float v23;					 // r6
	float v24;					 // s21
	TextureUVCoordinateSet v26;	 // [sp+8h] [bp-68h]

	v9 = this->levelSource->getData(x, y, z);
	v26 = *tile->getTexture(0, v9);
	if ( this->hasUVCoords )
	{
		v26 = this->field_8;
	}
	if(tile->isUsesDataBit()) {
		v9 &= 7u;
	}
	v13 = tile->getBrightness(this->levelSource, x, y, z);
	Tesselator::instance.color(v13, v13, v13);
	v14 = (float)x + 1.0f;
	v15 = (float)y + 0.0625f;
	v16 = (float)x + 0.0f;
	v17 = (float)z + 0.0f;
	v18 = (float)z + 1.0f;
	if((uint32_t)(v9 - 1) <= 2) {
		v22 = (float)x + 1.0f;
		v20 = v9 == 2;
		v23 = (float)x + 0.0f;
		v19 = (float)z + 0.0f;
		v21 = v19;
		v17 = (float)z + 1.0f;
	} else {
		switch(v9) {
			case 7:
				v19 = (float)z + 0.0f;
				v21 = v19;
				v22 = (float)x + 1.0f;
				v17 = (float)z + 1.0f;
				v23 = (float)x + 0.0f;
				goto LABEL_17;
			case 8:
				v21 = (float)z + 0.0f;
				v22 = (float)x + 1.0f;
				v19 = (float)z + 1.0f;
				v17 = v19;
				v23 = (float)x + 0.0f;
				v14 = v23;
				v18 = v21;
				v16 = v22;
				goto LABEL_17;
			case 9:
				v23 = (float)x + 1.0f;
				v19 = (float)z + 1.0f;
				v21 = v19;
				v22 = (float)x + 0.0f;
				v14 = v22;
				v18 = (float)z + 0.0f;
				v16 = v23;
				goto LABEL_17;
		}
		v19 = (float)z + 0.0f;
		v20 = v9 == 4;
		v21 = (float)z + 1.0f;
		v22 = (float)x + 0.0f;
		v23 = (float)x + 1.0f;
	}
	if(!v20) {
		if(v9 == 3 || v9 == 5) {
			v24 = v15 + 1.0f;
			goto LABEL_21;
		}
LABEL_17:
		v24 = v15;
		goto LABEL_21;
	}
	v24 = v15;
	v15 = v15 + 1.0f;
LABEL_21:
	Tesselator::instance.vertexUV(v14, v15, v17, v26.maxX, v26.minY);
	Tesselator::instance.vertexUV(v23, v24, v18, v26.maxX, v26.maxY);
	Tesselator::instance.vertexUV(v16, v24, v21, v26.minX, v26.maxY);
	Tesselator::instance.vertexUV(v22, v15, v19, v26.minX, v26.minY);
	Tesselator::instance.vertexUV(v22, v15, v19, v26.minX, v26.minY);
	Tesselator::instance.vertexUV(v16, v24, v21, v26.minX, v26.maxY);
	Tesselator::instance.vertexUV(v23, v24, v18, v26.maxX, v26.maxY);
	Tesselator::instance.vertexUV(v14, v15, v17, v26.maxX, v26.minY);
	return 1;
}
bool_t TileRenderer::tesselateRowInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	float v9;	 // r0
	int32_t v10; // r0

	v9 = tile->getBrightness(this->levelSource, x, y, z);
	Tesselator::instance.color(v9, v9, v9);
	v10 = this->levelSource->getData(x, y, z);
	this->tesselateRowTexture(tile, v10, (float)x, (float)y - 0.0625f, (float)z);
	return 1;
}
void TileRenderer::tesselateRowTexture(Tile* tile, int32_t a3, float a4, float a5, float a6) {
	const TextureUVCoordinateSet* v7; // r0
	float minY;					// r7
	float maxX;					// s16
	float maxY;					// s17
	float minX;					// s18
	float v12;					// s22

	if(this->hasUVCoords) {
		v7 = &this->field_8;
	} else {
		v7 = tile->getTexture(0, a3);
	}
	minY = v7->minY;
	maxX = v7->maxX;
	maxY = v7->maxY;
	minX = v7->minX;
	v12 = a4 + 0.5f;
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.5f, v7->minX, minY);
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.5f, minX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.5f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.5f, maxX, minY);
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.5f, minX, minY);
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.5f, minX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.5f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.5f, maxX, minY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.5f, minX, minY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.5f, minX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.5f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.5f, maxX, minY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.5f, minX, minY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.5f, minX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.5f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.25f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.5f, maxX, minY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.25f, minX, minY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.25f, minX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.25f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.25f, maxX, minY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.25f, minX, minY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.25f, minX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) - 0.25f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) - 0.25f, maxX, minY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.25f, minX, minY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.25f, minX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.25f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.25f, maxX, minY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.25f, minX, minY);
	Tesselator::instance.vertexUV(v12 - 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.25f, minX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 0.0f, (float)(a6 + 0.5f) + 0.25f, maxX, maxY);
	Tesselator::instance.vertexUV(v12 + 0.5f, a5 + 1.0f, (float)(a6 + 0.5f) + 0.25f, maxX, minY);
}
bool_t TileRenderer::tesselateStairsInWorld(StairTile* tile, int32_t x, int32_t y, int32_t z) {
	bool_t v9;
	tile->setBaseShape(this->levelSource, x, y, z);
	this->tesselateBlockInWorld(tile, x, y, z);
	v9 = tile->setStepShape(this->levelSource, x, y, z);
	this->tesselateBlockInWorld((Tile*)tile, x, y, z);
	if(v9) {
		if(tile->setInnerPieceShape(this->levelSource, x, y, z)) {
			this->tesselateBlockInWorld((Tile*)tile, x, y, z);
		}
	}
	return 1;
}
void TileRenderer::tesselateStemDirTexture(Tile* a2, int32_t a3, int32_t a4, float a5, float a6, float a7, float a8) {
	TextureUVCoordinateSet* ConnectedTexture; // r0
	float minX;								  // r5
	float maxX;								  // r6
	float minY;								  // r8
	float maxY;								  // r9
	float v14;								  // s17
	float v15;								  // s16
	float v16;								  // s19
	float v17;								  // s18
	bool v18;								  // cc
	float v19;								  // r7
	float v20;								  // s18
	float v21;								  // r1
	float v22;								  // s16
	float v23;								  // r1
	float v24;								  // r3
	float v25;								  // r2
	float v26;								  // [sp+40h] [bp+0h]
	float v27;								  // [sp+44h] [bp+4h]

	if(this->hasUVCoords) {
		ConnectedTexture = &this->field_8;
	} else {
		ConnectedTexture = ((StemTile*)a2)->getConnectedTexture();
	}
	minX = ConnectedTexture->minX;
	maxX = ConnectedTexture->maxX;
	minY = ConnectedTexture->minY;
	maxY = ConnectedTexture->maxY;
	v14 = a8 + 0.5f;
	v15 = a6 + 0.5f;
	v16 = (float)(a8 + 0.5f) - 0.5f;
	v17 = (float)(a8 + 0.5f) + 0.5f;
	if((a4 + 1) / 2 % 2 == 1) {
		minX = ConnectedTexture->maxX;
		maxX = ConnectedTexture->minX;
	}
	v18 = a4 <= 1;
	v19 = a7 + a5;
	if(v18) {
		v20 = v15 - 0.5f;
		v21 = v15 - 0.5f;
		v22 = v15 + 0.5f;
		Tesselator::instance.vertexUV(v21, v19, v14, minX, minY);
		Tesselator::instance.vertexUV(v20, a7 + 0.0f, v14, minX, maxY);
		Tesselator::instance.vertexUV(v22, a7 + 0.0f, v14, maxX, maxY);
		Tesselator::instance.vertexUV(v22, v19, v14, maxX, minY);
		Tesselator::instance.vertexUV(v22, v19, v14, maxX, minY);
		Tesselator::instance.vertexUV(v22, a7 + 0.0f, v14, maxX, maxY);
		Tesselator::instance.vertexUV(v20, a7 + 0.0f, v14, minX, maxY);
		v26 = minX;
		v27 = minY;
		v23 = v20;
		v25 = v19;
		v24 = a8 + 0.5f;
	} else {
		Tesselator::instance.vertexUV(v15, v19, v14 + 0.5f, minX, minY);
		Tesselator::instance.vertexUV(v15, a7 + 0.0f, v17, minX, maxY);
		Tesselator::instance.vertexUV(v15, a7 + 0.0f, v16, maxX, maxY);
		Tesselator::instance.vertexUV(v15, v19, v16, maxX, minY);
		Tesselator::instance.vertexUV(v15, v19, v16, maxX, minY);
		Tesselator::instance.vertexUV(v15, a7 + 0.0f, v16, maxX, maxY);
		Tesselator::instance.vertexUV(v15, a7 + 0.0f, v17, minX, maxY);
		v23 = a6 + 0.5f;
		v24 = (float)(a8 + 0.5f) + 0.5f;
		v25 = a7 + a5;
		v26 = minX;
		v27 = minY;
	}
	Tesselator::instance.vertexUV(v23, v25, v24, v26, v27);
}
bool_t TileRenderer::tesselateStemInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	float v9;			// s16
	int32_t v10;		// r0
	int32_t ConnectDir; // r9
	int32_t v12;		// r0
	int32_t v13;		// r0

	v9 = tile->getBrightness(this->levelSource, x, y, z);
	v10 = tile->getColor(this->levelSource, x, y, z);
	Tesselator::instance.color(v9 * (float)((float)((v10 & 0xff0000) >> 16) / 255.0f), v9 * (float)((float)((v10 & 0xff00) >> 8) / 255.0f), v9 * (float)((float)(v10 & 0xff) / 255.0f));
	tile->updateShape(this->levelSource, x, y, z);
	ConnectDir = ((StemTile*)tile)->getConnectDir(this->levelSource, x, y, z);
	v12 = this->levelSource->getData(x, y, z);
	if(ConnectDir < 0) {
		this->tesselateStemTexture(tile, v12, tile->maxY, (float)x, (float)y - 0.0625f, (float)z);
	} else {
		this->tesselateStemTexture(tile, v12, 0.5f, (float)x, (float)y - 0.0625f, (float)z);
		v13 = this->levelSource->getData(x, y, z);
		this->tesselateStemDirTexture(tile, v13, ConnectDir, tile->maxY, (float)x, (float)y - 0.0625f, (float)z);
	}
	return 1;
}
void TileRenderer::tesselateStemTexture(Tile* a2, int32_t a3, float a4, float a5, float a6, float a7) {
	const TextureUVCoordinateSet* v8; // r0
	float minY;					// s16
	float minX;					// r11
	float maxX;					// s18
	float v12;					// s17
	float v13;					// s20

	if(this->hasUVCoords) {
		v8 = &this->field_8;
	} else {
		v8 = a2->getTexture(0, a3);
	}
	minY = v8->minY;
	minX = v8->minX;
	maxX = v8->maxX;
	v12 = (float)(minY + (float)(a4 * (float)(v8->maxY - minY))) - 0.0001f;
	v13 = a6 + a4;
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, v13, (float)(a7 + 0.5f) - 0.45f, v8->minX, minY);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) - 0.45f, minX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) + 0.45f, maxX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, v13, (float)(a7 + 0.5f) + 0.45f, maxX, minY);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, v13, (float)(a7 + 0.5f) + 0.45f, maxX, minY);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) + 0.45f, maxX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) - 0.45f, minX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, v13, (float)(a7 + 0.5f) - 0.45f, minX, minY);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, v13, (float)(a7 + 0.5f) + 0.45f, minX, minY);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) + 0.45f, minX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) - 0.45f, maxX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, v13, (float)(a7 + 0.5f) - 0.45f, maxX, minY);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, v13, (float)(a7 + 0.5f) - 0.45f, maxX, minY);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) + 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) - 0.45f, maxX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, a6 + 0.0f, (float)(a7 + 0.5f) + 0.45f, minX, v12);
	Tesselator::instance.vertexUV((float)(a5 + 0.5f) - 0.45f, v13, (float)(a7 + 0.5f) + 0.45f, minX, minY);
}
bool_t TileRenderer::tesselateThinFenceInWorld(ThinFenceTile* tile, int32_t x, int32_t y, int32_t z) {
	float v6;	// s16
	int32_t v7; // r0
	//int32_t hasUVCoords; // r5
	//float* p_width;				 // r5
	TextureUVCoordinateSet* v10; // r7
	int32_t v11;				 // r0
	float minY;					 // r1
	float maxX;					 // r2
	float maxY;					 // r3
	float height;				 // r1
	float minX;					 // s16
	float v17;					 // s18
	float v18;					 // s19
	float v19;					 // s25
	float v20;					 // s17
	float v21;					 // s16
	float v22;					 // r8
	float v23;					 // s12
	float v24;					 // r5
	float v25;					 // r6
	float v26;					 // r7
	float v27;					 // r10
	int32_t v28;				 // r0
	int32_t v29;				 // r0
	int32_t v30;				 // r0
	int32_t v31;				 // r0
	float v32;					 // r11
	float v33;					 // r1
	float v35;					 // [sp+0h] [bp-F8h]
	float v36;					 // [sp+4h] [bp-F4h]
	float v37;					 // [sp+Ch] [bp-ECh]
	float v38;					 // [sp+10h] [bp-E8h]
	float v39;					 // [sp+14h] [bp-E4h]
	float v40;					 // [sp+18h] [bp-E0h]
	float v41;					 // [sp+1Ch] [bp-DCh]
	float v42;					 // [sp+20h] [bp-D8h]
	int32_t v46;				 // [sp+30h] [bp-C8h]
	int32_t v47;				 // [sp+34h] [bp-C4h]
	bool_t v48;					 // [sp+38h] [bp-C0h]
	bool_t v49;					 // [sp+3Ch] [bp-BCh]
	int32_t v50;				 // [sp+40h] [bp-B8h]
	int32_t v51;				 // [sp+44h] [bp-B4h]
	int32_t v52;				 // [sp+48h] [bp-B0h]
	int32_t v53;				 // [sp+4Ch] [bp-ACh]
	int32_t v54;				 // [sp+50h] [bp-A8h]
	int32_t v55;				 // [sp+54h] [bp-A4h]
	bool_t v56;					 // [sp+58h] [bp-A0h]
	bool_t v57;					 // [sp+5Ch] [bp-9Ch]
	TextureUVCoordinateSet v58;	 // [sp+60h] [bp-98h]
	float v59;					 // [sp+80h] [bp-78h]
	//int32_t v60;					 // [sp+88h] [bp-70h]
	//int32_t v61;					 // [sp+8Ch] [bp-6Ch]
	TextureUVCoordinateSet v62; // [sp+90h] [bp-68h] BYREF

	v6 = tile->getBrightness(this->levelSource, x, y, z);
	v7 = tile->getColor(this->levelSource, x, y, z);
	Tesselator::instance.color(v6 * (float)((float)((v7 & 0xff0000) >> 16) / 255.0f), v6 * (float)((float)((v7 & 0xff00) >> 8) / 255.0f), v6 * (float)((float)(v7 & 0xff) / 255.0f));
	//hasUVCoords = (unsigned __int8)this->hasUVCoords;
	if(this->hasUVCoords) {
		//p_width = &this->field_8.width;
		v58 = this->field_8;
		v10 = &this->field_8;
	} else {
		v10 = &v62;
		v11 = this->levelSource->getData(x, y, z);
		v58 = *tile->getTexture(0, v11);
		minY = tile->field_80.minY;
		maxX = tile->field_80.maxX;
		maxY = tile->field_80.maxY;
		v62.minX = tile->field_80.minX;
		v62.minY = minY;
		v62.maxX = maxX;
		v62.maxY = maxY;
		//p_width = &v62.width;
		height = tile->field_80.height;
		v62.width = tile->field_80.width;
		v62.height = height;
	}
	v59 = v10->maxX;
	minX = v10->minX;
	v17 = v10->minY;
	v18 = v10->maxY;
	//v60 = *(_DWORD*)p_width;
	//v61 = *((_DWORD*)p_width + 1);
	v19 = v58.minX + (float)((float)(v58.maxX - v58.minX) * 0.49f);
	v20 = minX + (float)((float)(v59 - minX) * 0.4375f);
	v21 = minX + (float)((float)(v59 - minX) * 0.56187f);
	v39 = (float)x;
	v22 = (float)x + 0.5f;
	v41 = (float)x + 1.0f;
	v23 = (float)((float)y + 0.001f) + 1.0f;
	v24 = (float)y + 0.001f;
	v25 = v23 - 0.002f;
	v40 = (float)z;
	v26 = (float)z + 0.5f;
	v42 = (float)z + 1.0f;
	v37 = v22 - 0.0625f;
	v38 = v22 + 0.0625f;
	v52 = z - 1;
	v27 = v26 + 0.0625f;
	v28 = this->levelSource->getTile(x, y, z - 1);
	v53 = z + 1;
	v49 = tile->attachsTo(v28);
	v29 = this->levelSource->getTile(x, y, z + 1);
	v54 = x - 1;
	v48 = tile->attachsTo(v29);
	v30 = this->levelSource->getTile(x - 1, y, z);
	v55 = x + 1;
	v57 = tile->attachsTo(v30);
	v31 = this->levelSource->getTile(x + 1, y, z);
	v46 = y + 1;
	v56 = tile->attachsTo(v31);
	v47 = y - 1;
	v50 = tile->shouldRenderFace(this->levelSource, x, y + 1, z, 1);
	v51 = tile->shouldRenderFace(this->levelSource, x, y - 1, z, 0);
	if(v57) {
		if(!v56) {
			Tesselator::instance.vertexUV(v39, v23 - 0.002f, v26, v58.minX, v58.minY);
			Tesselator::instance.vertexUV(v39, v24, v26, v58.minX, v58.maxY);
			Tesselator::instance.vertexUV(v22, v24, v26, v19, v58.maxY);
			Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v19, v58.minY);
			Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v58.minX, v58.minY);
			Tesselator::instance.vertexUV(v22, v24, v26, v58.minX, v58.maxY);
			Tesselator::instance.vertexUV(v39, v24, v26, v19, v58.maxY);
			Tesselator::instance.vertexUV(v39, v23 - 0.002f, v26, v19, v58.minY);
			if(!v48 && !v49) {
				Tesselator::instance.vertexUV(v22, v23 - 0.002f, v27, v20, v17);
				Tesselator::instance.vertexUV(v22, v24, v27, v20, v18);
				Tesselator::instance.vertexUV(v22, v24, v26 - 0.0625f, v21, v18);
				Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26 - 0.0625f, v21, v17);
				Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26 - 0.0625f, v20, v17);
				Tesselator::instance.vertexUV(v22, v24, v26 - 0.0625f, v20, v18);
				Tesselator::instance.vertexUV(v22, v24, v27, v21, v18);
				Tesselator::instance.vertexUV(v22, v23 - 0.002f, v27, v21, v17);
			}
			if(v50 || y <= 126 && this->levelSource->isEmptyTile(v54, v46, z)) {
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v18);
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v18);
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v27, v21, v18);
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v26 - 0.0625f, v20, v18);
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			}
			if(!v51 && (y <= 1 || !this->levelSource->isEmptyTile(v54, v47, z))) {
				goto LABEL_43;
			}
			v32 = v24 - 0.01f;
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v22, v24 - 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v22, v24 - 0.01f, v26 - 0.0625f, v20, v18);
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v22, v24 - 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v26 - 0.0625f, v20, v18);
			v33 = (float)x + 0.5f;
			v35 = v20;
			v36 = v17 + (float)((float)(v18 - v17) * 0.5f);
LABEL_87:
			Tesselator::instance.vertexUV(v33, v32, v26 - 0.0625f, v35, v36);
			goto LABEL_43;
		}
		goto LABEL_10;
	}
	if(v56) {
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v19, v58.minY);
		Tesselator::instance.vertexUV(v22, v24, v26, v19, v58.maxY);
		Tesselator::instance.vertexUV(v41, v24, v26, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v41, v23 - 0.002f, v26, v58.maxX, v58.minY);
		Tesselator::instance.vertexUV(v41, v23 - 0.002f, v26, v19, v58.minY);
		Tesselator::instance.vertexUV(v41, v24, v26, v19, v58.maxY);
		Tesselator::instance.vertexUV(v22, v24, v26, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v58.maxX, v58.minY);
		if(!v48 && !v49) {
			Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26 - 0.0625f, v20, v17);
			Tesselator::instance.vertexUV(v22, v24, v26 - 0.0625f, v20, v18);
			Tesselator::instance.vertexUV(v22, v24, v27, v21, v18);
			Tesselator::instance.vertexUV(v22, v23 - 0.002f, v27, v21, v17);
			Tesselator::instance.vertexUV(v22, v23 - 0.002f, v27, v20, v17);
			Tesselator::instance.vertexUV(v22, v24, v27, v20, v18);
			Tesselator::instance.vertexUV(v22, v24, v26 - 0.0625f, v21, v18);
			Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26 - 0.0625f, v21, v17);
		}
		if(v50 || y <= 126 && this->levelSource->isEmptyTile(v55, v46, z)) {
			Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v17);
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v17);
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v27, v21, v17);
			Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v26 - 0.0625f, v20, v17);
		}
		if(!v51 && (y <= 1 || !this->levelSource->isEmptyTile(v55, v47, z))) {
			goto LABEL_43;
		}
		v32 = v24 - 0.01f;
LABEL_90:
		Tesselator::instance.vertexUV(v22, v32, v27, v21, v17);
		Tesselator::instance.vertexUV(v41, v32, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
		Tesselator::instance.vertexUV(v41, v32, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
		Tesselator::instance.vertexUV(v22, v32, v26 - 0.0625f, v20, v17);
		Tesselator::instance.vertexUV(v41, v32, v27, v21, v17);
		Tesselator::instance.vertexUV(v22, v32, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
		Tesselator::instance.vertexUV(v22, v32, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
		v35 = v20;
		v36 = v17;
		goto LABEL_91;
	}
	if(!v49) {
		if(v48) {
			goto LABEL_74;
		}
LABEL_10:
		Tesselator::instance.vertexUV(v39, v23 - 0.002f, v26, v58.minX, v58.minY);
		Tesselator::instance.vertexUV(v39, v24, v26, v58.minX, v58.maxY);
		Tesselator::instance.vertexUV(v41, v24, v26, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v41, v23 - 0.002f, v26, v58.maxX, v58.minY);
		Tesselator::instance.vertexUV(v41, v23 - 0.002f, v26, v58.minX, v58.minY);
		Tesselator::instance.vertexUV(v41, v24, v26, v58.minX, v58.maxY);
		Tesselator::instance.vertexUV(v39, v24, v26, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v39, v23 - 0.002f, v26, v58.maxX, v58.minY);
		if(v50) {
			Tesselator::instance.vertexUV(v39, v25 + 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v27, v21, v17);
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v26 - 0.0625f, v20, v17);
			Tesselator::instance.vertexUV(v39, v25 + 0.01f, v26 - 0.0625f, v20, v18);
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v39, v25 + 0.01f, v27, v21, v17);
			Tesselator::instance.vertexUV(v39, v25 + 0.01f, v26 - 0.0625f, v20, v17);
			Tesselator::instance.vertexUV(v41, v25 + 0.01f, v26 - 0.0625f, v20, v18);
		} else if(y <= 126) {
			if(this->levelSource->isEmptyTile(v54, v46, z)) {
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v18);
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v18);
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v27, v21, v18);
				Tesselator::instance.vertexUV(v39, v25 + 0.01f, v26 - 0.0625f, v20, v18);
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			}
			if(this->levelSource->isEmptyTile(v55, v46, z)) {
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v17);
				Tesselator::instance.vertexUV(v41, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v41, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v17);
				Tesselator::instance.vertexUV(v41, v25 + 0.01f, v27, v21, v17);
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v22, v25 + 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v41, v25 + 0.01f, v26 - 0.0625f, v20, v17);
			}
		}
		if(v51) {
			v32 = v24 - 0.01f;
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v41, v24 - 0.01f, v27, v21, v17);
			Tesselator::instance.vertexUV(v41, v24 - 0.01f, v26 - 0.0625f, v20, v17);
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v26 - 0.0625f, v20, v18);
			Tesselator::instance.vertexUV(v41, v24 - 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v27, v21, v17);
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v26 - 0.0625f, v20, v17);
			v35 = v20;
			v36 = v18;
LABEL_91:
			v33 = (float)x + 1.0f;
			goto LABEL_87;
		}
		if(y <= 1) {
			goto LABEL_43;
		}
		if(this->levelSource->isEmptyTile(v54, v47, z)) {
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v22, v24 - 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v22, v24 - 0.01f, v26 - 0.0625f, v20, v18);
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v22, v24 - 0.01f, v27, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v27, v21, v18);
			Tesselator::instance.vertexUV(v39, v24 - 0.01f, v26 - 0.0625f, v20, v18);
			Tesselator::instance.vertexUV(v22, v24 - 0.01f, v26 - 0.0625f, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
		}
		if(!this->levelSource->isEmptyTile(v55, v47, z)) {
LABEL_43:
			if(!v49) {
				goto LABEL_45;
			}
			goto LABEL_44;
		}
		v32 = v24 - 0.01f;
		goto LABEL_90;
	}
LABEL_44:
	if(v48) {
LABEL_49:
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v42, v58.minX, v58.minY);
		Tesselator::instance.vertexUV(v22, v24, v42, v58.minX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v24, v40, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v40, v58.maxX, v58.minY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v40, v58.minX, v58.minY);
		Tesselator::instance.vertexUV(v22, v24, v40, v58.minX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v24, v42, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v42, v58.maxX, v58.minY);
		if(v50) {
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v42, v21, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v40, v21, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v40, v20, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v42, v20, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v40, v21, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v42, v21, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v42, v20, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v40, v20, v18);
		} else if(y <= 126) {
			if(this->levelSource->isEmptyTile(x, v46, v52)) {
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v40, v21, v17);
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v40, v20, v17);
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v21, v17);
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v40, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v40, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v20, v17);
			}
			if(this->levelSource->isEmptyTile(x, v46, v53)) {
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v42, v20, v18);
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v42, v21, v18);
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v42, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
				Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v20, v18);
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v21, v18);
				Tesselator::instance.vertexUV(v38, v23 - 0.002f, v42, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			}
		}
		if(v51) {
			Tesselator::instance.vertexUV(v38, v24, v42, v21, v18);
			Tesselator::instance.vertexUV(v38, v24, v40, v21, v17);
			Tesselator::instance.vertexUV(v37, v24, v40, v20, v17);
			Tesselator::instance.vertexUV(v37, v24, v42, v20, v18);
			Tesselator::instance.vertexUV(v38, v24, v40, v21, v18);
			Tesselator::instance.vertexUV(v38, v24, v42, v21, v17);
			Tesselator::instance.vertexUV(v37, v24, v42, v20, v17);
			Tesselator::instance.vertexUV(v37, v24, v40, v20, v18);
			return 1;
		}
		if(y <= 1) {
			return 1;
		}
		if(this->levelSource->isEmptyTile(x, v47, v52)) {
			Tesselator::instance.vertexUV(v37, v24, v40, v21, v17);
			Tesselator::instance.vertexUV(v37, v24, v26, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v26, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v40, v20, v17);
			Tesselator::instance.vertexUV(v37, v24, v26, v21, v17);
			Tesselator::instance.vertexUV(v37, v24, v40, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v40, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v26, v20, v17);
		}
		goto LABEL_82;
	}
LABEL_45:
	if(v57 || v56) {
		if(!v49) {
			if(!v48) {
				return 1;
			}
			goto LABEL_74;
		}
	} else if(!v49) {
		if(!v48) {
			goto LABEL_49;
		}
LABEL_74:
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v19, v58.minY);
		Tesselator::instance.vertexUV(v22, v24, v26, v19, v58.maxY);
		Tesselator::instance.vertexUV(v22, v24, v42, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v42, v58.maxX, v58.minY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v42, v19, v58.minY);
		Tesselator::instance.vertexUV(v22, v24, v42, v19, v58.maxY);
		Tesselator::instance.vertexUV(v22, v24, v26, v58.maxX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v58.maxX, v58.minY);
		if(!v56 && !v57) {
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v20, v17);
			Tesselator::instance.vertexUV(v38, v24, v26, v20, v18);
			Tesselator::instance.vertexUV(v37, v24, v26, v21, v18);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v21, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v20, v17);
			Tesselator::instance.vertexUV(v37, v24, v26, v20, v18);
			Tesselator::instance.vertexUV(v38, v24, v26, v21, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v21, v17);
		}
		if(v50 || y <= 126 && this->levelSource->isEmptyTile(x, v46, v53)) {
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v42, v20, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v42, v21, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v42, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v20, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v21, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v42, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
		}
		if(v51) {
LABEL_96:
			Tesselator::instance.vertexUV(v37, v24, v26, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v37, v24, v42, v20, v18);
			Tesselator::instance.vertexUV(v38, v24, v42, v21, v18);
			Tesselator::instance.vertexUV(v38, v24, v26, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v37, v24, v42, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v37, v24, v26, v20, v18);
			Tesselator::instance.vertexUV(v38, v24, v26, v21, v18);
			Tesselator::instance.vertexUV(v38, v24, v42, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			return 1;
		}
		if(y <= 1) {
			return 1;
		}
LABEL_82:
		if(!this->levelSource->isEmptyTile(x, v47, v53)) {
			return 1;
		}
		goto LABEL_96;
	}
	if(!v48) {
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v40, v58.minX, v58.minY);
		Tesselator::instance.vertexUV(v22, v24, v40, v58.minX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v24, v26, v19, v58.maxY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v19, v58.minY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v26, v58.minX, v58.minY);
		Tesselator::instance.vertexUV(v22, v24, v26, v58.minX, v58.maxY);
		Tesselator::instance.vertexUV(v22, v24, v40, v19, v58.maxY);
		Tesselator::instance.vertexUV(v22, v23 - 0.002f, v40, v19, v58.minY);
		if(!v56 && !v57) {
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v20, v17);
			Tesselator::instance.vertexUV(v37, v24, v26, v20, v18);
			Tesselator::instance.vertexUV(v38, v24, v26, v21, v18);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v21, v17);
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v20, v17);
			Tesselator::instance.vertexUV(v38, v24, v26, v20, v18);
			Tesselator::instance.vertexUV(v37, v24, v26, v21, v18);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v21, v17);
		}
		if(v50 || y <= 126 && this->levelSource->isEmptyTile(x, v46, v52)) {
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v40, v21, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v40, v20, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v26, v21, v17);
			Tesselator::instance.vertexUV(v37, v23 - 0.002f, v40, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v40, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v23 - 0.002f, v26, v20, v17);
		}
		if(v51 || y > 1 && this->levelSource->isEmptyTile(x, v47, v52)) {
			Tesselator::instance.vertexUV(v37, v24, v40, v21, v17);
			Tesselator::instance.vertexUV(v37, v24, v26, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v26, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v40, v20, v17);
			Tesselator::instance.vertexUV(v37, v24, v26, v21, v17);
			Tesselator::instance.vertexUV(v37, v24, v40, v21, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v40, v20, v17 + (float)((float)(v18 - v17) * 0.5f));
			Tesselator::instance.vertexUV(v38, v24, v26, v20, v17);
		}
	}
	return 1;
}
void TileRenderer::tesselateTorch(Tile* tile, float a3, float a4, float a5, float a6, float a7) {
	const TextureUVCoordinateSet* v9; // r0
	float maxY;					// s16
	float minY;					// s23
	float v12;					// s14
	float v13;					// s19
	float v14;					// s18
	float v15;					// s14
	float v16;					// s17
	float v17;					// s23
	float v18;					// s25
	float v19;					// s27
	float v20;					// s30
	float v21;					// s26
	float v22;					// s30
	float v23;					// s27
	float v24;					// s28
	float v25;					// s15
	float v26;					// s25
	float v27;					// s28
	float v28;					// s23
	float v29;					// s20
	float v30;					// s21
	float v31;					// s29

	if(this->hasUVCoords) {
		v9 = &this->field_8;
	} else {
		v9 = tile->getTexture(0);
	}
	maxY = v9->maxY;
	minY = v9->minY;
	v12 = v9->maxX - v9->minX;
	v13 = v9->minX + (float)(v12 * 0.4375f);
	v14 = v9->minX + (float)(v12 * 0.5625f);
	v15 = maxY - minY;
	v16 = minY + (float)((float)(maxY - minY) * 0.375f);
	if(v16 != 0.0f) {
		minY = minY + (float)((float)(maxY - minY) * 0.375f);
	}
	v17 = minY + (float)(v15 * 0.125f);
	v18 = a3 + 0.5f;
	v19 = v18 + (float)(a6 * 0.38125f);
	v20 = (float)(a5 + 0.5f) + (float)(a7 * 0.38125f);
	v21 = v20 - 0.0625f;
	Tesselator::instance.vertexUV(v19 - 0.0625f, a4 + 0.61875f, v20 - 0.0625f, v13, v16);
	v22 = v20 + 0.0625f;
	Tesselator::instance.vertexUV(v19 - 0.0625f, a4 + 0.61875f, v22, v13, v17);
	v23 = v19 + 0.0625f;
	Tesselator::instance.vertexUV(v23, a4 + 0.61875f, v22, v14, v17);
	Tesselator::instance.vertexUV(v23, a4 + 0.61875f, v21, v14, v16);
	v24 = (float)(a5 + 0.5f) + (float)((float)(a7 * 0.61875f) * 0.61875f);
	v25 = v18 + (float)((float)(a6 * 0.61875f) * 0.61875f);
	v26 = v24 - 0.0625f;
	v27 = v24 + 0.0625f;
	v28 = v27 + (float)(a7 * 0.61875f);
	v29 = (float)(v25 + (float)(a6 * 0.61875f)) + 0.0625f;
	Tesselator::instance.vertexUV(v29, a4, v28, v13, maxY);
	Tesselator::instance.vertexUV((float)(v25 - 0.0625f) + (float)(a6 * 0.61875f), a4, v28, v13, maxY);
	v30 = v26 + (float)(a7 * 0.61875f);
	Tesselator::instance.vertexUV((float)(v25 - 0.0625f) + (float)(a6 * 0.61875f), a4, v30, v14, maxY);
	Tesselator::instance.vertexUV(v29, a4, v30, v14, maxY);
	Tesselator::instance.vertexUV(v25 - 0.0625f, a4 + 0.61875f, v26, v13, v16);
	Tesselator::instance.vertexUV((float)(v25 - 0.0625f) + (float)(a6 * 0.61875f), a4 + 0.0f, v30, v13, maxY);
	Tesselator::instance.vertexUV((float)(v25 - 0.0625f) + (float)(a6 * 0.61875f), a4 + 0.0f, v28, v14, maxY);
	Tesselator::instance.vertexUV(v25 - 0.0625f, a4 + 0.61875f, v27, v14, v16);
	Tesselator::instance.vertexUV(v25 + 0.0625f, a4 + 0.61875f, v27, v13, v16);
	Tesselator::instance.vertexUV(v29, a4 + 0.0f, v28, v13, maxY);
	Tesselator::instance.vertexUV(v29, a4 + 0.0f, v30, v14, maxY);
	Tesselator::instance.vertexUV(v25 + 0.0625f, a4 + 0.61875f, v26, v14, v16);
	Tesselator::instance.vertexUV(v25 - 0.0625f, a4 + 0.61875f, v27, v13, v16);
	Tesselator::instance.vertexUV((float)(v25 - 0.0625f) + (float)(a6 * 0.61875f), a4 + 0.0f, v28, v13, maxY);
	v31 = (float)(v25 + 0.0625f) + (float)(a6 * 0.61875f);
	Tesselator::instance.vertexUV(v31, a4 + 0.0f, v28, v14, maxY);
	Tesselator::instance.vertexUV(v25 + 0.0625f, a4 + 0.61875f, v27, v14, v16);
	Tesselator::instance.vertexUV(v25 + 0.0625f, a4 + 0.61875f, v26, v13, v16);
	Tesselator::instance.vertexUV(v31, a4 + 0.0f, v30, v13, maxY);
	Tesselator::instance.vertexUV((float)(v25 - 0.0625f) + (float)(a6 * 0.61875f), a4 + 0.0f, v30, v14, maxY);
	Tesselator::instance.vertexUV(v25 - 0.0625f, a4 + 0.61875f, v26, v14, v16);
}
bool_t TileRenderer::tesselateTorchInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	int32_t v9;		   // r7
	float v10;		   // r1
	float v11;		   // s15
	float v12;		   // s16
	float v13;		   // s14
	TileRenderer* v14; // r0
	Tile* v15;		   // r1
	float v16;		   // r3
	float v17;		   // r2
	float v19;		   // [sp+0h] [bp-38h]
	float v20;		   // [sp+4h] [bp-34h]
	float v21;		   // [sp+8h] [bp-30h]

	v9 = this->levelSource->getData(x, y, z);
	v10 = tile->getBrightness(this->levelSource, x, y, z);
	if(Tile::lightEmission[tile->blockID] > 0) {
		v10 = 1.0f;
	}
	Tesselator::instance.color(v10, v10, v10);
	v11 = (float)x;
	if(v9 != 1) {
		v12 = (float)z;
		v13 = (float)y;
		if(v9 == 2) {
			v19 = (float)z;
			v21 = 0.0f;
			v14 = this;
			v15 = tile;
			v20 = 0.4f;
			v11 = v11 + 0.1f;
		} else {
			if(v9 == 3) {
				v20 = 0.0f;
				v16 = -0.4f;
				v19 = v12 - 0.1f;
			} else {
				if(v9 != 4) {
					v17 = (float)x;
					v14 = this;
					v15 = tile;
					v19 = (float)z;
					v20 = 0.0f;
					v21 = 0.0f;
					goto LABEL_14;
				}
				v16 = 0.4f;
				v20 = 0.0f;
				v19 = v12 + 0.1f;
			}
			v14 = this;
			v15 = tile;
			v21 = v16;
		}
		v17 = v11;
		v13 = v13 + 0.2f;
LABEL_14:
		v14->tesselateTorch(v15, v17, v13, v19, v20, v21);
		return 1;
	}
	this->tesselateTorch(tile, v11 - 0.1f, (float)y + 0.2f, (float)z, -0.4f, 0.0f);
	return 1;
}
bool_t TileRenderer::tesselateTreeInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	int32_t v9; // r0

	v9 = this->levelSource->getData(x, y, z) & 0xC;
	if(v9 == 4) {
		this->randomizeFace[0] = this->randomizeFace[1] = this->randomizeFace[3] = this->randomizeFace[2] = 1;
	} else if(v9 == 8) {
		this->randomizeFace[4] = this->randomizeFace[5] = 1;
	}
	return this->tesselateBlockInWorld(tile, x, y, z);
}
bool_t TileRenderer::tesselateWallInWorld(WallTile* tile, int32_t x, int32_t y, int32_t z) {
	bool_t v9;	 // r0
	int32_t v10; // r10
	int32_t v11; // r11
	bool_t v12;	 // r0
	float v13;	 // s18
	float v14;	 // s17
	bool_t v16;	 // [sp+10h] [bp-48h]
	bool_t v17;	 // [sp+14h] [bp-44h]
	bool_t v18;	 // [sp+18h] [bp-40h]
	bool_t v19;	 // [sp+1Ch] [bp-3Ch]

	v16 = tile->connectsTo(this->levelSource, x - 1, y, z);
	v17 = tile->connectsTo(this->levelSource, x + 1, y, z);
	v19 = tile->connectsTo(this->levelSource, x, y, z - 1);
	v9 = tile->connectsTo(this->levelSource, x, y, z + 1);
	v18 = v9;
	if(v19) {
		if(v9 && !v16 && !v17) {
			v10 = 1;
			v11 = 0;
			goto LABEL_13;
		}
	} else {
		if(v9) {
			v10 = 0;
			goto LABEL_12;
		}
		if(v16 && v17) {
			v10 = 0;
			v11 = 1;
			goto LABEL_13;
		}
	}
	v10 = 0;
LABEL_12:
	v11 = 0;
LABEL_13:
	v12 = this->levelSource->isEmptyTile(x, y + 1, z);
	if(v10) {
		if(v12) {
			tile->setShape(0.5f - 0.1875f, 0.0f, 0.0f, 0.1875f + 0.5f, 0.8125f, 1.0f);
			goto LABEL_24;
		}
	} else if(v11 && v12) {
		tile->setShape(0.0f, 0.0f, 0.5f - 0.1875f, 1.0f, 0.8125f, 0.1875f + 0.5f);
		goto LABEL_24;
	}
	v13 = 0.5f - 0.25f;
	v14 = 0.25f + 0.5f;
	tile->setShape(0.5f - 0.25f, 0.0f, 0.5f - 0.25f, 0.25f + 0.5f, 1.0f, 0.25f + 0.5f);
	this->tesselateBlockInWorld(tile, x, y, z);
	if(v16) {
		tile->setShape(0.0f, 0.0f, 0.5f - 0.1875f, v13, 0.8125f, 0.1875f + 0.5f);
		this->tesselateBlockInWorld(tile, x, y, z);
	}
	if(v17) {
		tile->setShape(v14, 0.0f, 0.5f - 0.1875f, 1.0f, 0.8125f, 0.1875f + 0.5f);
		this->tesselateBlockInWorld(tile, x, y, z);
	}
	if(v19) {
		tile->setShape(0.5f - 0.1875f, 0.0f, 0.0f, 0.1875f + 0.5f, 0.8125f, v13);
		this->tesselateBlockInWorld(tile, x, y, z);
	}
	if(v18) {
		tile->setShape(0.5f - 0.1875f, 0.0f, v14, 0.1875f + 0.5f, 0.8125f, 1.0f);
LABEL_24:
		this->tesselateBlockInWorld(tile, x, y, z);
	}
	tile->updateShape(this->levelSource, x, y, z);
	return 1;
}
bool_t TileRenderer::tesselateWaterInWorld(Tile* tile, int32_t x, int32_t y, int32_t z) {
	int32_t v9;						   // r9
	int32_t v10;					   // r0
	LevelSource* levelSource;		   // r1
	int32_t v13;					   // r0
	LevelSource* v14;				   // r1
	int32_t v16;					   // r0
	LevelSource* v17;				   // r1
	int32_t v19;					   // r6
	int32_t v20;					   // r0
	Material* a5;					   // r6
	float WaterHeight;				   // s16
	float v23;						   // s17
	float v24;						   // s18
	float v25;						   // s19
	const TextureUVCoordinateSet* v26;	   // r0
	float v27;						   // s20
	float v28;						   // s22
	float v29;						   // s23
	float v30;						   // s24
	float SlopeAngle;				   // s25
	const TextureUVCoordinateSet* v32;	   // r0
	float v33;						   // s23
	float v34;						   // s25
	float v35;						   // s14
	float v36;						   // s12
	float v37;						   // s11
	float v38;						   // s15
	float v39;						   // s13
	float v40;						   // s12
	float v41;						   // s11
	float v42;						   // s25
	float v43;						   // s30
	float v44;						   // s11
	float v45;						   // s14
	float v46;						   // s31
	float v47;						   // s28
	float v48;						   // r0
	float v49;						   // r0
	const TextureUVCoordinateSet* v50; // r0
	int32_t i;						   // r6
	int32_t v52;					   // r12
	int32_t v53;					   // r9
	const TextureUVCoordinateSet* v54;	   // r0
	float v55;						   // s30
	float v56;						   // s15
	float v57;						   // s31
	float v58;						   // s20
	float v59;						   // s21
	float v60;						   // s23
	float v61;						   // s22
	float v62;						   // s24
	float v63;						   // s25
	float v64;						   // s29
	float v65;						   // s29
	float v66;						   // r0
	float v67;						   // s15
	float v68;						   // s27
	int32_t v70;					   // [sp+10h] [bp-98h]
	int32_t v71;					   // [sp+14h] [bp-94h]
	float v72;						   // [sp+14h] [bp-94h]
	float v73;						   // [sp+14h] [bp-94h]
	int32_t a4;						   // [sp+18h] [bp-90h]
	int32_t a2;						   // [sp+1Ch] [bp-8Ch]
	int32_t v76;					   // [sp+20h] [bp-88h]
	int32_t v77;					   // [sp+20h] [bp-88h]
	int32_t v78;					   // [sp+24h] [bp-84h]
	float v79;						   // [sp+24h] [bp-84h]
	bool_t v80;						   // [sp+30h] [bp-78h]
	int32_t v81;					   // [sp+34h] [bp-74h]
	bool_t v82[4];					   // [sp+3Ch] [bp-6Ch] BYREF

	v78 = y - 1;
	v9 = tile->shouldRenderFace(this->levelSource, x, y + 1, z, 1);
	v81 = tile->shouldRenderFace(this->levelSource, x, v78, z, 0);
	v10 = tile->shouldRenderFace(this->levelSource, x, y, z - 1, 2);
	a4 = z + 1;
	levelSource = this->levelSource;
	v76 = v10;
	v82[0] = v10;
	v13 = tile->shouldRenderFace(levelSource, x, y, z + 1, 3);
	v14 = this->levelSource;
	v71 = v13;
	v82[1] = v13;
	v16 = tile->shouldRenderFace(v14, x - 1, y, z, 4);
	a2 = x + 1;
	v17 = this->levelSource;
	v82[2] = v16;
	v19 = v16;
	v20 = tile->shouldRenderFace(v17, x + 1, y, z, 5);
	v82[3] = v20;
	if(!v9 && !v81 && !v76 && !v71 && !v19 && !v20) {
		return 0;
	}
	a5 = (Material*)tile->material;
	v77 = this->levelSource->getData(x, y, z);
	WaterHeight = this->getWaterHeight(x, y, z, a5);
	v23 = this->getWaterHeight(x, y, a4, a5);
	v24 = this->getWaterHeight(a2, y, a4, a5);
	v25 = this->getWaterHeight(a2, y, z, a5);
	if(this->disableCulling || v9) {
		v26 = tile->getTexture(1, v77);
		v27 = v26->minX;
		v28 = v26->minY;
		v29 = v26->maxX;
		v30 = v26->maxY;
		SlopeAngle = LiquidTile::getSlopeAngle(this->levelSource, x, y, z, a5);
		if(SlopeAngle > -999.0f) {
			v32 = tile->getTexture(2, v77);
			v27 = v32->minX;
			v28 = v32->minY;
			v29 = v32->maxX;
			v30 = v32->maxY;
		}
		WaterHeight = WaterHeight - 0.001f;
		v23 = v23 - 0.001f;
		v24 = v24 - 0.001f;
		v25 = v25 - 0.001f;
		if(SlopeAngle < -999.0f) {
			v47 = v30;
			v72 = v29;
			v43 = v28;
			v42 = v27;
			v46 = v27;
		} else {
			v33 = v29 - v27;
			v35 = Mth::sin(SlopeAngle) * 0.5f;
			v36 = Mth::cos(SlopeAngle) * 0.5f;
			v37 = 1.0f - v36;
			v38 = v30 - v28;
			v39 = (float)(1.0f - v36) - v35;
			v40 = v36 + 1.0f;
			v41 = v37 + v35;
			v42 = v27 + (float)(v41 * v33);
			v43 = v28 + (float)(v41 * (float)(v30 - v28));
			v44 = v40 + v35;
			v45 = v40 - v35;
			v72 = v27 + (float)(v44 * v33);
			v46 = v27 + (float)(v39 * v33);
			v47 = v28 + (float)(v44 * (float)(v30 - v28));
			v30 = v28 + (float)(v45 * (float)(v30 - v28));
			v29 = v27 + (float)(v45 * v33);
			v28 = v28 + (float)(v39 * v38);
		}
		v48 = tile->getBrightness(this->levelSource, x, y, z);
		Tesselator::instance.color(v48, v48, v48);
		Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + WaterHeight, (float)z + 0.0f, v46, v43);
		Tesselator::instance.vertexUV((float)x + 0.0f, (float)y + v23, (float)z + 1.0f, v42, v47);
		Tesselator::instance.vertexUV((float)x + 1.0f, (float)y + v24, (float)z + 1.0f, v72, v30);
		Tesselator::instance.vertexUV((float)x + 1.0f, (float)y + v25, (float)z + 0.0f, v29, v28);
		v80 = 1;
	} else {
		v80 = 0;
	}
	if(this->disableCulling || v81) {
		v49 = tile->getBrightness(this->levelSource, x, v78, z);
		Tesselator::instance.color((float)(v49 * 0.5f), v49 * 0.5f, v49 * 0.5f);
		v50 = tile->getTexture(0);
		this->renderFaceDown(tile, (float)x, (float)y, (float)z, *v50);
		v80 = 1;
	}
	for(i = 0; i != 4; ++i) {
		if(!i) {
			v52 = z - 1;
LABEL_28:
			v53 = x;
			goto LABEL_29;
		}
		if(i == 1) {
			v52 = z + 1;
			goto LABEL_28;
		}
		v52 = z;
		if(i == 2) {
			v53 = x - 1;
		} else {
			if(i != 3) {
				goto LABEL_28;
			}
			v53 = x + 1;
		}
LABEL_29:
		v70 = v52;
		v54 = tile->getTexture(i + 2, v77);
		v55 = v54->minX;
		v56 = v54->minY;
		v57 = v54->maxX;
		if(this->disableCulling || v82[i]) {
			if(i) {
				if(i == 1) {
					v58 = (float)a4 - 0.001f;
					v59 = (float)a2;
					v60 = (float)x;
					v61 = v58;
					v62 = v23;
					v63 = v24;
				} else if(i == 2) {
					v59 = (float)x + 0.001f;
					v58 = (float)a4;
					v61 = (float)z;
					v60 = v59;
					v62 = WaterHeight;
					v63 = v23;
				} else {
					v59 = (float)a2 - 0.001f;
					v58 = (float)z;
					v61 = (float)a4;
					v60 = v59;
					v62 = v24;
					v63 = v25;
				}
			} else {
				v58 = (float)z + 0.001f;
				v59 = (float)x;
				v60 = (float)a2;
				v61 = v58;
				v62 = v25;
				v63 = WaterHeight;
			}
			v64 = v54->maxY - v56;
			v73 = v56 + (float)((float)(1.0f - v63) * v64);
			v79 = v56 + (float)((float)(1.0f - v62) * v64);
			v65 = v56 + v64;
			v66 = tile->getBrightness(this->levelSource, v53, y, v70);
			if(i > 1) {
				v67 = v66 * 0.6f;
			} else {
				v67 = v66 * 0.8f;
			}
			Tesselator::instance.color(v67, v67, v67);
			Tesselator::instance.vertexUV(v59, (float)y + v63, v58, v55, v73);
			Tesselator::instance.vertexUV(v60, (float)y + v62, v61, v57, v79);
			v68 = (float)y + 0.0f;
			Tesselator::instance.vertexUV(v60, v68, v61, v57, v65);
			Tesselator::instance.vertexUV(v59, v68, v58, v55, v65);
			v80 = 1;
		}
	}
	tile->minY = 0.0f;
	tile->maxY = 1.0f;
	return v80;
}
