#pragma once
#include <IConfigListener.hpp>
#include <math/Vec3.hpp>
#include <perf/Stopwatch.hpp>

struct ITurnInput : IConfigListener{
	int32_t field_4;
	double curTime;

	float getDeltaTime() {
		if (this->curTime == -1.0) {
			this->curTime = getTimeS();
		}
		double timeS = getTimeS();
		double curTime = this->curTime;
		this->curTime = timeS;
		return timeS - curTime;
	}
	static float linearTransform(float a1, float a2, float a3, bool_t a4) {
		float v4; // s14
		float v5; // s15
		float v6; // s14
		v4 = a2;
		if (a1 < 0.0) {
			v4 = -a2;
		}
		if (fabsf(v4) >= fabsf(a1)) {
			return 0.0;
		}
		v5 = (float) ((a1 - v4)) * a3;
		if (a4) {
			v6 = fabsf(v5);
			if (v6 > 1.0) {
				return v5 / v6;
			}
		}
		return v5;
	}

	virtual ~ITurnInput() {
	}
	virtual void onConfigChanged(const Config&) {
	}
	virtual Vec3 getTurnDelta() = 0;
};
