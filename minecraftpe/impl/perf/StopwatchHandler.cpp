#include <perf/StopwatchHandler.hpp>
#include <perf/Stopwatch.hpp>

void StopwatchHandler::clear(const std::string& a2) {
	auto&& p = this->field_0.find(a2);
	if(p != this->field_0.end()) {
		if(p->second) delete p->second;
	}
	this->field_0.erase(a2);
}
void StopwatchHandler::clearAll() {
	for(auto&& p: this->field_0) {
		if(p.second) delete p.second;
	}
	this->field_0.clear();
}
Stopwatch* StopwatchHandler::get(const std::string& a2) {
	auto&& p = this->field_0.find(a2);
	if(p != this->field_0.end()) {
		return p->second;
	}
	Stopwatch* pp = new Stopwatch();
	this->field_0.insert({a2, pp});
	return pp;
}
void StopwatchHandler::print() {
	for(auto&& p: this->field_0) {
		p.second->print(p.first);
	}
}
void StopwatchHandler::printEvery(int32_t a2) {
	int32_t v2 = this->field_18 + 1;
	if(v2 >= a2) {
		this->field_18 = 0;
		this->print();
	} else {
		this->field_18 = v2;
	}
}

StopwatchHandler::~StopwatchHandler() {
	this->clearAll();
}
