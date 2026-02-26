#pragma once
#include <_types.h>
#include <string>
#include <map>

struct I18n
{
	static std::map<std::string, std::string> _strings;

	static void loadLanguage(struct AppPlatform*, const std::string&);
	static std::string getDescriptionString(const struct ItemInstance&);
	static bool_t get(const std::string&, std::string&);
	static std::string get(const std::string&);
	static void fillTranslations(struct AppPlatform*, const std::string&, bool_t);
};
