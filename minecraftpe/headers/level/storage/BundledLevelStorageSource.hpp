#pragma once
#include <level/storage/MemoryLevelStorageSource.hpp>

struct BundledLevelStorageSource: MemoryLevelStorageSource
{
	struct Minecraft* minecraft;
	BundledLevelStorageSource(struct Minecraft*);

	virtual ~BundledLevelStorageSource();
	virtual std::string getName();
	virtual struct LevelStorage* selectLevel(const std::string&, bool_t);
};
