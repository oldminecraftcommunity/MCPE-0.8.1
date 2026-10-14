#include <util/CThread.hpp>
#include <unistd.h>

CThread::CThread(void* (*func)(void*), void* args) {
	this->function = func;
#ifdef EVILOREOBROKEPTHREADS
	pthread_mutex_init(&this->lock, 0);
	pthread_mutex_lock(&this->lock);
#endif

	pthread_attr_init(&this->field_C);
	pthread_attr_setdetachstate(&this->field_C, 1);
	pthread_create(&this->field_8, &this->field_C, this->function, args);
}
int32_t CThread::sleep(uint32_t a2) {
	return usleep(1000 * a2);
}
int32_t CThread::join() {
	return pthread_join(this->field_8, 0);
}

CThread::~CThread() {
#ifdef EVILOREOBROKEPTHREADS
	pthread_mutex_unlock(&this->lock);
#endif
	pthread_join(this->field_8, 0);
	pthread_attr_destroy(&this->field_C);
#ifdef EVILOREOBROKEPTHREADS
	pthread_mutex_destroy(&this->lock);
#endif
}
