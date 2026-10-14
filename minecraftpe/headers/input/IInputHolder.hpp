#pragma once
#include <IConfigListener.hpp>
#include <input/Mouse.hpp>
#include <input/ITurnInput.hpp>
#include <input/IBuildInput.hpp>

struct IInputHolder : IConfigListener{
	float mouseX, mouseY, field_C;

	virtual ~IInputHolder(){}
	virtual void onConfigChanged(const Config& a2) {
		this->getTurnInput()->onConfigChanged(a2);
		this->getTurnInput()->onConfigChanged(a2);
		this->getBuildInput()->onConfigChanged(a2);
	}
	virtual void render(float){}
	virtual bool_t allowPicking(void) {
		this->mouseX = Mouse::getX();
		this->mouseY = Mouse::getY();
		return Mouse::getButtonState(1) == 1;
	}
	virtual struct IMoveInput* getMoveInput() = 0;
	virtual struct ITurnInput* getTurnInput() = 0;
	virtual struct IBuildInput* getBuildInput() = 0;
};
