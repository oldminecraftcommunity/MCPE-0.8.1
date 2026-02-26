#include <util/ChunkPos.hpp>

bool_t ChunkPos::operator<(const ChunkPos& a2) const {
	int32_t v2; // r4
	int32_t x;	// r2
	int32_t z;	// r3
	int32_t v5; // r0
	int32_t v6; // r1

	if(this->z >= 0) {
		v2 = 0;
	} else {
		v2 = 0x8000;
	}
	x = a2.x;
	z = a2.z;
	v5 = this->z & 0x7FFF | this->x & 0x80000000 | ((this->x & 0x7FFF) << 16) | v2;
	if(z >= 0) {
		v6 = 0;
	} else {
		v6 = 0x8000;
	}
	return v5 < (int32_t)(z & 0x7FFF | x & 0x80000000 | ((x & 0x7FFF) << 16) | v6);
}
