#include <level/gen/feature/LargeFeature.hpp>
#include <level/Level.hpp>

LargeFeature::~LargeFeature(){

}

LargeFeature::LargeFeature(void) {
	this->range = 8;
}
void LargeFeature::apply(ChunkSource* source, Level* level, int32_t cx, int32_t cz, uint8_t* blocks, int32_t a7) {
	int32_t range; // r7
	Random* p_random; // r4
	int32_t v13; // r6
	int32_t v14; // r10
	int32_t v15; // r11
	int32_t i; // r7
	int32_t v18; // [sp+14h] [bp-44h]
	int32_t v19; // [sp+18h] [bp-40h]
	int32_t v20; // [sp+1Ch] [bp-3Ch]
	int32_t v21; // [sp+20h] [bp-38h]
	int32_t v22; // [sp+24h] [bp-34h]

	range = this->range;
	p_random = &this->random;
	p_random->setSeed(level->getSeed());
	v13 = cx - range;
	v18 = 2 * (p_random->genrand_int32() >> 2) + 1;
	v20 = cz - range;
	v19 = 2 * (p_random->genrand_int32() >> 2) + 1;
	v14 = v19 * (cz - range) + v18 * (cx - range);
	v21 = cx + range;
	v22 = cz + range;
	while ( v13 <= v21 )
	{
		v15 = v14;
		for ( i = v20; i <= v22; ++i )
		{
			p_random->setSeed(level->getSeed() ^ v15);
			this->addFeature(level, v13, i, cx, cz, blocks, a7);
			v15 += v19;
		}
		++v13;
		v14 += v18;
	}
}
