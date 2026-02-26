#include <network/RestService.hpp>

RestService::RestService(const std::string& a2) {
	this->serviceURL = a2;
}
std::map<std::string, std::string> RestService::getCookieData() {
	return this->cookieData;
}
std::string RestService::getCookieDataAsString() {
	//TODO check
	std::string ss = "";
	for(auto&& data: this->cookieData) {
		ss += (data.first + "=" + data.second) + ";";
	}
	return ss;
}
std::string* RestService::getSeriveURL() {
	return &this->serviceURL;
}
void RestService::setCookieData(const std::string& a2, const std::string& a3) {
	if(a3 == "") {
		this->cookieData[a2] = a3;
	} else {
		this->cookieData.insert({a2, a3}); //TODO check
	}
}
