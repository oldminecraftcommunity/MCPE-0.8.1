#pragma once
#include <_types.h>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/common.hpp>
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

		CurrentVertexPointers();
		CurrentVertexPointers(uint8_t*, const MeshBuffer::VertexFormat&);
	};

	Tesselator::CurrentVertexPointers currentVertexPointers;
	std::vector<uint8_t> field_14;
	std::vector<uint8_t> vertexes;
	int32_t someSIzeMaybe;
	int32_t useDrawElementsOrDrawArrays;
	//TODO field_34 is std::_Hashtable -> unordered_map (https://gcc.gnu.org/onlinedocs/gcc-4.8.5/libstdc++/api/a01318_source.html line 100)
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
	glm::tmat4x4<float> tmat4x4_2;
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
	//TODO methods

	Tesselator(int32_t);
	void _buildQuadIndexBuffer();
	MeshBuffer::VertexFormat* _genVertexFormat();
	void addOffset(const Vec3&);
	void addOffset(float, float, float);
	void begin(int32_t);
	void begin(int32_t, int32_t);
	void beginOverride(void);
	void cancel(void);
	void clear(void);
	void color(int8_t, int8_t, int8_t);
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
	void endOverrideAndDraw(void);
	int32_t getColor(void);
	int32_t getVertexCount(void);
	void init();
	void noColor(void);
	void normal(const Vec3&);
	void normal(float, float, float);
	void offset(const Vec3&);
	void offset(float, float, float);
	void quad(bool_t);
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
	void triangle(uint16_t, uint16_t, uint16_t);
	void vertex(float, float, float);
	void vertexUV(float, float, float, float, float);
	void voidBeginAndEndCalls(bool_t);
	~Tesselator();
};
