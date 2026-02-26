#include <network/mco/RestRequestJob.hpp>
#include "util/JobStatus.hpp"
#include <network/mco/RestCallTagData.hpp>

std::shared_ptr<RestRequestJob> RestRequestJob::CreateJob(RestRequestType, std::shared_ptr<RestService>, Minecraft*) {
	printf("RestRequestJob::CreateJob - not implemented\n"); //TODO
	return std::shared_ptr<RestRequestJob>();
}

RestRequestJob::RestRequestJob(){
	this->field_4 = 0;
	this->field_8 = 0;
	this->field_C = 0;
	this->status = JS_0;
}
void RestRequestJob::launchRequest(std::shared_ptr<RestRequestJob>, std::shared_ptr<ThreadCollection>, std::function<void(int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)>, std::function<void(bool_t, bool_t, int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>)>) {
	printf("RestRequestJob::launchRequest - not implemented\n"); //TODO
}
void RestRequestJob::setBody(const std::string& a2) {
	this->body = a2;
}

template<typename... _args>
void RestRequestJob::setMethod(const std::string&, _args... args);
void RestRequestJob::setTagData(const RestCallTagData& a2) {
	this->field_44 = a2.guid_g;
	this->field_4C = a2.str;
}

RestRequestJob::~RestRequestJob() {
}
void RestRequestJob::stop() {
	this->status = JS_2;
}
void RestRequestJob::run() {
	this->trySetStatus(JS_1);
	timespec t{1, 0};
	nanosleep(&t, 0);
	this->trySetStatus(JS_3);
}
void RestRequestJob::finish(){
	//copyRawCharArrayInside(&v6, "Yey"); Nay
	printf("RestRequestJob::finish - not implemented\n"); //TODO

}
