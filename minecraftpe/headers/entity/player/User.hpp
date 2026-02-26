#pragma once
#include <_types.h>
#include <string>

struct User{
	std::string username;
	std::string str2;

	User(const std::string& username, const std::string str2);
};
