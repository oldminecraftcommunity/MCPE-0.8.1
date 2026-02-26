#include <Timer.hpp>
#include <utils.h>

void Timer::advanceTime(){
	int32_t nowMs = getTimeMs();
	int32_t passedMs = nowMs - this->lastMs;
	if(passedMs <= 1000){
		if(passedMs >= 0) goto LABEL_7;
	}else{
		int32_t v4 = nowMs - this->lastMsSysTime;
		if(!v4){
			v4 = 1;
			passedMs = 1;
		}
		this->adjustTime += ((((float)passedMs / (float)v4) - this->adjustTime) * 0.2);
	}
	this->lastMs = nowMs;
	this->lastMsSysTime = nowMs;
	LABEL_7:
	float adjustTime = this->adjustTime;
	float v6 = (float)nowMs / 1000;
	float v7 = v6 - this->lastTime;
	this->lastTime = v6;
	float passedSeconds = v7*adjustTime;
	if(passedSeconds < 0) passedSeconds = 0;
	else if(passedSeconds > 1) passedSeconds = 1;
	float v9 = this->passedTime + ((float)(passedSeconds*this->timeScale) * this->ticksPerSecond);
	int32_t v10 = (int32_t)v9;
	this->ticks = (int32_t)v9;
	float v11 = v9 - (float)(int32_t)v9;
	this->passedTime = v11;
	this->field_8 = v11;
	if(v10 > 10) this->ticks = 10;
}
