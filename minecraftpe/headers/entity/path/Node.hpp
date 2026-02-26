#pragma once
#include <_types.h>

struct Node
{
	int32_t xCoord, yCoord, zCoord;
	int32_t nodeHash;
	int32_t nodePositionInHeapMaybe;
	float field_14;
	float field_18;
	float nodeCost;
	Node* field_20;
	int8_t field_24, field_25, field_26, field_27;

	Node(int32_t, int32_t, int32_t);
	void _init();
	static uint32_t createHash(int32_t, int32_t, int32_t);
	float distanceTo(Node*);
	bool_t equals(Node*);
	int32_t hashCode();
	bool_t inOpenSet();

};
