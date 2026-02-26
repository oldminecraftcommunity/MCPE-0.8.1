#include <perf/PerfTimer.hpp>
#include <util/Util.hpp>
#include <utils.h>


std::map<std::string, float> PerfTimer::times;
std::string PerfTimer::path = "";
std::vector<double> PerfTimer::startTimes;
std::vector<std::string> PerfTimer::paths;
bool_t PerfTimer::enabled = 0;

PerfTimer::ResultField::ResultField(PerfTimer::ResultField&& a2) {
	this->field_0 = a2.field_0;
	this->field_8 = a2.field_8;
	a2.field_8 = "";
}
int32_t PerfTimer::ResultField::getColor() {
	return (Util::hashCode(this->field_8) & 0xAAAAAA) + 4473924;
}
bool_t PerfTimer::ResultField::operator<(const PerfTimer::ResultField& a2) {
	if(this->field_0 == a2.field_0) {
		return this->field_8.compare(a2.field_8);
	}
	return this->field_0 > a2.field_0;
}
PerfTimer::ResultField& PerfTimer::ResultField::operator=(ResultField&& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	return *this;
}
PerfTimer::ResultField::~ResultField() {
}

std::vector<PerfTimer::ResultField> PerfTimer::getLog(const std::string&) {
	printf("PerfTimer::getLog - not implemented\n"); //TODO PerfTimer::getLog
	return {};
}
void PerfTimer::pop() {
	if(PerfTimer::enabled) {
		printf("PerfTimer::pop - not implemented\n"); //TODO PerfTimer::pop
	}
}
void PerfTimer::popPush(const std::string& a1) {
	PerfTimer::pop();
	PerfTimer::push(a1);
}
void PerfTimer::push(const std::string& a2) {
	if(PerfTimer::enabled) {
		if(PerfTimer::path.size()) {
			PerfTimer::path += ".";
		}
		PerfTimer::path += a2;
		PerfTimer::paths.emplace_back(PerfTimer::path);
		double timeS = getTimeS();
		PerfTimer::startTimes.emplace_back(timeS);
	}

}
void PerfTimer::reset() {
	PerfTimer::times.clear();
}
