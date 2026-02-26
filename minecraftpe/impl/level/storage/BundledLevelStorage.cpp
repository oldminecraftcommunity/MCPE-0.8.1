#include <level/storage/BundledLevelStorage.hpp>
#include <BinaryBlob.hpp>
#include <level/gen/RandomLevelSource.hpp>
#include <util/Util.hpp>

BundledLevelStorage::BundledLevelStorage(struct Minecraft* a2, const std::string& a3)
	: MemoryLevelStorage(0)
	, levelNameMaybe(a3) {
	this->levelData = new LevelData();
	this->field_14 = 0;
	this->field_18 = 3;
	this->field_1C = 0;
	this->minecraft = a2;
}

BundledLevelStorage::~BundledLevelStorage() {
	if(this->levelData) {
		delete this->levelData;
	}
	if(this->field_1C) {
		delete this->field_1C;
	}
}
LevelData* BundledLevelStorage::prepareLevel(Level* a2) {
	this->field_14 = a2;
	this->field_1C = new RandomLevelSource(a2, Util::hashCode("Nya1n"), 0, 1);
	bool_t v3 = this->levelNameMaybe.find("survival") == -1;
	this->levelData->setGameType(v3);
	this->levelData->setSpawnMobs(!v3);
	return this->levelData;
}
ChunkStorage* BundledLevelStorage::createChunkStorage(Dimension*) {
	return this;
}
bool_t BundledLevelStorage::load(Player*) {
	return 0;
}
struct LevelChunk* BundledLevelStorage::load(Level*, int32_t, int32_t) {
	printf("BundledLevelStorage::save2 - not implemented\n"); //TODO
	return 0;
}
void BundledLevelStorage::save2(Level* a2, LevelChunk* a3) {
	printf("BundledLevelStorage::save2 - not implemented\n"); //TODO
}
void BundledLevelStorage::getChunkData(int32_t, int32_t) {
	printf("BundledLevelStorage::save2 - not implemented\n"); //TODO
}
void BundledLevelStorage::freeChunkData(int32_t a2, int32_t a3, BinaryBlob* a4) {
	delete a4->ptr1;
	a4->ptr1 = 0;
	a4->field_4 = -1;
}
