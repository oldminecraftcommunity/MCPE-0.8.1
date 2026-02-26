#include <rendering/LevelRenderer.hpp>
#include <GL/glu.h>
#include <Minecraft.hpp>
#include <algorithm>
#include <entity/LocalPlayer.hpp>
#include <float.h>
#include <level/Level.hpp>
#include <level/dimension/Dimension.hpp>
#include <math/Mth.hpp>
#include <math/Vec3.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/GameRenderer.hpp>
#include <rendering/ParticleEngine.hpp>
#include <rendering/RenderChunk.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/TextureTesselator.hpp>
#include <rendering/Textures.hpp>
#include <rendering/TileEntityRenderDispatcher.hpp>
#include <rendering/TileRenderer.hpp>
#include <rendering/entity/EntityRenderer.hpp>
#include <rendering/states/BlendFunctionState.hpp>
#include <rendering/states/DisableState.hpp>
#include <rendering/states/EnableClientState.hpp>
#include <rendering/states/EnableState.hpp>
#include <sound/SoundEngine.hpp>
#include <tile/Tile.hpp>
#include <tile/entity/TileEntity.hpp>
#include <utils.h>
#include <rendering/frustum/FrustumCuller.hpp>
#include <util/DirtyChunkSorter.hpp>
#include <perf/Stopwatch.hpp>

