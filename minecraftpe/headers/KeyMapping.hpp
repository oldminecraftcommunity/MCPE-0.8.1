#pragma once

#include <_types.h>
#include <string>

struct KeyMapping{
	std::string name; //TODO 4 bytes?
	int32_t keyCode;

	KeyMapping();
	KeyMapping(const std::string&, int32_t);
	void operator=(KeyMapping&&);
};
