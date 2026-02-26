#include <tile/material/DecorationMaterial.hpp>
#include <_types.h>

bool_t DecorationMaterial::isSolid(void) const{
	return 0;
}
bool_t DecorationMaterial::blocksLight(void) const{
	return 0;
}
bool_t DecorationMaterial::blocksMotion(void) const{
	return 0;
}

DecorationMaterial::DecorationMaterial(void) : Material(){
}
