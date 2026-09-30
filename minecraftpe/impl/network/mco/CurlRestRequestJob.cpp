#ifndef ANDROID
#include <network/mco/CurlRestRequestJob.hpp>
#include <curl/curl.h>
#include <network/RestService.hpp>

static volatile bool canUseCurl = 0;
CurlRestRequestJob::CurlRestRequestJob() {
	static bool globalInit = 0;
	if(!globalInit) {
		globalInit = 1;
		CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
		if(code != CURLE_OK) {
			printf("curl global init failed: %d\n", code);
			return;
		}
		canUseCurl = 1;
	}
	this->field_58 = 0;
	this->field_5C = 0;
	this->started = 0;
}
bool CurlRestRequestJob::isRunning() {
	std::unique_lock<std::mutex> v5(this->mutex, std::defer_lock);
	v5.lock();
	return this->started;
}
void CurlRestRequestJob::onRequestComplete(int a2, int a3, const std::string& a4) {
	this->httpStatusOrNegativeError = a3;
	this->content = a4;
	this->field_60.notify_one();
}

CurlRestRequestJob::~CurlRestRequestJob() {
	if(this->isRunning()) {
		this->stop();
	}
}
void CurlRestRequestJob::stop() {
	{
		std::unique_lock<std::mutex> v5(this->mutex, std::defer_lock);
		if(this->getStatus() == JS_STOPPED) {
			return;
		}
		this->trySetStatus(JS_STOPPED);
		this->started = 0;
	}
	this->field_60.notify_one();
}

static size_t curl_onWrite(char* contents, size_t size, size_t nmemb, void* userp) {
	std::string* str = (std::string*)userp;
	str->append(contents, size * nmemb);
	return size * nmemb;
}

void CurlRestRequestJob::run() {
	std::unique_lock<std::mutex> v5(this->mutex, std::defer_lock);
	v5.lock();

	if(!canUseCurl) {
		printf("curl: not using because canUseCurl is 0\n");
		return;
	}

	this->started = 1;
	this->trySetStatus(JS_STARTED);

	CURL* curl = curl_easy_init();
	if(!curl) {
		printf("curl_easy_init returned 0\n");
		return;
	}

	struct curl_slist* list = NULL;
	std::string v10 = *this->restService->getServiceURL() + this->url;

	printf("%s: Sending %d\n", v10.c_str(), this->requestType);
	curl_easy_setopt(curl, CURLOPT_URL, v10.c_str());
	switch(this->requestType) {
		case RRT_GET:
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
			break;
		case RRT_POST:
			curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1L);
			if(this->body != "") {
				printf("%s: set postfields to %s\n", v10.c_str(), this->body.c_str());

				list = curl_slist_append(list, "Content-Type: application/json");
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, this->body.c_str());
			}else{
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
			}
			break;
		case RRT_PUT:
			curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
			if(this->body != "") {
				printf("%s: set readdata to %s\n", v10.c_str(), this->body.c_str());

				list = curl_slist_append(list, "Content-Type: application/json");
				curl_easy_setopt(curl, CURLOPT_READDATA, this->body.c_str());
			} else {
				curl_easy_setopt(curl, CURLOPT_READDATA, "");
				curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, 0);
			}

			break;
		case RRT_DELETE:
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
			break;
	}

	std::string response;
	//list = curl_slist_append(list, "User-Agent: MCPE/Curl");
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_onWrite);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	std::string cookie = this->restService->getCookieDataAsString();

	if(/*cookie != null &&*/ cookie.length() > 0) {
		printf("Setting cookie: (%lu) %s\n", cookie.length(), cookie.c_str());
		list = curl_slist_append(list, ("Cookie: " + cookie).c_str());
	}

	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	CURLcode result = curl_easy_perform(curl);

	printf("Req: %s -> %d: (%s)\n", v10.c_str(), result, response.c_str());
	if(result == CURLE_OK) {
		long code;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
		this->onRequestComplete(0, code, response);
	} else {
		this->httpStatusOrNegativeError = -1;
	}
	curl_easy_cleanup(curl);


	this->trySetStatus(JS_FINISHED);
	this->started = 0;
}
void CurlRestRequestJob::finish(){
	if(this->getStatus() != JS_STOPPED) {
		if(this->httpStatusOrNegativeError > 0) {
			//int32_t, const std::string&, const RestCallTagData&, std::shared_ptr<RestRequestJob>
			if(this->httpStatusOrNegativeError < 300) {
				this->onFinish(this->httpStatusOrNegativeError, this->content, this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));
			} else {
				this->onError(0, 0, this->httpStatusOrNegativeError, this->content, this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));
			}
		} else {
			this->onError(0, 1, this->httpStatusOrNegativeError, this->content, this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));
		}

		return;
	}
	this->onError(1, 0, 0, "", this->field_44, std::shared_ptr<RestRequestJob>(this->field_8));

	printf("CurlRestRequestJob::finish - not implemented\n");
}
#endif
