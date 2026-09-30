#pragma once
#include <_types.h>
#include <string>

struct ControllerData;
struct Random;
struct MCOPayloadPacker
{
	Random* random;

	MCOPayloadPacker(Random&);
	ControllerData readControlPackage(char*, uint32_t);
	std::string writeBitStream(long long, std::string);
	std::string writeControllPackage(const ControllerData&);
};
