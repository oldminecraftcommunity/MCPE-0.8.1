#pragma once
#include <_types.h>
#include <string>

struct LoginInformation{
	std::string accessToken;
	std::string clientId;
	std::string profileId;
	std::string profileName;
	LoginInformation();
	~LoginInformation(void);
};
