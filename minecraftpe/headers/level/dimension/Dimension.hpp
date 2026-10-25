#pragma once
#include <_types.h>
#include <util/Color4.hpp>

struct Dimension{
	struct Level* levelPtr;
	struct BiomeSource* biomeSourcePtr;
	bool_t field_C;
	bool isOverworldMaybe;
	bool hasNoSkyMaybe;
	float lightRamp[16];
	int32_t id;

	Dimension();
	int32_t getMoonPhase(long);
	static Dimension* getNew(int32_t id);

	virtual ~Dimension();
	virtual void init(struct Level*);
	virtual struct ChunkSource* createRandomLevelSource(void);
	virtual bool_t isValidSpawn(int32_t, int32_t);
	virtual bool_t isNaturalDimension() {
		return 0;
	}
	virtual float getTimeOfDay(long, float);
	virtual Color4 getSunriseColor(float, float);
	virtual Color4 getFogColor(float, float);
	virtual float getCloudHeight();
	virtual bool_t mayRespawn(void);
	virtual void updateLightRamp(void);
	virtual void init();
};
