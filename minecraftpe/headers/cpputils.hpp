#pragma once
#include <_types.h>
#include <Config.hpp>
#include <vector>
#include <string>
#include <memory>
#include <network/mco/RestRequestJob.hpp>

#define vcvts_n_f32_s32(a2, a3) (float)((float)(a2) / (1 << (uint32_t)(a3)))

struct RestRequestJob;
struct Minecraft;

double getTimeS();
time_t getEpochTimeS();
int32_t getTimeMs();
void sleepMs(int32_t a1);

template <typename T> void safeRemove(T*& p){
	if(p){
		delete p;
		p = 0;
	}
}

template <typename T> void safeStopAndRemove(T&);

template <>
inline void safeStopAndRemove(std::shared_ptr<RestRequestJob>& a2) {
	if(a2.get()) {
		a2->stop();
		a2 = std::shared_ptr<RestRequestJob>(); //TODO check
	}
}

void splitString(const std::string&, char_t, std::vector<std::string>&);
int recursiveDelete(const char_t*);
bool_t DeleteDirectory(const std::string& a1, bool_t);
int getRawTimeS();
