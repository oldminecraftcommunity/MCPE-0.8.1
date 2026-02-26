#pragma once
#include <_types.h>

struct Goal
{
	int32_t controlFlags;

	Goal();

	virtual ~Goal();
	virtual bool_t canUse() = 0;
	virtual bool_t canContinueToUse();
	virtual bool_t canInterrupt();
	virtual void start();
	virtual void stop();
	virtual void tick();
	virtual void setRequiredControlFlags(int32_t);
	virtual int32_t getRequiredControlFlags();

};
