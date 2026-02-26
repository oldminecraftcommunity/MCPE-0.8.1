#pragma once
#include <_types.h>
struct Minecraft;
struct Options;

struct Config{
	int32_t field_0;
	int32_t field_4;
	float guiScale;
	float guiScaleNorm;
	int32_t field_10;
	int32_t field_14;
	float field_18;
	float field_1C;
	float field_20;
	float field_24;
	Minecraft* mc;
	Options* options;
};

Config createConfig(Minecraft*);
