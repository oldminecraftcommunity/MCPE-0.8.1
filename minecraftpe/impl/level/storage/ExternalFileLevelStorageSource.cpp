#include <level/storage/ExternalFileLevelStorageSource.hpp>
#include <compression.hpp>
#include <fileutil.hpp>
#include <dirent.h>
#include <level/storage/ExternalFileLevelStorage.hpp>
#include <level/storage/LevelData.hpp>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <util/Util.hpp>
#include <set>

int32_t ExternalFileLevelStorageSource::getDataTagFor(const std::string&) {
	return 0;
}
bool_t ExternalFileLevelStorageSource::isNewLevelIdAcceptable(const std::string&) {
	return 1;
}


std::string ExternalFileLevelStorageSource::getName() {
	return "External File Level Storage";
}
int recursiveDelete(const char_t* a1) {
#ifdef __WIN32__
	WIN32_FIND_DATA data;
	HANDLE hFind = FindFirstFile((std::string(a1)+("\\*.*")).c_str(), &data);
	if(hFind == INVALID_HANDLE_VALUE){
		return remove(a1);
	}
	do{
		if(!strcmp(data.cFileName, ".") || !strcmp(data.cFileName, "..")) continue;
		int result;
		if(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
			result = recursiveDelete((std::string(a1)+"\\"+data.cFileName).c_str());
		}else{
			result = remove((std::string(a1)+"\\"+data.cFileName).c_str());
		}
		if(result) return result;
	}while(FindNextFile(hFind, &data) != 0);
	return remove(a1);
#else
	DIR* v2 = opendir(a1);
	if(v2) {
		while(1) {
			struct dirent* v5 = readdir(v2);
			if(!v5) break;
			if(strcmp(v5->d_name, ".")) { //TODO it should use d_name[8] ?
				if(strcmp(v5->d_name, "..")) {
					char_t s[2048];
					sprintf(s, "%s/%s", a1, v5->d_name);
					int result = v5->d_type == DT_DIR ? recursiveDelete(s) : remove(s); //TODO references some unknown var
					if(result) {
						return result;
					}
				}
			}
		}

		closedir(v2);
	}
	return remove(a1);
#endif
}
bool_t DeleteDirectory(const std::string& a1, bool_t a2) {
	return recursiveDelete(a1.c_str()) == 0;
}
void ExternalFileLevelStorageSource::clearCache() {
	if(Util::endsWith(this->folderName, "_LevelCache")) {
		std::string& folderName = this->folderName;
		DeleteDirectory(std::string(folderName), 1);
		createFolderIfNotExists(folderName.c_str());
	}
}
//TODO CopyFile(const std::string&, const std::string&);

ExternalFileLevelStorageSource::ExternalFileLevelStorageSource(const std::string& a2, const std::string& a3) {
	const char* v10[3];
	v10[0] = "/games";
	v10[1] = "/com.mojang";
	v10[2] = "/minecraftWorlds";

	this->field_10 = !(a3 == a2);
	createTree(a2.c_str(), v10, 3);
	if(this->field_10) {
		createTree(a3.c_str(), v10, 3);
	}
	this->field_4 = a2 + "/games" + "/com.mojang" + "/minecraftWorlds";
	this->field_8 = a3 + "/games" + "/com.mojang" + "/minecraftWorlds";
	this->folderName = this->field_8 + "/_LevelCache";
	createFolderIfNotExists(this->folderName.c_str());
}
std::string ExternalFileLevelStorageSource::getFullPath(const std::string& a3) {
	const std::string& ret = (LevelStorageSource::TempLevelId == a3 ? this->field_8 : this->field_4);
	return ret + "/" + a3;
}
void ExternalFileLevelStorageSource::deleteLevel(const std::string& a2) {
	DeleteDirectory(this->getFullPath(a2), 1);
}
LevelStorage* ExternalFileLevelStorageSource::selectLevel(const std::string& a2, bool_t a3) {
	return new ExternalFileLevelStorage(a2, this->getFullPath(a2));
}
static std::string _D66784C8(LevelData* a2) { //inlined
	std::stringstream v10;
	v10 << a2->getSeed();
	v10 << '_';
	v10 << a2->getGeneratorVersion();
	v10 << ".cach1";
	return v10.str();
}

void ExternalFileLevelStorageSource::loadFromCache(LevelData* a2, const std::string& a3) {
	std::string filename = (std::string(this->folderName) + '/') + _D66784C8(a2);
	if(exists(filename.c_str())) {
		std::string v8 = this->getFullPath(a3) + "/chunks.dat";
		if(!compression::gzip::decompress(filename, v8)) {
			remove(filename.c_str());
			remove(v8.c_str());
		}
	}
}
void ExternalFileLevelStorageSource::storeToCache(LevelData* a2, const std::string& a3) {
	std::string v6 = this->folderName + '/' + _D66784C8(a2);
	if(!exists(v6.c_str())) {
		std::string v7 = this->getFullPath(a3);
		std::string v8 = v7 + "/chunks.dat";
		compression::gzip::compress(v8, v6, 1);
	}
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
void ExternalFileLevelStorageSource::renameLevel(const std::string& oldName, const std::string& newName)
{
	std::string fullPath = this->getFullPath(oldName);
	if(!FUNC_ACCESS(fullPath.c_str(), 0)) {
		std::string v22 = Util::stringTrim(newName);
		for(int v6 = 0; v6 != 15; ++v6) {
			//TODO
		}
		std::vector<LevelSummary> levels;
		this->getLevelList(levels);

		std::set<std::string> levelslookup;
		for(int v9 = 0; v9 < levels.size(); ++v9) {
			levelslookup.insert(levels[v9].levelName);
		}

		//TODO
	}
	printf("ExternalFileLevelStorageSource::renameLevel - not implemented\n");
}


