#include <util/Worker.hpp>

Worker::Worker(ThreadCollection& a2) {
	this->field_0 = &a2;
}
void Worker::operator()(void);
