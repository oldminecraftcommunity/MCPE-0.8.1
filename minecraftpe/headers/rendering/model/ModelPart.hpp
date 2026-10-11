#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <rendering/MeshBuffer.hpp>

struct ModelPart
{
	bool noFaceCull;
	float xOffset, yOffset, zOffset;
	float xRotAngle, yRotAngle, zRotAngle;
	bool mirror;
	bool field_1D;
	std::vector<struct Cube*> cubes;
	std::vector<struct ModelPart*> children;
	std::string field_38;
	float texWidth, texHeight;
	int32_t texOffsetX, texOffsetY;
	bool field_4C;
	int32_t field_50;
	MeshBuffer meshBuffer;
	struct Model* parent;

	ModelPart() : ModelPart(0, 0, 64, 32){

	}
	ModelPart(struct Model*, int32_t, int32_t, int32_t, int32_t);
	ModelPart(int32_t, int32_t, int32_t, int32_t);
	ModelPart(const std::string&);
	void _init(int32_t, int32_t);
	ModelPart* addBox(float, float, float, int32_t, int32_t, int32_t);
	void addBox(float, float, float, int32_t, int32_t, int32_t, float);
	ModelPart* addBox(const std::string&, float, float, float, int32_t, int32_t, int32_t);
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
