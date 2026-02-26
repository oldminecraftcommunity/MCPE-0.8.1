#include <rendering/GLBufferPool.hpp>
#include <GLES/gl.h>

GLBufferPool glBufferPool;

GLBufferPool::~GLBufferPool(){
	this->trim();
}

bool_t GLBufferPool::trim(){
	//TODO check is correct
	if(this->buffers.size() == 0){
		return 0;
	}

	for(uint32_t e : this->buffers){
		glDeleteBuffers(1, &e);
	}
	return 1;
}

void GLBufferPool::release(uint32_t n){
	uint32_t v4;

	v4 = n;
	this->buffers.push_back(v4);
	this->field_0.erase(v4);
}

GLuint GLBufferPool::get(){
	//TODO check is correct
	GLuint bf;
	glGenBuffers(1, &bf);
	if(glGetError()) return 0; //this is in loop
	this->buffers.push_front(bf);
	//this->field_0.insert(0, bf); //TODO idk what is supposed to be there

	return bf;
}
