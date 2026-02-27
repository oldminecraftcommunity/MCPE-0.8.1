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
		char align, align1, align2; //TODO this struct is not aligned?

		VertexFormat(void);
		void bindArrays(void) const;
		void enableField(MeshBuffer::VertexFormat::Field);
	};
	int32_t arrayBuffer;
	int32_t arrayElementsBuffer;
	int32_t arraysCount;
	int32_t elementsCount;
	float transformX, transformY, transformZ;
	int32_t drawMode, drawType;
	const MeshBuffer::VertexFormat* vertexFormat;


	MeshBuffer(MeshBuffer&&);
	MeshBuffer(const MeshBuffer::VertexFormat*, void*, int32_t, void*, uint32_t, uint32_t, uint32_t);
	MeshBuffer(void);
	bool_t _load(const MeshBuffer::VertexFormat*, void*, int32_t, void*, uint32_t, uint32_t, uint32_t);
	void _move(MeshBuffer&);
	bool_t isValid(void);
	bool_t load(const MeshBuffer::VertexFormat*, void*, int32_t, void*, uint32_t, uint32_t, uint32_t);
	MeshBuffer& operator=(MeshBuffer&&);
	void render(void);
	void reset(void);
	~MeshBuffer();
};
