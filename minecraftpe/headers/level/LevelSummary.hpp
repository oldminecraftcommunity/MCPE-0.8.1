#pragma once
#include <_types.h>
#include <string>

struct LevelSummary
{
	std::string levelDir, levelName;
	int32_t lastPlayed, gamemode, seed, sizeOnDisk;

	LevelSummary() {
	}
	LevelSummary(const LevelSummary& a2) = default;
	LevelSummary(LevelSummary&& a2) = default;
	LevelSummary& operator=(const LevelSummary& a2) = default;
	LevelSummary& operator=(LevelSummary&& a2) = default;


	bool operator<(const LevelSummary& a2) const{
		//TODO check is this correct
		return this->lastPlayed > a2.lastPlayed;
	}
};
