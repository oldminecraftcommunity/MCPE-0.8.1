#include <util/input/IDataInput.hpp>

IDataInput::~IDataInput() {
}

bool_t IDataInput::hasBytesLeft(int32_t a2) {
	return this->numBytesLeft() >= a2;
}
