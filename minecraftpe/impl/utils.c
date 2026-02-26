#include <utils.h>
#include <_types.h>
#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

time_t startedAtSec = 0; //XXX mojang does it somehow else probably

double getTimeS(){
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec - startedAtSec + (double)v1.tv_usec / 1000000.0;

}

time_t getEpochTimeS() {
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
