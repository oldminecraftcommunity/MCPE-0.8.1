#pragma once
#include <_types.h>
#include <string>

struct SoundSystem{
	virtual ~SoundSystem();
	virtual bool_t isAvailable(void);
	virtual void enable(bool_t);
	virtual void setListenerPos(float, float, float);
	virtual void setListenerAngle(float);
	virtual void load(const std::string&);
	virtual void play(const std::string&);
	virtual void pause(const std::string&);
	virtual void stop(const std::string&);
	virtual void playAt(const struct SoundDesc&, float, float, float, float, float);
};
