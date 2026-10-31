#pragma once
#include <item/Item.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>

struct CompassItem: Item
{
	TextureUVCoordinateSet textures[32];
	CompassItem(int32_t id) :
			Item(id) {
		this->itemTexture = "compass.png";
		this->field_C = 32;
		for (int32_t i = 0; i != 32;) {
			TextureUVCoordinateSet* tex = &this->textures[i];
			tex->minX = 0;
			float v418 = i++;
			tex->maxX = 1.0;
			tex->width = 16.0;
			tex->height = 512.0;
			tex->minY = v418 * 0.03125;
			tex->maxY = (float) (i) * 0.03125;
		}
	}
	virtual ~CompassItem() {
	}
	const virtual TextureUVCoordinateSet* getIcon(int32_t a2, int32_t a3, bool_t a4) const {
		if (a4) return &this->iconUV;

		return &this->textures[a3];
	}
	virtual int32_t getAnimationFrameFor(Mob* a2) const {
		float i; // s15
		TilePos spawn = a2->level->getSharedSpawnPos();
		Vec3 x = Vec3(spawn.x, 0, spawn.z).sub(Vec3(a2->posX, 0, a2->posZ)).normalized();

		for (i = (float) (((float) ((Mth::rad2deg(atan2f(x.z, x.x)))) - a2->yaw)) + 90; i < 0; i += 360) {
			;
		}
		while (i >= 360) i -= 360;
		return (int32_t) ((float) (((float) ((i / 360.0f)) * (float) (this->field_C))));
	}
};
