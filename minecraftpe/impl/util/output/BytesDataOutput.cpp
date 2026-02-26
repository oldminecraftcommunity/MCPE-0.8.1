#include <util/output/BytesDataOutput.hpp>

BytesDataOutput::~BytesDataOutput() {
}
void BytesDataOutput::writeString(const std::string& a2) {
	this->writeShort(a2.size() & 0x7fff);
	this->writeBytes(a2.data(), a2.size() & 0x7fff);
}
void BytesDataOutput::writeFloat(float a2) {
	this->writeBytes(&a2, 4);
}
void BytesDataOutput::writeDouble(double a2) {
	this->writeBytes(&a2, 8);
}
void BytesDataOutput::writeByte(int8_t a2) {
	this->writeBytes(&a2, 1);
}
void BytesDataOutput::writeShort(int16_t a2) {
	this->writeBytes(&a2, 2);
}
void BytesDataOutput::writeInt(int32_t a2) {
	this->writeBytes(&a2, 4);
}
void BytesDataOutput::writeLongLong(int64_t a2) {
	this->writeBytes(&a2, 8);
}
