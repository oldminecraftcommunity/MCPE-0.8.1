#include <input/Controller.hpp>
#include <math.h>

float Controller::stickValuesX[2];
float Controller::stickValuesY[2];
bool_t Controller::isTouchedValues[2];

float _D67238D0[] = {0, 0.64, -0.64};

void Controller::feed(int32_t a2, int32_t a3, float a4, float a5){
	int32_t v7; // r2
	int32_t v8; // r5

	if(Controller::isValidStick(a2)) {
		if(a4 >= 0.0) {
			v7 = 2;
		} else {
			v7 = 1;
		}
		Controller::isTouchedValues[v7 - 1] = a3 != 0;
		v8 = v7 - 1;
		Controller::stickValuesX[v8] = Controller::linearTransform(a4 + _D67238D0[v7], 0.0, 2.78, 1);
		Controller::stickValuesY[v8] = a5;
	}
}
float Controller::getTransformedX(int32_t a2, float a3, float a4, bool_t a5){
	if(Controller::isValidStick(a2)) {
		return Controller::linearTransform(Controller::stickValuesX[a2 - 1], a3, a4, a5);
	} else {
		return 0.0;
	}
}
float Controller::getTransformedY(int32_t a2, float a3, float a4, bool_t a5){
	if(Controller::isValidStick(a2)) {
		return Controller::linearTransform(Controller::stickValuesY[a2 - 1], a3, a4, a5);
	} else {
		return 0.0;
	}
}
float Controller::getX(int32_t a1){
	if(Controller::isValidStick(a1)) return Controller::stickValuesX[a1 - 1];
	return 0;
}
float Controller::getY(int32_t a1) {
	if(Controller::isValidStick(a1)) return Controller::stickValuesY[a1 - 1];
	return 0;
}
bool_t Controller::isTouched(int32_t a1) {
	if(Controller::isValidStick(a1)) return Controller::isTouchedValues[a1 - 1];
	return 0;
}
bool_t Controller::isValidStick(int32_t a1){
	return (uint32_t)(a1 - 1) <= 1;
}
float Controller::linearTransform(float a2, float a3, float a4, bool_t a5) {
	float v4;  // s14
	float v5;  // s15
	bool_t v6; // fzf
	bool_t v7; // fnf

	v4 = a3;
	if(a2 < 0.0) {
		v4 = -a3;
	}
	if(fabsf(v4) >= fabsf(a2)) {
		return 0.0;
	}
	v5 = (float)(a2 - v4) * a4;
	if(a5 && fabsf(v5) > 1.0) {
		v6 = v5 == 0.0;
		v7 = v5 < 0.0;
		v5 = -1.0;
		if(!v7 && !v6) {
			return 1.0;
		}
	}
	return v5;
}
