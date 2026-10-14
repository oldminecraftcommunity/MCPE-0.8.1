#include <util/CMutex.hpp>

CMutex::CMutex(){
	pthread_mutex_init(&this->mutex, 0);
}

CMutex::~CMutex(){
	pthread_mutex_destroy(&this->mutex);
}

void CMutex::lock(){
	pthread_mutex_lock(&this->mutex);
}

void CMutex::unlock(){
	pthread_mutex_unlock(&this->mutex);
}
