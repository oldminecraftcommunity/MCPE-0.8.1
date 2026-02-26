#pragma once
#include <_types.h>
#include <string>

struct MCOStringify
{
	static std::string stringifyAuthenticate(const std::string&, const std::string&, const std::string&);
	static std::string stringifyRefresh(const std::string&, const std::string&, const std::string&, const std::string&);
	static std::string stringifySignOut(const std::string&, const std::string&);
};
