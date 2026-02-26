#include <math/Pos.hpp>
bool_t Pos::operator==(const Pos& a2) {
	return this->x == a2.x && this->y == a2.y && this->z == a2.z;
}
