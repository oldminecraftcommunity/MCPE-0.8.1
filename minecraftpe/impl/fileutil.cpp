#include <fileutil.hpp>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

#ifdef __WIN32__
#define FUNC_ACCESS _access2
#else
#define FUNC_ACCESS _access
#endif

int FUNC_MKDIR(const char* a1) {
#ifdef __WIN32__
	return mkdir(a1);
#else
	return mkdir(a1, 0755u);
#endif
}

int FUNC_ACCESS(const char* a, int b){
	return access(a, b);
}
int FUNC_ERRNO() {
	return errno; //TODO check
}
bool exists(const char* a1){
	return FUNC_ACCESS(a1, 0) == 0;
}
bool createFolderIfNotExists(const char* a1){
	if ( exists(a1) || !FUNC_MKDIR(a1) )
	{
		return 1;
	}
	FUNC_ERRNO();
	return 0;
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

long getFileSize(const char* a1){ //unused method
	FILE* v1 = fopen(a1, "rb");
	if(!v1) return -1;
	fseek(v1, 0, SEEK_END);
	long v3 = ftell(v1);
	fclose(v1);
	return v3;
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
