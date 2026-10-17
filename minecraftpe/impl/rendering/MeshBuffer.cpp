#include <rendering/MeshBuffer.hpp>
#include <rendering/GLBufferPool.hpp>
#include <string.h>
#include <unigl.hpp>

MeshBuffer::MeshBuffer(void){
	this->transformX = 0;
	this->transformY = 0;
	this->transformZ = 0;
	memset(this, 0, sizeof(MeshBuffer));
}

MeshBuffer::MeshBuffer(MeshBuffer&& o) : MeshBuffer(){
	this->_move(o);
}

MeshBuffer::MeshBuffer(const MeshBuffer::VertexFormat* a2, void* a3, int32_t a4, void* a5, uint32_t a6, int32_t a7, uint32_t a8){
	this->arrayBuffer = 0;
	this->arrayElementsBuffer = 0;
	this->arraysCount = 0;
	this->elementsCount = 0;
	this->drawMode = 0;
	this->transformX = 0;
	this->transformY = 0;
	this->transformZ = 0;
	this->load(a2, a3, a4, a5, a6, a7, a8);
}

bool_t MeshBuffer::_load(const MeshBuffer::VertexFormat* a2, void* a3, int32_t a4, void* a5, uint32_t a6, int32_t a7, uint32_t a8){
	GLenum v11;
	int32_t v12;

	if(!a3 || a4 <= 2 || !a8 || !a2) return 0;
	this->arraysCount = a4;
	this->drawMode = a8;
	this->elementsCount = a6;
	v11 = GL_UNSIGNED_SHORT;
	this->vertexFormat = a2;
	if(a7 != 2) v11 = GL_UNSIGNED_BYTE;
	this->drawType = v11;
	v12 = a2->stride * a4;
	if(!this->arrayBuffer){
		this->arrayBuffer = glBufferPool.get();
		if(this->arrayBuffer == 0) return 0;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->arrayBuffer);
	glBufferData(GL_ARRAY_BUFFER, v12, a3, GL_STATIC_DRAW);
	if(this->elementsCount && a7 && a5){
		if(!this->arrayElementsBuffer){
			this->arrayElementsBuffer = glBufferPool.get();
			if(!this->arrayElementsBuffer) return 0;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->arrayElementsBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->elementsCount*a7, a5, GL_STATIC_DRAW);
	}else{
		if(this->arrayElementsBuffer) glBufferPool.release(this->arrayElementsBuffer);
		this->arrayElementsBuffer = 0;
	}

	return glGetError() == 0;
}

void MeshBuffer::_move(MeshBuffer& a2){
	this->reset();
	this->arrayBuffer = a2.arrayBuffer;
	this->arraysCount = a2.arraysCount;
	this->vertexFormat = a2.vertexFormat;
	this->arrayElementsBuffer = a2.arrayElementsBuffer;
	this->elementsCount = a2.elementsCount;
	this->drawType = a2.drawType;
	this->drawMode = a2.drawMode;
	a2.arrayElementsBuffer = 0;
	a2.arrayBuffer = 0;
	a2.elementsCount = 0;
	a2.arraysCount = 0;
	a2.vertexFormat = 0;
}

MeshBuffer& MeshBuffer::operator=(MeshBuffer&& a2){
	this->_move(a2);
	return *this;
}

void MeshBuffer::render(){
	if(this->arrayBuffer && this->arraysCount > 3 && this->drawMode && this->vertexFormat){
		glBindBuffer(GL_ARRAY_BUFFER, this->arrayBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->arrayElementsBuffer);
		this->vertexFormat->bindArrays();
		if(this->elementsCount){
			glDrawElements(this->drawMode, this->elementsCount, this->drawType, 0);
		}else{
			glDrawArrays(this->drawMode, 0, this->arraysCount);
		}
	}
}

bool_t MeshBuffer::load(const MeshBuffer::VertexFormat* a2, void* a3, int32_t a4, void* a5, uint32_t a6, int32_t a7, uint32_t a8){
	if(this->_load(a2, a3, a4, a5, a6, a7, a8)){
		return 1;
	}
	this->reset();
	return 0;
}

void MeshBuffer::reset(){
	if(this->arrayBuffer) glBufferPool.release(this->arrayBuffer);
	if(this->arrayElementsBuffer) glBufferPool.release(this->arrayElementsBuffer);

	this->arrayBuffer = 0;
	this->arraysCount = 0;
	this->arrayElementsBuffer = 0;
	this->elementsCount = 0;
	this->drawMode = 0;
	this->drawType = 0;
	this->vertexFormat = 0;
}

MeshBuffer::~MeshBuffer(){
  this->reset();
}

void MeshBuffer::VertexFormat::bindArrays() const{
	glVertexPointer(3, GL_FLOAT, this->stride, (void*) this->offsets[0]);
	uint8_t texOffset = this->offsets[1];
	if(texOffset != 255) glTexCoordPointer(2, GL_FLOAT, this->stride, (void*) texOffset);
	uint8_t colOffset = this->offsets[2];
	if(colOffset != 255) glColorPointer(4, GL_UNSIGNED_BYTE, this->stride, (void*) colOffset);
	uint8_t normOffset = this->offsets[3];
	if(normOffset != 255) glNormalPointer(GL_BYTE, this->stride, (void*) normOffset);
}


