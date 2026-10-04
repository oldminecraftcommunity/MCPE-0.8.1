#pragma once
#include <_types.h>

struct MeshBuffer{
	struct VertexFormat{
		enum Field{
			FIELD0,
			FIELD1,
			FIELD2,
			FIELD3
		};

		uint8_t offsets[4];
		uint8_t stride;

		VertexFormat(void){
			this->stride = 0;
			for(auto&& p : this->offsets) p = -1;
		}
		void bindArrays(void) const;
		void enableField(MeshBuffer::VertexFormat::Field f){
			static int32_t FieldSize[] = {0xC, 0x8, 0x4, 0x4};
			if(this->offsets[f] == 255){
				this->offsets[f] = stride;
				this->stride += FieldSize[f];
			}
		}
	};
	int32_t arrayBuffer;
	int32_t arrayElementsBuffer;
	int32_t arraysCount;
	int32_t elementsCount;
	float transformX, transformY, transformZ;
	int32_t drawMode, drawType;
	const MeshBuffer::VertexFormat* vertexFormat;


	MeshBuffer(MeshBuffer&&);
	MeshBuffer(const MeshBuffer::VertexFormat*, void*, int32_t, void*, uint32_t, int32_t, uint32_t);
	MeshBuffer(void);
	bool_t _load(const MeshBuffer::VertexFormat*, void*, int32_t, void*, uint32_t, int32_t, uint32_t);
	void _move(MeshBuffer&);
	bool_t isValid() const{
		if(this->arrayBuffer){
			if(this->arraysCount <= 3) return 0;
			if(this->drawMode){
				return this->vertexFormat != 0;
			}
		}
		return 0;
	}
	bool_t load(const MeshBuffer::VertexFormat*, void*, int32_t, void*, uint32_t, int32_t, uint32_t);
	MeshBuffer& operator=(MeshBuffer&&);
	void render(void);
	void reset(void);
	~MeshBuffer();
};
