#pragma once
#include <tile/StoneTile.hpp>

struct ObsidianTile : StoneTile{
	bool_t glowing;
	byte field_81, field_82, field_83;

	ObsidianTile(int32_t, const std::string&, bool_t glowing);
	void poofParticles(Level*, int32_t, int32_t, int32_t);

	virtual ~ObsidianTile();
	virtual void animateTick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
};
