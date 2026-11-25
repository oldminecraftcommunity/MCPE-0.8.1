#include <level/storage/BundledLevelStorage.hpp>
#include <BinaryBlob.hpp>
#include <BitStream.h>
#include <level/chunk/LevelChunk.hpp>
#include <level/gen/RandomLevelSource.hpp>
#include <sstream>
#include <util/Util.hpp>
#include <zlib.h>
#include <perf/Stopwatch.hpp>
#include <Minecraft.hpp>
#include <_AssetFile.hpp>

BundledLevelStorage::BundledLevelStorage(struct Minecraft* a2, const std::string& a3)
	: MemoryLevelStorage(0)
	, levelNameMaybe(a3) {
	this->levelData = new LevelData();
	this->field_14 = 0;
	this->field_18 = 3;
	this->field_1C = 0;
	this->minecraft = a2;
}

BundledLevelStorage::~BundledLevelStorage() {
	if(this->levelData) {
		delete this->levelData;
	}
	if(this->field_1C) {
		delete this->field_1C;
	}
}
LevelData* BundledLevelStorage::prepareLevel(Level* a2) {
	this->field_14 = a2;
	this->field_1C = new RandomLevelSource(a2, Util::hashCode("Nya1n"), 0, 1);
	bool_t v3 = this->levelNameMaybe.find("survival") == -1;
	this->levelData->setGameType(v3);
	this->levelData->setSpawnMobs(!v3);
	return this->levelData;
}

LevelChunk* BundledLevelStorage::load(Level* a2, int32_t a3, int32_t a4) {
	static Stopwatch sw1;
	static Stopwatch sw2;
	sw1.start();
	sw2.start();
	BinaryBlob v12 = this->getChunkData(a3, a4);
	sw2.stop();
	sw2.printEvery(31, "asset");
	if(!v12.data) return 0;
	if(v12.length < 0) return 0;
	RakNet::BitStream v13;
	char* v10 = new char[0x8000];
	v13.Read(v10, 0x8000);
	LevelChunk* lc = new LevelChunk(a2, (unsigned char*)v10, a3, a4);
	v13.Read((char*)lc->tileMeta.data, 0x4000);
	v13.Read((char*)lc->skyLight.data, 0x4000);
	v13.Read((char*)lc->blockLight.data, 0x4000);
	v13.Read((char*)lc->updateMap, 0x100);
	this->freeChunkData(a3, a4, &v12);
	lc->recalcHeightmap();
	lc->unsaved = 1;
	lc->decorated = 1;
	lc->field_24B = 1;
	sw1.stop();
	sw1.printEvery(31, "gen");
	return lc;
}
void BundledLevelStorage::save2(Level* a2, LevelChunk* a3) {
	std::stringstream v13;
	v13 << "c:/temp/level/chunk_" << a3->chunkX << "_" << a3->chunkZ << ".bin";
	FILE* v8 = fopen(v13.str().c_str(), "wb");
	if(v8) {
		RakNet::BitStream v14;
		char v15[1024];
		v14.Write((char*)a3->tiles, 0x8000u);
		v14.Write((char*)a3->tileMeta.data, 0x4000u);
		v14.Write((char*)a3->skyLight.data, 0x4000u);
		v14.Write((char*)a3->blockLight.data, 0x4000u);
		v14.Write((char*)a3->updateMap, 0x100u);
		z_stream strm;
		strm.zalloc = Z_NULL;
		strm.zfree = Z_NULL;
		strm.opaque = Z_NULL;
		deflateInit2(&strm, -1, 8, 15, 8, 3);
		int ret;
		do {
			strm.avail_out = sizeof(v15);
			strm.next_out = (Bytef*)v15;
			ret = deflate(&strm, 4);
			fwrite(v15, sizeof(*v15), sizeof(v15) - strm.avail_out, v8);
		} while(ret != -1 && strm.avail_out == 0);
		deflateEnd(&strm);
		fclose(v8);
	}
}
static inline std::string evilStd(int x, int z) {
	std::stringstream v19;
	v19 << "levels/a/chunk_" << x << "_" << z << ".bin";
	return v19.str();
}
BinaryBlob BundledLevelStorage::getChunkData(int32_t x, int32_t z) {
	//> 'class std::basic_ostream<char>' has no member named 'str' </3
	std::string v19 = evilStd(x, z);
	AssetFile file = this->minecraft->platform()->readAssetFile(v19);
	if(file.bytes == 0 || file.length < 0) {
		return BinaryBlob(0, -1);
	}
	uLongf destLen = *(int*)file.bytes;
	if(destLen == 0) {
		delete[] file.bytes;
		return BinaryBlob(0, -1);
	}
	Bytef* v15 = new Bytef[destLen];
	uncompress(v15, &destLen, file.bytes + sizeof(int), file.length - sizeof(int));
	delete[] file.bytes;
	return BinaryBlob((char*)v15, destLen);
}
void BundledLevelStorage::freeChunkData(int32_t a2, int32_t a3, BinaryBlob* a4) {
	delete[] a4->data;
	a4->data = 0;
	a4->length = -1;
}
