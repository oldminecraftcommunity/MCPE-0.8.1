#ifndef UTILS_H
#define UTILS_H
#include <_types.h>
#include <sys/time.h>
#include <stdio.h>
#define vcvts_n_f32_s32(a2, a3) (float)((float)(a2) / (1 << (uint32_t)(a3)))

extern time_t startedAtSec;
#ifdef __cplusplus
extern "C" {
	double getTimeS();
	time_t getEpochTimeS();
	int32_t getTimeMs();
	int32_t getRemainingFileSize(FILE* file);
	void sleepMs(int32_t);
}
#endif

#endif // UTILS_H
