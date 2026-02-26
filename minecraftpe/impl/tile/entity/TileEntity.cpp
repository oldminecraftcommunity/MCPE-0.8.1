#include <tile/entity/TileEntity.hpp>
#include <level/Level.hpp>
#include <entity/Mob.hpp>
#include <entity/Player.hpp>
#include <tile/Tile.hpp>
#include <nbt/CompoundTag.hpp>
#include <GL/gl.h>
#include <string.h>
#include <math.h>
#include <math/Mth.hpp>
#include <nbt/StringTag.hpp>
#include <tile/entity/TileEntityFactory.hpp>

int32_t TileEntity::_runningId = 0;
std::map<int32_t, std::string> TileEntity::classIdMap;
std::map<std::string, int32_t> TileEntity::idClassMap;

void TileEntity::initTileEntities() {
	TileEntity::setId(1, "Furnace");
	TileEntity::setId(2, "Chest");
	TileEntity::setId(3, "NetherReactor");
	TileEntity::setId(4, "Sign");
}
void TileEntity::teardownTileEntities() {
}
TileEntity* TileEntity::loadStatic(CompoundTag* a2) {
	TileEntity* te; // r0

	std::string ss = a2->contains("id", 8) ? ((StringTag*)a2->get("id"))->value : ""; //Tag::NullString maybe?

	const auto& id = TileEntity::idClassMap.find(ss);
	if(id == TileEntity::idClassMap.end() || (te = TileEntityFactory::createTileEntity(id->second)) == 0) {
		return 0;
	}
	te->load(a2);
	return te;
}

TileEntity::TileEntity(int32_t a2) {
	int32_t v2;

	this->type = a2;
	this->aabb.maxX = 1.0;
	this->aabb.maxY = 1.0;
	this->aabb.maxZ = 1.0;
	this->level = 0;
	this->aabb.minX = 0.0;
	this->aabb.minY = 0.0;
	this->aabb.minZ = 0.0;
	this->blockMetadata = -1;
	this->field_34 = 0;
	this->renderId = TER_NONE;
	v2 = TileEntity::_runningId;
	this->block = 0;
	this->removed = 0;
	TileEntity::_runningId = v2 + 1;
	this->id = v2 + 1;
	this->field_44 = 0.0;
	this->field_48 = 0.0;
	this->field_4C = 0.0;
	this->field_50 = 0.0;
	this->field_54 = 0.0;
}
void TileEntity::_destructionWobble(float& x, float& y, float& z) {
	float v4; // s14
	float v9; // s15
	float v10; // s18
	float v11; // s21
	float v12; // s15
	float v13; // s14
	float v14; // s15
	double v15; // d8
	float v16; // s15
	float v17; // s14
	float v18; // s15

	v4 = this->field_54;
	if(v4 > 0.0) {
		v9 = this->field_44 + 0.016667;
		this->field_44 = v9;
		if(v9 > 0.2) {
			Vec3 v19((float)((float)(v4 * 0.05) + 0.01) * this->field_48, (float)((float)(v4 * 0.05) + 0.01) * this->field_4C, (float)((float)(v4 * 0.05) + 0.01) * this->field_50);
			double _v10 = (float)((float)((float)(Mth::random() - 0.5) * 6.2832) * 0.15);
			v11 = cos(_v10);
			v12 = sin(_v10);
			v13 = (float)(v19.z * v12) + (float)(v19.y * v11);
			v14 = (float)(v19.z * v11) - (float)(v19.y * v12);
			v19.y = v13;
			v19.z = v14;
			v15 = (float)((float)((float)(Mth::random() - 0.5) * 6.2832) * 0.15);
			v10 = cos(v15);
			v16 = sin(v15);
			v17 = (float)(v19.z * v16) + (float)(v19.x * v10);
			v18 = (float)(v19.z * v10) - (float)(v19.x * v16);
			x = x + v17;
			y = y + v19.y;
			z = z + v18;
			this->field_44 = 0.0;
		}
	}
}
void TileEntity::_resetAABB(void) {
	float posX; // s12
	float x; // s9
	float y; // s10
	float z; // s11
	float posY; // s13
	float posZ; // s14
	float v7; // s9
	float v8; // s10
	float v9; // s11

	posX = (float)this->posX;
	x = Vec3::ONE.x;
	y = Vec3::ONE.y;
	z = Vec3::ONE.z;
	posY = (float)this->posY;
	posZ = (float)this->posZ;
	if(posX == 0.0) {
		posX = 0.0;
	}
	this->aabb.minX = posX;
	if(posY == 0.0) {
		posY = 0.0;
	}
	this->aabb.minY = posY;
	v7 = posX + x;
	v8 = posY + y;
	if(posZ == 0.0) {
		posZ = 0.0;
	}
	this->aabb.minZ = posZ;
	v9 = posZ + z;
	if(v7 == 0.0) {
		v7 = 0.0;
	}
	this->aabb.maxX = v7;
	if(v8 == 0.0) {
		v8 = 0.0;
	}
	this->aabb.maxY = v8;
	if(v9 == 0.0) {
		v9 = 0.0;
	}
	this->aabb.maxZ = v9;
}
void TileEntity::clearRemoved(void) {
	this->removed = 0;
}
void TileEntity::destroyTick(const Mob* a2, float a3) {
	float y; // r1
	float z; // r2

	this->field_54 = a3;
	Vec3 v6 = a2->getLookAngle();
	y = v6.y;
	z = v6.z;
	this->field_48 = v6.x;
	this->field_4C = y;
	this->field_50 = z;
}
float TileEntity::distanceToSqr(float x, float y, float z) {
	float xd; // s13
	float yd; // s15
	float zd; // s14

	xd = (float)((float)this->posX + 0.5) - x;
	yd = (float)((float)this->posY + 0.5) - y;
	zd = (float)((float)this->posZ + 0.5) - z;
	return (float)((float)(yd * yd) + (float)(xd * xd)) + (float)(zd * zd);
}
float TileEntity::getBrightness(float a2) {
	return this->level->getBrightness(this->posX, this->posY, this->posZ);
}
int32_t TileEntity::getData(void) {
	if(this->blockMetadata == -1) {
		this->blockMetadata = this->level->getData(this->posX, this->posY, this->posZ);
	}
	return this->blockMetadata;
}
struct Tile* TileEntity::getTile() {
	if(!this->block) {
		this->block = Tile::tiles[this->level->getTile(this->posX, this->posY, this->posZ)];
	}
	return this->block;
}

