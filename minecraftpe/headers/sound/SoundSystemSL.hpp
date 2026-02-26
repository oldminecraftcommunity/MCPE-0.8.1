#pragma once
#include <_types.h>
#include <sound/SoundSystem.hpp>
//TODO: rewrite to something other than opensl

struct SoundSystemSL : public SoundSystem{
	//TODO static fields
	int32_t field_0, field_4;
	int32_t field_8, field_C;
	int32_t field_10, field_14;
	int32_t field_18, field_1C;
	int32_t field_20, field_24;
	int8_t field_28, field_29, field_2A, field_2B;
	//TODO std::vector<SLObjectItf> field_2C;

	SoundSystemSL(void);
	virtual ~SoundSystemSL();
	bool_t checkErr(uint32_t);
	void destroy(void);
	void init(void);
	void removePlayer(const struct SLAndroidSimpleBufferQueueItf_*, void*); //XXX SoundSystemSL::removePlayer(SLAndroidSimpleBufferQueueItf_ const* const*,void *)
	void removeStoppedSounds(void);
	virtual void setListenerPos(float, float, float);
	virtual void setListenerAngle(float);
	virtual void load(const std::string&);
	virtual void play(const std::string&);
	virtual void pause(const std::string&);
	virtual void stop(const std::string&);
	virtual void playAt(const struct SoundDesc&, float, float, float, float, float);
};
