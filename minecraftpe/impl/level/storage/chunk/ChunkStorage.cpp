#include <level/storage/chunk/ChunkStorage.hpp>

ChunkStorage::~ChunkStorage() {
}
struct LevelChunk* ChunkStorage::load(Level*, int32_t, int32_t) {
	return 0;
}

void ChunkStorage::save(Level*, LevelChunk*) {
}
void ChunkStorage::saveEntities(Level*, LevelChunk*) {
}
void ChunkStorage::saveAll(Level* a2, std::vector<LevelChunk*>& a3) {
	for(int32_t i = 0; i < a3.size(); ++i) {
		this->save(a2, a3[i]);
	}
}
void ChunkStorage::tick() {
}
void ChunkStorage::flush(){}
