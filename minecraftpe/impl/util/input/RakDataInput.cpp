#include <util/input/RakDataInput.hpp>


bool_t RakDataInput::readBytes(void* a2, int32_t a3) {
	if(this->hasBytesLeft(a3)) {
		this->stream->ReadBits(a2, 8 * a3, 1);
		return 1;
	}
	return 0;
}
int32_t RakDataInput::numBytesLeft(void) {
	//XXX might be not as in 0.8.1
	return this->stream->GetNumberOfUnreadBits() >> 3;
}
