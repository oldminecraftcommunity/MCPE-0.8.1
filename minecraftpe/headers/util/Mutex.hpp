#pragma once
#include <pthread.h>

//TODO check
struct Mutex{
	pthread_mutex_t mutex;

	Mutex();
	~Mutex();
};
