#include <rendering/entity/ChickenRenderer.hpp>
#include <entity/Chicken.hpp>
#include <math/Mth.hpp>

ChickenRenderer::ChickenRenderer(Model* a2, float a3)
	: MobRenderer(a2, a3) {
}
ChickenRenderer::~ChickenRenderer() {
}
float ChickenRenderer::getBob(Mob* a2_, float a3) {
	Chicken* a2 = (Chicken*)a2_;
	return (float)(Mth::sin(((float)(a2->field_C98 + (float)((float)(a2->field_C8C - a2->field_C98) * a3)))) + 1.0) * (float)(a2->field_C94 + (float)((float)(a2->field_C90 - a2->field_C94) * a3));
}
