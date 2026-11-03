#pragma once
#include <_types.h>
#include <string>

int getRawTimeS();
double getTimeS();
int32_t getTimeMs();
void sleepMs(int32_t a1);
time_t getEpochTimeS();

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

	virtual ~Stopwatch() {
	}
	virtual void stop();
	virtual double stopContinue();
	virtual void print(const std::string&);
};

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
