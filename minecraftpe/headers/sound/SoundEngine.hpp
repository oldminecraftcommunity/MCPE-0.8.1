#pragma once
#include <_types.h>
#include <sound/SoundSystemSL.hpp>
#include <util/Random.hpp>
#include <sound/SoundRepository.hpp>

struct SoundEngine : public SoundSystemSL{
	struct Options* options;
	int32_t field_40;
	Random randomInstance;
	float field_A14;
	float field_A18;
	float field_A1C;
	float field_A20;
	float field_A24;
	SoundRepository sounds;
	struct Minecraft* minecraft;

	SoundEngine(float);
	float _getVolumeMult(float, float, float);
	void destroy(void);
	virtual void enable(bool_t);
	void init(struct Minecraft*, struct Options*);
	void play(const std::string&, float, float, float, float, float);
	void playUI(const std::string&, float, float);
	void update(struct Mob*, float);
	void updateOptions(void);
	~SoundEngine();
};
