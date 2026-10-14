#include <util/ThreadCollection.hpp>
#include <util/Job.hpp>
#include <unistd.h>
#include <util/Worker.hpp>

void ThreadCollection::processUIThread() {
	std::unique_lock<std::mutex> lock;
	while(1) {
		if(this->field_34.empty()) break;
		auto&& it = this->field_34.front();

		if(it->status == JS_FINISHED) {
			it->finish();
		}
		this->field_34.pop_front();
	}
}

ThreadCollection::~ThreadCollection() {
	std::unique_lock<std::mutex>(this->mutex, std::defer_lock).lock();
	std::unique_lock<std::mutex>(this->field_60, std::defer_lock).lock();
	this->isStopped = 1;
	this->field_64.notify_all();

	for(auto&& t: this->threads) {
		t.join();
	}
	this->threads.clear();
}

static int _maxThreadCnt() {
#ifdef __WIN32__
	return 2; //TODO get max threads cnt
#else
	int v0; // r0
	v0 = sysconf(97);
	return v0 < 0 ? 0 : v0;
#endif
}
ThreadCollection::ThreadCollection(uint32_t maxthreads) {

	this->isStopped = 0;
	if(maxthreads == 0) {
		int v4 = _maxThreadCnt();
		maxthreads = v4 ? v4 : 1;
	}

	for(unsigned int i = 0; i != maxthreads; ++i) {
			this->threads.push_back(std::thread(Worker(*this)));
	}
}
void ThreadCollection::enqueue(std::shared_ptr<Job> a2) {
	Job* j = a2.get();
	{
		std::unique_lock<std::mutex> v11(this->mutex, std::defer_lock);
		v11.lock();
		this->field_C.push_back(a2);
	}
	this->field_64.notify_one();
}
