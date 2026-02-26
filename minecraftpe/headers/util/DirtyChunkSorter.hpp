#pragma once
#include <_types.h>

struct RenderChunk;
struct Entity;

struct DirtyChunkSorter
{
	const Entity* entity;

	bool_t operator()(RenderChunk*, RenderChunk*);
};
