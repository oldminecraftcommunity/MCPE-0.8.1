#pragma once
#include <_types.h>
#include <IConfigListener.hpp>
#include <math/Vec3.hpp>

struct ITurnInput : IConfigListener{
	int32_t field_4;
	double curTime;

	float getDeltaTime();
	static float linearTransform(float, float, float, bool_t);

	virtual ~ITurnInput();
	virtual void onConfigChanged(const Config&);
	virtual Vec3 getTurnDelta() = 0;
};
