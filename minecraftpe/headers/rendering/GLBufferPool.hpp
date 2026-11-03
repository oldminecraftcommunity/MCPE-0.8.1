#pragma once
#include <_types.h>
#include <unordered_set>
#include <queue>
#include <unigl.hpp>

extern struct GLBufferPool glBufferPool;

struct GLBufferPool{
	std::unordered_set<uint32_t> usedBuffers;
	std::queue<uint32_t> unusedBuffers;
	int reserveCnt;

	GLBufferPool(unsigned int reserveCnt) {
		this->reserveCnt = reserveCnt;
	}
	GLuint get(){
		//TODO check is correct
		if(this->unusedBuffers.size() < this->reserveCnt) {
			while(this->unusedBuffers.size() < this->reserveCnt) {
				unsigned int bf;
				glGenBuffers(1, &bf);
				if(glGetError()) break;
				this->unusedBuffers.push(bf);
			}
		}

		if(this->unusedBuffers.empty()) {
			return 0;
		}

		uint32_t bf = this->unusedBuffers.front();
		this->unusedBuffers.pop();
		this->usedBuffers.insert(bf);
		return bf;
	}
	void release(uint32_t n){
		uint32_t v4;
		this->unusedBuffers.push(n);
		this->usedBuffers.erase(v4);
	}
	bool_t trim(void) {
		if(this->unusedBuffers.empty()) {
			return 0;
		}
		while(!this->unusedBuffers.empty()) {
			uint32_t n = this->unusedBuffers.front();
			glDeleteBuffers(1, &n);
			this->unusedBuffers.pop();
		}
		return 1;
	}
	~GLBufferPool(){
		this->trim();
	}
};