LevelRenderer::LevelRenderer(Minecraft* minecraft, std::shared_ptr<TextureAtlas> a3)
	: field_164(Color4::BLACK) {
	this->field_160 = this->field_15C = 0; //XXX doesnt seem to be in mcpe
	this->field_14 = 0.0;
	this->field_1C = 0;
	this->field_8 = -9999.0;
	this->field_C = -9999.0;
	this->field_10 = -9999.0;
	this->field_20 = 0;
	this->field_18 = 2;
	this->field_24 = 0;
	this->totalLoaded = 0;
	this->frustrumClippedCnt = 0;
	this->occludedCnt = 0;
	this->totalRendered = 0;
	this->field_38 = 0;
	this->field_3C = 0;
	this->field_40 = 0;
	this->field_44 = 0;
	this->field_48 = 0;
	this->field_4C = 0;
	this->field_50 = 0;
	this->field_54 = 0;
	this->level = 0;
	this->chunks = 0;
	this->field_70 = 0;
	this->renderXsize = 0;
	this->renderYsize = 0;
	this->renderZSize = 0;
	this->field_80 = 0;
	this->minecraft = minecraft;
	this->renderDistance = -1;
	this->field_88 = 0;
	this->ticksElapsed = 0;
	this->textures = minecraft->texturesPtr;
	this->field_1CC.x = 0.0;
	this->field_1CC.y = 0.0;
	this->field_1CC.z = 0.0;
	this->shadowRed = 0.0;
	this->shadowGreen = 0.0;
	this->shadowBlue = 0.0;
	this->shadowAlpha = 0.0;
	this->_initResources();
	this->destroyTexture = *a3->getTextureItem("destroy_stage_x");
	AppPlatform::_singleton->addListener(this, 1.0);
}
void LevelRenderer::_buildShadowOverlay(const Color4& color) {
	Tesselator::instance.instance.begin(4, 8);
	Tesselator::instance.color(Color4::NIL.r, Color4::NIL.g, Color4::NIL.b, Color4::NIL.a);
	Tesselator::instance.vertex(-50.0, 2.5, -50.0);
	Tesselator::instance.vertex(50.0, 2.5, -50.0);
	Tesselator::instance.vertex(50.0, 2.5, 50.0);
	Tesselator::instance.vertex(-50.0, 2.5, 50.0);
	Tesselator::instance.color(color.r, color.g, color.b, color.a);
	Tesselator::instance.vertex(-50.0, -1.0, -50.0);
	Tesselator::instance.vertex(50.0, -1.0, -50.0);
	Tesselator::instance.vertex(50.0, -1.0, 50.0);
	Tesselator::instance.vertex(-50.0, -1.0, 50.0);
	Tesselator::instance.triangle(0, 4u, 1u);
	Tesselator::instance.triangle(4u, 5u, 1u);
	Tesselator::instance.triangle(1u, 5u, 2u);
	Tesselator::instance.triangle(5u, 6u, 2u);
	Tesselator::instance.triangle(2u, 6u, 3u);
	Tesselator::instance.triangle(6u, 7u, 3u);
	Tesselator::instance.triangle(3u, 7u, 0);
	Tesselator::instance.triangle(7u, 4u, 0);
	Tesselator::instance.quad(4u, 0);
	this->shadowOverlayBuffer = Tesselator::instance.end();
	this->shadowRed = color.r;
	this->shadowGreen = color.g;
	this->shadowBlue = color.b;
	this->shadowAlpha = color.a;
}
void LevelRenderer::_buildShadowVolume() {
	int32_t v2;	 // r6
	float v3;	 // s16
	float v4;	 // s16
	uint16_t vc; // r5

	v2 = 1;
	Tesselator::instance.begin(4, 28);
	Tesselator::instance.vertex(0.25, -3.0, 0.0);
	Tesselator::instance.vertex(0.75, 0.001, 0.0);
	do {
		Vec3 v6{0.75, 0, 0};	 // [sp+4h] [bp-74h] BYREF
		Vec3 result{0.25, 0, 0}; // [sp+10h] [bp-68h] BYREF
		v3 = (float)v2;
		++v2;
		v4 = (float)(v3 / 13.0) * 6.2832;
		v6.yRot(v4);
		result.yRot(v4);
		vc = Tesselator::instance.getVertexCount();
		Tesselator::instance.vertex(result.x, -3.0, result.z);
		Tesselator::instance.vertex(v6.x, 0.001, v6.z);
		Tesselator::instance.triangle(vc - 2, vc - 1, vc);
		Tesselator::instance.triangle(vc - 1, vc + 1, vc);
		Tesselator::instance.triangle(vc, 0, vc - 2);
		Tesselator::instance.triangle(1u, vc + 1, vc - 1);
	} while(v2 != 14);
	this->shadowVolumeBuffer = Tesselator::instance.end();
}
void LevelRenderer::_buildStarsMesh() {
	int32_t v2;		   // r7
	float v3;		   // s12
	float v4;		   // s21
	float v5;		   // s13
	float v6;		   // r0
	float v7;		   // s24
	float v8;		   // s19
	float v9;		   // r0
	float v10;		   // s19
	float v11;		   // s15
	float v12;		   // s25
	float v13;		   // s22
	float v14;		   // s22
	float v15;		   // s21
	float v16;		   // s24
	float v17;		   // s22
	float v18;		   // s27
	float v19;		   // s15
	float v20;		   // s29
	float v21;		   // s28
	float v22;		   // s19
	float v23;		   // s20
	float v24;		   // s15
	float v25;		   // s15
	float v26;		   // s21
	float v27;		   // s22
	float v28;		   // r0
	float v29;		   // s15
	float v30;		   // r0
	float v31;		   // s24
	int32_t v32;	   // r6
	float v33;		   // s23
	int32_t v34;	   // r3
	float v35;		   // s13
	float v36;		   // s15
	Random v38(10842); // [sp+28h] [bp-A30h] BYREF

	v2 = 1500;
	Tesselator::instance.begin(6000);
	do {
		v3 = v38.nextFloat();
		v4 = (float)(v3 + v3) - 1.0;
		v5 = v38.nextFloat();
		v6 = v38.nextFloat();
		v7 = (float)(v5 + v5) - 1.0;
		v8 = v6 + v6;
		v9 = v38.nextFloat();
		v10 = v8 - 1.0;
		v11 = (float)((float)(v7 * v7) + (float)(v4 * v4)) + (float)(v10 * v10);
		if(v11 < 1.0 && v11 > 0.01) {
			v12 = (float)(v9 * 0.1) + 0.15;
			v13 = sqrt(v11);
			v14 = 1.0 / v13;
			v15 = v4 * v14;
			v16 = v7 * v14;
			v17 = v10 * v14;
			v18 = v17 * 100.0;
			v19 = atan2(v15, v17);
			v20 = v15 * 100.0;
			v21 = v16 * 100.0;
			v22 = Mth::sin(v19);
			v23 = Mth::cos(v19);
			v24 = sqrt((float)((float)(v17 * v17) + (float)(v15 * v15)));
			v25 = atan2(v24, v16);
			v26 = Mth::sin(v25);
			v27 = Mth::cos(v25);
			v28 = v38.nextFloat();
			v29 = (float)(v28 * 3.1416) + (float)(v28 * 3.1416);
			v30 = Mth::cos(v29);
			v31 = Mth::sin(v29);
			v32 = 0;
			v33 = v30;
			do {
				v34 = v32++ & 2;
				v35 = (float)((v32 & 2) - 1) * v12;
				v36 = (float)(v34 - 1) * v12;
				Tesselator::instance.vertex(v20 + (float)((float)((float)((float)(v26 * 0.0) - (float)((float)((float)(v36 * v33) - (float)(v35 * v31)) * v27)) * v22) - (float)((float)((float)(v36 * v31) + (float)(v35 * v33)) * v23)), v21 + (float)((float)(v27 * 0.0) + (float)((float)((float)(v36 * v33) - (float)(v35 * v31)) * v26)), v18 + (float)((float)((float)((float)(v26 * 0.0) - (float)((float)((float)(v36 * v33) - (float)(v35 * v31)) * v27)) * v23) + (float)((float)((float)(v36 * v31) + (float)(v35 * v33)) * v22)));
			} while(v32 != 4);
		}
		--v2;
	} while(v2);
	this->starsMesh = Tesselator::instance.end();
}
void LevelRenderer::_initResources() {
	this->generateSky();
	this->_buildStarsMesh();
	this->_buildShadowVolume();
	this->shadowOverlayBuffer.reset();
	this->cloudsMesh.reset();
}
bool_t LevelRenderer::_renderChunk(MeshBuffer& a2) {
	if(a2.arraysCount <= 2) return 0;
	a2.render();
	return 1;
}
void LevelRenderer::_renderShadow(float a2, const Vec3& a3, float a4) {
	glPushMatrix();
	glTranslatef(a3.x, a3.y, a3.z);
	glScalef(a2, a2, a2);
	glStencilFunc(0x207u, 1, 0xFFu);
	glStencilOp(0x1E00u, 0x1E00u, 0x1E01u);
	glCullFace(0x404u);
	this->shadowVolumeBuffer.render();
	glCullFace(0x405u);
	glStencilFunc(0x207u, 0, 0xFFu);
	glStencilOp(0x1E00u, 0x1E00u, 0x1E01u);
	this->shadowVolumeBuffer.render();
	glPopMatrix();
}
void LevelRenderer::_renderStars(float a2) {
	float sb;		// s16
	float SunAngle; // r0

	sb = this->level->getStarBrightness(a2);
	if(sb > 0.0) {
		DisableState v6(2884);
		DisableState v7(3553);
		glPushMatrix();
		{
			BlendFunctionState v5(0x307u, 1);
			SunAngle = this->minecraft->level->getSunAngle(1.0);
			glRotatef((float)(SunAngle / 6.2832) * 360.0, 1.0, 0.0, 0.0);
			glColor4f(sb, sb, sb, 1.0);
			this->starsMesh.render();
			//~v5
		}
		glPopMatrix();
		//~v7
		//~v6
	}
}
void LevelRenderer::_renderSunOrMoon(float a2, bool_t a3) {
	float sunAngle;	   // r0
	float v6;		   // s14
	float v7;		   // r0
	float v8;		   // s20
	float v9;		   // s16
	float v10;		   // s17
	float v11;		   // r4
	float v12;		   // s18
	float v13;		   // s19
	int32_t moonPhase; // r0
	int32_t v17;	   // r3

	sunAngle = this->minecraft->level->getSunAngle(a2);
	v6 = 0.0;
	if(!a3) {
		v6 = 180.0;
	}
	v7 = fmodf(v6 + (float)((float)(sunAngle / 6.2832) * 360.0), 360.0);
	v8 = v7;
	if(v7 <= 105.0 || v7 >= 255.0) {
		if(a3) {
			v9 = 1.0;
			v10 = 0.0;
			v11 = 30.0;
			v12 = 1.0;
			v13 = 0.0;
		} else {
			moonPhase = this->level->getMoonPhase();
			v17 = moonPhase / 4 % 2;
			v11 = 20.0;
			v13 = (float)(moonPhase % 4) * 0.25;
			v10 = (float)v17 * 0.5;
			v12 = (float)(moonPhase % 4 + 1) * 0.25;
			v9 = (float)(v17 + 1) * 0.5;
		}
		Tesselator::instance.begin(4);
		Tesselator::instance.vertexUV(-v11, 120.0, -v11, v12, v10);
		Tesselator::instance.vertexUV(v11, 120.0, -v11, v13, v10);
		Tesselator::instance.vertexUV(v11, 120.0, v11, v13, v9);
		Tesselator::instance.vertexUV(-v11, 120.0, v11, v12, v9);

		this->textures->loadAndBindTexture(a3 ? "environment/sun.png" : "environment/moon_phases.png");
		DisableState v19(2884);
		glPushMatrix();
		{
			BlendFunctionState v18(1u, 1u);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRotatef(v8, 1.0, 0.0, 0.0);
			Tesselator::instance.draw(1);
			//BlendFunctionState::~BlendFunctionState((BlendFunctionState *)v18);
		}
		glPopMatrix();
		//DisableState::~DisableState((DisableState *)&v19);
	}
}
void LevelRenderer::cullAndSort(FrustumCuller* a2, float a3, float a4) {
	if(this->minecraft->options.renderDistance != this->renderDistance) {
		this->allChanged();
	}
	Mob* ve = this->minecraft->viewEntityMaybe;
	Vec3 v36(ve->posX, ve->posY, ve->posZ);
	if((float)((float)((float)((float)(this->field_1CC.y - v36.y) * (float)(this->field_1CC.y - v36.y)) + (float)((float)(this->field_1CC.x - v36.x) * (float)(this->field_1CC.x - v36.x))) + (float)((float)(this->field_1CC.z - v36.z) * (float)(this->field_1CC.z - v36.z))) > 16.0) {
		this->field_1CC = v36;
		this->resortChunks(Mth::floor(ve->posX), Mth::floor(ve->posY), Mth::floor(ve->posZ));
	}
	int32_t v13 = 10;
	do {
		int v14 = (this->field_3C + 1) % this->chunksToRenderSize;
		this->field_3C = v14;
		RenderChunk* v35 = this->chunks[v14];
		if(v35->isDirty()) {
			if(this->_renderChunks.end() == std::find(this->_renderChunks.begin(), this->_renderChunks.end(), v35)) {
				this->_renderChunks.push_back(v35);
			}
		}
		--v13;
	} while(v13);
	this->totalLoaded = 0;
	this->frustrumClippedCnt = 0;
	this->occludedCnt = 0;
	this->totalRendered = 0;
	this->field_38 = 0;
	Vec3 v37(ve->prevPosX + (float)((float)(ve->posX - ve->prevPosX) * a4), ve->prevPosY + (float)((float)(ve->posY - ve->prevPosY) * a4), ve->prevPosZ + (float)((float)(ve->posZ - ve->prevPosZ) * a4));

	this->field_19C.clear(); //TODO check
	this->field_1B4.clear();
	static Vec3 _D6E0698C(8, 8, 8);
	float v17 = a3 * a3;
	for(int i = 0; i < this->chunksToRenderSize; ++i) {
		RenderChunk* v19 = this->chunks[i];
		bool isVisible;
		if(v19->built && v19->skipRenderMaybe) {
			isVisible = 0;
		} else {
			isVisible = a2->isVisible(v19->frustumBB);
		}
		v19->isInFrustumMaybe = isVisible;
		if(isVisible) {
			Vec3 v38(v37.x - (float)v19->xPos, v37.y - (float)v19->yPos, v37.z - (float)v19->zPos);
			Vec3 v39(v38.x - _D6E0698C.x, v38.y - _D6E0698C.y, v38.z - _D6E0698C.z);

			float v21 = (float)((float)((float)(v39.y + v39.y) * (float)(v39.y + v39.y)) + (float)(v39.x * v39.x)) + (float)(v39.z * v39.z);
			if(v21 >= (float)(v17 * 0.5)) {
				this->field_1B4.insert({v21, v19});
			} else {
				this->field_19C.insert({v21, v19});
			}
		}
	}

	++this->field_24;
	this->totalLoaded = chunksToRenderSize;
	this->totalRendered = this->field_19C.size() + this->field_1B4.size();
}
void LevelRenderer::deleteChunks() {
	RenderChunk* v2;	  // r6
	MeshBuffer* j;		  // r7
	int32_t i;			  // r5
	RenderChunk** chunks; // r0

	if(this->chunks) {
		for(i = 0;; ++i) {
			chunks = this->chunks;
			if(i >= this->chunksToRenderSize) {
				break;
			}
			v2 = chunks[i];
			if(v2) {
				delete v2;
			}
		}
		if(chunks) {
			delete[] chunks;
		}
		this->chunks = 0;
	}
}
std::string LevelRenderer::gatherStats1() {
	return "C: " + std::to_string(this->totalRendered) + "/" + std::to_string(this->totalLoaded) + ". F: " + std::to_string(this->frustrumClippedCnt) + ", O: " + std::to_string(this->occludedCnt) + ", E: " + std::to_string(this->field_38) + "\n";
}
void LevelRenderer::generateSky() {
	int32_t v2; // r4
	int32_t v3; // s14

	v2 = 0;
	Tesselator::instance.begin(6, 12);
	Tesselator::instance.vertex(0.0, 128.0, 0.0);
	do {
		v3 = v2;
		Vec3 v4(2000.0, 0, 0);
		++v2;
		v4.yRot((float)((float)v3 / 10.0) * 6.2832);
		Tesselator::instance.vertex(v4.x, 128.0, v4.z);
	} while(v2 != 11);
	this->skyMesh = Tesselator::instance.end();
}
int32_t LevelRenderer::getLayerFeature(int32_t a1, bool_t a2) {
	switch(a1) {
		case 2:
			return 3042;
		case 3:
			if(a2) {
				return 3008;
			} else {
				return 0;
			}
		case 1:
			return 3008;
		default:
			return 0;
	}
}
void LevelRenderer::render(const AABB& a2) {
	this->textures->loadAndBindTexture("terrain-atlas.tga");
	Vec3 v5 = this->minecraft->player->getPos(0.0);
	Vec3 v6(-v5.x, -v5.y, -v5.z);
	Tesselator::instance.offset(v6);
	Tesselator::instance.begin(3);
	Tesselator::instance.vertex(a2.minX, a2.minY, a2.minZ);
	Tesselator::instance.vertex(a2.maxX, a2.minY, a2.minZ);
	Tesselator::instance.vertex(a2.maxX, a2.minY, a2.maxZ);
	Tesselator::instance.vertex(a2.minX, a2.minY, a2.maxZ);
	Tesselator::instance.vertex(a2.minX, a2.minY, a2.minZ);
	Tesselator::instance.draw(1);
	Tesselator::instance.begin(3);
	Tesselator::instance.vertex(a2.minX, a2.maxY, a2.minZ);
	Tesselator::instance.vertex(a2.maxX, a2.maxY, a2.minZ);
	Tesselator::instance.vertex(a2.maxX, a2.maxY, a2.maxZ);
	Tesselator::instance.vertex(a2.minX, a2.maxY, a2.maxZ);
	Tesselator::instance.vertex(a2.minX, a2.maxY, a2.minZ);
	Tesselator::instance.draw(1);
	Tesselator::instance.begin(1);
	Tesselator::instance.vertex(a2.minX, a2.minY, a2.minZ);
	Tesselator::instance.vertex(a2.minX, a2.maxY, a2.minZ);
	Tesselator::instance.vertex(a2.maxX, a2.minY, a2.minZ);
	Tesselator::instance.vertex(a2.maxX, a2.maxY, a2.minZ);
	Tesselator::instance.vertex(a2.maxX, a2.minY, a2.maxZ);
	Tesselator::instance.vertex(a2.maxX, a2.maxY, a2.maxZ);
	Tesselator::instance.vertex(a2.minX, a2.minY, a2.maxZ);
	Tesselator::instance.vertex(a2.minX, a2.maxY, a2.maxZ);
	Tesselator::instance.offset(0.0, 0.0, 0.0);
	Tesselator::instance.draw(1);
}
int32_t LevelRenderer::renderChunks(int32_t a2, float a3, bool_t a4) {
	int32_t v10;
	glPushMatrix();
	{
		EnableClientState v15(32886);
		EnableClientState v16(32888);
		EnableState v17(LevelRenderer::getLayerFeature(a2, this->minecraft->options.graphics));
		EnableState v18(a4 ? 2912 : 0);
		v10 = 0;
		Mob* ve = this->minecraft->viewEntityMaybe;
		glTranslatef(-(float)(ve->prevPosX + (float)((float)(ve->posX - ve->prevPosX) * a3)), -(float)(ve->prevPosY + (float)((float)(ve->posY - ve->prevPosY) * a3)), -(float)(ve->prevPosZ + (float)((float)(ve->posZ - ve->prevPosZ) * a3)));
		for(auto&& i = this->field_19C.begin(); i != this->field_19C.end(); ++i) {
			MeshBuffer* mb = i->second->getRenderChunk(a2);
			if(mb->isValid()) {
				glPushMatrix();
				glTranslatef(mb->transformX, mb->transformY, mb->transformZ);
				v10 += this->_renderChunk(*mb);
				glPopMatrix();
			}
		}
		if(a2 == 2) {
			for(auto&& i = this->field_1B4.begin(); i != this->field_1B4.end(); ++i) {
				MeshBuffer* mb = i->second->getRenderChunk(2);
				if(mb->isValid()) {
					glPushMatrix();
					glTranslatef(mb->transformX, mb->transformY, mb->transformZ);
					v10 += this->_renderChunk(*mb);
					glPopMatrix();
				}
			}
		}
	}
	glPopMatrix();
	return v10;
}
void LevelRenderer::renderClouds(float a2) {
	float v4;			 // s17
	float v5;			 // r0
	LocalPlayer* player; // r3
	float v7;			 // s17
	float v8;			 // s19
	float v9;			 // s20
	float v10;			 // r0
	int32_t v11;		 // r8
	int32_t v12;		 // r7
	float v13;			 // s21
	int32_t v14;		 // r3
	float v16;			 // s19
	float v17;			 // r6
	float fov;			 // r0
	TextureData* td;	 // r9
	float r;			 // r0
	float g;			 // r1
	float b;			 // r2
	float a;			 // r3
	float v25;			 // [sp+0h] [bp-D8h] BYREF
	float iptr;			 // [sp+4h] [bp-D4h] BYREF

	v4 = this->minecraft->player->prevPosY + (float)((float)(this->minecraft->player->posY - this->minecraft->player->prevPosY) * a2);
	v5 = this->level->dimensionPtr->getCloudHeight();
	player = this->minecraft->player;
	v7 = (float)(v5 - v4) + 0.33;
	v8 = player->prevZ + (float)((float)(player->posZ - player->prevZ) * a2);
	v9 = modff((float)((float)(player->prevX + (float)((float)(player->posX - player->prevX) * a2)) + (float)((float)((float)this->ticksElapsed + a2) * 0.03)) * 0.0625, &v25);
	v10 = modff(v8 * 0.0625, &iptr);
	v11 = (int32_t)v25;
	v12 = (int32_t)iptr;
	v13 = v10;
	Color4 v30 = this->level->getCloudColor(a2);
	v14 = this->field_15C;
	v30.a = 0.7;
	if(v11 != v14 || v12 != this->field_160 || !this->cloudsMesh.isValid() || (float)((float)(fabsf(v30.r - this->field_164.r) + fabsf(v30.g - this->field_164.g)) + fabsf(v30.b - this->field_164.b)) > 0.06) {
		td = this->textures->loadAndGetTextureData("environment/clouds.png");
		TextureTesselator textes(td, v11 - 32, v12 - 32, v11 + 32, v12 + 32, Vec3(0, 0.70711, 0.70711), Color4(0.6, 0.6, 0.6, 1), v30); // [sp+54h] [bp-84h] BYREF
		this->cloudsMesh = textes.tesselate();
		r = v30.r;
		g = v30.g;
		b = v30.b;
		a = v30.a;
		this->field_15C = v11;
		this->field_160 = v12;
		this->field_164.r = r;
		this->field_164.g = g;
		this->field_164.b = b;
		this->field_164.a = a;
	}
	EnableState v27(2912);
	DisableState v28(3553);
	EnableClientState v29(32886);
	DisableState v15(this->minecraft->options.graphics ? 0 : 3042);

	v16 = this->minecraft->gameRenderer->field_8;
	v17 = sqrtf((float)(v7 * v7) + 262140.0);
	glFogf(0xB63u, 0.0);
	glFogf(0xB64u, v17);
	if(v7 > 1.0) {
		glDepthRange(0.0, 1.0); //XXX uses glDepthRangef
	}
	glPushMatrix();
	glTranslatef(-(float)(v9 * 16.0), v7, -(float)(v13 * 16.0));
	glScalef(16.0, 7.0, 16.0);
	glTranslatef(-32.0, 0.0, -32.0);
	glMatrixMode(0x1701u);
	glPushMatrix();
	glLoadIdentity();
	fov = this->minecraft->gameRenderer->getFov(a2, 1);
	gluPerspective(fov, (float)this->minecraft->field_1C / (float)this->minecraft->field_20, 2.0, v17);
	this->cloudsMesh.render();
	glPopMatrix();
	glMatrixMode(0x1700u);
	glPopMatrix();
	glFogf(0xB63u, v16 * 0.7);
	glFogf(0xB64u, v16);
	if(v7 > 1.0) {
		glDepthRange(0.0, 0.7); //XXX uses glDepthRangef
	}
	//DisableState::~DisableState((DisableState *)&textes);
	//EnableClientState::~EnableClientState((EnableClientState *)&res);
	//DisableState::~DisableState((DisableState *)&v28);
	//EnableState::~EnableState((EnableState *)&v27);
}
void LevelRenderer::renderDebug(const AABB& a2, float a3) {
	float minX; // r11
	float maxX; // r8
	float minY; // r10
	float maxY; // r7
	float minZ; // r9=
	float maxZ; // [sp+14h] [bp-4Ch]

	minX = a2.minX;
	maxX = a2.maxX;
	minY = a2.minY;
	maxY = a2.maxY;
	minZ = a2.minZ;
	maxZ = a2.maxZ;
	BlendFunctionState v14(0x306u, 0x300u);
	DisableState v12(0xDE1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	this->textures->loadAndBindTexture("terrain-atlas.tga");
	Tesselator::instance.begin(24);
	Tesselator::instance.color(0xFFu, 0xFFu, 0xFFu, 255);
	Vec3 v13 = this->minecraft->player->getPos(a3);
	Tesselator::instance.offset(Vec3(-v13.x, -v13.y, -v13.z));
	Tesselator::instance.vertexUV(minX, minY, maxZ, 0.0, 1.0);
	Tesselator::instance.vertexUV(minX, minY, minZ, 0.0, 0.0);
	Tesselator::instance.vertexUV(maxX, minY, minZ, 1.0, 0.0);
	Tesselator::instance.vertexUV(maxX, minY, maxZ, 1.0, 1.0);
	Tesselator::instance.vertexUV(maxX, maxY, maxZ, 1.0, 1.0);
	Tesselator::instance.vertexUV(maxX, maxY, minZ, 1.0, 0.0);
	Tesselator::instance.vertexUV(minX, maxY, minZ, 0.0, 0.0);
	Tesselator::instance.vertexUV(minX, maxY, maxZ, 0.0, 1.0);
	Tesselator::instance.vertexUV(minX, maxY, minZ, 1.0, 0.0);
	Tesselator::instance.vertexUV(maxX, maxY, minZ, 0.0, 0.0);
	Tesselator::instance.vertexUV(maxX, minY, minZ, 0.0, 1.0);
	Tesselator::instance.vertexUV(minX, minY, minZ, 1.0, 1.0);
	Tesselator::instance.vertexUV(minX, maxY, maxZ, 0.0, 0.0);
	Tesselator::instance.vertexUV(minX, minY, maxZ, 0.0, 1.0);
	Tesselator::instance.vertexUV(maxX, minY, maxZ, 1.0, 1.0);
	Tesselator::instance.vertexUV(maxX, maxY, maxZ, 1.0, 0.0);
	Tesselator::instance.vertexUV(minX, maxY, maxZ, 1.0, 0.0);
	Tesselator::instance.vertexUV(minX, maxY, minZ, 0.0, 0.0);
	Tesselator::instance.vertexUV(minX, minY, minZ, 0.0, 1.0);
	Tesselator::instance.vertexUV(minX, minY, maxZ, 1.0, 1.0);
	Tesselator::instance.vertexUV(maxX, minY, maxZ, 0.0, 1.0);
	Tesselator::instance.vertexUV(maxX, minY, minZ, 1.0, 1.0);
	Tesselator::instance.vertexUV(maxX, maxY, minZ, 1.0, 0.0);
	Tesselator::instance.vertexUV(maxX, maxY, maxZ, 0.0, 0.0);
	Tesselator::instance.offset(0.0, 0.0, 0.0);
	Tesselator::instance.draw(1);
}
void LevelRenderer::renderEntities(Vec3 a2, FrustumCuller* a3, bool_t a4, float a5)
{
	TileEntityRenderDispatcher::getInstance()->prepare(this->level, this->textures, this->minecraft->font, this->minecraft->viewEntityMaybe, a5);
	EntityRenderDispatcher::getInstance()->prepare(this->level, this->minecraft->font, this->minecraft->viewEntityMaybe, &this->minecraft->options, a5);
	this->field_178.clear(); //TODO check
	int v8 = this->field_18;
	if(v8 <= 0) {
		Minecraft* minecraft = this->minecraft;
		this->field_1C = 0;
		this->field_20 = 0;
		Mob* viewEntityMaybe = minecraft->viewEntityMaybe;
		float posY = viewEntityMaybe->posY;
		TileEntityRenderDispatcher::xOff = viewEntityMaybe->prevPosX + (float)((float)(viewEntityMaybe->posX - viewEntityMaybe->prevPosX) * a5);
		EntityRenderDispatcher::xOff = TileEntityRenderDispatcher::xOff;
		float v12 = viewEntityMaybe->prevPosY + (float)((float)(posY - viewEntityMaybe->prevPosY) * a5);
		float posZ = viewEntityMaybe->posZ;
		TileEntityRenderDispatcher::yOff = v12;
		EntityRenderDispatcher::yOff = v12;
		TileEntityRenderDispatcher::zOff = viewEntityMaybe->prevPosZ + (float)((float)(posZ - viewEntityMaybe->prevPosZ) * a5);
		EntityRenderDispatcher::zOff = TileEntityRenderDispatcher::zOff;
		{
			EnableClientState v47(0x8078u);
			EnableState v48(0xB60u);
			EnableClientState v49(0);
			EnableState v53(0);
			EnableState v54(0);
			EnableState v55(0);
			if(this->minecraft->options.graphics) {
				{
					EnableState v51(2896);
					v53.enabled = v51.enabled;
					v51.enabled = 0;
				}
				{
					EnableState v51(0x4000);
					v54.enabled = v51.enabled;
					v51.enabled = 0;
				}
				{
					EnableState v51(2977);
					v55.enabled = v51.enabled;
					v51.enabled = 0;
				}
				{
					EnableClientState v51(32885);
					v49.enabled = v51.enabled;
					v51.enabled = 0;
				}
			}
			std::vector<struct Entity*>* ents = this->level->getAllEntities();
			int v21 = ents->size();
			this->field_1C = v21;
			if(v21 > 0) {
				for(int i = 0; i < this->field_1C; ++i) {
					Entity* v25 = ents->at(i);
					if(v25->shouldRender(a2)) {
						if(a3->isVisible(v25->boundingBox) || v25->rider == this->minecraft->player) {
							Minecraft* v43 = this->minecraft;
							if(v25 != v43->viewEntityMaybe || v43->options.thirdPerson || !v25->isPlayer() || this->minecraft->viewEntityMaybe->isSleeping()) {
								Minecraft* v26 = this->minecraft;
								if(v25 != v26->viewEntityMaybe || v26->options.thirdPerson) {
									int x = Mth::floor(v25->posX);
									int v27 = Mth::floor(v25->posY);
									int v28 = Mth::floor(v25->posZ);
									if(this->level->hasChunkAt(x, v27, v28)) {
										this->field_178.insert({v25->entityRenderId, v25}); //TODO check
									}
								}
							}
						}
					}
				}

				for(auto&& p: this->field_178) {
					EntityRenderDispatcher::getInstance()->render(p.second, a5);
				}
			}
			this->field_190.clear();
			Level* level = this->level;
			for(auto&& v40: level->tileEntities) {
				if(a3->isVisible(v40->aabb)) {
					if(v40->getShadowRadius() != 0.0) {
						this->field_190.emplace_back(v40);
					}
					TileEntityRenderDispatcher::getInstance()->render(v40, a5);
				}
			}
		}
		if ( a4 )
		{
			this->renderShadows(this->field_178, this->field_190, a5);
		}
	}
	else
	{
		this->field_18 = v8 - 1;
	}
}

int32_t LevelRenderer::renderFarChunks(float a2) {
	int32_t v4;			  // r7
	Mob* viewEntityMaybe; // r3
	int32_t v9;			  // r7

	glPushMatrix();
	{
		EnableClientState v11(32886);
		EnableClientState v12(32888);
		EnableState v13(2912);
		v4 = 0;
		viewEntityMaybe = this->minecraft->viewEntityMaybe;
		glTranslatef(-(float)(viewEntityMaybe->prevPosX + (float)((float)(viewEntityMaybe->posX - viewEntityMaybe->prevPosX) * a2)), -(float)(viewEntityMaybe->prevPosY + (float)((float)(viewEntityMaybe->posY - viewEntityMaybe->prevPosY) * a2)), -(float)(viewEntityMaybe->prevPosZ + (float)((float)(viewEntityMaybe->posZ - viewEntityMaybe->prevPosZ) * a2)));
		for(auto&& i = this->field_1B4.begin(); i != this->field_1B4.end(); ++i) {
			RenderChunk* v6 = i->second;
			if(!v6->built || !v6->skipRenderMaybe) {
				MeshBuffer* rc = v6->getRenderChunk(0);
				glPushMatrix();
				glTranslatef(rc->transformX, rc->transformY, rc->transformZ);
				v9 = v4 + this->_renderChunk(*v6->getRenderChunk(3));
				v4 = v9 + this->_renderChunk(*rc);
				glPopMatrix();
			}
		}
		//EnableState::~EnableState((EnableState*)&v13);
		//EnableClientState::~EnableClientState(&v12);
		//EnableClientState::~EnableClientState(&v11);
	}
	glPopMatrix();
	return v4;
}
void LevelRenderer::renderFilledHitSelect(Player* a2, float a3, Tile* a4, const HitResult& a5) {
	float v10;		// s18
	float prevPosZ; // s15
	float v12;		// s17
	float posZ;		// s14

	DisableState v14(3553);
	BlendFunctionState v16(0x306u, 0x300u);
	EnableState v15(32823);
	glPushMatrix();
	this->textures->loadAndBindTexture("terrain-atlas.tga");
	glColor4f(0.65, 0.65, 0.65, 0.65);
	v10 = a2->prevPosX + (float)((float)(a2->posX - a2->prevPosX) * a3);
	prevPosZ = a2->prevPosZ;
	v12 = a2->prevPosY + (float)((float)(a2->posY - a2->prevPosY) * a3);
	posZ = a2->posZ;
	Tesselator::instance.begin(0);
	Tesselator::instance.offset(-v10, -v12, -(float)(prevPosZ + (float)((float)(posZ - prevPosZ) * a3)));
	Tesselator::instance.noColor();
	if(!a4) {
		a4 = Tile::rock;
	}
	this->field_70->tesselateInWorld(a4, a5.field_4, a5.field_8, a5.field_C);
	Tesselator::instance.draw(1);
	Tesselator::instance.offset(0.0, 0.0, 0.0);
	glDepthMask(1u);
	glPopMatrix();
	//EnableState::~EnableState((EnableState *)&v15);
	//BlendFunctionState::~BlendFunctionState((BlendFunctionState *)&v16);
	//DisableState::~DisableState((DisableState *)&v14);
}
void LevelRenderer::renderHit(Player* a2, const HitResult& a3, int32_t df, void* a5, float a6) {
	Tile* v8;	 // r7
	int32_t v10; // r0
	int32_t v11; // r9
	int32_t v12; // r4
	int32_t v14; // r5
	int32_t v16; // [sp+10h] [bp-28h] BYREF

	if(!df && this->field_14 > 0.0) {
		v8 = 0;
		BlendFunctionState v17(0x306u, 0);
		glPushMatrix();
		{
			EnableState v16(32823);
			this->textures->loadAndBindTexture("terrain-atlas.tga");
			v10 = this->level->getTile(a3.field_4, a3.field_8, a3.field_C);
			if(v10 > 0) {
				v8 = Tile::tiles[v10];
			}
			Tesselator::instance.begin(0);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			Tesselator::instance.noColor();
			glTranslatef(-EntityRenderDispatcher::xOff, -EntityRenderDispatcher::yOff, -EntityRenderDispatcher::zOff);
			if(!v8) {
				v8 = Tile::rock;
			}
			v11 = a3.field_4;
			v12 = a3.field_8;
			v14 = a3.field_C;
			this->field_70->tesselateInWorld(v8, v11, v12, v14, *this->destroyTexture.getUV((int32_t)(float)(this->field_14 * 10.0)));
			Tesselator::instance.draw(1);
			//EnableState::~EnableState((EnableState*)&v16);
		}
		glPopMatrix();
		//BlendFunctionState::~BlendFunctionState((BlendFunctionState *)&v17);
	}
}
void LevelRenderer::renderHitOutline(Player* a2, const HitResult& a3, int32_t a4, void*, float a6) {
	int32_t v9;	 // r0
	int32_t v10; // r8
	float v11;	 // s17
	float v12;	 // s18
	float v13;	 // s16

	if(!a4 && a3.hitType == 0) {
		glColor4f(0.0, 0.0, 0.0, 0.4);
		glLineWidth(1.0);
		DisableState v14(3553);
		v9 = this->level->getTile(a3.field_4, a3.field_8, a3.field_C);
		v10 = v9;
		if(v9 > 0) {
			Tile::tiles[v9]->updateShape(this->level, a3.field_4, a3.field_8, a3.field_C);
			v11 = a2->prevPosX + (float)((float)(a2->posX - a2->prevPosX) * a6);
			v12 = a2->prevPosY + (float)((float)(a2->posY - a2->prevPosY) * a6);
			v13 = a2->prevPosZ + (float)((float)(a2->posZ - a2->prevPosZ) * a6);
			AABB v15 = Tile::tiles[v10]->getTileAABB(this->level, a3.field_4, a3.field_8, a3.field_C);
			AABB v16{
				.minX = (float)(v15.minX - 0.002) - v11,
				.minY = (float)(v15.minY - 0.002) - v12,
				.minZ = (float)(v15.minZ - 0.002) - v13,
				.maxX = (float)(v15.maxX + 0.002) - v11,
				.maxY = (float)(v15.maxY + 0.002) - v12,
				.maxZ = (float)(v15.maxZ + 0.002) - v13,
			};

			this->render(v16);
		}
		//~v14
	}
}
void LevelRenderer::renderHitSelect(Player* a2, const HitResult& a3, int32_t a4, void* a5, float a6) {
	if(a4 == 0) {
		Tile* v8 = 0;
		EnableState v11(32823);
		DisableState v12(3553);
		BlendFunctionState v13(0x306u, 0x300u);
		glPushMatrix();
		int32_t v9 = this->level->getTile(a3.field_4, a3.field_8, a3.field_C);
		if(v9 > 0) v8 = Tile::tiles[v9];
		glColor4f(0.65, 0.65, 0.65, 1.0);
		glTranslatef(-EntityRenderDispatcher::xOff, -EntityRenderDispatcher::yOff, -EntityRenderDispatcher::zOff);
		Tesselator::instance.begin(0);
		Tesselator::instance.noColor();
		if(!v8) {
			v8 = Tile::rock;
		}
		this->field_70->tesselateInWorld(v8, a3.field_4, a3.field_8, a3.field_C);
		Tesselator::instance.draw(1);
		Tesselator::instance.offset(0.0, 0.0, 0.0);
		glPopMatrix();
	}
}
void LevelRenderer::renderNameTags(float a2) {
	glDepthFunc(GL_ALWAYS);

	for(auto&& p: this->field_178) {
		EntityRenderer* er = EntityRenderDispatcher::getInstance()->getRenderer(p.second->entityRenderId);
		if(er) {
			er->renderName(p.second, a2);
		}
	}

	glDepthFunc(GL_LEQUAL);
}
void LevelRenderer::renderOutlineHitSelect(Player* a2, float a3, Tile* a4, const HitResult& a5) {
	DisableState v7(0xDE1u);
	glDepthMask(0);
	glColor4f(0.0, 0.0, 0.0, 0.4);
	AABB v8 = a4->getTileAABB(this->level, a5.field_4, a5.field_8, a5.field_C);
	this->render({v8.minX + 0.002f, v8.minY + 0.002f, v8.minZ + 0.002f, v8.maxX - 0.002f, v8.maxY - 0.002f, v8.maxZ - 0.002f});
	glDepthMask(1u);
}
void LevelRenderer::renderShadows(const std::multimap<int32_t, Entity*, std::greater<int>>& a2, const std::vector<TileEntity*>& a3, float a4) {
	float v8;		 // s18
	float v9;		 // s20
	float v10;		 // s19
	int v11;		 // r6
	int v12;		 // r8
	Entity* v13;	 // r5
	float v14;		 // s18
	TileEntity* v18; // t1
	float v19;		 // s18

	DisableState v20(3553);
	glDepthMask(0);
	EnableState v21(2960); //destroyed befrore glDepthMask(1);
	Color4 color = this->level->getSkyColor(this->minecraft->viewEntityMaybe, a4);
	v8 = (float)(color.r * 0.5) + 0.4;
	v9 = (float)(color.g * 0.5) + 0.4;
	v10 = (float)(color.b * 0.5) + 0.4;
	Color4 v26 = this->level->getSunriseColor(a4);
	color.a = 1.0;
	color.b = (float)((float)((float)(v26.a * v26.b) + (float)(v10 * (float)(1.0 - v26.a))) * 0.8) * 0.25;
	color.g = (float)((float)((float)(v26.a * v26.g) + (float)(v9 * (float)(1.0 - v26.a))) * 0.8) * 0.25;
	color.r = (float)((float)((float)(v26.a * v26.r) + (float)(v8 * (float)(1.0 - v26.a))) * 0.8) * 0.25;
	color.clamp();
	color.a = (float)((float)((float)((float)(color.r + color.g) + color.b) * 0.33333) * 1.2) + 0.1;
	if((float)((float)(fabsf(this->shadowRed - color.r) + fabsf(this->shadowGreen - color.g)) + fabsf(this->shadowBlue - color.b)) > 0.05 || !this->shadowOverlayBuffer.arrayBuffer) {
		this->_buildShadowOverlay(color);
	}
	glPushMatrix();
	glColorMask(0, 0, 0, 0);
	{
		EnableState v24(32823);
		glTranslatef(-EntityRenderDispatcher::xOff, -EntityRenderDispatcher::yOff, -EntityRenderDispatcher::zOff);
		for(auto&& v11: a2) {
			Entity* v13 = v11.second;
			v14 = v13->getShadowRadius();
			if(v14 != 0.0 && !v13->isOnFire()) {
				Vec3 v25(v13->prevPosX + (float)((float)(v13->posX - v13->prevPosX) * a4), (float)((float)(v13->prevPosY + (float)((float)(v13->posY - v13->prevPosY) * a4)) - v13->ridingHeight) + v13->field_74, v13->prevPosZ + (float)((float)(v13->posZ - v13->prevPosZ) * a4));
				this->_renderShadow(v14, v25, a4);
			}
		}

		for(auto&& v18: a3) {
			v19 = v18->getShadowRadius();
			if(v19 != 0.0) {
				Vec3 v25((float)v18->posX + 0.5, (float)v18->posY, (float)v18->posZ + 0.5);
				this->_renderShadow(v19, v25, a4);
			}
		}
	}
	glColorMask(1u, 1u, 1u, 1u);
	glPopMatrix();
	glShadeModel(0x1D01u);
	{
		EnableState v22(3042);
		DisableState v23(2929);
		DisableState v24(2884);
		EnableClientState v25(0x8076u);
		glMatrixMode(0x1701u);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode(0x1700u);
		glPushMatrix();
		glLoadIdentity();
		this->minecraft->gameRenderer->setupCamera(a4, 1);
		if(this->minecraft->options.thirdPerson) {
			glTranslatef(0.0, -3.0, 0.0);
		}
		glStencilFunc(0x202u, 1, 0xFFu);
		this->shadowOverlayBuffer.render();
		glMatrixMode(0x1701u);
		glPopMatrix();
		glMatrixMode(0x1700u);
		glPopMatrix();
	}
	glShadeModel(0x1D00u);
	glDepthMask(1u);
}
void LevelRenderer::renderSky(float a2) {
	Dimension* dimensionPtr; // r3
	int32_t v5;				 // r6
	Entity* v6;				 // [sp+4h] [bp-2Ch] BYREF
	float v7;				 // [sp+8h] [bp-28h] BYREF
	int32_t v8;				 // [sp+Ch] [bp-24h] BYREF

	dimensionPtr = this->minecraft->level->dimensionPtr;
	v5 = dimensionPtr->field_C;
	if(!dimensionPtr->field_C) {
		glDepthMask(dimensionPtr->field_C);
		{
			EnableState v6(0xB60);
			DisableState v7(0xB44);
			DisableState v8(0xDE1);
			Color4 red = this->level->getSkyColor(this->minecraft->viewEntityMaybe, a2);
			glColor4f(red.r, red.g, red.b, 1.0);
			this->skyMesh.render();
			//~v8, ~v7, ~v6
		}
		this->_renderSunOrMoon(a2, 1);
		this->_renderSunOrMoon(a2, v5);
		this->_renderStars(a2);
		glDepthMask(1u);
	}
}
int32_t LevelRenderer::renderStencilChunks(float a2) {
	int v4;	 // r6
	Mob* ve; // r3

	glPushMatrix();
	v4 = 0;
	ve = this->minecraft->viewEntityMaybe;
	glTranslatef(-(float)(ve->prevPosX + (float)((float)(ve->posX - ve->prevPosX) * a2)), -(float)(ve->prevPosY + (float)((float)(ve->posY - ve->prevPosY) * a2)), -(float)(ve->prevPosZ + (float)((float)(ve->posZ - ve->prevPosZ) * a2)));
	for(auto&& i = this->field_1B4.begin(); i != this->field_1B4.end(); ++i) {
		MeshBuffer* rc = i->second->getRenderChunk(2);
		glPushMatrix();
		glTranslatef(rc->transformX, rc->transformY, rc->transformZ);
		v4 += this->_renderChunk(*rc);
		glPopMatrix();
	}
	glPopMatrix();
	return v4;
}
void LevelRenderer::resortChunks(int32_t a2, int32_t a3, int32_t a4) {
	int v5;			  // r11
	int v6;			  // r5
	int v7;			  // r8
	int v8;			  // r0
	int v9;			  // r6
	int v10;		  // r7
	int v11;		  // r3
	int v12;		  // r10
	int v13;		  // r0
	int v14;		  // r0
	int v15;		  // r9
	int v16;		  // r3
	int v17;		  // r2
	int v18;		  // r3
	int v19;		  // r1
	bool v20;		  // cc
	int renderXsize;  // r1
	int renderYsize;  // r3
	int z;			  // [sp+8h] [bp-48h]
	int isDirty;	  // [sp+14h] [bp-3Ch]
	RenderChunk* v26; // [sp+24h] [bp-2Ch] BYREF

	v5 = 0;
	v6 = 16 * this->renderXsize;
	this->field_40 = 0x7FFFFFFF;
	this->field_44 = 0x7FFFFFFF;
	this->field_48 = 0x7FFFFFFF;
	v7 = (v6 >> 1) + 8 - a2;
	this->field_4C = 0x80000000;
	this->field_50 = 0x80000000;
	this->field_54 = 0x80000000;
	while(v5 < this->renderXsize) {
		v8 = v7;
		if(v7 < 0) {
			v8 = 1 - v6;
		}
		if(v7 < 0) {
			v8 += v7;
		}
		v9 = 0;
		v10 = 16 * v5 - v6 * (v8 / v6);
		v11 = this->field_4C;
		if(v10 < this->field_40) {
			this->field_40 = v10;
		}
		if(v10 > v11) {
			this->field_4C = v10;
		}
		v12 = 8 - a4 + (v6 >> 1);
		while(v9 < this->renderZSize) {
			v13 = v12;
			if(v12 < 0) {
				v13 = 1 - v6 + v12;
			}
			v14 = 16 * v9 - v6 * (v13 / v6);
			v15 = 0;
			v16 = this->field_54;
			z = v14;
			if(v14 < this->field_48) {
				this->field_48 = v14;
			}
			if(v14 > v16) {
				this->field_54 = v14;
			}
			while(1) {
				renderYsize = this->renderYsize;
				if(v15 >= renderYsize) {
					break;
				}
				v17 = 16 * v15;
				v18 = v15 + renderYsize * v9;
				v19 = this->field_50;
				if(16 * v15 < this->field_44) {
					this->field_44 = v17;
				}
				v20 = v17 <= v19;
				renderXsize = this->renderXsize;
				if(!v20) {
					this->field_50 = v17;
				}
				v26 = this->chunks[v5 + renderXsize * v18];
				isDirty = v26->isDirty();
				v26->setPos(v10, 16 * v15, z);
				if(!isDirty) {
					if(v26->isDirty()) {
						this->_renderChunks.push_back(v26);
					}
				}
				++v15;
			}
			++v9;
			v12 += 16;
		}
		++v5;
		v7 += 16;
	}
}
void LevelRenderer::setDirty(int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2) {
	int32_t v10;		 // r5
	int32_t v11;		 // r10
	int32_t v12;		 // r11
	int32_t v13;		 // r1
	int32_t v14;		 // r8
	int32_t i;			 // r6
	int32_t v16;		 // r1
	int32_t v17;		 // r9
	int32_t j;			 // r7
	int32_t v19;		 // r1
	int32_t renderZSize; // [sp+4h] [bp-44h]
	int32_t v21;		 // [sp+8h] [bp-40h]
	int32_t v22;		 // [sp+Ch] [bp-3Ch]
	int32_t v23;		 // [sp+10h] [bp-38h]
	RenderChunk* v24;	 // [sp+1Ch] [bp-2Ch] BYREF

	v10 = Mth::intFloorDiv(x1, 16);
	v21 = Mth::intFloorDiv(y1, 16);
	v22 = Mth::intFloorDiv(z1, 16);
	v23 = Mth::intFloorDiv(x2, 16);
	v11 = Mth::intFloorDiv(y2, 16);
	v12 = Mth::intFloorDiv(z2, 16);
	while(v10 <= v23) {
		v13 = v10 % this->renderXsize;
		v14 = v13;
		if(v13 < 0) {
			v14 = v13 + this->renderXsize;
		}
		for(i = v21; i <= v11; ++i) {
			v16 = i % this->renderYsize;
			v17 = v16;
			if(v16 < 0) {
				v17 = v16 + this->renderYsize;
			}
			for(j = v22; j <= v12; ++j) {
				renderZSize = this->renderZSize;
				v19 = j % renderZSize;
				if(j % renderZSize < 0) {
					v19 += renderZSize;
				}
				v24 = this->chunks[v14 + this->renderXsize * (v17 + this->renderYsize * v19)];
				if(!v24->isDirty()) {
					this->_renderChunks.push_back(v24);
					v24->setDirty();
				}
			}
		}
		++v10;
	}
}
void LevelRenderer::setLevel(Level* a2) {
	if(this->level) {
		this->level->removeListener(this);
	}
	this->field_8 = -9999;
	this->field_C = -9999;
	this->field_10 = -9999;

	EntityRenderDispatcher::getInstance()->setLevel(a2);
	EntityRenderDispatcher::getInstance()->setMinecraft(this->minecraft);
	TileEntityRenderDispatcher::getInstance()->minecraft = this->minecraft;
	this->level = a2;
	delete this->field_70;
	this->field_70 = new TileRenderer(a2);
	if(a2) {
		a2->addListener(this);
		this->allChanged();
	}
	this->field_178.clear(); //TODO check
}
void LevelRenderer::tick() {
	++this->ticksElapsed;
}
bool LevelRenderer::updateDirtyChunks(Mob* a2, bool_t a3) {
	DirtyChunkSorter v37{a2};
	RenderChunk* v39[3] = {0};
	int v6 = 0;
	std::vector<RenderChunk*>* v7 = 0;
	int v8 = this->_renderChunks.size();
	for(int v5 = 0; v5 < v8; ++v5) {
		RenderChunk* v9 = this->_renderChunks[v5];
		if(a3) {
			if(!v9->isInFrustumMaybe) {
				continue;
			}
LABEL_4:
			if(!v7) {
				v7 = new std::vector<RenderChunk*>();
			}
			v7->push_back(v9);
			++v6;
			this->_renderChunks[v5] = 0;
			continue;
		}
		if(v9->distanceToSqr(a2) <= 1024) {
			goto LABEL_4;
		}

		int i;
		for(i = 0; i != 3; ++i) {
			if(v39[i] && !v37(v39[i], v9)) {
				break;
			}
		}
		int v12 = i - 1;
		if(v12 > 0) {
			RenderChunk* v13 = v39[0];
			if(v12 != 1) {
				v13 = v39[1];
			}
			v39[0] = v13;
			v39[v12] = v9;
		}
	}
	Stopwatch v40;
	v40.start();
	if(v7) {
		int v16 = v7->size();
		if(v16 > 1) {
			std::sort(v7->begin(), v7->end(), v37);
		}
		int v19 = v7->size();
		int v20 = v19 - 1;
		while(v20 >= 0) {
			RenderChunk* v22 = v7->at(v20);
			--v20;
			v22->rebuild();
			v22->setClean();
		}
		delete v7;
	}

	int v23 = 2;
	int v24 = 0;
	RenderChunk* v25;
	while(1) {
		v25 = v39[v23];
		if(v25) break;
LABEL_38:
		if(v23-- == 0) {
			goto LABEL_39;
		}
	}
	if(v40.stopContinue() >= 0.01) {
		goto LABEL_39;
	}
	if(v25->isInFrustumMaybe || v23 == 2) {
		++v24;
		v25->rebuild();
		v25->setClean();
		goto LABEL_38;
	}
	v39[v23] = 0;
	v39[0] = 0;
LABEL_39:
	int v30 = 0;
	int k;
	for(k = 0; k != this->_renderChunks.size(); ++k) {
		RenderChunk* v33 = this->_renderChunks[k];
		if(v33) {
			if(v33 != v39[0] && v33 != v39[1] && v33 != v39[2]) {
				if(v30 != k) {
					this->_renderChunks[v30] = v33;
				}
				++v30;
			}
		}
	}
	if(k > v30) {
		this->_renderChunks.resize(v30);
	}
	return v8 == v6 + v24;
}

LevelRenderer::~LevelRenderer() {
	delete this->field_70;
	this->deleteChunks();
	this->field_70 = 0;
	AppPlatform::_singleton->removeListener(this);
}
void LevelRenderer::setTilesDirty(int32_t x1, int32_t y1, int32_t z1, int32_t x2, int32_t y2, int32_t z2) {
	this->setDirty(x1 - 1, y1 - 1, z1 - 1, x2 + 1, y2 + 1, z2 + 1);
}
void LevelRenderer::tileChanged(int32_t x, int32_t y, int32_t z) {
	this->setDirty(x - 1, y - 1, z - 1, x + 1, y + 1, z + 1);
}
void LevelRenderer::skyColorChanged() {
	for(int32_t i = 0; i < this->chunksToRenderSize; ++i) {
		RenderChunk* rc = this->chunks[i];
		if(rc->touchedSky) {
			if(!rc->isDirty()) {
				this->_renderChunks.push_back(rc);
				rc->setDirty();
			}
		}
	}
}
void LevelRenderer::allChanged() {
	Minecraft* minecraft; // r1
	int renderDistance;	  // r2
	int v7;				  // r3
	int x;				  // r5
	int v9;				  // r11
	int v10;			  // r9
	int v11;			  // r3
	int v12;			  // r0
	RenderChunk** v13;	  // r0
	int renderXsize;	  // r3
	int renderYsize;	  // r3
	RenderChunk* v16;	  // r6
	bool_t v17;			  // r3
	int z;				  // r8
	int y;				  // r7
	int v20;			  // [sp+14h] [bp-44h]
	RenderChunk* v21;	  // [sp+20h] [bp-38h] BYREF
	int v22;			  // [sp+24h] [bp-34h]
	int v23;			  // [sp+28h] [bp-30h]
	int v24;			  // [sp+2Ch] [bp-2Ch]

	this->deleteChunks();
	for(Tile* t: Tile::tiles) {
		if(t) {
			t->onGraphicsModeChanged(this->minecraft->options.graphics);
		}
	}

	v22 = 0x7F7FFFFF;
	v23 = 0x7F7FFFFF;
	v24 = 0x7F7FFFFF;
	this->field_1CC.x = FLT_MAX;
	this->field_1CC.y = FLT_MAX;
	this->field_1CC.z = FLT_MAX;
	minecraft = this->minecraft;
	renderDistance = minecraft->options.renderDistance;
	this->renderDistance = renderDistance;
	v7 = 64 << (3 - renderDistance);
	if(renderDistance <= 2) {
		if(minecraft->powerVR) {
			v7 = (int)(float)((float)v7 * 0.8);
		}
	}
	if(v7 >= 400) {
		v7 = 400;
	}
	this->renderYsize = 8;
	x = 0;
	v9 = 0;
	v10 = 0;
	v11 = v7 / 16 + 1;
	this->renderXsize = v11;
	this->renderZSize = v11;
	v12 = v11 * 8 * v11;
	this->chunksToRenderSize = v12;
	v13 = new RenderChunk*[v12];
	renderXsize = this->renderXsize;
	this->field_40 = 0;
	this->field_44 = 0;
	this->field_4C = renderXsize;
	renderYsize = this->renderYsize;
	this->field_48 = 0;
	this->field_50 = renderYsize;
	this->field_54 = this->renderZSize;
	this->_renderChunks.clear();
	this->chunks = v13;
	while(x < this->renderXsize) {
		for(y = 0; y < this->renderYsize; ++y) {
			z = 0;
			while(z < this->renderZSize) {
				v20 = x + this->renderXsize * (y + this->renderYsize * z);
				v16 = new RenderChunk(this->level, 16 * x, 16 * y, 16 * z, 16, this->field_80 + v10);
				v17 = this->field_88;
				v21 = v16;
				if(v17) {
					v16->field_50 = 0;
				}
				v16->field_48 = z + v9;
				v16->field_4D = 1;
				v16->isInFrustumMaybe = 1;
				v10 += 3;
				v16->field_4E = 0;
				++z;
				v16->setDirty();
				this->chunks[v20] = v21;
				this->_renderChunks.push_back(v21);
			}
			v9 += z;
		}
		++x;
	}
	this->field_18 = 2;
}

static char _D6E06888[256];
void LevelRenderer::takePicture(TripodCamera* a2, Entity* a3) {
	Minecraft* minecraft; // r3
	Mob* ve;			  // r6
	bool hideGUI;		  // r8
	bool thirdPerson;	  // r7
	int TimeMs;			  // r0

	minecraft = this->minecraft;
	ve = minecraft->viewEntityMaybe;
	hideGUI = minecraft->options.hideGUI;
	thirdPerson = minecraft->options.thirdPerson;
	minecraft->viewEntityMaybe = (Mob*)a2;
	this->minecraft->options.hideGUI = 1;
	this->minecraft->options.thirdPerson = 0;
	this->minecraft->gameRenderer->renderLevel(0.0);
	this->minecraft->viewEntityMaybe = ve;
	this->minecraft->options.hideGUI = hideGUI;
	this->minecraft->options.thirdPerson = thirdPerson;
	t_keepPic = -1;
	sprintf(_D6E06888, "%s/games/com.mojang/img_%.4d.jpg", this->minecraft->dataPathMaybe.c_str(), getTimeMs());
	this->minecraft->platform()->saveScreenshot(_D6E06888, this->minecraft->field_1C, this->minecraft->field_20);
}
Particle* LevelRenderer::addParticle(ParticleType a2, float x, float y, float z, float a6, float a7, float a8, int32_t a9) {
	Minecraft* minecraft; // r4
	Mob* viewEntityMaybe; // r0

	minecraft = this->minecraft;
	viewEntityMaybe = minecraft->viewEntityMaybe;
	if((float)((float)((float)((float)(viewEntityMaybe->posY - y) * (float)(viewEntityMaybe->posY - y)) + (float)((float)(viewEntityMaybe->posX - x) * (float)(viewEntityMaybe->posX - x))) + (float)((float)(viewEntityMaybe->posZ - z) * (float)(viewEntityMaybe->posZ - z))) > 256.0) {
		return 0;
	} else {
		return minecraft->particleEngine->instance(a2, x, y, z, a6, a7, a8, a9);
	}
}
void LevelRenderer::playSound(const std::string& a2, float x, float y, float z, float a6, float a7) {
	float v12; // s17

	v12 = 16.0;
	if(a6 > 1.0) {
		v12 = a6 * 16.0;
	}
	if(this->minecraft->viewEntityMaybe->distanceToSqr(x, y, z) < (float)(v12 * v12)) {
		this->minecraft->soundEngine->play(a2, x, y, z, a6, a7);
	}
}
void LevelRenderer::entityAdded(Entity* a2) {
	a2->isPlayer();
}
void LevelRenderer::levelEvent(Player* player, int32_t event, int32_t x, int32_t y, int32_t z, int32_t) {
	if(event == 1003) {
		this->level->playSound((float)x + 0.5, (float)y + 0.5, (float)z + 0.5, Mth::random() >= 0.5 ? "random.door_close" : "random.door_open", 1.0, (float)(level->random.nextFloat() * 0.1) + 0.9);
	}
}
void LevelRenderer::onAppSuspended() {
	this->shadowVolumeBuffer.reset();
	this->shadowOverlayBuffer.reset();
	this->starsMesh.reset();
	this->cloudsMesh.reset();
	this->skyMesh.reset();
	this->deleteChunks();
}
void LevelRenderer::onAppResumed() {
	this->_initResources();
	this->allChanged();
}
