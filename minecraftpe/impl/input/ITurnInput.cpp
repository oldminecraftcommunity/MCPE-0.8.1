#include <input/ITurnInput.hpp>
#include <math.h>
#include <utils.h>

float ITurnInput::getDeltaTime() {
	if(this->curTime == -1.0) {
		this->curTime = getTimeS();
	}
	double timeS = getTimeS();
	double curTime = this->curTime;
	this->curTime = timeS;
	return timeS - curTime;
}
float ITurnInput::linearTransform(float a1, float a2, float a3, bool_t a4) {
	float v4; // s14
	float v5; // s15
	float v6; // s14

	v4 = a2;
	if(a1 < 0.0) {
		v4 = -a2;
	}
	if(fabsf(v4) >= fabsf(a1)) {
		return 0.0;
	}
	v5 = (float)(a1 - v4) * a3;
	if(a4) {
		v6 = fabsf(v5);
		if(v6 > 1.0) {
			return v5 / v6;
		}
	}
	return v5;
}

ITurnInput::~ITurnInput() {
}
void ITurnInput::onConfigChanged(const Config&) {
}
