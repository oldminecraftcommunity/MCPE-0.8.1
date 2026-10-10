#include <util/ThreadCollection.hpp>
#include <util/Job.hpp>
#include <unistd.h>
#include <util/Worker.hpp>

static int sub_D66E4980() {
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
		int v4 = sub_D66E4980();
		if(v4) maxthreads = v4;
		else maxthreads = 1;
	}

	for(unsigned int i = 0; i != maxthreads; ++i) {
			this->threads.push_back(std::thread(Worker(*this)));
	}
}
void ThreadCollection::enqueue(std::shared_ptr<Job> a2) {
	Job* j = a2.get();
	std::unique_lock<std::mutex> v11(this->mutex, std::defer_lock);
	v11.lock();
	this->field_C.push_back(a2);
	v11.unlock();
	this->field_64.notify_one();
}
void ThreadCollection::processUIThread() {
	for(auto&& it = this->field_34.begin(); it != this->field_34.end();) {

		if(it->get()->status == JS_FINISHED) {
			it->get()->finish();
		}
		it = this->field_34.erase(it); //TODO check
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
