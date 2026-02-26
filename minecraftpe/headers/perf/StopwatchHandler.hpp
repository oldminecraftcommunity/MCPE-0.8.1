#pragma once
#include <_types.h>
#include <string>
#include <map>

struct Stopwatch;

struct StopwatchHandler
{
	std::map<std::string, Stopwatch*> field_0;
	int32_t field_18;

	void clear(const std::string&);
	void clearAll();
	Stopwatch* get(const std::string&);
	void print();
	void printEvery(int32_t);

	~StopwatchHandler();
};
