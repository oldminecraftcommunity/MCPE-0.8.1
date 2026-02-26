#include <item/CompassItem.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <math.h>

CompassItem::CompassItem(int32_t id)
	: Item(id) {
	this->itemTexture = "compass.png";
	this->field_C = 32;
	for(int32_t i = 0; i != 32;) {
		TextureUVCoordinateSet* tex = &this->textures[i];
		tex->minX = 0;
		float v418 = i++;
		tex->maxX = 1.0;
		tex->width = 16.0;
		tex->height = 512.0;
		tex->minY = v418 * 0.03125;
		tex->maxY = (float)i * 0.03125;
	}
}
CompassItem::~CompassItem() {
}
TextureUVCoordinateSet* CompassItem::getIcon(int32_t a2, int32_t a3, bool_t a4) {
	if(a4) return &this->iconUV;
	return &this->textures[a3];
}
int32_t CompassItem::getAnimationFrameFor(Mob* a2) {
	float v4; // s15
	float i;  // s15

	TilePos result = a2->level->getSharedSpawnPos();
	Vec3 v8((float)result.x, 0.0, (float)result.z);
	Vec3 v9(a2->posX, 0.0, a2->posZ);
	Vec3 v11(v8.x - v9.x, v8.y - v9.y, v8.z - v9.z);
	v4 = sqrt((float)((float)((float)(v11.y * v11.y) + (float)(v11.x * v11.x)) + (float)(v11.z * v11.z)));
	Vec3 x = v4 >= 0.0001 ? Vec3(v11.x / v4, v11.y / v4, v11.z / v4) : Vec3::ZERO; // [sp+28h] [bp-28h] BYREF

	for(i = (float)((float)(atan2f(x.z, x.x) * 57.296) - a2->yaw) + 90.0; i < 0.0; i = i + 360.0) {
		;
	}
	while(i >= 360.0) {
		i = i - 360.0;
	}
	return (int32_t)(float)((float)(i / 360.0) * (float)this->field_C);
}
