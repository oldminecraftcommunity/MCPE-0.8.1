#pragma once
#include <_types.h>
#include <unordered_map>
#include <deque>
#include <GL/gl.h>

extern struct GLBufferPool glBufferPool;

struct GLBufferPool{
	std::unordered_map<uint32_t, uint32_t> field_0; //XXX std::_Hashtable, idk what is it
	std::deque<uint32_t> buffers;

	GLuint get(void);
	void release(uint32_t);
	bool_t trim(void);
	~GLBufferPool();
};
