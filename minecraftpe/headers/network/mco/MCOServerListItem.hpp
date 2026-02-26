#pragma once
#include <_types.h>
#include <string>
#include <map>
#include <vector>

struct MCOServerListItem
{
	int32_t field_0, field_4;
	std::string worldName;
	bool_t field_C;
	int8_t field_D, field_E, field_F;
	std::string field_10;
	bool_t field_14;
	int8_t field_15, field_16, field_17;
	int32_t field_18;
	std::string gamemodeName;
	std::vector<std::string> field_20;
	std::map<std::string, std::string> field_2C;

	MCOServerListItem(const MCOServerListItem&);
	MCOServerListItem(MCOServerListItem&&);
	MCOServerListItem();

	MCOServerListItem& operator=(const MCOServerListItem&);
	MCOServerListItem& operator=(MCOServerListItem&&);
	~MCOServerListItem();
};
