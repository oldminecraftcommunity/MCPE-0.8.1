#include <input/IInputHolder.hpp>
#include <input/Mouse.hpp>
#include <input/ITurnInput.hpp>
#include <input/IBuildInput.hpp>

IInputHolder::~IInputHolder() {
}
void IInputHolder::onConfigChanged(const Config& a2) {
	this->getTurnInput()->onConfigChanged(a2);
	this->getTurnInput()->onConfigChanged(a2);
	this->getBuildInput()->onConfigChanged(a2);
}
void IInputHolder::render(float) {
}
bool_t IInputHolder::allowPicking(void) {
	this->mouseX = Mouse::getX();
	this->mouseY = Mouse::getY();
	return Mouse::getButtonState(1) == 1;
}
