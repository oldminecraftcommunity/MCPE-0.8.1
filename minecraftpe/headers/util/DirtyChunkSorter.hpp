#pragma once
#include <rendering/RenderChunk.hpp>

struct RenderChunk;
struct Entity;

struct DirtyChunkSorter
{
	const Entity* entity;

	bool_t operator ()(RenderChunk* a2, RenderChunk* a3) {
		if (a2->isInFrustumMaybe) {
			if (!a3->isInFrustumMaybe) {
				return 0;
			}
		} else if (a3->isInFrustumMaybe) {
			return 1;
		}

		float v8 = a2->distanceToSqr(this->entity);
		float v9 = a3->distanceToSqr(this->entity);
		if (v8 < v9) {
			return 0;
		}
		if (v8 <= v9) {
			return a2->field_48 > a3->field_48;
		}
		return 1;
	}
};
