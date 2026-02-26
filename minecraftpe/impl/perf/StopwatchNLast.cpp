#include <perf/StopwatchNLast.hpp>
#include <string.h>

StopwatchNLast::StopwatchNLast(int32_t a2) {
	this->size = a2;
	this->field_34 = 0;
	this->field_40 = 0;
	this->field_38 = new double[this->size];
	memset(this->field_38, 0, this->size * 8);
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
void StopwatchNLast::print(const std::string&) {
	this->getMax();
}
