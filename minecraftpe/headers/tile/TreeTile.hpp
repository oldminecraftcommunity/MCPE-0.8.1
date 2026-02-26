#pragma once
#include <tile/RotatedPillarTile.hpp>

struct TreeTile : RotatedPillarTile{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8, field_E0;
	TextureUVCoordinateSet field_F8, field_110, field_128;

	TreeTile(int32_t);

	virtual ~TreeTile();
	virtual void onRemove(Level*, int32_t, int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getResourceCount(Random*);
	virtual std::string getTypeDescriptionId(int32_t);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);
	virtual TextureUVCoordinateSet* getDirTexture(int32_t, int32_t);

};
