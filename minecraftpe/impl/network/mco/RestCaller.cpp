#include <network/mco/RestCaller.hpp>
#include <util/CMutex.hpp>
#include <network/mco/RestCallerObject.hpp>
#include <util/Common.hpp>

#ifdef ANDROID
#include <android/AndroidRestCaller.hpp>
#endif

RestCaller::RestCaller(MCOConnector* a2, const std::string& a3)
	: field_8(a3)
	, connector(a2) {
	this->mutex = new CMutex();
}
void RestCaller::addToCookieData(std::string& a2, const std::string& a3, const std::string& a4) {
	if(a4 != "") {
		if(a2.size()) a2 += ' ';
		a2 += a3;
		a2 += '=';
		a2 += a4;
		a2 += ';';
	}
}
void RestCaller::call(RestCallerType type, RestCallerInterup inter, const char_t* a4, const char_t* a5, void (MCOConnector::*a6)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*a7)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData& a8, int32_t a9) {
	this->makeRequest(new RestCallerObject(type, inter, this, a4, a5, a6, a7, a8, a9));
}
RestCaller* RestCaller::create(MCOConnector* a1, const std::string& a2) {
#ifdef ANDROID
	return new AndroidRestCaller(a1, a2);
#endif
	printf("RestCaller::create - not implemented\n");
	return 0;
}
void RestCaller::del(RestCallerInterup a2, const char_t* a3, void (MCOConnector::*a4)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*a5)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData& a6, int32_t a7) {
	this->call(RCT_DELETE, a2, a3, 0, a4, a5, a6, a7);
}
void RestCaller::get(RestCallerInterup a2, const char_t* a3, void (MCOConnector::*a4)(int32_t, std::string, RestCallTagData const&), void (MCOConnector::*a5)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData& a6, int32_t a7) {
	this->call(RCT_GET, a2, a3, 0, a4, a5, a6, a7);
}
std::string RestCaller::getCookieData() {
	std::string ret;
	ret.reserve(512);

	this->addToCookieData(ret, "sid", this->sid);
	this->addToCookieData(ret, "user", this->user);
	this->addToCookieData(ret, "gameversion", Common::getGameVersionStringNet());
	this->addToCookieData(ret, "key", this->key);
	return ret;
}
void RestCaller::globalCleanUp(){
}
void RestCaller::globalInit(){
}
void RestCaller::post(RestCallerInterup a2, const char_t* a3, const char_t* a4, void (MCOConnector::*a5)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*a6)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData& a7, int32_t a8){
	this->call(RCT_POST, a2, a3, a4, a5, a6, a7, a8);
}
void RestCaller::put(RestCallerInterup a2, const char_t* a3, const char_t* a4, void (MCOConnector::*a5)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*a6)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData& a7, int32_t a8) {
	this->call(RCT_PUT, a2, a3, a4, a5, a6, a7, a8);
}
void RestCaller::setKey(const std::string& a2) {
	this->key = a2;
}
void RestCaller::setSidAndUser(const std::string& a2, const std::string& a3){
	this->sid = a2;
	this->user = a3;
}

RestCaller::~RestCaller() {
	this->mutex->lock();
	if(this->mutex) { //TODO maybe inlined safeRemove?
		delete this->mutex;
		this->mutex = 0;
	}
}
std::string RestCaller::urlEscape(const std::string& a3) {
	char* v5 = new char[3 * a3.length() + 1];
	char* v6 = v5;
	const char* s = a3.c_str();
	char c;
	while((c = *(s++))) {
		if(std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
			*(v6++) = c;
		} else if(c == ' ') {
			*(v6++) = '+';
		} else {
			*v6 = '%';
			v6[1] = "0123456789abcdef"[((unsigned char)c) >> 4];
			v6[2] = "0123456789abcdef"[c & 0xf];
			v6 += 3;
		}
	}
	*v6 = 0;
	std::string r = v5;
	if(v5) delete[] v5;
	return r;
}
