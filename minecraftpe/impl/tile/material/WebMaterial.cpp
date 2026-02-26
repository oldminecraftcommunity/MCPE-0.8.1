#include <tile/material/WebMaterial.hpp>

WebMaterial::WebMaterial(void){
	this->alwaysDestroyable = 0;
}

bool_t WebMaterial::blocksMotion(void) const{
	return 0;
}
