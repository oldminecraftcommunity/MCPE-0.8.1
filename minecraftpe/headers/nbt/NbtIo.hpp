#pragma once
#include <_types.h>

struct Tag;
struct IDataInput;

struct NbtIo{
	static Tag* read(IDataInput*);
};
