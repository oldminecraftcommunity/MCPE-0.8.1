#include <rendering/states/BlendFunctionState.hpp>

BlendFunctionState::BlendFunctionState(GLenum sf, GLenum df){
	glBlendFunc(sf, df);
}

BlendFunctionState::~BlendFunctionState(){
	glBlendFunc(0x302, 0x303);
}
