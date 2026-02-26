#include <rendering/frustum/FrustumCuller.hpp>
#include <math/AABB.hpp>

bool_t FrustumCuller::isVisible(const AABB& bb) {
	return this->data.cubeInFrustum(bb.minX - this->xOff, bb.minY - this->yOff, bb.minZ - this->zOff, bb.maxX - this->xOff, bb.maxY - this->yOff, bb.maxZ - this->zOff);
}
