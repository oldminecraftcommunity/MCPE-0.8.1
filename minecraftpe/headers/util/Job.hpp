#pragma once
#include <_types.h>
#include <memory>
#include <util/JobStatus.hpp>

struct ThreadCollection;
struct RestRequestJob;
struct Job
{
	JobStatus status;
	int32_t field_4;

	static void addToThreadCollection(std::shared_ptr<Job>, ThreadCollection&);
	Job() : field_4(0){

	}
	JobStatus getStatus();
	JobStatus trySetStatus(JobStatus);
	virtual ~Job() {
	}
	virtual void stop() = 0;
	virtual void run() = 0;
	virtual void finish() = 0;
};
