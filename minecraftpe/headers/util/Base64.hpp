#pragma once
#include <_types.h>
#include <string>

// mojang copied the answer from
// https://stackoverflow.com/questions/5288076/base64-encoding-and-decoding-with-openssl
// and slightly changed function names?
struct Base64
{
	static const char_t b64_table[65];
	static const char_t reverse_table[128];

	static std::string base64Decode(const std::string&);
	static std::string base64Encode(const std::string&);
};
