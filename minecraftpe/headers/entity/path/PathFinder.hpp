#pragma once
#include <entity/path/BinaryHeap.hpp>
#include <unordered_map>
#include <util/ArrayWithLength.hpp>

struct LevelSource;
struct Entity;
struct Path;

struct PathFinder
{
	LevelSource* levelSource;
	BinaryHeap heap;
	std::unordered_map<int32_t, Node*> nodes; //TODO
	arrayWithLength<Node*>* neighborNodes;
	int8_t field_34, field_35, field_36, field_37;
	int8_t field_38, field_39, field_3A, field_3B;
	int8_t field_3C, field_3D, field_3E, field_3F;
	int8_t field_40, field_41, field_42, field_43;
	int8_t field_44, field_45, field_46, field_47;
	int8_t field_48, field_49, field_4A, field_4B;
	int8_t field_4C, field_4D, field_4E, field_4F;
	int8_t field_50, field_51, field_52, field_53;
	int8_t field_54, field_55, field_56, field_57;

	PathFinder(LevelSource*, bool_t, bool_t, bool_t, bool_t);
	Path* findPath(Entity*, Entity*, float);
	Path* findPath(Entity*, Node*, Node*, Node*, float);
	Path* findPath(Entity*, float, float, float, float);
	Path* findPath(Entity*, int32_t, int32_t, int32_t, float);
	int32_t getNeighbors(Entity*, Node*, Node*, Node*, float);
	Node* getNode(Entity*, int32_t, int32_t, int32_t, Node*, int32_t);
	Node* getNode(int32_t, int32_t, int32_t);
	int32_t isFree(Entity*, int32_t, int32_t, int32_t, Node*);
	Path* reconstruct_path(Node*, Node*);
	~PathFinder();
};
