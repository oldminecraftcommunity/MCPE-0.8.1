#include <perf/Stopwatch.hpp>
#include <utils.h>

Stopwatch::Stopwatch() {
	this->count = 0;
	this->field_28 = 0;
	this->reset();
}
int32_t Stopwatch::getCount() {
	return this->count;
}
double Stopwatch::getLast() {
	return this->lastDiffTime;
}
double Stopwatch::getMax() {
	return this->maxDiffTime;
}
double Stopwatch::getTotal() {
	return this->total;
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
void Stopwatch::reset() {
	this->startTime = -1.0;
	this->total = 0.0;
	this->maxDiffTime = 0.0;
}
void Stopwatch::start() {
	this->startTime = getTimeS();
}
Stopwatch::~Stopwatch() {
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
