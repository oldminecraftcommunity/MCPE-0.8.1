#pragma once
#include <_types.h>
#include <vector>
#include <level/LevelSummary.hpp>
struct LevelData;
struct LevelStorage;

struct LevelStorageSource
{
	static std::string TempLevelId;
	virtual ~LevelStorageSource();
	virtual std::string getName() = 0;
	virtual void getLevelList(std::vector<LevelSummary>&);
	virtual int32_t getDataTagFor(const std::string&) = 0; //TODO probably returns not int but a pointer to something
	virtual LevelStorage* selectLevel(const std::string&, bool_t) = 0;
	virtual bool_t isNewLevelIdAcceptable(const std::string&) = 0;
	virtual void clearAll() = 0;
	virtual void deleteLevel(const std::string&) = 0;
	virtual void renameLevel(const std::string&, const std::string&) = 0;
	virtual bool_t isConvertible(const std::string&) = 0;
	virtual bool_t requiresConversion(const std::string&) = 0;
	virtual bool_t convertLevel(const std::string&, struct ProgressListener*) = 0;
	virtual void storeToCache(LevelData*, const std::string&);
	virtual void loadFromCache(LevelData*, const std::string&);
	virtual void clearCache();

};
