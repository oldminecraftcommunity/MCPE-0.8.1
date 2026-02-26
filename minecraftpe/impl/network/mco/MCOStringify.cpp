#include <network/mco/MCOStringify.hpp>
#include <json/json.h>

std::string MCOStringify::stringifyAuthenticate(const std::string& username, const std::string& password, const std::string& version) {
	Json::Value v23;
	v23["username"] = username;
	v23["password"] = password;
	v23["agent"]["name"] = "mcpe";
	v23["agent"]["version"] = version;

	return Json::FastWriter().write(v23);
}
std::string MCOStringify::stringifyRefresh(const std::string& accessToken, const std::string& clientToken, const std::string& a4, const std::string& version) {
	Json::Value v23;
	v23["accessToken"] = accessToken;
	v23["clientToken"] = clientToken;
	v23["agent"]["name"] = "mcpe";
	v23["agent"]["version"] = version;

	return Json::FastWriter().write(v23);
}
std::string MCOStringify::stringifySignOut(const std::string& accessToken, const std::string& clientToken){
	Json::Value v13;
	v13["accessToken"] = accessToken;
	v13["clientToken"] = clientToken;

	return Json::FastWriter().write(v13);
}
