#pragma once
#include <_types.h>
#include <string>
#include <set>
#include <vector>

struct MCOServerListItem
{
	long long serverId;
	std::string worldName;
	bool_t open;
	std::string ownerName;
	bool_t myWorld;
	int32_t maxNrPlayers;
	std::string gamemodeName;
	std::vector<std::string> playerNames;
	std::set<std::string> invited;

	MCOServerListItem(const MCOServerListItem&) = default;
	MCOServerListItem(MCOServerListItem&&) = default;
	MCOServerListItem() {
		this->worldName = "My World";
		this->gamemodeName = "creative";
	}

	MCOServerListItem& operator=(const MCOServerListItem& a2) = default;
	MCOServerListItem& operator=(MCOServerListItem&&) = default;
	~MCOServerListItem(){}
};
