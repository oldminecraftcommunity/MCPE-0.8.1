#pragma once
#include <_types.h>
#include <string>
#include <vector>
#include <map>

struct PerfTimer
{
	struct ResultField
	{
		float field_0;
		int32_t field_4;
		std::string field_8;

		ResultField(PerfTimer::ResultField&&);
		int32_t getColor();
		bool_t operator<(const PerfTimer::ResultField&);
		ResultField& operator=(ResultField&&);
		~ResultField();
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
