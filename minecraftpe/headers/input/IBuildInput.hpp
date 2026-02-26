#pragma once
#include <_types.h>
#include <IConfigListener.hpp>

struct IBuildInput : IConfigListener{
	virtual ~IBuildInput();
	virtual void onConfigChanged(const struct Config&);
	virtual bool_t tickBuild(struct Player*, struct BuildActionIntention*);
};
