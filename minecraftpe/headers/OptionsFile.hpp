#pragma once
#include <_types.h>
#include <vector>
#include <string>

struct OptionsFile
{
	std::string filename;

	void save(const std::vector<std::string>&);
	void setSettingsFolderPath(const std::string&);
	std::vector<std::string> getOptionStrings();
};
