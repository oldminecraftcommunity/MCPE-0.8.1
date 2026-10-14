#ifdef ANDROID
#include <android/AndroidRestRequestJob.hpp>
#include <Minecraft.hpp>
#include <mutex>
#include <network/RestService.hpp>
AndroidRestRequestJob::AndroidRestRequestJob(Minecraft* a2) : field_58(0), field_5C(0){
	this->started = 0;
	this->platform = (AppPlatform_android*) a2->platform();
}
bool AndroidRestRequestJob::isRunning(){
	std::unique_lock<std::mutex> v3(this->mutex);
	return this->started;
}
void AndroidRestRequestJob::onRequestComplete(int a2, int a3, const std::string& a4){
	this->httpStatusOrNegativeError = a3;
	this->content = a4;
	this->field_60.notify_one();
}

AndroidRestRequestJob::~AndroidRestRequestJob(){
	if(this->isRunning()){
		this->stop();
	}
}
void AndroidRestRequestJob::stop(){
	{
		std::unique_lock<std::mutex> v3(this->mutex);
		if(this->getStatus() != JS_STOPPED){
			this->trySetStatus(JS_STOPPED);
			this->started = 0;
			this->platform->abortWebRequest(this->field_6C);
		}else{
			return;
		}
	}
	this->field_60.notify_one();
}
static std::mutex _run_counter_mut;
static int _run_counter = 1;
static inline int _nextRunCounter(){
	std::unique_lock<std::mutex> lock(_run_counter_mut);
	return ++_run_counter;
}
void AndroidRestRequestJob::run(){
	{
		std::unique_lock<std::mutex> v11(this->mutex);
		this->started = 1;
		this->trySetStatus(JS_STARTED);
		std::string reqType;
		if(this->requestType == RRT_GET) reqType = "GET";
		else if(this->requestType == RRT_POST) reqType = "POST";
		else if(this->requestType == RRT_PUT) reqType = "PUT";
		else if(this->requestType == RRT_DELETE) reqType = "DELETE";
		std::string serviceURL(*this->restService->getServiceURL());
		serviceURL = this->url;
		int c = _nextRunCounter();
		this->platform->webRequest(c, (long long int) this, serviceURL, reqType, this->restService->getCookieDataAsString(), this->body);
	}
	std::unique_lock<std::mutex> v11(this->field_64);
	this->field_60.wait(v11);
	this->trySetStatus(JS_FINISHED);
	this->started = 0;
}
void AndroidRestRequestJob::finish(){
	if(this->getStatus() != JS_STOPPED){
		if(this->httpStatusOrNegativeError < 0){
			this->onError(0, 1, this->httpStatusOrNegativeError, this->content, this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));
		}else{
			if(this->httpStatusOrNegativeError >= 300){
				this->onError(0, 0, this->httpStatusOrNegativeError, this->content, this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));
			}else{
				this->onFinish(this->httpStatusOrNegativeError, this->content, this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));
			}
		}
	}else{
		this->onError(1, 0, 0, "", this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));
	}
}
#endif
