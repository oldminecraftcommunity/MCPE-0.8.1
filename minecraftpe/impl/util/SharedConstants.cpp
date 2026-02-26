#include <util/SharedConstants.hpp>

bool_t SharedConstants::isVesion(int32_t a, int32_t b, int32_t c, int32_t d) {
	if(a)
		return 0;
	else if(b == 8 && c == 1)
		return d == 0;
	return 0; //a
}

int32_t SharedConstants::getVersionCode(){
	return SharedConstants::getVersionCode(0, 8, 1, 0);
}

int32_t SharedConstants::getVersionCode(int32_t a1, int32_t a2, int32_t a3, int32_t a4) {
	return 100000 * a2 + 10000000 * a1 + 1000 * a3 + a4;
}
