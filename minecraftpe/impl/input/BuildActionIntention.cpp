#include <input/BuildActionIntention.hpp>

bool_t BuildActionIntention::isRemove() {
	int32_t v1; // r0

	v1 = this->field_0;
	if((v1 & 4) != 0) {
		return 1;
	} else {
		return ((uint32_t)v1 >> 1) & 1;
	}
}
