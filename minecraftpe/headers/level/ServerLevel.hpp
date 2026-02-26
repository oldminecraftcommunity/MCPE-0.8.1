#pragma once
#include <level/Level.hpp>

struct ServerLevel: Level
{
	bool_t _allPlayersSleeping;
	byte align[3];

	ServerLevel(LevelStorage*, const std::string&, const LevelSettings&, int32_t, Dimension*);
	bool_t allPlayersSleeping();
	void awakenAllPlayers();

	virtual ~ServerLevel();
	virtual void tick();
	virtual void updateSleepingPlayerList();
};
