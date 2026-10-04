#ifdef ANDROID
#include <android/AndroidRestCaller.hpp>
#include <android/AppPlatform_android.hpp>
#include <network/mco/MCOConnector.hpp>
#include <Minecraft.hpp>
#include <network/mco/RestCallerObject.hpp>

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

AndroidRestCaller::~AndroidRestCaller() {
	this->requestStop();
}
void AndroidRestCaller::requestStop() {
	this->mutex.lock();
	for(int v3 = 0; v3 < this->id2request.size(); ++v3){
		this->platform->abortWebRequest(this->id2request[v3].first);
	}
	this->id2request.clear();
	this->mutex.unlock();
}
void AndroidRestCaller::makeRequest(RestCallerObject* a2) {
	if(a2->interup == 1){
		if(!this->id2request.empty()) return;
	}else if(a2->interup == 0){
		this->requestStop();
	}
	printf("AndroidRestCaller::makeRequest - not implemented\n");
}

//top secret mojang functions :scream:
//imagine leaving this in libminecraftpe.so and increasing its size by less than 1kb </3
void test_failed(bool a1, bool a2, int a3, std::string a4, RestCallTagData const&) {
	printf("Failed (%d, %d)! %d, %s\n", a1, a2, a3, a4.c_str());
}
void test_successful(int a1,std::string a2,RestCallTagData const&) {
	printf("Successful! %d, %s\n", a1, a2.c_str());
}
#endif
