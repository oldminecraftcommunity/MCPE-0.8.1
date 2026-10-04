#pragma once
#include <_types.h>
#include <glm/glm.hpp>
#include <rendering/MeshBuffer.hpp>
#include <vector>
#include <math/Vec3.hpp>
#include <map>
#include <unordered_map>
#include <memory>

struct Tesselator{
	static Tesselator instance;
	struct CurrentVertexPointers{
		uint8_t* field_0;
		uint8_t* hasColor;
		uint8_t* hasNormals;
		uint8_t* hasTexture;
		const MeshBuffer::VertexFormat* field_10;

		CurrentVertexPointers() {
			this->field_0 = 0;
			this->hasColor = 0;
			this->hasNormals = 0;
			this->hasTexture = 0;
		}
		CurrentVertexPointers(uint8_t* a2, const MeshBuffer::VertexFormat& a3) {
			this->field_10 = &a3;
			this->field_0 = 0;
			this->hasColor = 0;
			this->hasNormals = 0;
			this->hasTexture = 0;
			this->field_0 = &a2[a3.offsets[0]];
			if (a3.offsets[2] != 255) this->hasColor = &a2[a3.offsets[2]];

			if (a3.offsets[3] != 255) this->hasNormals = &a2[a3.offsets[3]];

			if (a3.offsets[1] != 255) this->hasTexture = &a2[a3.offsets[1]];
		}
	};

	Tesselator::CurrentVertexPointers currentVertexPointers;
	std::vector<uint8_t> field_14;
	std::vector<uint8_t> vertexes;
	int32_t someSIzeMaybe;
	int32_t useDrawElementsOrDrawArrays;
	std::unordered_map<uint32_t, std::unique_ptr<MeshBuffer::VertexFormat>> field_34;
	int32_t field_4C;
	int32_t field_50;
	MeshBuffer::VertexFormat meshBuffer_vf2;
	int32_t vertexFormat;
	Vec3 vec;
	float textureU;
	float textureV;
	int32_t color_int;
	int8_t normX;
	int8_t normY;
	int8_t normZ;
	int8_t field_7B;
	float scale2;
	float scale1;
	float scale3;
	float scale4;
	float scale5;
	int8_t isTilted;
	int8_t field_91;
	int8_t field_92;
	int8_t field_93;
	glm::mat4x4 tmat4x4_2;
	uint8_t field_D4;
	int8_t isColorDisabled;
	uint8_t field_D6;
	int8_t field_D7;
	int32_t vertexCount;
	int32_t maxVertextNumber;
	int8_t isDrawing;
	int8_t field_E1;
	int8_t field_E2;
	int8_t field_E3;
	int32_t bufSize;
	int32_t field_E8;
	int32_t drawMode;
	int32_t accessMode;
	std::map<uint32_t, int32_t> stdTree;

	Tesselator(int32_t);
	void _buildQuadIndexBuffer();
	MeshBuffer::VertexFormat* _genVertexFormat() {
		uint32_t offsets = *(uint32_t*)this->meshBuffer_vf2.offsets;
		auto&& pp = this->field_34.find(offsets);
		if(pp != this->field_34.end()) {
			return pp->second.get();
		}

		MeshBuffer::VertexFormat* v7 = new MeshBuffer::VertexFormat(this->meshBuffer_vf2);
		this->field_34[offsets] = std::unique_ptr<MeshBuffer::VertexFormat>(v7);
		return v7;
	}
	void addOffset(const Vec3&);
	void addOffset(float, float, float);
	void begin(int32_t);
	void begin(int32_t, int32_t);
	void beginOverride() {
		this->begin(0);
		this->voidBeginAndEndCalls(true);
	}
	void cancel(void);
	void clear(void);
	void color(char, char, char);
	void color(float, float, float);
	void color(float, float, float, float);
	void color(int32_t);
	void color(int32_t, int32_t);
	void color(int32_t, int32_t, int32_t);
	void color(int32_t, int32_t, int32_t, int32_t);
	void colorABGR(int32_t);
	void draw(bool_t);
	void enableColor(void);
	MeshBuffer end(void);
	void endOverrideAndDraw(void) {
		this->voidBeginAndEndCalls(0);
		this->draw(1);
	}
	int32_t getColor(void);
	int32_t getVertexCount(void);
	void init();
	void noColor(void);
	void normal(const Vec3& v) {
		this->normal(v.x, v.y, v.z);
	}
	void normal(float, float, float);
	void offset(const Vec3&);
	void offset(float, float, float);
	void quad(bool_t b) {
		this->quad(this->maxVertextNumber - 4, b);
	}
	void quad(uint16_t, bool_t);
	void quad(uint16_t, uint16_t, uint16_t, uint16_t);
	void resetScale(void);
	void resetTilt(void);
	void scale2d(float, float);
	void scale3d(float, float, float);
	void setAccessMode(int32_t);
	void setMaxVertexNumber(int32_t);
	void tex(float, float);
	void tilt(void);
	void triangle(uint16_t a2, uint16_t a3, uint16_t a4) { //TODO
		unsigned int v8;											   // r5
		int useDrawElementsOrDrawArrays;							   // r5
		uint8_t* v12;												   // r0
		uint8_t* v13;												   // r3
		uint16_t* v14;												   // r3

		if(!this->someSIzeMaybe) {
			this->someSIzeMaybe = 2;
		}
		v8 = (this->useDrawElementsOrDrawArrays + 3) * this->someSIzeMaybe;
		this->vertexes.resize(v8); //TODO check

		useDrawElementsOrDrawArrays = this->useDrawElementsOrDrawArrays;
		v12 = this->vertexes.data();
		if(this->someSIzeMaybe == 1) {
			v13 = &v12[useDrawElementsOrDrawArrays];
			v12[useDrawElementsOrDrawArrays] = a2;
			v13[1] = a3;
			v13[2] = a4;
		} else {
			v14 = (uint16_t*)&v12[2 * useDrawElementsOrDrawArrays];
			*v14 = a2;
			v14[1] = a3;
			v14[2] = a4;
		}
		this->useDrawElementsOrDrawArrays += 3;
	}
	void vertex(float, float, float);
	void vertexUV(float, float, float, float, float);
	void voidBeginAndEndCalls(bool_t);
	~Tesselator();
};
