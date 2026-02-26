#pragma once
#include <_types.h>
#include <string>
#include <map>
#include <BitStream.h>

struct RegionFile
{
	FILE* fileRaw;
	std::string path2file;
	int32_t* locTable;
	int8_t* bytes4096_2;
	std::map<int32_t, bool_t> stdMap;

	RegionFile(const std::string&);
	void close();
	bool_t open();
	bool_t readChunk(int32_t, int32_t, RakNet::BitStream**);
	bool_t write(int32_t, RakNet::BitStream&);
	bool_t writeChunk(int32_t, int32_t, RakNet::BitStream&);

	virtual ~RegionFile();
};
