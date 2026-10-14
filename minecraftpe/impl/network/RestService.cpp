#include <network/RestService.hpp>
#include <sstream>


std::string RestService::getCookieDataAsString() const{
	std::stringstream str;
	for(auto&& data: this->cookieData) {
		if(str.rdbuf()->in_avail()) str << ' '; //c++ std is the least usable std lib lib ive seen
		str << data.first << "=" << data.second << ";";
	}
	return str.str();
}
const std::string* RestService::getServiceURL() const{
	return &this->serviceURL;
}

RestService::RestService(const std::string& a2) : serviceURL(a2) {
}

void RestService::setCookieData(const std::string& a2, const std::string& a3) {
	if(a3 == "") {
		this->cookieData.erase(a2);
	} else {
		this->cookieData[a2] = a3;
	}
}
std::map<std::string, std::string> RestService::getCookieData() const{
	return this->cookieData;
}