bool_t TileEntity::isRemoved() {
	return this->removed;
}
bool_t TileEntity::isType(TileEntity* ent, int32_t a2) {
	if(ent) return ent->isType(a2);
	return 0;
}
bool_t TileEntity::isType(int32_t a2) {
	return this->type == a2;
}
void TileEntity::setChanged(void) {
	if(this->level) {
		this->blockMetadata = this->level->getData(this->posX, this->posY, this->posZ);
		this->level->tileEntityChanged(this->posX, this->posY, this->posZ, this);
	}
}
void TileEntity::setData(int32_t a2) {
	this->blockMetadata = a2;
	this->level->setData(this->posX, this->posY, this->posZ, a2, 3);
}
void TileEntity::setId(int32_t a1, const std::string& a2) {
	if(TileEntity::idClassMap.find(a2) == TileEntity::idClassMap.end()) {
		TileEntity::idClassMap.insert({a2, a1});
		TileEntity::classIdMap.insert({a1, a2});
	}
}
void TileEntity::setupLighting(bool_t a2, float a3) {
	float bright; // r0
	float v7; // s16
	int32_t isSkyLit; // r6
	float v9; // s21
	float v10; // s20
	float v11; // s19
	float v12; // s21
	float v13; // s20
	float v14; // s15
	float v15; // s21
	float v16; // s20
	float v17; // s19
	float v18; // s13
	float v19; // s14
	float v20; // s15
	float v21; // s18
	float v22; // r0
	float v23; // r1
	float v24; // r2

	bright = this->getBrightness(a3);
	v7 = bright;
	if(bright > 1.0) {
		v7 = 1.0;
	} else if(bright <= 0.4) {
		v7 = 0.4;
	}
	if(a2) {
		isSkyLit = this->level->isSkyLit(this->posX, this->posY, this->posZ);
		Vec3 result = isSkyLit ? this->level->getSunlightDirection(a3) : Vec3(0.40825, 0.8165, 0.40825);
		float params[4];
		memset(&params, 0, sizeof(*params) * 4);
		params[0] = result.x;
		params[1] = result.y;
		params[2] = result.z;
		glLightfv(0x4000u, 0x1203u, params);
		if(isSkyLit) {
			Color4 ret = this->level->getSkyColor(this->posX, this->posZ, a3);
			v9 = (float)(v7 * 0.5) + (float)(ret.r * 0.5);
			v10 = (float)(v7 * 0.5) + (float)(ret.g * 0.5);
			v11 = (float)(v7 * 0.5) + (float)(ret.b * 0.5);
			ret = this->level->getSunriseColor(a3);
			v12 = (float)((float)(ret.a * ret.r) + (float)(v9 * (float)(1.0 - ret.a))) * v7;
			v13 = (float)((float)(ret.a * ret.g) + (float)(v10 * (float)(1.0 - ret.a))) * v7;
			v14 = (float)((float)(ret.a * ret.b) + (float)(v11 * (float)(1.0 - ret.a))) * v7;
		} else {
			v14 = 0.0;
			v13 = 0.0;
			v12 = 0.0;
		}
		v15 = v12 + v7;
		v16 = v13 + v7;
		v17 = v14 + v7;
		v18 = (float)(v15 * v7) + (float)(v15 * v7);
		v19 = (float)(v16 * v7) + (float)(v16 * v7);
		v20 = (float)((float)(v14 + v7) * v7) + (float)((float)(v14 + v7) * v7);
		if(v18 > 1.0) {
			v18 = 1.0;
		} else if(v18 <= 0.0) {
			v18 = 0.0;
		}
		float ret[4];
		ret[0] = v18;
		if(v19 > 1.0) {
			v19 = 1.0;
		} else if(v19 <= 0.0) {
			v19 = 0.0;
		}
		ret[1] = v19;
		if(v20 > 1.0) {
			v20 = 1.0;
		} else if(v20 <= 0.0) {
			v20 = 0.0;
		}
		ret[2] = v20;
		ret[3] = 1.0;
		glLightfv(0x4000u, 0x1201u, ret);
		ret[3] = 1.0;
		v21 = (float)(v7 + v7) + 0.5;
		ret[0] = v15 * v21;
		ret[1] = v16 * v21;
		ret[2] = v17 * v21;
		glLightfv(0x4000u, 0x1200u, ret);
		v22 = 1.0;
		v23 = 1.0;
		v24 = 1.0;
	} else {
		v22 = v7;
		v23 = v7;
		v24 = v7;
	}
	glColor4f(v22, v23, v24, 1.0);
}

