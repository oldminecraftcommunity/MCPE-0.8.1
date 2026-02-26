#pragma once
#include <_types.h>
#include <string>
#include <vector>

struct PerfRenderer{
	struct Minecraft* minecraft;
	struct Font* font;
	std::string field_8;
	std::vector<float> field_C;
	std::vector<float> field_18;
	int field_24;
	double field_28;

	PerfRenderer(struct Minecraft*, struct Font*);
	void debugFpsMeterKeyPress(int);
	void renderFpsMeter(float);
	std::string toPercentString(float);
};
