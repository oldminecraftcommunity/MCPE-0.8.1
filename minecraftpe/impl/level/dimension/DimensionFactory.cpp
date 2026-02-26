#include <level/dimension/DimensionFactory.hpp>
#include <level/dimension/Dimension.hpp>

Dimension* DimensionFactory::createDefaultDimension(struct LevelData*) {
	return Dimension::getNew(10);
}
