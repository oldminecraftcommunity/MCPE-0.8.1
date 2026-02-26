#pragma once
#include <level/storage/LevelStorageSource.hpp>

struct MemoryLevelStorageSource: LevelStorageSource
{
	virtual ~MemoryLevelStorageSource();
	virtual std::string getName();
	virtual int32_t getDataTagFor(const std::string&);
	virtual struct LevelStorage* selectLevel(const std::string&, bool_t);
	virtual bool_t isNewLevelIdAcceptable(const std::string&);
	virtual void clearAll();
	virtual void deleteLevel(const std::string&);
	virtual void renameLevel(const std::string&, const std::string&);
	virtual bool_t isConvertible();
	virtual bool_t requiresConversion(const std::string&);
	virtual bool_t convertLevel(const std::string&, struct ProgressListener*);
};
