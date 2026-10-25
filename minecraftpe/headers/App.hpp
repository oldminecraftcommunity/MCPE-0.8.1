#pragma once
#include <AppPlatform.hpp>
#include <AppContext.hpp>

struct App : AppPlatform::Listener{

	bool initialized;
	bool wantsToQuit;
	AppContext context;
	bool field_18;
	int32_t width, height, field_24, field_28, field_2C;
	int field_30;
	int field_34;

	void init(AppContext& ctx){
		this->context = ctx;
		this->init();
		this->initialized = 1;
		this->platform()->addListener(this, 0); //XXX not like in vanilla ?
	}


	virtual ~App(){}
	virtual void onAppSuspended(void) = 0;
	virtual AppPlatform* platform(void){
		return this->context.platform;
	}
	virtual void audioEngineOn(void){}
	virtual void audioEngineOff(void){}
	virtual void destroy(void){}
	virtual void loadState(void*, int32_t){}
	virtual bool saveState(void**, int32_t*){
		return 0;
	}
	virtual bool_t useTouchscreen(void){
		return 1;
	}
	virtual void setTextboxText(const std::string&){}
	virtual void draw(void){}
	virtual void update(void){}
	virtual void setSize(int32_t, int32_t){}
	virtual void quit(void) {
		this->wantsToQuit = 1;
	}
	virtual bool_t wantToQuit(void){
		return this->wantsToQuit;
	}
	virtual bool_t handleBack(bool_t) {
		return 0;
	}
	virtual void handleBack(void){}
	virtual void init(void){}
};
