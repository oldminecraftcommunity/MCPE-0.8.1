#pragma once
#include <_types.h>
#include <IConfigListener.hpp>

struct IMoveInput : IConfigListener{
	float strafeInput, forwardInput;
	int8_t idkWhatIsThis;
	bool jumping, sneaking;
	int8_t flyUpPressed;
	int8_t flyDownPressed, idkWhatIsThis2;

	virtual ~IMoveInput(){}
	virtual void tick(struct Player*){}
	virtual void render(float){}
	virtual void setKey(int32_t, bool_t){}
	virtual void releaseAllKeys(){}
	virtual void onConfigChanged(const Config&){}
};
