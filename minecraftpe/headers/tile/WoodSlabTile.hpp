#pragma once
#include <tile/SlabTile.hpp>
#include <tile/material/Material.hpp>
#include <level/Level.hpp>


struct WoodSlabTile : SlabTile{
	struct Item;

	TextureAtlasTextureItem field_84;

	WoodSlabTile(int32_t a2, bool_t a3)
		: SlabTile(a2, "planks", a3, Material::wood) {
		this->field_84 = *this->getTextureItem("planks");
	}

	virtual ~WoodSlabTile() {
	}
	virtual const TextureUVCoordinateSet* getTexture(int32_t a2, int32_t a3) {
		return this->field_84.getUV(a3 & 7);
	}
	virtual int32_t getResource(int32_t, Random*) {
		return Tile::woodSlabHalf->blockID;
	}
	virtual std::string getTypeDescriptionId(int32_t a2) {
		return Tile::WOOD_NAMES[a2 & 7];
	}
	virtual int32_t getSpawnResourcesAuxValue(int32_t a2) {
		return a2 & 7;
	}

};
