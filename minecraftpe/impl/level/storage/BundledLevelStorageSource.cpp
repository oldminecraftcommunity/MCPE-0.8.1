#include <level/storage/BundledLevelStorageSource.hpp>
#include <level/storage/BundledLevelStorage.hpp>

BundledLevelStorageSource::BundledLevelStorageSource(struct Minecraft* mc) {
	this->minecraft = mc;
}

std::string BundledLevelStorageSource::getName() {
	return "Bundled Level Storage";
}

struct LevelStorage* BundledLevelStorageSource::selectLevel(const std::string& a2, bool_t a3) {
	return new BundledLevelStorage(this->minecraft, a2);
}

BundledLevelStorageSource::~BundledLevelStorageSource(){}
