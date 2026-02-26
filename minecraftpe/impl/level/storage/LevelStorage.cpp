#include <level/storage/LevelStorage.hpp>

LevelStorage::~LevelStorage() {
}
void LevelStorage::saveLevelData(LevelData& a2) {
	this->saveLevelData(a2, 0);
}
bool_t LevelStorage::load(Player*) {
	return 0;
}
bool_t LevelStorage::save(Player*) {
	return 0;
}
void LevelStorage::saveGame(Level*) {
}
void LevelStorage::loadEntities(Level*, LevelChunk*) {
}
