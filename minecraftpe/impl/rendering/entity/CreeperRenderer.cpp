#include <rendering/entity/CreeperRenderer.hpp>
#include <math/Mth.hpp>
#include <entity/Creeper.hpp>
#include <GL/gl.h>

CreeperRenderer::CreeperRenderer(Model* a2, float a3) : MobRenderer(a2, a3){

}

CreeperRenderer::~CreeperRenderer() {
}
int32_t CreeperRenderer::getOverlayColor(Mob* a2, float a3, float a4) {
	float sw;		// s15
	int32_t result; // r0
	int32_t v6;		// r0

	sw = ((Creeper*)a2)->getSwelling(a4);
	result = (int32_t)(float)(sw * 10.0) & 1;
	if(result) {
		v6 = (int32_t)(float)((float)(sw * 0.2) * 255.0);
		if(v6 < 0) {
			v6 = 0;
		} else if(v6 >= 255) {
			v6 = 255;
		}
		return (v6 << 24) | 0xFFFFFF;
	}
	return result;
}

void CreeperRenderer::scale(Mob* a2, float a3){
	float sw =((Creeper *)a2)->getSwelling(a3);
	float v4 = (float)((float)(Mth::sin(sw * 100.0) * sw) * 0.01) + 1.0;
	if ( sw < 0.0 )
	{
		sw = 0.0;
	}
	else if ( sw > 1.0 )
	{
		sw = 1.0;
	}
	glScalef(
		(float)((float)((float)((float)(sw * sw) * (float)(sw * sw)) * 0.4) + 1.0) * v4,
		(float)((float)((float)((float)(sw * sw) * (float)(sw * sw)) * 0.1) + 1.0) / v4,
		(float)((float)((float)((float)(sw * sw) * (float)(sw * sw)) * 0.4) + 1.0) * v4);
}
