#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <functional>

struct Util{

	static std::string EMPTY_STRING;

	static bool_t startsWith(const std::string&, const std::string&);
	static std::string getExtension(const std::string&);
	static bool_t endsWith(const std::string&, const std::string&);
	static std::string* stringReplace(std::string&, const std::string&, const std::string&, int32_t);
	static int32_t hashCode(const std::string&);
	static void removeAll(std::string&, const char_t**, int32_t);
	static int32_t utf8len(const std::string&);
	static std::string utf8substring(const std::string&, int32_t start, int32_t end);
	static std::string simpleFormat(const std::string&, std::vector<std::string>);
	static std::string toString(int32_t);
	static std::string toString(float);
	static std::string toLower(std::string const&);
	//TODO	static			compareNoCase		(std::string,std::string)
	static void stringSplit(const std::string&, int32_t, const float*, std::function<void(const std::string&, float)>);
	static std::string stringTrim(const std::string&, const std::string&, bool_t, bool_t);
	static std::string stringTrim(const std::string&);
};
