#pragma once
#include <tile/Tile.hpp>

struct RedStoneOreTile : Tile{
	bool_t emitLight;
	byte field_81, field_82, field_83;

	RedStoneOreTile(int32_t, const std::string&, bool_t);

	void interact(Level*, int32_t, int32_t, int32_t);
	void poofParticles(Level*, int32_t, int32_t, int32_t);

	virtual ~RedStoneOreTile();
	virtual int32_t getTickDelay();
	virtual void tick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual void animateTick(Level*, int32_t, int32_t, int32_t, Random*);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
	virtual void stepOn(Level*, int32_t, int32_t, int32_t, Entity*);
	virtual void attack(Level*, int32_t, int32_t, int32_t, Player*);
};
