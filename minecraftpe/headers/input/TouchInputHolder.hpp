#pragma once
#include <input/UnifiedTurnBuild.hpp>
#include <input/TouchscreenInput.hpp>
#include <input/IInputHolder.hpp>

struct TouchInputHolder: IInputHolder
{
	TouchscreenInput moveInput;
	UnifiedTurnBuild turnInput;
	Minecraft* minecraft;
	int8_t field_1F4, field_1F5, field_1F6, field_1F7;

	TouchInputHolder(Minecraft* mc);

	virtual ~TouchInputHolder();
	virtual void onConfigChanged(const Config&);
	virtual void render(float);
	virtual bool_t allowPicking();
	virtual IMoveInput* getMoveInput();
	virtual ITurnInput* getTurnInput();
	virtual IBuildInput* getBuildInput();
};
