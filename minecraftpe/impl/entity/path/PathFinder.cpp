#include <entity/path/PathFinder.hpp>
#include <entity/Entity.hpp>
#include <entity/path/Node.hpp>
#include <entity/path/Path.hpp>
#include <level/LevelSource.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <string.h>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

PathFinder::PathFinder(LevelSource* a2, bool_t a3, bool_t a4, bool_t a5, bool_t a6) {
	this->neighborNodes = new arrayWithLength<Node*>{new Node*[32], 32};
	this->field_34 = a3;
	this->field_36 = a5;
	this->field_35 = a4;
	this->levelSource = a2;
	this->field_37 = a6;
}
Path* PathFinder::findPath(Entity* a2, Entity* a3, float a4) {
	return this->findPath(a2, a3->posX, a3->boundingBox.minY, a3->posZ, a4);
}
Path* PathFinder::findPath(Entity* a2, Node* a3, Node* a4, Node* a5, float a6) {
	Node* v9;	   // r8
	float v10;	   // r0
	Node* v11;	   // r5
	int v12;	   // r10
	Node* v14;	   // r1
	Node* v15;	   // r2
	float v16;	   // s16
	float v17;	   // r0
	float v18;	   // s16
	Node* node;	   // r11
	float v20;	   // s16
	bool_t v22;	   // r0
	float v23;	   // s15
	float v24;	   // s14
	int neighbors; // [sp+Ch] [bp-3Ch]

	a3->field_14 = 0.0;
	v9 = a3;
	v10 = a3->distanceTo(a4);
	a3->field_18 = v10;
	a3->nodeCost = v10;
	this->heap.clear();
	this->heap.insert(a3);
	while(!this->heap.isEmpty()) {
		v11 = this->heap.pop();
		v12 = v11->equals(a4);
		if(v12) {
			v14 = a3;
			v15 = a4;
			return this->reconstruct_path(v14, v15);
		}
		v16 = v11->distanceTo(a4);
		v17 = v9->distanceTo(a4);
		v11->field_24 = 1;
		if(v16 < v17) {
			v9 = v11;
		}
		neighbors = this->getNeighbors(a2, v11, a5, a4, a6);
		while(v12 < neighbors) {
			v18 = v11->field_14;
			node = (this->neighborNodes->array)[v12];
			v20 = v18 + v11->distanceTo(node);
			if(!node->inOpenSet() || v20 < node->field_14) {
				node->field_20 = v11;
				node->field_14 = v20;
				node->field_18 = node->distanceTo(a4);
				v22 = node->inOpenSet();
				v23 = node->field_14;
				v24 = node->field_18;
				if(v22) {
					this->heap.changeCost(node, v23 + v24);
				} else {
					node->nodeCost = v23 + v24;
					this->heap.insert(node);
				}
			}
			++v12;
		}
	}
	if(v9 != a3) {
		v14 = a3;
		v15 = v9;
		return this->reconstruct_path(v14, v15);
	}
	return 0;
}
Path* PathFinder::findPath(Entity* a2, float a3, float a4, float a5, float a6) {
	float v10;				  // s18
	float v11;				  // r0
	Node* node;				  // r0
	float v13;				  // s19
	int v14;				  // r6
	int v15;				  // r11
	int v16;				  // r7
	Node* v17;				  // r8
	float v18;				  // s18
	int v19;				  // r10
	int j;					  // r9
	float v21;				  // r0
	Path* result;			  // r0
	int minY;				  // r6
	LevelSource* levelSource; // r9
	int v25;				  // r10
	int v26;				  // r0
	int i;					  // r0
	int v28;				  // r0
	LevelSource* v29;		  // r9
	int v30;				  // r11
	int v31;				  // r0
	int32_t v32;			  // [sp+8h] [bp-78h]
	char v33;				  // [sp+Ch] [bp-74h]
	Node* v34;				  // [sp+14h] [bp-6Ch]
	int v35;				  // [sp+18h] [bp-68h]
	int v36;				  // [sp+1Ch] [bp-64h]

	this->heap.clear();
	this->nodes.clear();
	v33 = this->field_36;
	if(this->field_37 && a2->isInWater()) {
		levelSource = this->levelSource;
		minY = (int)a2->boundingBox.minY;
		v25 = Mth::floor(a2->posX);
		v26 = Mth::floor(a2->posZ);
		for(i = levelSource->getTile(v25, minY, v26); i == Tile::water->blockID || i == Tile::calmWater->blockID; i = v29->getTile(v30, minY, v31)) {
			++minY;
			v28 = Mth::floor(a2->posX);
			v29 = this->levelSource;
			v30 = v28;
			v31 = Mth::floor(a2->posZ);
		}
		v33 = this->field_36;
		this->field_36 = 0;
	} else {
		minY = Mth::floor(a2->boundingBox.minY + 0.5);
	}
	v10 = floorf(a2->boundingBox.minX);
	v11 = floorf(a2->boundingBox.minZ);
	node = this->getNode((int)v10, minY, (int)v11);
	v13 = a2->entityWidth * 0.5;
	v34 = node;
	v14 = Mth::floor(a3 - v13);
	v15 = Mth::floor(a4);
	v16 = Mth::floor(a5 - v13);
	if(this->levelSource->getTile(v14, v15 - 1, v16)) {
		goto LABEL_18;
	}
	v17 = 0;
	v18 = a2->entityWidth * 0.5;
	v19 = v14;
	v35 = Mth::floor(a3 + v18);
	v36 = Mth::floor(a5 + v18);
	while(v19 <= v35) {
		for(j = v16; j <= v36; ++j) {
			if(this->levelSource->getTile(v19, v15 - 1, j)) {
				v17 = this->getNode(v19, v15, j);
				break;
			}
		}
		++v19;
	}
	if(!v17) {
		while(!this->levelSource->getTile(v14, v15 - 1, v16) && v15 > 0) {
			--v15;
		}
LABEL_18:
		v17 = this->getNode(v14, v15, v16);
	}
	v32 = (int)floorf(a2->entityWidth + 1.0);
	Node v37((int)v32, (int)floorf(a2->entityHeight + 1.0), (int)v32);
	result = this->findPath(a2, v34, v17, &v37, a6);
	this->field_36 = v33;
	return result;
}
Path* PathFinder::findPath(Entity* a2, int32_t a3, int32_t a4, int32_t a5, float a6) {
	return this->findPath(a2, (float)a3 + 0.5f, (float)a4 + 0.5f, (float)a5 + 0.5f, a6);
}
int32_t PathFinder::getNeighbors(Entity* a2, Node* a3, Node* a4, Node* a5, float a6) {
	int32_t v10; // r11
	Node* node;	 // r8
	Node* v12;	 // r9
	Node* v13;	 // r7
	Node* v14;	 // r6
	int32_t v15; // r4

	v10 = this->isFree(a2, a3->xCoord, a3->yCoord + 1, a3->zCoord, a4) == 1;
	node = this->getNode(a2, a3->xCoord, a3->yCoord, a3->zCoord + 1, a4, v10);
	v12 = this->getNode(a2, a3->xCoord - 1, a3->yCoord, a3->zCoord, a4, v10);
	v13 = this->getNode(a2, a3->xCoord + 1, a3->yCoord, a3->zCoord, a4, v10);
	v14 = this->getNode(a2, a3->xCoord, a3->yCoord, a3->zCoord - 1, a4, v10);
	if(node && !node->field_24 && node->distanceTo(a5) < a6) {
		v15 = 1;
		this->neighborNodes->array[0] = node;
	} else {
		v15 = 0;
	}
	if(v12) {
		if(!v12->field_24 && v12->distanceTo(a5) < a6) {
			this->neighborNodes->array[v15++] = v12;
		}
	}
	if(v13) {
		if(!v13->field_24 && v13->distanceTo(a5) < a6) {
			this->neighborNodes->array[v15++] = v13;
		}
	}
	if(v14) {
		if(!v14->field_24 && v14->distanceTo(a5) < a6) {
			this->neighborNodes->array[v15++] = v14;
		}
	}
	return v15;
}
Node* PathFinder::getNode(Entity* a2, int32_t a3, int32_t a4, int32_t a5, Node* a6, int32_t a7) {
	int32_t v10;	// r4
	int32_t isFree; // r0
	Node* node;		// r8
	int32_t v14;	// r0
	int32_t v15;	// r9

	v10 = a4;
	isFree = this->isFree(a2, a3, a4, a5, a6);
	if(isFree == 2) {
		return this->getNode(a3, v10, a5);
	}
	if(isFree != 1) {
		if(a7 <= 0 || isFree == -3 || isFree == -4) {
			return 0;
		}
		goto LABEL_9;
	}
	node = this->getNode(a3, v10, a5);
	if(node) {
		goto LABEL_17;
	}
	if(a7 > 0) {
LABEL_9:
		v10 += a7;
		if(this->isFree(a2, a3, v10, a5, a6) != 1) {
			return 0;
		}
		node = this->getNode(a3, v10, a5);
		if(!node) {
			return 0;
		}
LABEL_17:
		v15 = 4;
		while(v10 > 0) {
			v14 = this->isFree(a2, a3, v10 - 1, a5, a6);
			if(this->field_36 && v14 == -1) {
				return 0;
			}
			if(v14 != 1) {
				if(v14 != -2) {
					return node;
				}
				return 0;
			}
			if(!--v15) {
				return 0;
			}
			if(!--v10) {
				return node;
			}
			node = this->getNode(a3, v10, a5);
		}
		return node;
	}
	return 0;
}
Node* PathFinder::getNode(int32_t x, int32_t y, int32_t z) {
	uint32_t hash = Node::createHash(x, y, z);
	auto&& p = this->nodes.find(hash); //TODO check
	if(p != this->nodes.end()) {
		return p->second;
	}
	Node* r = new Node(x, y, z);
	this->nodes.insert({hash, r});
	return r;
}
int32_t PathFinder::isFree(Entity* a2, int32_t x, int32_t y, int32_t z, Node* a6) {
	int32_t v7;	 // r9
	int32_t v8;	 // r11
	int32_t v9;	 // r0
	int32_t v10; // r5
	int32_t v12; // r7
	int32_t v13; // r8
	Tile* v14;	 // [sp+Ch] [bp-3Ch]

	v7 = x;
	v8 = 0;
	while(v7 < x + a6->xCoord) {
		v13 = y;
		while(2) {
			if(v13 < y + a6->yCoord) {
				v12 = z;
LABEL_21:
				if(v12 >= z + a6->zCoord) {
					++v13;
					continue;
				}
				v9 = this->levelSource->getTile(v7, v13, v12);
				v10 = v9;
				if(v9 > 0) {
					if(v9 == Tile::trapdoor->blockID) {
						goto LABEL_11;
					}
					if(v9 == Tile::water->blockID || v9 == Tile::calmWater->blockID) {
						if(this->field_36) {
							return -1;
						}
LABEL_11:
						v8 = 1;
					} else if(!this->field_34 && v9 == Tile::door_wood->blockID) {
						return 0;
					}
					v14 = Tile::tiles[v9];
					if(!v14->isPathfindable(this->levelSource, v7, v13, v12) && (!this->field_35 || v10 != Tile::door_wood->blockID)) {
						if(v10 == Tile::fence->blockID || v10 == Tile::fenceGate->blockID) {
							return -3;
						}
						if(v10 == Tile::trapdoor->blockID) {
							return -4;
						}
						if(v14->material != Material::lava) {
							return 0;
						}
						if(!a2->isInLava()) {
							return -2;
						}
					}
				}
				++v12;
				goto LABEL_21;
			}
			break;
		}
		++v7;
	}
	if(v8) {
		return 2;
	} else {
		return 1;
	}
}
Path* PathFinder::reconstruct_path(Node* a2, Node* a3) {
	Node* v4;	  // r6
	int32_t size; // r5
	Node** v6;	  // r4
	Node* v7;	  // r2

	v4 = a3;
	for(size = 1;; ++size) {
		v4 = v4->field_20;
		if(!v4) {
			break;
		}
	}
	v6 = new Node*[size];
	memset(v6, 0, sizeof(*v6) * size);
	v7 = a3;
	int32_t v4_ = 0;
	do {
		v6[size - 1 - v4_] = a3;
		a3 = a3->field_20;
		++v4_;
	} while(a3);

	Path* v8 = new Path(arrayWithLength<Node*>{v6, size});
	if(v6) {
		delete[] v6;
	}
	return v8;
}
PathFinder::~PathFinder() {
	if(this->neighborNodes->array) delete[] this->neighborNodes->array;
	delete this->neighborNodes;
	for(auto&& p: this->nodes) {
		delete p.second;
	}
}
