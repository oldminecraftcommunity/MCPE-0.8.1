#include <_types.h>
#include <tile/material/LiquidMaterial.hpp>

bool_t LiquidMaterial::isLiquid(void) const{
	return 1;
}
bool_t LiquidMaterial::isSolid(void) const{
	return 0;
}
bool_t LiquidMaterial::blocksMotion(void) const{
	return 0;
}
