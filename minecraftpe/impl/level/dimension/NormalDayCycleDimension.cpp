#include <level/dimension/NormalDayCycleDimension.hpp>
#include <math.h>

NormalDayCycleDimension::~NormalDayCycleDimension() {
}
float NormalDayCycleDimension::getTimeOfDay(int32_t a2, float a3) {
	float v3; // s16
	float v4; // s14

	v3 = (float)((float)((float)(a2 % 19200) + a3) / 19200.0) - 0.25;
	if(v3 < 0.0) {
		v3 = v3 + 1.0;
	}
	if(v3 > 1.0) {
		v3 = v3 - 1.0;
	}
	v4 = 1.0 - (cos((float)(v3 * 3.1416)) + 1.0) * 0.5;
	return v3 + (float)((float)(v4 - v3) / 3.0);
}
