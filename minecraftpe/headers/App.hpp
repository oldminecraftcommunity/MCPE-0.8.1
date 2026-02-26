#pragma once
#include <AppPlatform.hpp>
#include <AppContext.hpp>

struct App : AppPlatform::Listener{

	byte field_4;
	bool_t wantsToQuit;
	byte field_2, field_3;
	AppContext context;
	int8_t field_18, field_19, field_1A, field_1B;
	int32_t field_1C, field_20, field_24, field_28, field_2C, field_30, field_34;

	void init(AppContext&);

	virtual ~App();
	virtual void onAppSuspended(void) = 0;
	virtual AppPlatform* platform(void);
	virtual void audioEngineOn(void);
	virtual void audioEngineOff(void);
	virtual void destroy(void);
	virtual void loadState(void*, int32_t);
	virtual void saveState(void**, int32_t*);
	virtual bool_t useTouchscreen(void);
	virtual void setTextboxText(const std::string&);
	virtual void draw(void);
	virtual void update(void);
	virtual void setSize(int32_t, int32_t);
	virtual void quit(void);
	virtual bool_t wantToQuit(void);
	virtual bool_t handleBack(bool_t);
	virtual void handleBack(void);
	virtual void init(void);
};
