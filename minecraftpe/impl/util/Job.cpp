#include <util/Job.hpp>
#include <util/ThreadCollection.hpp>


JobStatus Job::getStatus() {
	return this->status;
}

void Job::addToThreadCollection(std::shared_ptr<Job> a1, ThreadCollection& a2) {
	a2.enqueue(a1);
}

JobStatus Job::trySetStatus(JobStatus a2) {
	if(this->status != JS_STOPPED) {
		this->status = a2;
	}
	return this->status;
}
