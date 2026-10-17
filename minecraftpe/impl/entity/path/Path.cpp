#include <entity/path/Path.hpp>
#include <entity/path/Node.hpp>
#include <cpputils.hpp>
#include <entity/Entity.hpp>

Path::~Path() {
	if(this->nodes) {
		for(uint32_t i = 0; i < this->pathSize; ++i) {
			delete this->nodes[i];
		}

		delete[] this->nodes;
	}
}
Path::Path(arrayWithLength<Node*> a2) {
	this->nodes = 0;
	this->pathSize = 0;
	this->currentIndex = 0;
	this->size = a2.size;
	this->nodes = new Node*[a2.size];
	this->pathSize = a2.size;
	for(int32_t i = 0; i < this->size; ++i) {
		this->nodes[i] = new Node(0, 0, 0);
		*this->nodes[i] = *a2.array[i];
	}
}
void Path::next() {
	++this->currentIndex;
}
bool_t Path::isDone() {
	return this->currentIndex >= this->size;
}
Node* Path::last() {
	if(this->size <= 0) return 0;
	return this->nodes[this->size - 1];
}
Node* Path::get(int32_t a2) {
	return this->nodes[a2];
}
int32_t Path::getSize() {
	return this->size;
}
void Path::setSize(int32_t a2) {
	this->size = a2;
}
int32_t Path::getIndex() {
	return this->currentIndex;
}
void Path::setIndex(int32_t a2) {
	this->currentIndex = a2;
}
Vec3 Path::getPos(const Entity* a2, int32_t a3) {
	Node* v4 = this->nodes[a3];
	float v5 = vcvts_n_f32_s32((int32_t)(float)(a2->entityWidth + 1.0), 1u);
	return Vec3(v4->xCoord + v5, v4->yCoord, v4->zCoord + v5);
}

Vec3 Path::currentPos(const Entity* a2) {
	return this->getPos(a2, this->currentIndex);
}
Vec3 Path::currentPos() {
	Node* n = this->nodes[this->currentIndex];
	return Vec3(n->xCoord, n->yCoord, n->zCoord);
}
bool_t Path::sameAs(Path* a2) {
	if(!a2) return 0;
	if(a2->pathSize != this->pathSize) return 0;
	for(int i = 0; i != a2->pathSize; ++i) {
		Node* v4 = this->nodes[i];
		Node* v5 = a2->nodes[i];
		if(v4->xCoord != v5->xCoord || v4->yCoord != v5->yCoord || v4->zCoord != v5->zCoord) {
			return 0;
		}
	}
	return 1;
}
bool_t Path::endsIn(Vec3* a2) {
	Node* v3 = this->last();
	if(v3) {
		return v3->xCoord == (int32_t)a2->x && v3->yCoord == (int32_t)a2->y && v3->zCoord == (int32_t)a2->z;
	}
	return 0;
}
bool_t Path::endsInXZ(Vec3* a2) {
	Node* v3 = this->last();
	if(v3) {
		return v3->xCoord == (int32_t)a2->x && v3->zCoord == (int32_t)a2->z;
	}
	return 0;
}
