#pragma once
#include <util/IntPair.hpp>

struct _ChunkSorter
{
	IntPair pair;

	bool_t operator()(const IntPair&, const IntPair&) const;
};
