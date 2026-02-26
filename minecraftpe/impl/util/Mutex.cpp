#include <util/Mutex.hpp>

Mutex::Mutex() {
	pthread_mutex_init(&this->mutex, 0);
}
Mutex::~Mutex() {
	pthread_mutex_destroy(&this->mutex);
}
