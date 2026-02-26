#include <level/storage/MemoryLevelStorage.hpp>
#include <level/storage/chunk/MemoryChunkStorage.hpp>

MemoryLevelStorage::MemoryLevelStorage(ChunkStorage* a2) {
	this->chunkStorage = a2;
} //inlined in mcpe?
MemoryLevelStorage::~MemoryLevelStorage() {
	if(this->chunkStorage) delete this->chunkStorage;
}
LevelData* MemoryLevelStorage::prepareLevel(Level*) {
	return 0;
}
ChunkStorage* MemoryLevelStorage::createChunkStorage(Dimension* a2) {
	this->chunkStorage = new MemoryChunkStorage();
	return this->chunkStorage;
}
void MemoryLevelStorage::saveLevelData(LevelData&, std::vector<Player*>*) {
}
void MemoryLevelStorage::closeAll() {
}
