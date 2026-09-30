#include <network/mco/MCOPayloadPacker.hpp>
#include <input/ControllerData.hpp>
#include <BitStream.h>
#include <util/Random.hpp>
MCOPayloadPacker::MCOPayloadPacker(Random& a2) {
	this->random = &a2;
}
ControllerData MCOPayloadPacker::readControlPackage(char* src, uint32_t a4) {
	ControllerData ret;
	RakNet::BitStream v10((unsigned char*)src, a4, 1);
	int v7 = 0;
	v10.Read(v7);
	v10.Read(ret.field_0);
	v10.Read(ret.field_4);
	char dest[4096];
	int toRead;
	std::string unused = "";
	if(v7 <= 11) toRead = 0;
	else if(v7 > 4107) toRead = 4096;
	else toRead = v7 - 12;
	v10.Read(dest, toRead);
	ret.field_8 = std::string(dest, toRead);
	return ret;
}
std::string MCOPayloadPacker::writeBitStream(long long a3, std::string a4) {
	unsigned int v14 = this->random->genrand_int32();
	unsigned int v15 = this->random->genrand_int32();
	unsigned int v16 = this->random->genrand_int32();
	unsigned int v17 = this->random->genrand_int32();
	RakNet::BitStream v19;
	short v13 = a4.size();
	v19.Write<long long>(a3); //inlined
	v19.Write<short>(v13);
	v19.Write(a4.c_str(), a4.size());
	v19.Write<unsigned int>(v14);
	v19.Write<unsigned int>(v15);
	v19.Write<unsigned int>(v16);
	v19.Write<unsigned int>(v17);
	return std::string((const char*) v19.GetData(), v19.GetNumberOfBytesUsed());
}
std::string MCOPayloadPacker::writeControllPackage(const ControllerData& a3) {
	RakNet::BitStream v15;
	v15.Write((int)a3.field_8.size());
	v15.Write((int)a3.field_0);
	v15.Write(a3.field_4);
	v15.WriteBits((const unsigned char*)a3.field_8.c_str(), a3.field_8.size() >= 0x1000 ? 32768 : a3.field_8.size() * 8);
	unsigned int v13 = 0;
	v15.Write(v13);
	return std::string((const char*) v15.GetData(), v15.GetNumberOfBytesUsed());
}
