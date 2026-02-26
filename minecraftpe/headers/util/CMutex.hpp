#pragma once
#include <pthread.h>
struct CMutex{
	pthread_mutex_t mutex;

	CMutex();
	void lock();
	void unlock();
	~CMutex();
};
