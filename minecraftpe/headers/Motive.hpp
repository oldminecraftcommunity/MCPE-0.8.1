#pragma once
#include <_types.h>
#include <string>
#include <vector>

struct Motive{
	std::string name;
	int32_t w, h;
	int32_t uo, vo;
	bool_t isUsed;

	static Motive* DefaultImage;
	static Motive DonkeyKong;
	static Motive BurningSkull;
	static Motive SkullAndRoses;
	static Motive Sea;
	static Motive Bomb;
	static Motive Bust;
	static Motive Fire;
	static Motive Pool;
	static Motive Void;
	static Motive Wind;
	static Motive Alban;
	static Motive Aztec;
	static Motive Earth;
	static Motive Kebab;
	static Motive Match;
	static Motive Plant;
	static Motive Stage;
	static Motive Water;
	static Motive Aztec2;
	static Motive Graham;
	static Motive Sunset;
	static Motive Courbet;
	static Motive Creebet;
	static Motive Pointer;
	static Motive Fighters;
	static Motive Pigscene;
	static Motive Skeleton;
	static Motive Wanderer;
	static Motive Wasteland;


	Motive(std::string, int32_t, int32_t, int32_t, int32_t, bool_t);

	static std::vector<const Motive*> getAllMotivesAsList(void);
	static const Motive* getMotiveByName(const std::string&);
};
