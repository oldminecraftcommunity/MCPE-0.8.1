#pragma once
#include <_types.h>
//XXX represents unknown(yet) struct from AppPlatform::readAssetFile
struct AssetFile{
	uint8_t* bytes;
	int32_t length;

	AssetFile(uint8_t* bytes, int32_t length);
};
