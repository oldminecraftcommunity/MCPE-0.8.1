#include <util/output/RakDataOutput.hpp>

RakDataOutput::~RakDataOutput() {
}
void RakDataOutput::writeBytes(const void* a2, int32_t a3){
	this->bitStream->WriteBits((const unsigned char*)a2, a3*8, 1);
}
