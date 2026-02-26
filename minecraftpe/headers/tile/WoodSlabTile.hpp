#pragma once
#include <tile/SlabTile.hpp>
#include <item/AuxDataTileItem.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


struct WoodSlabTile : SlabTile{
	struct Item : AuxDataTileItem{
		//TODO constructor
		virtual ~Item();
		virtual bool_t useOn(ItemInstance*, Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float);
	};

	TextureAtlasTextureItem field_84;

	WoodSlabTile(int32_t, bool_t);

	virtual ~WoodSlabTile();
	virtual TextureUVCoordinateSet* getTexture(int32_t, int32_t);
	virtual int32_t getResource(int32_t, Random*);
	virtual std::string getTypeDescriptionId(int32_t);
	virtual int32_t getSpawnResourcesAuxValue(int32_t);

};
