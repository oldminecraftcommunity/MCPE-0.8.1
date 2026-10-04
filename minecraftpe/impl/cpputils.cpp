#include <cpputils.hpp>
#include <sstream>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
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

long getFileSize(const char* a1){ //unused method
	FILE* v1 = fopen(a1, "rb");
	if(!v1) return -1;
	fseek(v1, 0, SEEK_END);
	long v3 = ftell(v1);
	fclose(v1);
	return v3;
}

time_t getEpochTimeS() { //TODO returns int?
	return time(0);
}

int32_t getTimeMs(){
	return (int32_t) (getTimeS() * 1000);
}


int32_t getRemainingFileSize(FILE* file){
	if(file){
		int32_t cur = ftell(file);
		fseek(file, 0, SEEK_END);
		int32_t end = ftell(file);
		fseek(file, cur, SEEK_SET);
		return end - cur;

	}
	return 0;
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
bool_t DeleteDirectory(const std::string& a1, bool_t a2) {
	return recursiveDelete(a1.c_str()) == 0;
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
bool _access(const char* a, int b){
	return access(a, b);
}
bool_t exists(const char_t* a1){
	return _access(a1, 0) == 0;
}
int FUNC_ERRNO() {
	return errno; //TODO check
}
int FUNC_MKDIR(const char* a1) {
#ifdef __WIN32__
	return mkdir(a1);
#else
	return mkdir(a1, 0755u);
#endif
}
bool createFolderIfNotExists(const char* a1){
	if ( exists(a1) || !FUNC_MKDIR(a1) )
	{
		return 1;
	}
	FUNC_ERRNO();
	return 0;
}
bool createTree(const char* a1, const char** a2, int a3) {
	if(!createFolderIfNotExists(a1)) {
		return 0;
	}
	std::string v10 = a1;
	for(int v7 = 0; v7 < a3; ++v7) {
		v10 += a2[v7];
		if(!createFolderIfNotExists(v10.c_str())) {
			return 0;
		}
	}
	return 1;
}

int getRawTimeS() {
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec;
}
