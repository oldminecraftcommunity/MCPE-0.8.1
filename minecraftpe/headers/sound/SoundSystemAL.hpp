#pragma once
#include <_types.h>
#include <sound/SoundSystem.hpp>

struct SoundSystemAL: public SoundSystem
{
	static const int MAX_PLAYED = 4;

	struct ALCdevice* device = 0;
	struct ALCcontext* context = 0;
	int playedCnt = 0;
	uint32_t buffers[MAX_PLAYED] = {0};
	uint32_t sources[MAX_PLAYED] = {0};

	SoundSystemAL(void);
	virtual ~SoundSystemAL();
	bool_t checkErr(uint32_t);
	void destroy(void);
	void init(void);
	void removeStoppedSounds(void);
	virtual void setListenerPos(float, float, float);
	virtual void setListenerAngle(float);
	virtual void load(const std::string&);
	virtual void play(const std::string&);
	virtual void pause(const std::string&);
	virtual void stop(const std::string&);
	virtual void playAt(const struct SoundDesc&, float, float, float, float, float);
};