TileEntity::~TileEntity() {
}
void TileEntity::load(CompoundTag* a2) {
	this->posX = a2->getInt("x");
	this->posY = a2->getInt("y");
	this->posZ = a2->getInt("z");
	this->_resetAABB();
}
bool_t TileEntity::save(CompoundTag* a2) {
	const auto& id = TileEntity::classIdMap.find(this->type);
	if(id == TileEntity::classIdMap.end()) return 0;
	a2->putString("id", id->second);
	a2->putInt("x", this->posX);
	a2->putInt("y", this->posY);
	a2->putInt("z", this->posZ);
	return 1;
}
void TileEntity::tick() {
}
bool_t TileEntity::isFinished() {
	return 0;
}
void TileEntity::setLevelAndPos(Level* level, int32_t x, int32_t y, int32_t z) {
	this->level = level;
	this->posX = x;
	this->posY = y;
	this->posZ = z;
	this->_resetAABB();
	if(this->level){
		this->block = Tile::tiles[level->getTile(x, y, z)];
	}
}
Packet* TileEntity::getUpdatePacket() {
	return 0;
}
void TileEntity::onUpdatePacket(CompoundTag*) {
}
void TileEntity::setRemoved(void) {
	Level* level;			// r3
	uint32_t isClientMaybe; // r5
	Level* v5;				// r2

	if(!this->removed) {
		this->removed = 1;
		level = this->level;
		isClientMaybe = level->isClientMaybe;
		if(!level->isClientMaybe) {
			for(auto& player: level->playersMaybe) {
				player->tileEntityDestroyed(this->id);
			}
		}
	}
}
void TileEntity::triggerEvent(int32_t, int32_t) {
}
void TileEntity::clearCache(void) {
	this->block = 0;
	this->blockMetadata = -1;
}
void TileEntity::onNeighborChanged(int32_t, int32_t, int32_t) {
}
float TileEntity::getShadowRadius() {
	return 0;
}
