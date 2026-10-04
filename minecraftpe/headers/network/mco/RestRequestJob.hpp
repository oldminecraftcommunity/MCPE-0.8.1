#pragma once
#include <util/Job.hpp>
#include <functional>
#include <memory>
#include <string>
#include <network/mco/RestRequestType.hpp>
#include <RakNetTypes.h>
#include <network/mco/RestCallTagData.hpp>
#include <util/Util.hpp>
#include <util/ParameterStringify.hpp>

struct RestService;
struct Minecraft;
struct ThreadCollection;

struct RestRequestJob: Job
{
	std::weak_ptr<RestRequestJob> field_8;
	std::function<void(int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)> onFinish;
	std::function<void(bool_t, bool_t, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)> onError;
	std::string url;
	std::string body;
	std::shared_ptr<RestService> restService;
	RestRequestType requestType;
	RestCallTagData field_44;

	static std::shared_ptr<RestRequestJob> CreateJob(RestRequestType, std::shared_ptr<RestService>, Minecraft*);

	RestRequestJob();
	static void launchRequest(std::shared_ptr<RestRequestJob>, std::shared_ptr<ThreadCollection>, std::function<void(int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)>, std::function<void(bool, bool, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)>);
	void setBody(const std::string&);

	template<typename... _args>
	void setMethod(const std::string& fmt, _args... args) {
		std::vector<std::string> v4;
		ParameterStringify::stringifyNext(v4, args...);
		this->url = Util::simpleFormat(fmt, v4);
	}

	void setTagData(const RestCallTagData&);

	virtual ~RestRequestJob();
	virtual void stop();
	virtual void run();
	virtual void finish();
};

