#include <tile/TreeTile.hpp>
#include <level/Level.hpp>
#include <tile/material/Material.hpp>
#include <rendering/TextureAtlasTextureItem.hpp>


TreeTile::TreeTile(int32_t a2)
	: RotatedPillarTile(a2, Material::wood) {
	TextureAtlasTextureItem* texItem = this->getTextureItem("log");
	this->field_80 = *texItem->getUV(0);
	this->field_98 = *texItem->getUV(1);
	this->field_B0 = *texItem->getUV(2);
	this->field_C8 = *texItem->getUV(3);
	this->field_E0 = *texItem->getUV(4);
	this->field_F8 = *texItem->getUV(5);
	this->field_110 = *texItem->getUV(6);
	this->field_128 = *texItem->getUV(7);

}

TreeTile::~TreeTile() {
}
void TreeTile::onRemove(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t v8; // r11
	int32_t v9; // r0
	int32_t zPos; // r7
	int32_t yPos; // r6
	int32_t i; // r5
	int32_t xDecPos; // [sp+10h] [bp-30h]

	if(!level->isClientMaybe && level->hasChunksAt(x - 5, y - 5, z - 5, x + 5, y + 5, z + 5)) {
		for(i = -4; i != 5; ++i) {
			yPos = -4;
			xDecPos = i + x;
			do {
				for(zPos = -4; zPos != 5; ++zPos) {
					v8 = zPos + z;
					if(level->getTile(xDecPos, yPos + y, zPos + z) == Tile::leaves->blockID) {
						v9 = level->getData(xDecPos, yPos + y, v8);
						if((v9 & 4) == 0) {
							level->setDataNoUpdate(xDecPos, yPos + y, v8, v9 | 4);
						}
					}
				}
				++yPos;
			} while(yPos != 5);
		}
	}
}
int32_t TreeTile::getResource(int32_t, Random*) {
	return Tile::treeTrunk->blockID;
}
int32_t TreeTile::getResourceCount(Random*) {
	return 1;
}
std::string TreeTile::getTypeDescriptionId(int32_t a2) {
	return Tile::WOOD_NAMES[a2 & 7];
}
int32_t TreeTile::getSpawnResourcesAuxValue(int32_t a2) {
	return a2 & 3;
}
TextureUVCoordinateSet* TreeTile::getDirTexture(int32_t a2, int32_t a3) {
	int32_t v3; // r2
	TextureUVCoordinateSet* v6; // r6

	v3 = a3 & 3;
	if((unsigned int)a2 > 1) {
		switch(v3) {
			case 1:
				v6 = &this->field_E0;
				break;
			case 2:
				v6 = &this->field_B0;
				break;
			case 3:
				v6 = &this->field_110;
				break;
			default:
				v6 = &this->field_80;
				break;
		}
	} else {
		switch(v3) {
			case 1:
				v6 = &this->field_F8;
				break;
			case 2:
				v6 = &this->field_C8;
				break;
			case 3:
				v6 = &this->field_128;
				break;
			default:
				v6 = &this->field_98;
				break;
		}
	}
	this->textureUV = *v6;
	return &this->textureUV;
}
