#include <util/output/BytesDataOutput.hpp>

void BytesDataOutput::writeString(const std::string& a2) {
	int sz = a2.size() & 0x7fff;
	this->writeShort(sz);
	this->writeBytes(a2.data(), sz);
}
