#pragma once
#include <_types.h>
#include <string>
#include <network/mco/RestCallerInterup.hpp>
#include <network/mco/RestCallerType.hpp>

struct CMutex;
struct MCOConnector;
struct RestCallerObject;

struct RestCaller
{
	CMutex* mutex;
	std::string field_8;
	MCOConnector* connector;
	std::string key, sidOrUser2, sidOrUser1;

	RestCaller(MCOConnector*, const std::string&);
	void addToCookieData(std::string&, const std::string&, const std::string&);
	void call(RestCallerType, RestCallerInterup, const char_t*, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t);
	static RestCaller* create(MCOConnector*, const std::string&);
	void del(RestCallerInterup, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t);
	void get(RestCallerInterup, const char_t*, void (MCOConnector::*)(int32_t, std::string, RestCallTagData const&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t);
	std::string getCookieData();
	void globalCleanUp();
	void globalInit();
	void post(RestCallerInterup, const char_t*, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t);
	void put(RestCallerInterup, const char_t*, const char_t*, void (MCOConnector::*)(int32_t, std::string, const RestCallTagData&), void (MCOConnector::*)(bool_t, bool_t, int32_t, std::string, const RestCallTagData&), const RestCallTagData&, int32_t);
	void setKey(const std::string&);
	void setSidAndUser(const std::string&, const std::string&);

	virtual ~RestCaller();
	void requestStop() = 0;
	void urlEscape(const std::string&);
	void update();
	void makeRequest(RestCallerObject*) = 0;

};
