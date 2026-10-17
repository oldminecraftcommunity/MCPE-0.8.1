#include <math/Direction.hpp>


const int32_t Direction::DIRECTION_FACING[] = {3, 4, 2, 5};
const int32_t Direction::FACING_DIRECTION[] = {-1, -1, 2, 0, 1, 3};
const int32_t Direction::DIRECTION_OPPOSITE[] = {2, 3, 0, 1};

const int32_t Direction::RELATIVE_DIRECTION_FACING[] = {
	0, 1, 3, 2, 5, 4,
	0, 1, 5, 4, 2, 3,
	0, 1, 2, 3, 4, 5,
	0, 1, 4, 5, 3, 2
};
