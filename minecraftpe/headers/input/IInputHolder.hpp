#pragma once
#include <_types.h>
#include <IConfigListener.hpp>

struct IInputHolder : IConfigListener{
	float mouseX, mouseY, field_C;

	virtual ~IInputHolder();
	virtual void onConfigChanged(const Config&);
	virtual void render(float);
	virtual bool_t allowPicking(void);
	virtual struct IMoveInput* getMoveInput() = 0;
	virtual struct ITurnInput* getTurnInput() = 0;
	virtual struct IBuildInput* getBuildInput() = 0;
};
