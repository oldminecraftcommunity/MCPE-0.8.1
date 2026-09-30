#pragma once
#include <util/Util.hpp>
#include <string>
#include <vector>
#include <map>

struct PerfTimer
{
	struct ResultField
	{
		float field_0;
		float field_4;
		std::string sectionName;

		ResultField(PerfTimer::ResultField&& a2) = default;
		ResultField(const PerfTimer::ResultField& a2) = default;
		ResultField(const std::string& c, float a, float b) : field_0(a), field_4(b), sectionName(c){

		}
		int32_t getColor() const {
			return (Util::hashCode(this->sectionName) & 0xAAAAAA) + 4473924;
		}
		bool_t operator <(const PerfTimer::ResultField& a2) const {
			if (this->field_0 == a2.field_0) {
				return this->sectionName.compare(a2.sectionName);
			}
			return this->field_0 > a2.field_0;
		}

		PerfTimer::ResultField& operator=(PerfTimer::ResultField&& a2) {
			this->field_0 = a2.field_0;
			this->field_4 = a2.field_4;
			this->sectionName = a2.sectionName;
			return *this;
		}
		~ResultField() {
		}
	};

	static std::map<std::string, float> times;
	static std::string path;
	static std::vector<double> startTimes;
	static std::vector<std::string> paths;
	static bool_t enabled;


	static std::vector<PerfTimer::ResultField> getLog(const std::string&);
	static void pop();
	static void popPush(const std::string&);
	static void push(const std::string&);
	static void reset();
};
