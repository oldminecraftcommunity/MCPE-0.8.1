#include <level/storage/RegionFile.hpp>
#include <BitStream.h>

RegionFile::RegionFile(const std::string& a2) {
	this->fileRaw = 0;
	this->path2file = a2;
	this->path2file += "/";
	this->path2file += "chunks.dat";
	this->locTable = new int32_t[1024];
	this->bytes4096_2 = new int8_t[4096];
	memset(this->bytes4096_2, 0, 4096);
}
void RegionFile::close() {
	if(this->fileRaw) {
		fclose(this->fileRaw);
		this->fileRaw = 0;
	}
}
bool_t RegionFile::open() {
	FILE* file; // r0
	int32_t v3; // r5
	int32_t v4; // r3
	int32_t v5; // r11
	int32_t v6; // r10
	int32_t i; // r7
	FILE* result; // r0
	int32_t v9; // [sp+4h] [bp-2Ch] BYREF

	this->close();
	memset(this->locTable, 0, 4096u);
	file = fopen(this->path2file.c_str(), "r+b");
	this->fileRaw = file;
	if(file) // file_exists
	{
		fread(this->locTable, 4u, 1024u, file);
		v3 = 0;
		v9 = 0;
		this->stdMap[v9] = 0;
		do {
			v4 = this->locTable[v3];
			if(v4) {
				v5 = v4 >> 8;
				v6 = (uint8_t)v4;
				for(i = 0; i < v6; ++i) {
					v9 = i + v5;
					this->stdMap[v9] = 0;
				}
			}
			++v3;
		} while(v3 != 1024);
	} else {
		result = fopen(this->path2file.c_str(), "w+b");
		this->fileRaw = result;
		if(!result) {
			return 0;
		}
		fwrite(this->locTable, 4u, 1024u, result);
		v9 = 0;
		this->stdMap[v9] = 0;
	}
	return this->fileRaw != 0;
}
bool_t RegionFile::readChunk(int32_t chunkX, int32_t chunkZ, RakNet::BitStream** a4) {
	int32_t result; // r0
	FILE* fileRaw; // r3
	uint8_t* v8; // r7
	int32_t n; // [sp+4h] [bp-1Ch] OVERLAPPED BYREF
	int32_t useless; // [sp+8h] [bp-18h]

	n = chunkX;
	useless = chunkZ;
	result = this->locTable[32 * chunkZ + chunkX];
	if(result) {
		fseek(this->fileRaw, result >> 8 << 12, 0);
		fileRaw = this->fileRaw;
		n = 0;
		fread(&n, 4u, 1u, fileRaw);
		n -= 4;
		v8 = new uint8_t[n];
		fread(v8, 1u, n, this->fileRaw);
		*a4 = new RakNet::BitStream(v8, n, 0);
		return 1;
	}
	return 0;
}
bool_t RegionFile::write(int32_t a2, RakNet::BitStream& a3) {
	fseek(this->fileRaw, a2 << 12, 0);
	int32_t v6 = a3.GetNumberOfBytesUsed() + 4;
	fwrite(&v6, 4u, 1u, this->fileRaw);
	fwrite(a3.GetData(), 1u, a3.GetNumberOfBytesUsed(), this->fileRaw);
	return 1;
}
bool_t RegionFile::writeChunk(int32_t chunkX, int32_t chunkZ, RakNet::BitStream& a4) {
	int32_t regionIndex; // r10
	int32_t locTableEntry; // r7
	int32_t v8; // r5
	int32_t firstByteOfLocTableEntry; // r8
	int32_t v10; // r7
	int32_t v11; // r6
	int32_t v13; // r2
	int32_t v14; // r11
	int32_t v16; // r6
	int32_t v17; // r3
	int32_t v22; // r7
	int32_t i; // r12
	int32_t v24; // r7
	int32_t v26; // [sp+4h] [bp-3Ch]
	int32_t v28; // [sp+8h] [bp-38h]
	int32_t off; // [sp+Ch] [bp-34h]
	int32_t v30; // [sp+14h] [bp-2Ch] BYREF

	regionIndex = chunkX + 32 * chunkZ;
	off = regionIndex;
	locTableEntry = this->locTable[regionIndex];
	v8 = ((int32_t)(a4.GetNumberOfBytesUsed() + 4) >> 12) + 1;
	if(v8 <= 256) {
		firstByteOfLocTableEntry = (uint8_t)locTableEntry;
		v10 = locTableEntry >> 8;
		if(v10) {
			if(firstByteOfLocTableEntry == v8) {
				this->write(v10, a4);
				return 1;
			}
			v11 = 0;
		} else {
			v11 = 0;
		}
		v13 = 1;
		while(v11 < firstByteOfLocTableEntry) {
			v30 = v11 + v10;
			v26 = v13;
			this->stdMap[v30] = v26;
			v13 = v26;
			++v11;
		}
		v14 = 0;
		v16 = 0;
		while(1) {
			v17 = v16 + v14;
			auto&& p = this->stdMap.find(v17); //TODO check, it was inlined here
			if(p == this->stdMap.end()) {
				break;
			}
			v30 = v16 + v14;
			if(this->stdMap[v30]) {
				if(++v14 >= v8) {
					goto LABEL_25;
				}
			} else {
				v16 += v14 + 1;
				v14 = 0;
			}
		}
		v22 = 0;
		fseek(this->fileRaw, 0, 2);
		for(i = v8 - v14; v22 < i; i = v28) {
			v28 = i;
			fwrite(this->bytes4096_2, 4u, 0x400u, this->fileRaw);
			v30 = v22 + v16;
			++v22;
			this->stdMap[v30] = 1;
		}
LABEL_25:
		v24 = 0;
		this->locTable[regionIndex] = v8 | (v16 << 8);
		do {
			v30 = v24 + v16;
			++v24;
			this->stdMap[v30] = 0;
		}
		while ( v24 < v8 );
		this->write(v16, a4);
		fseek(this->fileRaw, off * 4, 0);
		fwrite(&this->locTable[off], 4u, 1u, this->fileRaw);
		return 1;
	}
	return 0;
}

RegionFile::~RegionFile() {
	this->close();
	if(this->locTable) delete[] this->locTable;
	if(this->bytes4096_2) delete[] this->bytes4096_2;
}
