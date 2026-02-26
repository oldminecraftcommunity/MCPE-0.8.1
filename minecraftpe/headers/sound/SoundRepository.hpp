#pragma once
#include <_types.h>
#include <string>
#include <map>
#include <vector>
#include <sound/SoundDesc.hpp>

struct SoundRepository{
	std::map<std::string, std::vector<SoundDesc>> sounds;

	void add(const std::string&, struct SoundDesc&);
	void add(const std::string&, const struct SoundDesc&);
	bool_t get(const std::string&, struct SoundDesc&);
};
