#pragma once
#ifdef ANDROID
#include <sound/SoundSystem.hpp>
#include <math/Vec3.hpp>
#include <list>
#include <vector>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
struct Mutex;
struct SoundSystemSL : public SoundSystem{
	static std::vector<SLObjectItf> toRemove;
	static Mutex toRemoveMutex;
	static SLObjectItf objEngine;

	std::list<SLObjectItf> field_0;
	int field_4;
	SLEngineItf field_8;
	int field_C;
	SL3DLocationItf field_10;
	SLObjectItf field_14;
	Vec3 field_18;
	int field_24;
	int8_t field_28, field_29, field_2A, field_2B;
	std::vector<SLObjectItf> field_2C;

	SoundSystemSL(void);
	virtual ~SoundSystemSL();
	bool_t checkErr(unsigned long);
	void destroy(void);
	void init(void);
	static void removePlayer(SLAndroidSimpleBufferQueueItf, void*); //XXX SoundSystemSL::removePlayer(SLAndroidSimpleBufferQueueItf_ const* const*,void *)
	void removeStoppedSounds(void);
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
};
#endif
