#include <sound/SoundSystem.hpp>

void SoundSystem::enable(bool_t){}
bool_t SoundSystem::isAvailable(){
	return 0;
}
void SoundSystem::load(const std::string&){}
void SoundSystem::pause(const std::string&){}
void SoundSystem::play(const std::string&){}
void SoundSystem::playAt(const SoundDesc&, float, float, float, float, float){}
void SoundSystem::setListenerAngle(float){}
void SoundSystem::setListenerPos(float, float, float){}
void SoundSystem::stop(const std::string&){}
SoundSystem::~SoundSystem(){}
