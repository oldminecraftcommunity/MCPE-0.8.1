#include <entity/path/Node.hpp>
#include <math.h>

Node::Node(int32_t x, int32_t y, int32_t z) {
	this->xCoord = x;
	this->yCoord = y;
	this->zCoord = z;
	this->nodeHash = Node::createHash(x, y, z);
	this->_init();
}
void Node::_init() {
	this->nodePositionInHeapMaybe = -1;
	this->field_24 = 0;
	this->field_20 = 0;
}
uint32_t Node::createHash(int32_t x, int32_t y, int32_t z) {
	int32_t v3;	 // r3
	uint32_t v4; // r0
	int32_t v5;	 // r3
	int32_t v6;	 // r2

	v3 = x & 0x7FFF;
	v4 = x & 0x80000000;
	v5 = (uint8_t)y | (v3 << 8) | (z << 24);
	if(z >= 0) {
		v6 = 0;
	} else {
		v6 = 0x8000;
	}
	return v4 | v5 | v6;
}
float Node::distanceTo(Node* a2) {
	float v2; // s15
	float v3; // s14

	v2 = (float)(a2->yCoord - this->yCoord);
	v3 = (float)(a2->zCoord - this->zCoord);
	return sqrt((float)((float)((float)(v2 * v2) + (float)((float)(a2->xCoord - this->xCoord) * (float)(a2->xCoord - this->xCoord))) + (float)(v3 * v3)));
}
bool_t Node::equals(Node* a2) {
	if(this->nodeHash == a2->nodeHash && this->xCoord == a2->xCoord && this->yCoord == a2->yCoord) {
		return this->zCoord - a2->zCoord + (this->zCoord == a2->zCoord) + a2->zCoord - this->zCoord;
	} else {
		return 0;
	}
}
int32_t Node::hashCode() {
	return this->nodeHash;
}
bool_t Node::inOpenSet() {
	return this->nodePositionInHeapMaybe >= 0;
}
