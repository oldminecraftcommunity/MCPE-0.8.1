#include <perf/Stopwatch.hpp>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

inline time_t _startedAt(){
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec;
}
static time_t startedAtSec = _startedAt(); //XXX mojang does it somehow else probably

int getRawTimeS() {
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec;
}

double getTimeS(){
	struct timeval v1;
	gettimeofday(&v1, 0);
	return v1.tv_sec - startedAtSec + (double)v1.tv_usec / 1000000.0;
}

int32_t getTimeMs(){
	return (int32_t) (getTimeS() * 1000);
}

void sleepMs(int32_t a1) {
	usleep(1000 * a1);
}

time_t getEpochTimeS() {
	return time(0);
}
void Stopwatch::start() {
	this->startTime = getTimeS();
}
double Stopwatch::getLast() {
	return this->lastDiffTime;
}
double Stopwatch::getTotal() {
	return this->total;
}
double Stopwatch::getMax() {
	return this->maxDiffTime;
}
void StopwatchNLast::print(const std::string&) {
	this->getMax();
}
int32_t Stopwatch::getCount() {
	return this->count;
}
void Stopwatch::reset() {
	this->startTime = -1.0;
	this->total = 0.0;
	this->maxDiffTime = 0.0;
}
Stopwatch::Stopwatch() {
	this->count = 0;
	this->field_28 = 0;
	this->reset();
}
StopwatchNLast::StopwatchNLast(int32_t a2) {
	this->size = a2;
	this->field_34 = 0;
	this->field_40 = 0;
	this->field_38 = new double[this->size];
	memset(this->field_38, 0, this->size * 8);
}

void Stopwatch::printEvery(int32_t a2, const std::string& a3) {
	int32_t v3; // r4

	v3 = this->field_28 + 1;
	if(v3 >= a2) {
		this->field_28 = 0;
		this->print(a3);
	} else {
		this->field_28 = v3;
	}
}

void Stopwatch::stop() {
	double diffTime;	   // d7
	double maxDiffTime; // d6
	double v4;		   // d7
	int32_t count;	   // r3

	if(this->startTime != -1.0) {
		diffTime = getTimeS() - this->startTime;
		maxDiffTime = this->maxDiffTime;
		this->lastDiffTime = diffTime;
		if(diffTime > maxDiffTime) {
			this->maxDiffTime = diffTime;
		}
		v4 = diffTime + this->total;
		count = this->count;
		this->startTime = -1.0;
		this->count = count + 1;
		this->total = v4;
	}
}
double Stopwatch::stopContinue() {
	double TimeS;	   // r0
	double v3;		   // d7
	double maxDiffTime; // d5
	double v5;		   // d7
	int32_t count;	   // r3

	if(this->startTime != -1.0) {
		TimeS = getTimeS();
		v3 = TimeS - this->startTime;
		maxDiffTime = this->maxDiffTime;
		this->lastDiffTime = v3;
		if(v3 > maxDiffTime) {
			this->maxDiffTime = v3;
		}
		v5 = v3 + this->total;
		count = this->count;
		this->startTime = TimeS;
		this->count = count + 1;
		this->total = v5;
		return v5;
	}
	return 0;
}
void Stopwatch::print(const std::string&) {
}


StopwatchNLast::~StopwatchNLast() {
	if(this->field_38) delete[] this->field_38;
}
void StopwatchNLast::stop() {
	Stopwatch::stop();
	double last = this->getLast();
	int32_t v3 = this->field_34;
	double v6 = this->field_38[v3];
	this->field_34 = ++v3;
	if(v3 == this->size) {
		this->field_34 = 0;
	}
	this->field_38[this->field_34] = last;
	this->field_40 = this->field_40 + last - v6;
}
