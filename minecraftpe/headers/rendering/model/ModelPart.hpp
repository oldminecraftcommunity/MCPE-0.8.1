#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <rendering/MeshBuffer.hpp>

struct ModelPart
{
	int8_t field_0, field_1, field_2, field_3;
	float xOffset, yOffset, zOffset;
	float xRotAngle, yRotAngle, zRotAngle;
	int8_t mirror;
	int8_t field_1D, field_1E, field_1F;
	std::vector<struct Cube*> cubes;
	std::vector<struct ModelPart*> children;
	std::string field_38;
	float texWidth, texHeight;
	int32_t texOffsetX, texOffsetY;
	int8_t field_4C, field_4D, field_4E, field_4F;
	int32_t field_50;
	MeshBuffer meshBuffer;
	struct Model* parent;

	ModelPart(); //TODO doesnt exist?
	ModelPart(struct Model*, int32_t, int32_t, int32_t, int32_t);
	ModelPart(int32_t, int32_t, int32_t, int32_t);
	ModelPart(const std::string&);
	void _init(int32_t, int32_t);
	void addBox(float, float, float, int32_t, int32_t, int32_t);
	void addBox(float, float, float, int32_t, int32_t, int32_t, float);
	void addBox(const std::string&, float, float, float, int32_t, int32_t, int32_t);
	void addChild(ModelPart*);
	void compile(float);
	void draw(float);
	void drawSlow(float);
	void mimic(const ModelPart*);
	ModelPart& operator=(const ModelPart&);
	void render(float);
	void renderHorrible(float);
	void reset(void);
	void setModel(struct Model*);
	void setPos(float, float, float);
	ModelPart* setTexSize(int32_t, int32_t);
	ModelPart* texOffs(int32_t, int32_t);
	void translateTo(float);
	~ModelPart();

};
