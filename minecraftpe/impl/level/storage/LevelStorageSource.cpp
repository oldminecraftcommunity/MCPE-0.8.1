#include <level/storage/LevelStorageSource.hpp>
std::string LevelStorageSource::TempLevelId = "_LastJoinedServer";

LevelStorageSource::~LevelStorageSource(){}
void LevelStorageSource::getLevelList(std::vector<LevelSummary>&){}
void LevelStorageSource::storeToCache(struct LevelData*, const std::string&){}
void LevelStorageSource::loadFromCache(struct LevelData*, const std::string&){}
void LevelStorageSource::clearCache(){}
