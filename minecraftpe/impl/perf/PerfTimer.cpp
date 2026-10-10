#include <perf/PerfTimer.hpp>
#include <cpputils.hpp>
#include <algorithm>

std::map<std::string, float> PerfTimer::times;
std::string PerfTimer::path = "";
std::vector<double> PerfTimer::startTimes;
std::vector<std::string> PerfTimer::paths;
bool_t PerfTimer::enabled = 0;

std::vector<PerfTimer::ResultField> PerfTimer::getLog(const std::string& a2) {
	if(PerfTimer::enabled) {
		std::string v31 = a2;
		auto&& it = PerfTimer::times.find("root");
		float v7 = it == PerfTimer::times.end() ? 0 : it->second;
		auto&& it2 = PerfTimer::times.find(v31);
		float v2 = it2 != PerfTimer::times.end() ? it2->second : -1;

		std::vector<PerfTimer::ResultField> v34;
		if(v31.size()) {
			v31 += ".";
		}
		float v9 = 0;
		for(auto&& it3: PerfTimer::times) {
			if(it3.first.size() > v31.size() && Util::startsWith(it3.first, v31) && it3.first.find(".", v31.size() + 1) == -1) {
				v9 += it3.second;
			}
		}
		float v12 = v9;
		if(v9 < v2) v9 = v2;
		if(v7 < v9) v7 = v9;
		for(auto&& it3: PerfTimer::times) {
			if(it3.first.size() > v31.size() && Util::startsWith(it3.first, v31) && it3.first.find(".", v31.size() + 1) == -1) {
				float v30 = PerfTimer::times.find(it3.first)->second * 100.0f; //wonder why didnt mojang use it3.second for this </3
				std::string v33 = it3.first.substr(v31.size());
				v34.push_back(PerfTimer::ResultField(v33, v30 / v9, v30 / v7));
			}
		}
		for(auto&& it3: PerfTimer::times) {
			it3.second *= 0.999f;
		}
		if(v9 > v12) {
			v34.push_back(PerfTimer::ResultField("unspecified", ((v9 - v12) * 100.0f) / v9, ((v9 - v12) * 100.0f) / v7));
		}
		std::sort(v34.begin(), v34.end()); //TODO check
		v34.insert(v34.begin(), PerfTimer::ResultField(a2, 100, (v9*100)/v7));
		return std::vector<PerfTimer::ResultField>(std::move(v34));
	} else {
		return {};
	}

}
void PerfTimer::pop() {
	if(PerfTimer::enabled) {
		double time = getTimeS();
		float v3 = time - PerfTimer::startTimes.back();
		PerfTimer::paths.pop_back();
		PerfTimer::startTimes.pop_back();
		auto&& v = PerfTimer::times.find(PerfTimer::path);
		if(v == PerfTimer::times.end()) {
			PerfTimer::times.insert(std::pair<std::string, float>(PerfTimer::path, v3));
		} else {
			v->second += v3;
		}

		std::string v7 = PerfTimer::paths.size() ? PerfTimer::paths.end()[-1] : ""; //i luv dis if it works
		PerfTimer::path = v7;
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
		PerfTimer::paths.push_back(PerfTimer::path);
		PerfTimer::startTimes.push_back(getTimeS());
	}

}
void PerfTimer::reset() {
	PerfTimer::times.clear();
}
