#pragma once
#include <_types.h>

struct ThreadCollection;
struct Worker
{
	ThreadCollection* field_0;

	Worker(ThreadCollection&);
	void operator()(void);
};
