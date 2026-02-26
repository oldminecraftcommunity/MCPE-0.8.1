#pragma once
#include <_types.h>
#include <string>

struct ControllerData;
struct Random;
struct MCOPayloadPacker
{
	Random* random;

	MCOPayloadPacker(Random&);
	std::string readControlPackage(char_t*, uint32_t);
	std::string writeBitStream(int64_t, std::string);
	std::string writeControllPackage(const ControllerData&);
};
