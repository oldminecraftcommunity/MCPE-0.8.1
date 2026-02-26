#include <math/SmoothFloat.hpp>
SmoothFloat::SmoothFloat() {
	this->field_0 = this->field_4 = this->field_8 = 0;
}
float SmoothFloat::getNewDeltaValue(float a, float b) {
	float v3; // s13
	float v4; // s14
	float v5; // s14
	float v6; // s15

	v3 = this->field_4;
	v4 = a + this->field_0;
	this->field_0 = v4;
	v5 = (float)(v4 - v3) * b;
	v6 = this->field_8 + (float)((float)(v5 - this->field_8) * 0.5);
	this->field_8 = v6;
	if(v5 <= 0.0 || v5 <= v6) {
		if(v5 >= 0.0) {
			v6 = v5;
		} else if(v5 >= v6) {
			v6 = v5;
		}
	}
	this->field_4 = v3 + v6;
	return v6;
}
