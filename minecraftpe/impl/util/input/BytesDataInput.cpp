#include <util/input/BytesDataInput.hpp>
BytesDataInput::~BytesDataInput(){

}
int8_t BytesDataInput::readByte() {
	int8_t v4;
	this->readBytes(&v4, 1);
	return v4;
}

double BytesDataInput::readDouble() {
	double v4;
	this->readBytes(&v4, 8);
	return v4;
}

float BytesDataInput::readFloat() {
	float v4;
	this->readBytes(&v4, 4);
	return v4;
}

int32_t BytesDataInput::readInt() {
	int32_t v4;
	this->readBytes(&v4, 4);
	return v4;
}

int64_t BytesDataInput::readLongLong() {
	int64_t v4;
	this->readBytes(&v4, 8);
	return v4;
}

int16_t BytesDataInput::readShort() {
	int16_t v4;
	this->readBytes(&v4, 2);
	return v4;
}

std::string BytesDataInput::readString() {
	int16_t slen = this->readShort();
	int32_t v6;
	void* v7;

	if(slen > 0) {
		if(slen == 0x7fff) v6 = 32766;
		else v6 = slen;
		v7 = ::operator new[](v6+1);
		this->readBytes(v7, v6);
		((char_t*)v7)[v6] = 0;
		std::string ret((char*)v7);
		if(v7) ::operator delete[](v7);
		return ret;
	}

	return "";
}
