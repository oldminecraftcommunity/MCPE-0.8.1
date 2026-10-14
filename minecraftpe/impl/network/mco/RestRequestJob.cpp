#include <network/mco/RestRequestJob.hpp>
#include <util/JobStatus.hpp>
#include <network/mco/RestCallTagData.hpp>
#include <time.h>
#include <network/mco/CurlRestRequestJob.hpp>
#ifdef ANDROID
#include <android/AndroidRestRequestJob.hpp>
#endif
std::shared_ptr<RestRequestJob> RestRequestJob::CreateJob(RestRequestType a2, std::shared_ptr<RestService> a3, Minecraft* a4) {
#ifdef ANDROID
	std::shared_ptr<RestRequestJob> ret; //init with 0
	ret = std::shared_ptr<AndroidRestRequestJob>(new AndroidRestRequestJob(a4)); //exchange
	ret->restService = a3;
	ret->requestType = a2;
	return ret;
#else
	std::shared_ptr<RestRequestJob> ret(new CurlRestRequestJob());
	ret->field_8 = ret; //TODO check is this actually how it is assigned
	ret->restService = a3;
	ret->requestType = a2;
	return ret;
#endif
}

RestRequestJob::RestRequestJob(){
	this->status = JS_0;
}
void RestRequestJob::launchRequest(std::shared_ptr<RestRequestJob> a1, std::shared_ptr<ThreadCollection> a2, std::function<void(int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)> a3, std::function<void(bool, bool, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)> a4) {
	a1->onFinish = a3;
	a1->onError = a4;
	Job::addToThreadCollection(a1, *a2.get());
}
void RestRequestJob::setBody(const std::string& a2) {
	this->body = a2;
}

void RestRequestJob::setTagData(const RestCallTagData& a2) {
	this->field_44 = a2;
}

RestRequestJob::~RestRequestJob() {
}
void RestRequestJob::stop() {
	this->status = JS_STOPPED;
}
void RestRequestJob::run() {
	this->trySetStatus(JS_STARTED);
	timespec t{1, 0};
	nanosleep(&t, 0);
	this->trySetStatus(JS_FINISHED);
}
void RestRequestJob::finish() {
	JobStatus status = this->status;
	std::unique_lock<std::mutex> l;
	if(status == JS_STOPPED) return;
	this->onFinish(200, "Yey", RestCallTagData(), std::shared_ptr<RestRequestJob>(this->field_8));
}
