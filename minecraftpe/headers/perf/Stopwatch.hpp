#pragma once
#include <_types.h>
#include <string>

struct Stopwatch
{
	int32_t field_4;
	double startTime, total;
	double lastDiffTime, maxDiffTime;
	int32_t count, field_28;

	Stopwatch();
	int32_t getCount();
	double getLast();
	double getMax();
	double getTotal();
	void printEvery(int32_t, const std::string&);
	void reset();
	void start();

	virtual ~Stopwatch();
	virtual void stop();
	virtual double stopContinue();
	virtual void print(const std::string&);

};
