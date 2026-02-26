#pragma once
#include <_types.h>
#include <deque>
#include <vector>
#include <mutex>
#include <thread>
#include <memory>

struct Job;
struct ThreadCollection
{
	std::vector<std::thread> threads;
	std::deque<std::shared_ptr<Job>> field_C;
	std::deque<std::shared_ptr<Job>> field_34;
	std::mutex mutex; //TODO check is this actually mutex

	ThreadCollection(uint32_t);
	void enqueue(std::shared_ptr<Job>);
	void processUIThread();
	~ThreadCollection();
};
