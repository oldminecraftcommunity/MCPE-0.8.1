#pragma once
#include <_types.h>
#include <string>
#include <unordered_map>

struct MCOServerListItem;
struct LoginInformation;
struct MCOParser
{
	//TODO check does it have any fields?

	void parseErrorMessage(const std::string&, std::string&, int32_t&);
	void parseJoinWorld(const std::string&, std::string&, uint16_t&, std::string&);
	LoginInformation parseMCOAccountValidSessionReturnValue(const std::string&);
	std::unordered_map<int64_t, MCOServerListItem> parseServerList(const std::string&);
	void parseStatus(const std::string&, bool_t&, bool_t&, bool_t&);
};
