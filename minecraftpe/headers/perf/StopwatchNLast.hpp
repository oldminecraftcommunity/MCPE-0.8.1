#pragma once
#include <perf/Stopwatch.hpp>

struct StopwatchNLast: Stopwatch
{
	int32_t size;
	int32_t field_34;
	double* field_38;
	int32_t field_3C;
	double field_40;
	Stopwatch field_48;

	StopwatchNLast(int32_t);

	virtual ~StopwatchNLast();
	virtual void stop();
	virtual void print(const std::string&);
};
