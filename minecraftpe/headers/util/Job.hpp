#pragma once
#include <_types.h>
#include <memory>
#include <util/JobStatus.hpp>

struct ThreadCollection;
struct Job
{
	JobStatus status;

	static void addToThreadCollection(std::shared_ptr<Job>, ThreadCollection&);

	JobStatus getStatus();
	JobStatus trySetStatus(JobStatus);
	virtual ~Job();
	virtual void stop() = 0;
	virtual void run() = 0;
	virtual void finish() = 0;
};
