#pragma once
#include <input/IInputHolder.hpp>

struct IMoveInput;
struct ITurnInput;
struct IBuildInput;

struct CustomInputHolder: IInputHolder
{
	IMoveInput* moveInput;
	ITurnInput* turnInput;
	IBuildInput* buildInput;
	CustomInputHolder(IMoveInput* move, ITurnInput* turn, IBuildInput* build);
	virtual ~CustomInputHolder();
	virtual IMoveInput* getMoveInput();
	virtual ITurnInput* getTurnInput();
	virtual IBuildInput* getBuildInput();
};
