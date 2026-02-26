#include <level/storage/MemoryLevelStorageSource.hpp>
#include <level/storage/MemoryLevelStorage.hpp>

MemoryLevelStorageSource::~MemoryLevelStorageSource(){

}
std::string MemoryLevelStorageSource::getName() {
	return "Memory Storage";
}
int32_t MemoryLevelStorageSource::getDataTagFor(const std::string&) {
	return 0;
}
struct LevelStorage* MemoryLevelStorageSource::selectLevel(const std::string& a2, bool_t a3) {
	return new MemoryLevelStorage(0);
}

bool_t MemoryLevelStorageSource::isNewLevelIdAcceptable(const std::string&) {
	return 1;
}
void MemoryLevelStorageSource::clearAll() {
}
void MemoryLevelStorageSource::deleteLevel(const std::string&){

}
void MemoryLevelStorageSource::renameLevel(const std::string&, const std::string&){

}
bool_t MemoryLevelStorageSource::isConvertible() {
	return 0;
}
bool_t MemoryLevelStorageSource::requiresConversion(const std::string&) {
	return 0;
}
bool_t MemoryLevelStorageSource::convertLevel(const std::string&, struct ProgressListener*) {
	return 0;
}
