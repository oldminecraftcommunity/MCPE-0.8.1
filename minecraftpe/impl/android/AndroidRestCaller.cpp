#ifdef ANDROID
#include <android/AndroidRestCaller.hpp>
#include <android/AppPlatform_android.hpp>
#include <network/mco/MCOConnector.hpp>
#include <Minecraft.hpp>
#include <network/mco/RestCallerObject.hpp>

void AndroidRestCaller::requestStop() {
	this->mutex.lock();
	for(int v3 = 0; v3 < this->id2request.size(); ++v3){
		this->platform->abortWebRequest(this->id2request[v3].first);
	}
	this->id2request.clear();
	this->mutex.unlock();
}
AndroidRestCaller::~AndroidRestCaller() {
	this->requestStop();
}

//top secret mojang functions :scream:
void test_successful(int a1,std::string a2,RestCallTagData const&) {
	printf("Successful! %d, %s\n", a1, a2.c_str());
}
//imagine leaving this in libminecraftpe.so and increasing its size by less than 1kb </3
void test_failed(bool a1, bool a2, int a3, std::string a4, RestCallTagData const&) {
	printf("Failed (%d, %d)! %d, %s\n", a1, a2, a3, a4.c_str());
}

AndroidRestCaller::AndroidRestCaller(MCOConnector* con, const std::string& s) : RestCaller(con, s){
	this->platform = (AppPlatform_android*) con->minecraft->platform();
}
int AndroidRestCaller::getRequestIndex(int a2, RestCallerObject** a3) {
	this->mutex.lock();
	int v13 = -1;
	for(int i = 0; i != this->id2request.size(); ++i){
		if(this->id2request[i].first == a2){
			v13 = i;
			if(a3) *a3 = this->id2request[i].second;
			break;
		}
	}

	this->mutex.unlock();
	return v13;
}
void AndroidRestCaller::onRequestComplete(int a2, int a3, const std::string& a4) {
	RestCallerObject* v24 = 0;
	int reqIndex = this->getRequestIndex(a2, &v24);
	if(reqIndex >= 0){
		printf("AndroidRestCaller::onRequestComplete - not implemented\n");
	}
}

static int _reqId = 1;
void AndroidRestCaller::makeRequest(RestCallerObject* a2) {
	if(a2->interup == 1){
		if(!this->id2request.empty()) return;
	}else if(a2->interup == 0){
		this->requestStop();
	}
	int reqId = ++_reqId;
	std::string v10 = this->field_8;
	v10 += a2->field_C;
	std::string v11;
	if(a2->type == RCT_GET) v11 = "GET";
	if(a2->type == RCT_PUT) v11 = "PUT";
	if(a2->type == RCT_POST) v11 = "POST";
	if(a2->type == RCT_DELETE) v11 = "DELETE";
	std::string v12 = this->getCookieData();
	this->platform->webRequest(reqId, (size_t) this, v10, v11, v12, "");
	this->mutex.lock();
	this->id2request.push_back(std::pair<int, RestCallerObject*>(reqId, a2));
	this->mutex.unlock();
}
#endif
