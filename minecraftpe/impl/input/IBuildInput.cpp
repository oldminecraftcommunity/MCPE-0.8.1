#include <input/IBuildInput.hpp>

IBuildInput::~IBuildInput() {
}
void IBuildInput::onConfigChanged(const struct Config&) {
}
bool_t IBuildInput::tickBuild(struct Player*, struct BuildActionIntention*) {
	return 0;
}
