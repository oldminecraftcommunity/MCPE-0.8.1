#pragma once
#ifdef __WIN32__
#include <_types.h>
#include <dsound.h>
#include <sound/SoundSystem.hpp>

struct SoundSystemDirectSound: public SoundSystem
{
	static const int MAX_PLAYED = 4;

	LPDIRECTSOUNDBUFFER buffers[MAX_PLAYED] = {0};
	LPDIRECTSOUND8 dsound = 0;
	int playedCnt = 0;

	SoundSystemDirectSound(void);
	virtual ~SoundSystemDirectSound();
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
#endif
