#include <entity/ai/Goal.hpp>
Goal::Goal() {
	this->controlFlags = 0;
}

Goal::~Goal() {
}
bool_t Goal::canContinueToUse() {
	return this->canUse();
}
bool_t Goal::canInterrupt() {
	return 1;
}
void Goal::start() {
}
void Goal::stop() {
}
void Goal::tick() {
}
void Goal::setRequiredControlFlags(int32_t a2) {
	this->controlFlags = a2;
}
int32_t Goal::getRequiredControlFlags() {
	return this->controlFlags;
}
