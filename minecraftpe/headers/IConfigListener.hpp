#pragma once
#include <_types.h>

struct Config;

struct IConfigListener{
	virtual ~IConfigListener();
	virtual void onConfigChanged(const Config&) = 0;
};
