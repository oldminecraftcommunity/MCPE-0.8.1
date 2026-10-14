#pragma once
#ifdef ANDROID
#include <math/Vec3.hpp>
#include <list>
#include <vector>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <sound/SoundSystem.hpp>
#include <util/Mutex.hpp>

struct SoundSystemSL : public SoundSystem{
	static SLObjectItf objEngine;
	static Mutex toRemoveMutex;
	static std::vector<SLObjectItf> toRemove;

	std::list<SLObjectItf> field_0;
	int field_4;
	SLEngineItf slInterface;
	int field_C;
	SL3DLocationItf field_10;
	SLObjectItf slMix;
	Vec3 listenerPos;
	int playingSoundsCnt;
	bool field_28;
	std::vector<SLObjectItf> field_2C;

	SoundSystemSL(void);

	bool_t checkErr(unsigned long);
	static void removePlayer(SLAndroidSimpleBufferQueueItf, void*);
	void removeStoppedSounds(void);

	virtual ~SoundSystemSL();
	virtual void setListenerPos(float, float, float);
	virtual void setListenerAngle(float);
	virtual void load(const std::string&) {
	}
	virtual void play(const std::string&) {
	}
	virtual void pause(const std::string&) {
	}
	virtual void stop(const std::string&) {
	}
	virtual void playAt(const struct SoundDesc&, float, float, float, float, float);
	virtual void destroy(void);
	virtual void init(void);
};
#endif
