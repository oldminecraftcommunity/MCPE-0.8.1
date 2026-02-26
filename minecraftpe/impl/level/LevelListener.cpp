#include <level/LevelListener.hpp>

LevelListener::~LevelListener() {
}
void LevelListener::setTilesDirty(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t) {
}
void LevelListener::tileChanged(int32_t, int32_t, int32_t) {
}
void LevelListener::tileBrightnessChanged(int32_t x, int32_t y, int32_t z) {
	this->tileChanged(x, y, z);
}
void LevelListener::skyColorChanged() {
}
void LevelListener::allChanged() {
}
void LevelListener::takePicture(TripodCamera*, Entity*) {
}
Particle* LevelListener::addParticle(ParticleType, float, float, float, float, float, float, int32_t) {
	return 0;
}
void LevelListener::playSound(const std::string&, float, float, float, float, float) {
}
void LevelListener::playMusic(const std::string&, float, float, float, float) {
}
void LevelListener::playStreamingMusic(const std::string&, int32_t, int32_t, int32_t) {
}
void LevelListener::entityAdded(Entity*) {
}
void LevelListener::entityRemoved(Entity*) {
}
void LevelListener::levelEvent(Player*, int32_t, int32_t, int32_t, int32_t, int32_t) {
}
void LevelListener::tileEvent(int32_t, int32_t, int32_t, int32_t, int32_t) {
}
void LevelListener::tileEntityChanged(int32_t, int32_t, int32_t, TileEntity*) {
}
