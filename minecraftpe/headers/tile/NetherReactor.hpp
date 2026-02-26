#pragma once
#include <tile/EntityTile.hpp>

struct NetherReactor: EntityTile
{
	TextureUVCoordinateSet field_80, field_98, field_B0;

	NetherReactor(int32_t, const std::string&, const struct Material*);
	bool_t allPlayersCloseToReactor(Level*, int32_t, int32_t, int32_t);
	bool_t canSpawnStartNetherReactor(Level*, int32_t, int32_t, int32_t, struct Player*);
	static void setPhase(Level*, int32_t, int32_t, int32_t, int32_t);

	virtual ~NetherReactor();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual int32_t getTileEntityType();
	virtual bool_t use(Level*, int32_t, int32_t, int32_t, Player*);
};
