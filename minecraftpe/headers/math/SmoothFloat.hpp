#pragma once
#include <_types.h>

struct SmoothFloat
{
	float field_0, field_4, field_8;
	SmoothFloat() {
		this->field_0 = this->field_4 = this->field_8 = 0;
	}
	float getNewDeltaValue(float a, float b) {
		this->field_0 += a;
		float v5 = (this->field_0 - this->field_4) * b;
		float v6 = this->field_8 + ((v5 - this->field_8) * 0.5f);
		this->field_8 = v6;
		if (v5 <= 0.0 || v5 <= v6) {
			if (v5 >= 0.0) {
				v6 = v5;
			} else if (v5 >= v6) {
				v6 = v5;
			}
		}
		this->field_4 += v6;
		return v6;
	}
};
