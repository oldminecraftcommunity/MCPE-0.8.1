#pragma once
#include <_types.h>
#include <string>


struct Base64
{
	static char_t reverse_table[128];
	static char_t b64_table[65];

	static std::string base64Decode(const std::string&);
	static std::string base64Encode(const std::string&);
};
