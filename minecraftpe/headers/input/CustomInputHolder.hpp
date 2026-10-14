#pragma once
#include <input/IInputHolder.hpp>
#include <input/IMoveInput.hpp>

struct IMoveInput;
struct ITurnInput;
struct IBuildInput;

struct CustomInputHolder: IInputHolder
{
	IMoveInput* moveInput;
	ITurnInput* turnInput;
	IBuildInput* buildInput;
	CustomInputHolder(IMoveInput* move, ITurnInput* turn, IBuildInput* build) {
		this->mouseX = this->mouseY = 0;
		this->field_C = 0;
		this->moveInput = move;
		this->turnInput = turn;
		this->buildInput = build;
	}
	virtual ~CustomInputHolder() {
		if (this->moveInput) delete this->moveInput;

		if (this->turnInput) delete this->turnInput;

		if (this->buildInput) delete this->buildInput;
	}
	virtual IMoveInput* getMoveInput() {
		return this->moveInput;
	}
	virtual ITurnInput* getTurnInput() {
		return this->turnInput;
	}
	virtual IBuildInput* getBuildInput() {
		return this->buildInput;
	}
};
