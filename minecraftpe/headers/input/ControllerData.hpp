#pragma once
#include <_types.h>
#include <string>

struct ControllerData
{
	int field_0 = 0;
	unsigned int field_4 = 0; //the only reason why this is unsigned is because it is inlined in MCOPayloadPacker
	std::string field_8;
};
