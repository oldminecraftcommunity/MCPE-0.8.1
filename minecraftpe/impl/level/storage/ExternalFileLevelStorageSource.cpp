#include <level/storage/ExternalFileLevelStorageSource.hpp>
#include <compression.hpp>
#include <cpputils.hpp>
#include <dirent.h>
#include <level/storage/ExternalFileLevelStorage.hpp>
#include <level/storage/LevelData.hpp>
#include <sstream>

ExternalFileLevelStorageSource::ExternalFileLevelStorageSource(const std::string& a2, const std::string& a3) {
	this->field_10 = !(a3 == a2);
	const char* v10[] = {"/games", "/com.mojang", "/minecraftWorlds"};
	createTree(a2.c_str(), v10, 3);
	if(this->field_10) {
		createTree(a3.c_str(), v10, 3);
	}
	this->field_4 = a2 + "/games" + "/com.mojang" + "/minecraftWorlds";
	this->field_8 = a3 + "/games" + "/com.mojang" + "/minecraftWorlds";
	this->folderName = this->field_8 + "/_LevelCache";
	createFolderIfNotExists(this->folderName.c_str());
}
void ExternalFileLevelStorageSource::addLevelSummaryIfExists(std::vector<LevelSummary>& a2, const char_t* a3) {
	std::string a1 = this->field_4;
	a1 += "/";
	a1 += a3;
	LevelData ld;
	if(ExternalFileLevelStorage::readLevelData(a1, ld)) {
		LevelSummary ls;
		ls.levelDir = a3;
		ls.seed = ld.getSeed();
		ls.levelName = ld.levelName;
		ls.lastPlayed = ld.getLastPlayed();
		ls.sizeOnDisk = ld.getSizeOnDisk();
		ls.gamemode = ld.getGameType();
		a2.push_back(ls);
	}
}
std::string ExternalFileLevelStorageSource::getFullPath(const std::string& a3) {
	if(LevelStorageSource::TempLevelId == a3) {
		return this->field_8 + '/' + a3;
	} else {
		return this->field_4 + '/' + a3;
	}
}

std::string ExternalFileLevelStorageSource::getName() {
	return "External File Level Storage";
}
void ExternalFileLevelStorageSource::getLevelList(std::vector<LevelSummary>& a2) {
#ifdef __WIN32__
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile((this->field_4+"\\*.*").c_str(), &data);
	if(hFind == INVALID_HANDLE_VALUE){
		return;
	}
	do{
		if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			this->addLevelSummaryIfExists(a2, data.cFileName);
		}
	}while(FindNextFile(hFind, &data));
	FindClose(hFind);
#else
	DIR* v4 = opendir(this->field_4.c_str());
	if(!v4) {
		_errno();
		return;
	}
	while(1) {
		struct dirent* v6 = readdir(v4);
		if(!v6) {
			break;
		}
		if(v6->d_type == DT_DIR) {
			this->addLevelSummaryIfExists(a2, v6->d_name);
		}
	}
	closedir(v4);
#endif
}
int32_t ExternalFileLevelStorageSource::getDataTagFor(const std::string&) {
	return 0;
}
LevelStorage* ExternalFileLevelStorageSource::selectLevel(const std::string& a2, bool_t a3) {
	return new ExternalFileLevelStorage(a2, this->getFullPath(a2));
}
bool_t ExternalFileLevelStorageSource::isNewLevelIdAcceptable(const std::string&) {
	return 1;
}

void ExternalFileLevelStorageSource::deleteLevel(const std::string& a2) {
	DeleteDirectory(this->getFullPath(a2), 1);
}
void ExternalFileLevelStorageSource::renameLevel(const std::string&, const std::string&)
{
	printf("ExternalFileLevelStorageSource::renameLevel - not implemented\n");
}
;

static std::string _D66784C8(LevelData* a2) { //inlined
	std::stringstream v10;
	v10 << a2->getSeed();
	v10 << '_';
	v10 << a2->getGeneratorVersion();
	v10 << ".cach1";
	return v10.str();
}
void ExternalFileLevelStorageSource::storeToCache(LevelData* a2, const std::string& a3) {
	std::string v6 = this->folderName + '/' + _D66784C8(a2);
	if(!exists(v6.c_str())) {
		std::string v7 = this->getFullPath(a3);
		std::string v8 = v7 + "/chunks.dat";
		compression::gzip::compress(v8, v6, 1);
	}
}
void ExternalFileLevelStorageSource::loadFromCache(LevelData* a2, const std::string& a3) {
	std::string filename = (std::string(this->folderName) + '/') + _D66784C8(a2);
	if(exists(filename.c_str())) {
		std::string v7 = this->getFullPath(a3);
		std::string v8 = v7 + "/chunks.dat";
		if(!compression::gzip::decompress(filename, v8)) {
			remove(filename.c_str());
			remove(v8.c_str());
		}
	}
}
void ExternalFileLevelStorageSource::clearCache() {
	if(Util::endsWith(this->folderName, "_LevelCache")) {
		DeleteDirectory(this->folderName, 1);
		createFolderIfNotExists(this->folderName.c_str());
	}
}
