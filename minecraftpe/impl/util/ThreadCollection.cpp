#include <util/ThreadCollection.hpp>
#include <stdio.h>
#include <util/Job.hpp>

ThreadCollection::ThreadCollection(uint32_t) {
	printf("ThreadCollection::ThreadCollection - not implemented\n");
}
void ThreadCollection::enqueue(std::shared_ptr<Job>) {
	printf("ThreadCollection::enqueue - not implemented\n");
}
void ThreadCollection::processUIThread() {
	for(auto&& it = this->field_34.begin(); it != this->field_34.end();) {

		if(it->get()->status == JS_3) {
			it->get()->finish();
		}
		it = this->field_34.erase(it); //TODO check
	}
}
ThreadCollection::~ThreadCollection() {
	printf("ThreadCollection::~ThreadCollection - not implemented\n");
}
