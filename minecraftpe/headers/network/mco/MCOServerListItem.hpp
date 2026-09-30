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

	MCOServerListItem& operator=(const MCOServerListItem& a2) {
		this->serverId = a2.serverId;
		this->worldName = a2.worldName;
		this->open = a2.open;
		this->ownerName = a2.ownerName;
		this->myWorld = a2.myWorld;
		this->maxNrPlayers = a2.maxNrPlayers;
		this->gamemodeName = a2.gamemodeName;
		this->playerNames = a2.playerNames;
		this->invited = a2.invited;
		return *this;
	}
	MCOServerListItem& operator=(MCOServerListItem&&) = default;
	~MCOServerListItem(){}
};
