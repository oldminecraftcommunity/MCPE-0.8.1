#pragma once
#include <level/storage/LevelStorageSource.hpp>

struct ExternalFileLevelStorageSource: LevelStorageSource
{
	std::string field_4, field_8, folderName;
	int8_t field_10, field_11, field_12, field_13;

	ExternalFileLevelStorageSource(const std::string&, const std::string&);
	void addLevelSummaryIfExists(std::vector<LevelSummary>&, const char_t*);
	std::string getFullPath(const std::string&);

	virtual ~ExternalFileLevelStorageSource();
	virtual std::string getName();
	virtual void getLevelList(std::vector<LevelSummary>&);
	virtual int32_t getDataTagFor(const std::string&);
	virtual LevelStorage* selectLevel(const std::string&, bool_t);
	virtual bool_t isNewLevelIdAcceptable(const std::string&);
	virtual void clearAll();
	virtual void deleteLevel(const std::string&);
	virtual void renameLevel(const std::string&, const std::string&);
	virtual bool_t isConvertible(const std::string&);
	virtual bool_t requiresConversion(const std::string&);
	virtual bool_t convertLevel(const std::string&, ProgressListener*);
	virtual void storeToCache(LevelData*, const std::string&);
	virtual void loadFromCache(LevelData*, const std::string&);
	virtual void clearCache();

};
