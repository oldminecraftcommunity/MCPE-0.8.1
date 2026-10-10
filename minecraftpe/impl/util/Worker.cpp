#include <util/Worker.hpp>
#include <util/ThreadCollection.hpp>
#include <util/Job.hpp>

Worker::Worker(ThreadCollection& a2) {
	this->threadCollection = &a2;
}
void Worker::operator()(void) {

	while(1) {
		if(this->threadCollection->isStopped) {
			break;
		}

		if(!this->threadCollection->field_C.empty()) {
			std::shared_ptr<Job> el;
			{
				std::unique_lock<std::mutex> v24(this->threadCollection->mutex, std::defer_lock);
				v24.lock();
				el = this->threadCollection->field_C.front();
				this->threadCollection->field_C.pop_front(); //TODO check;
			}
			if(el.get()) {
				el->run();
				if(el->getStatus() == JS_FINISHED) {
					std::unique_lock<std::mutex> v24(this->threadCollection->field_60, std::defer_lock);
					v24.lock();
					this->threadCollection->field_34.push_back(std::shared_ptr<Job>(el));
				}
			}
			continue;
		}

		std::unique_lock<std::mutex> mut(this->threadCollection->mutex, std::defer_lock);
		mut.lock();
		this->threadCollection->field_64.wait(mut);
	}
}
