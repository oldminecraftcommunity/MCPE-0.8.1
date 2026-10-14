#include <cpputils.hpp>
#include <sstream>
#include <dirent.h>
#include <string.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
inline time_t _startedAt(){
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec;
}
static time_t startedAtSec = _startedAt(); //XXX mojang does it somehow else probably

double getTimeS(){
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec - startedAtSec + (double)v1.tv_usec / 1000000.0;
}


time_t getEpochTimeS() { //TODO returns int?
	return time(0);
}

int32_t getTimeMs(){
	return (int32_t) (getTimeS() * 1000);
}




void sleepMs(int32_t a1) {
	usleep(1000 * a1);
}

void splitString(const std::string& a1, char_t a2, std::vector<std::string>& a3) {
	std::stringstream v9(a1);
	for(std::string v7; std::getline(v9, v7, a2);) {
		a3.push_back(v7);
	}
}

// TODO move to ExternalFileLevelStorageSource<?>

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

//TODO CopyFile

//move end


int getRawTimeS() {
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec;
}
