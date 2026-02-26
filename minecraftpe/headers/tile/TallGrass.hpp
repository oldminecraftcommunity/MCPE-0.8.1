#pragma once
#include <tile/Bush.hpp>

struct TallGrass: Bush
{
	TextureUVCoordinateSet field_80, field_98, field_B0, field_C8;

	TallGrass(int32_t, const std::string&);

	virtual ~TallGrass();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual TextureUVCoordinateSet* getCarriedTexture(int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual int32_t getColor(int32_t);
	virtual int32_t getColor(LevelSource*, int32_t, int32_t, int32_t);
	virtual void playerDestroy(Level*, Player*, int32_t, int32_t, int32_t, int32_t);
	virtual std::string getDescriptionId(const ItemInstance*);

};
