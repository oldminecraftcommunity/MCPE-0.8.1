#pragma once
#include <_types.h>
#include <map>
#include <string>
struct RestService
{
	std::map<std::string, std::string> cookieData;
	std::string serviceURL;

	RestService(const std::string&);
	std::map<std::string, std::string> getCookieData();
	std::string getCookieDataAsString();
	std::string* getSeriveURL();
	void setCookieData(const std::string&, const std::string&);


};
