#include <_types.h>
#include <_AssetFile.hpp>

AssetFile::AssetFile(uint8_t* bytes, int32_t length){
	this->bytes = bytes;
	this->length = length;
}
