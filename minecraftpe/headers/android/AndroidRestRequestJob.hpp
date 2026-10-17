#pragma once
#ifdef ANDROID
#include <network/mco/RestRequestJob.hpp>
#include <android/AppPlatform_android.hpp>
#include <mutex>
#include <condition_variable>

struct AndroidRestRequestJob: RestRequestJob
{
	int field_58, field_5C;
	std::condition_variable field_60;
	std::mutex field_64; //maybe waitForAnswerMutex?
	std::mutex mutex;
	int field_6C;
	int httpStatusOrNegativeError;
	std::string content;
	AppPlatform_android* platform;
	bool started;

	AndroidRestRequestJob(Minecraft*);
	void onRequestComplete(int, int, const std::string&);
	bool isRunning();

	virtual ~AndroidRestRequestJob();
	virtual void stop();
	virtual void run();
	virtual void finish();
};
#endif
