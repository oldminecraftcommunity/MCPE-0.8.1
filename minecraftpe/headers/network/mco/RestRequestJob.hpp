#pragma once
#include <_types.h>
#include <util/Job.hpp>
#include <functional>
#include <memory>
#include <string>
#include <network/mco/RestRequestType.hpp>
#include <RakNetTypes.h>

struct RestCallTagData;
struct RestService;
struct Minecraft;
struct ThreadCollection;

struct RestRequestJob: Job
{
	int32_t field_4, field_8, field_C;
	std::function<void(int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)> field_10;
	std::function<void(bool_t, bool_t, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)> field_20;
	std::string field_30;
	std::string body;
	std::shared_ptr<RestService> field_38;
	int32_t field_40;
	RakNet::RakNetGUID field_44;
	std::string field_4C;

	static std::shared_ptr<RestRequestJob> CreateJob(RestRequestType, std::shared_ptr<RestService>, Minecraft*);

	RestRequestJob();
	static void launchRequest(std::shared_ptr<RestRequestJob>, std::shared_ptr<ThreadCollection>, std::function<void(int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)>, std::function<void(bool_t, bool_t, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)>);
	void setBody(const std::string&);

	template<typename... _args>
	void setMethod(const std::string&, _args... args);
	void setTagData(const RestCallTagData&);

	virtual ~RestRequestJob();
	virtual void stop();
	virtual void run();
	virtual void finish();
};
