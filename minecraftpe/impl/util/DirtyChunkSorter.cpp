#include <util/DirtyChunkSorter.hpp>
#include <rendering/RenderChunk.hpp>

bool_t DirtyChunkSorter::operator()(RenderChunk* a2, RenderChunk* a3) {
	float v8; // s16
	float v9; // r0

	if(a2->isInFrustumMaybe) {
		if(!a3->isInFrustumMaybe) {
			return 0;
		}
	} else if(a3->isInFrustumMaybe) {
		return 1;
	}
	v8 = a2->distanceToSqr(this->entity);
	v9 = a3->distanceToSqr(this->entity);
	if(v8 < v9) {
		return 0;
	}
	if(v8 <= v9) {
		return a2->field_48 > a3->field_48;
	}
	return 1;
}
