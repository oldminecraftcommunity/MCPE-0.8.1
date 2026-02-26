#include <level/gen/feature/SpruceFeature.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>

SpruceFeature::SpruceFeature(bool_t u) : Feature(u){

}

SpruceFeature::~SpruceFeature() {
}
bool_t SpruceFeature::place(Level* level, Random* random, int32_t x, int32_t y, int32_t z){
	int8_t v8; // r5
	int8_t v9; // r0
	int32_t v11; // r5
	bool_t v12; // r7
	int32_t v13; // r0
	int32_t i; // r10
	int32_t v15; // r9
	int32_t v16; // r0
	int32_t v17; // r7
	int32_t v18; // r10
	int32_t v19; // r5
	int32_t v20; // r8
	int32_t v21; // r9
	int32_t v22; // r3
	int32_t v23; // r5
	int32_t v24; // r8
	int32_t v25; // r0
	int32_t v26; // r3
	int32_t v27; // r8
	int32_t v28; // [sp+14h] [bp-54h]
	int32_t v29; // [sp+14h] [bp-54h]
	int32_t v30; // [sp+18h] [bp-50h]
	int32_t v31; // [sp+18h] [bp-50h]
	int32_t v33; // [sp+20h] [bp-48h]
	int32_t a4; // [sp+24h] [bp-44h]
	int32_t a4a; // [sp+24h] [bp-44h]
	int32_t v36; // [sp+28h] [bp-40h]
	int32_t v38; // [sp+30h] [bp-38h]
	int32_t v39; // [sp+3Ch] [bp-2Ch]

	v28 = random->genrand_int32() & 3;
	v33 = v28 + 6;
	v8 = random->genrand_int32();
	v9 = random->genrand_int32();
	if ( y <= 0 || y + v33 > 127 )
	{
		return 0;
	}
	v30 = (v8 & 1) + 1;
	v11 = y;
	v12 = 1;
	v36 = (v9 & 1) + 2;
	while ( v11 <= y + 1 + v33 )
	{
		if ( !v12 )
		{
			return 0;
		}
		v26 = v36;
		if ( v11 - y < v30 )
		{
			v26 = 0;
		}
		v15 = x - v26;
		v27 = v26;
		a4a = v26 + x;
		v38 = z + v26;
		while ( v15 <= a4a && v12 )
		{
			for ( i = z - v27; i <= v38 && v12; ++i )
			{
				if ( (uint32_t)v11 <= 0x7F )
				{
					v13 = level->getTile(v15, v11, i);
					if ( v13 )
					{
						v12 = v13 == Tile::leaves->blockID;
					}
				}
				else
				{
					v12 = 0;
				}
			}
			++v15;
		}
		++v11;
	}
	if ( !v12 )
	{
		return 0;
	}
	v16 = level->getTile(x, y - 1, z);
	if ( v16 != Tile::grass->blockID && v16 != Tile::dirt->blockID )
	{
		return 0;
	}
	if ( y >= 121 - v28 )
	{
		return 0;
	}
	v17 = 1;
	v18 = 0;
	this->placeBlock(level, x, y - 1, z, Tile::dirt->blockID);
	v29 = 0;
	v39 = v33 - v30;
	v19 = random->genrand_int32() & 1;
	do
	{
		v20 = x - v19;
		a4 = y + v33 - v18;
		while ( v20 <= x + v19 )
		{
			v21 = z - v19;
			v31 = /*abs32*/ abs(v20 - x);
			while ( v21 <= z + v19 )
			{
				if ( v31 != v19 )
				{
					goto LABEL_58;
				}
				v22 = v21 - z;
				if ( v21 - z < 0 )
				{
					v22 = z - v21;
				}
				if ( v22 != v31 || !v31 )
				{
LABEL_58:
					if ( !Tile::solid[level->getTile(v20, a4, v21)] )
					{
						this->placeBlock(level, v20, a4, v21, Tile::leaves->blockID, 1);
					}
				}
				++v21;
			}
			++v20;
		}
		if ( v19 < v17 )
		{
			++v19;
		}
		else
		{
			if ( ++v17 > v36 )
			{
				v17 = v36;
			}
			v19 = v29;
			v29 = 1;
		}
		++v18;
	}
	while ( v18 <= v39 );
	v23 = 0;
	v24 = v33 - random->genrand_int32() % 3;
	while ( v23 < v24 )
	{
		v25 = level->getTile(x, v23 + y, z);
		if ( !v25 || v25 == Tile::leaves->blockID )
		{
			this->placeBlock(level, x, v23 + y, z, Tile::treeTrunk->blockID, 1);
		}
		++v23;
	}
	return 1;
}
