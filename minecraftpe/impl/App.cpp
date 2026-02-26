#include <App.hpp>

App::~App() {
}

AppPlatform* App::platform(void){
	return this->context.platform;
}
void App::audioEngineOn(void){}
void App::audioEngineOff(void){}
void App::destroy(void){}
void App::loadState(void*, int32_t){}
void App::saveState(void**, int32_t*){}
bool_t App::useTouchscreen(void){
	return 1;
}
void App::setTextboxText(const std::string&){}
void App::draw(void){}
void App::update(void){}
void App::setSize(int32_t, int32_t){}
void App::quit(void){}
bool_t App::wantToQuit(void){
	return this->wantsToQuit;
}
bool_t App::handleBack(bool_t){
	return 0;
}
void App::handleBack(void){}
void App::init(void){}

void App::init(AppContext& ctx){
	this->context = ctx;
	this->init();
	this->platform()->addListener(this, 0); //XXX not like in vanilla ?
}
