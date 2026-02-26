#include <sound/SoundSystemSL.hpp>

//opensl is alternative of openal for android
SoundSystemSL::SoundSystemSL(void) {
	this->field_10 = 0;
	this->field_18 = 0;
	this->field_1C = 0;
	this->field_20 = 0;
	this->field_24 = 0;
	this->field_28 = 1;
	this->init();
}
SoundSystemSL::~SoundSystemSL(){
	printf("SoundSystemSL::~SoundSystemSL - requires OpenSL - not implemented\n"); //TODO
}
bool_t SoundSystemSL::checkErr(uint32_t a2) {
	if(a2) {
		return 1;
	}
	return 0;
}
void SoundSystemSL::destroy(void) {
}
void SoundSystemSL::init(void) {
	printf("SoundSystemSL::init - requires OpenSL - not implemented\n"); //TODO
}
void SoundSystemSL::removePlayer(const struct SLAndroidSimpleBufferQueueItf_*, void*) { //XXX SoundSystemSL::removePlayer(SLAndroidSimpleBufferQueueItf_ const* const*,void *)
}
void SoundSystemSL::removeStoppedSounds(void) {
	printf("SoundSystemSL::removeStoppedSounds - requires OpenSL - not implemented\n"); //TODO
}
void SoundSystemSL::setListenerPos(float a, float b, float c) {
	printf("SoundSystemSL::setListenerPos(%f %f %f) - requires OpenSL - not implemented\n", a, b, c); //TODO
}
void SoundSystemSL::setListenerAngle(float a) {
	//printf("SoundSystemSL::setListenerAngle(%f) - requires OpenSL - not implemented\n", a); //TODO
}
void SoundSystemSL::load(const std::string&) {
}
void SoundSystemSL::play(const std::string&) {
}
void SoundSystemSL::pause(const std::string&) {
}
void SoundSystemSL::stop(const std::string&) {
}
void SoundSystemSL::playAt(const struct SoundDesc& a2, float a3, float a4, float a5, float a6, float a7) {
	printf("SoundSystemSL::playAt(%p, %f, %f, %f, %f, %f, %f) - requires OpenSL - not implemented\n", &a2, a3, a4, a5, a6, a7); //TODO
}
