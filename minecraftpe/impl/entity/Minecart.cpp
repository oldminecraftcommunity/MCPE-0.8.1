#include <entity/Minecart.hpp>
#include <entity/MinecartRideable.hpp>
#include <entity/Player.hpp>
#include <item/Item.hpp>
#include <level/Level.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <tile/BaseRailTile.hpp>
#include <nbt/CompoundTag.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/SetEntityLinkPacket.hpp>
#include <network/packet/SetEntityMotionPacket.hpp>
#include <network/packet/MoveEntityPacket_PosRot.hpp>
Minecart::Minecart(Level* a2)
	: Entity(a2) {
	this->linkedEntity = 0;
	this->field_FC = 1;
	this->field_118 = "";
	this->setSize(0.98, 0.7);
	this->entityRenderId = MINECART;
	this->field_110 = 0;
	this->ridingHeight = this->entityHeight * 0.5;
	this->synchedEntityData.define<int32_t>(17, 0);
	this->synchedEntityData.define<int32_t>(18, 1);
	this->synchedEntityData.define<float>(19, 0);
	this->synchedEntityData.define<int32_t>(20, 0);
	this->synchedEntityData.define<int32_t>(21, 6);
	this->synchedEntityData.define<int8_t>(22, 0);
	this->field_144 = this->posX;
	this->field_148 = this->posY;
	this->field_14C = this->posZ;
	this->field_150 = this->pitch;
	this->field_154 = this->yaw;
}
Minecart::Minecart(Level* a2, float a3, float a4, float a5)
	: Minecart(a2) {
	this->setPos(a3, a4, a5);
	this->prevX = a3;
	this->motionX = this->motionY = this->motionZ = 0;
	this->prevY = 0;
	this->prevZ = 0;
}
void Minecart::applyNaturalSlowdown() {
	float v1; // s15

	if(this->rider) {
		v1 = 0.997;
	} else {
		v1 = 0.96;
	}
	this->motionX = this->motionX * v1;
	this->motionY = this->motionY * 0.0;
	this->motionZ = this->motionZ * v1;
}
void Minecart::comeOffTrack(float a2) {
	float v2; // s14
	bool_t onGround; // r3
	float motionX; // s13
	bool_t v6; // fzf
	bool_t v7; // fnf
	float motionZ; // s13

	v2 = -a2;
	onGround = this->onGround;
	if(this->motionX < (float)-a2) {
		this->motionX = v2;
	}
	motionX = this->motionX;
	v6 = motionX == a2;
	v7 = motionX < a2;
	motionZ = this->motionZ;
	if(!v7 && !v6) {
		this->motionX = a2;
	}
	if(motionZ < v2) {
		this->motionZ = v2;
	}
	if(this->motionZ > a2) {
		this->motionZ = a2;
	}
	if(onGround) {
		this->motionX = this->motionX * 0.5;
		this->motionY = this->motionY * 0.5;
		this->motionZ = this->motionZ * 0.5;
	}
	this->move(this->motionX, this->motionY, this->motionZ);
	if(!this->onGround) {
		this->motionX = this->motionX * 0.95;
		this->motionY = this->motionY * 0.95;
		this->motionZ = this->motionZ * 0.95;
	}
}
Minecart* Minecart::createMinecart(Level* a1, float a2, float a3, float a4, int32_t a5) {
	return new MinecartRideable(a1, a2, a3, a4);
}
void Minecart::destroy(Entity* a2) {
	a2->remove();
	a2->spawnAtLocation(ItemInstance(Item::minecart, 1), 0);
}
std::string Minecart::getAName() {
	if(this->field_118.size()) return this->field_118;
	return "";
}
std::string* Minecart::getCustomName() {
	return &this->field_118;
}
float Minecart::getDamage() {
	return this->synchedEntityData.getFloat(19);
}
int32_t Minecart::getDefaultDisplayData() {
	return 0;
}
int32_t Minecart::getDefaultDisplayOffset() {
	return 6;
}
Tile* Minecart::getDefaultDisplayTile() {
	return 0;
}
int32_t Minecart::getDisplayData() {
	if(this->hasCustomDisplay()) {
		return this->synchedEntityData.getInt(16) >> 16;
	}
	return this->getDefaultDisplayData();
}
int32_t Minecart::getDisplayOffset() {
	if(this->hasCustomDisplay()) {
		return this->synchedEntityData.getInt(21);
	}
	return this->getDefaultDisplayOffset();
}
Tile* Minecart::getDisplayTile() {
	uint16_t i; // r0

	if(!this->hasCustomDisplay()) {
		return this->getDefaultDisplayTile();
	}
	i = this->synchedEntityData.getInt(20);
	if((uint32_t)i - 1 > 0xFD) {
		return 0;
	} else {
		return Tile::tiles[i];
	}
}
int32_t Minecart::getHurtDir() {
	return this->synchedEntityData.getInt(18);
}
int32_t Minecart::getHurtTime() {
	return this->synchedEntityData.getInt(17);
}
int32_t Minecart::EXITS[10][2][3] = {{{0, 0, -1}, {0, 0, 1}},
									 {{-1, 0, 0}, {1, 0, 0}},
									 {{-1, -1, 0}, {1, 0, 0}},
									 {{-1, 0, 0},

									  {1, -1, 0}},
									 {{0, 0, -1}, {0, -1, 1}},
									 {{0, -1, -1}, {0, 0, 1}},
									 {{0, 0, 1}, {1, 0, 0}},
									 {{0, 0, 1}, {-1, 0, 0}},
									 {{0, 0, -1}, {-1, 0, 0}},
									 {{0, 0, -1}, {1, 0, 0}}};
bool_t Minecart::getPos(Vec3& result, float x, float y, float z) {
	int blockX; // r6
	int blockY; // r4
	int blockZ; // r5
	int id; // r10
	bool_t isRail; // r0
	int meta; // r9
	float v16; // s9
	float v17; // s14
	float v18; // s11
	float v19; // s8
	float v20_tmp; // s12
	float v20; // s12
	float v21; // s10
	float v23; // s13
	float v24; // s14
	float v25; // s11

	blockX = Mth::floor(x);
	blockY = Mth::floor(y);
	blockZ = Mth::floor(z);
	if(BaseRailTile::isRail(this->level, blockX, blockY - 1, blockZ)) {
		--blockY;
	}
	id = this->level->getTile(blockX, blockY, blockZ);
	isRail = BaseRailTile::isRail(id);
	if(isRail) {
		meta = this->level->getData(blockX, blockY, blockZ);
		if(((BaseRailTile*)Tile::tiles[id])->isUsesDataBit()) {
			meta &= 7u;
		}
		v16 = (float)((float)blockX + 0.5) + (float)((float)Minecart::EXITS[meta][0][0] * 0.5);
		v17 = (float)((float)blockY + 0.5) + (float)((float)Minecart::EXITS[meta][0][1] * 0.5);
		v18 = (float)((float)blockZ + 0.5) + (float)((float)Minecart::EXITS[meta][0][2] * 0.5);
		v19 = (float)((float)((float)blockX + 0.5) + (float)((float)Minecart::EXITS[meta][1][0] * 0.5)) - v16;
		v20_tmp = (float)((float)((float)blockY + 0.5) + (float)((float)Minecart::EXITS[meta][1][1] * 0.5)) - v17;
		v20 = v20_tmp + v20_tmp;
		v21 = (float)((float)((float)blockZ + 0.5) + (float)((float)Minecart::EXITS[meta][1][2] * 0.5)) - v18;
		if(v19 == 0.0) {
			v23 = z - (float)blockZ;
		} else if(v21 == 0.0) {
			v23 = x - (float)blockX;
		} else {
			v23 = (float)((float)((float)(z - v18) * v21) + (float)((float)(x - v16) * v19)) + (float)((float)((float)(z - v18) * v21) + (float)((float)(x - v16) * v19));
		}
		v24 = v17 + (float)(v20 * v23);
		v25 = v18 + (float)(v21 * v23);
		result.x = v16 + (float)(v19 * v23);
		if(v20 < 0.0) {
			v23 = 1.0;
		}
		result.z = v25;
		if(v20 < 0.0) {
			v24 = v24 + v23;
		}
		if(v20 > 0.0) {
			v24 = v24 + 0.5;
		}
		result.y = v24;
		return 1;
	}
	return 0;
}
bool_t Minecart::getPosOffs(Vec3& a2, float a3, float a4, float a5, float a6) {
	float v6; // s15
	int v11; // r5
	int v12; // r4
	int v13; // r6
	int v14; // r11
	int v16; // r8
	int v17; // s12
	bool v18; // cc
	int v19; // r8
	int v21; // s23
	int v22; // r9
	int v23; // s22
	int v24; // r4
	int v25; // r8
	int v26; // r11
	float v27; // s16
	float v28; // s19
	float v29; // s20
	float v30; // s15
	float v31; // s17
	float v32; // s18

	v11 = Mth::floor(a3);
	v12 = Mth::floor(a4);
	v13 = Mth::floor(a5);
	if(BaseRailTile::isRail(this->level, v11, v12 - 1, v13)) {
		--v12;
	}
	v14 = this->level->getTile(v11, v12, v13);
	if(BaseRailTile::isRail(v14)) {
		v16 = this->level->getData(v11, v12, v13);
		if(((BaseRailTile*)Tile::tiles[v14])->isUsesDataBit()) {
			v16 &= 7u;
		}
		v17 = v12;
		v18 = (uint32_t)(v16 - 2) > 3;
		v19 = v16;
		if(!v18) {
			v6 = 1.0;
		}
		v21 = Minecart::EXITS[v19][0][1];
		v22 = Minecart::EXITS[v19][0][0];
		v23 = Minecart::EXITS[v19][1][1];
		v24 = Minecart::EXITS[v19][1][0];
		v25 = Minecart::EXITS[v19][0][2];
		v26 = Minecart::EXITS[v19][1][2];
		v27 = (float)v17;
		v28 = (float)(v26 - v25);
		if(!v18) {
			v27 = v27 + v6;
		}
		v29 = (float)(v24 - v22);
		v30 = sqrt((float)((float)(v28 * v28) + (float)(v29 * v29)));
		v31 = a3 + (float)((float)(v29 / v30) * a6);
		v32 = a5 + (float)((float)(v28 / v30) * a6);
		if(v21 && Mth::floor(v31) - v11 == v22 && Mth::floor(v32) - v13 == v25) {
			v27 = v27 + (float)v21;
		} else if(v23) {
			if(Mth::floor(v31) - v11 == v24 && Mth::floor(v32) - v13 == v26) {
				v27 = v27 + (float)v23;
			}
		}
		return Minecart::getPos(a2, v31, v27, v32);
	}
	return 0;
}
bool_t Minecart::hasCustomDisplay() {
	return this->synchedEntityData.getByte(22) == 1;
}
bool_t Minecart::hasCustomName() {
	return this->field_118.size() != 0;
}
void Minecart::moveAlongTrack(int32_t x, int32_t y, int32_t z, float maxSpeed, float boost, int32_t id, int32_t meta) {
	float posZ; // r3 MAPDST
	float posX; // r2
	float posY; // r3
	bool_t b; // r0
	float v16; // s16
	float v17; // s16
	int32_t mat_0_1; // s21
	int32_t mat_1_1; // s20
	int32_t mat_0_2; // r9
	int32_t mat_1_0; // r8
	int32_t mat_0_0; // r10
	float matXDiff; // s17
	float matZDiff; // s16
	float matDiffTotal; // r0 MAPDST
	float motionZ; // s13
	float motionX; // s14
	float speedTotal; // s15
	float v32; // s15
	float v33; // s14
	float v34; // s11
	float v36; // s15
	float v37; // s15
	float v38; // s12
	float v39; // s14
	float v40; // s11
	float v41; // s13
	float v42; // s15
	float v43; // s15
	float v44; // s15
	float newZ; // s14
	float v46; // s13
	float newX; // s12
	float ridingHeight; // s15
	float dx; // s15
	float dz; // s14
	float dz_2; // r3
	float v54; // r11
	float v55; // r10
	float v56; // r9
	float v57; // r10
	float v58; // r3
	int32_t v59; // r8
	int32_t v60; // r0
	int32_t v61; // r9
	float v62; // r0
	float totalSpeed; // r0
	float v64; // r3
	float v65; // r3
	Mob* rider_2; // r3
	float yDiff; // s16
	float v68; // r0
	int32_t mat_1_2; // [sp+Ch] [bp-6Ch]
	bool_t v72; // [sp+10h] [bp-68h]
	int32_t goldenRailID; // [sp+14h] [bp-64h]

	posZ = this->posZ;
	this->fallDistance = 0.0;
	posX = this->posX;
	posY = this->posY;
	Vec3 posVec1{0, 0, 0};
	b = this->getPos(posVec1, posX, posY, posZ);
	this->posY = (float)y;
	v72 = b;
	goldenRailID = Tile::goldenRail->blockID;
	if(((BaseRailTile*)Tile::tiles[id])->isUsesDataBit()) {
		meta &= 7u;
	}
	if((uint32_t)(meta - 2) <= 3) {
		this->posY = (float)y + 1.0;
		if(meta == 2) {
			v16 = this->motionX - boost;
LABEL_8:
			this->motionX = v16;
			goto LABEL_14;
		}
		if(meta == 3) {
			v16 = this->motionX + boost;
			goto LABEL_8;
		}
	}
	if(meta == 4) {
		v17 = this->motionZ + boost;
	} else {
		if(meta != 5) {
			goto LABEL_14;
		}
		v17 = this->motionZ - boost;
	}
	this->motionZ = v17;
LABEL_14:
	mat_0_1 = Minecart::EXITS[meta][0][1];
	mat_1_1 = Minecart::EXITS[meta][1][1];
	mat_0_2 = Minecart::EXITS[meta][0][2];
	mat_1_0 = Minecart::EXITS[meta][1][0];
	mat_0_0 = Minecart::EXITS[meta][0][0];
	mat_1_2 = Minecart::EXITS[meta][1][2];
	matXDiff = (float)(mat_1_0 - Minecart::EXITS[meta][0][0]);
	matZDiff = (float)(mat_1_2 - mat_0_2);
	matDiffTotal = Mth::sqrt((float)(matZDiff * matZDiff) + (float)(matXDiff * matXDiff));
	motionZ = this->motionZ;
	motionX = this->motionX;
	if((float)((float)(motionZ * matZDiff) + (float)(motionX * matXDiff)) < 0.0) {
		matXDiff = -matXDiff;
		matZDiff = -matZDiff;
	}
	speedTotal = Mth::sqrt((float)(motionZ * motionZ) + (float)(motionX * motionX));
	if(speedTotal > 2.0) {
		speedTotal = 2.0;
	}
	this->motionX = (float)(speedTotal * matXDiff) / matDiffTotal;
	this->motionZ = (float)(speedTotal * matZDiff) / matDiffTotal;
	if(this->rider) {
		if(this->rider->isMob()) {
			rider_2 = (Mob*)this->rider;
			if(rider_2->moveForward > 0.0) {
				v32 = (float)((float)(rider_2->yaw * 3.1416) / 180.0);
				v33 = this->motionX;
				v34 = Mth::sin(v32);
				v36 = this->motionZ;
				if((float)((float)(v36 * v36) + (float)(v33 * v33)) < 0.01) {
					v37 = v36 + (float)(Mth::cos(v32) * 0.1);
					this->motionX = v33 - (float)(v34 * 0.1);
					this->motionZ = v37;
				}
			}
		}
	}
	v38 = (float)((float)x + 0.5) + (float)((float)mat_0_0 * 0.5);
	v39 = (float)((float)z + 0.5) + (float)((float)mat_0_2 * 0.5);
	v40 = (float)((float)((float)x + 0.5) + (float)((float)mat_1_0 * 0.5)) - v38;
	v41 = (float)((float)((float)z + 0.5) + (float)((float)mat_1_2 * 0.5)) - v39;
	if(v40 == 0.0) {
		v42 = this->posZ - (float)z;
	} else {
		v43 = this->posX;
		if(v41 == 0.0) {
			v42 = v43 - (float)x;
		} else {
			v44 = (float)((float)(this->posZ - v39) * v41) + (float)((float)(v43 - v38) * v40);
			v42 = v44 + v44;
		}
	}
	newZ = v39 + (float)(v41 * v42);
	v46 = this->posY;
	newX = v38 + (float)(v40 * v42);
	ridingHeight = this->ridingHeight;
	this->posZ = newZ;
	this->posX = newX;
	this->setPos(newX, (float)(v46 + ridingHeight) + 0.00001, newZ);
	dx = this->motionX;
	dz = this->motionZ;
	if(this->rider) {
		dx = dx * 0.75;
		dz = dz * 0.75;
	}
	if(dx < (float)-maxSpeed) {
		dx = -maxSpeed;
	}
	if(dx > maxSpeed) {
		dx = maxSpeed;
	}
	if(dz < (float)-maxSpeed) {
		dz = -maxSpeed;
	}
	if(dz <= maxSpeed) {
		dz_2 = dz;
	} else {
		dz_2 = maxSpeed;
	}
	this->move(dx, 0.0, dz_2);
	if(mat_0_1 && (v54 = this->posX, Mth::floor(v54) - x == mat_0_0) && (v55 = this->posZ, Mth::floor(v55) - z == mat_0_2)) {
		this->setPos(v54, (float)mat_0_1 + this->posY, v55);
	} else if(mat_1_1) {
		v56 = this->posX;
		if(Mth::floor(v56) - x == mat_1_0) {
			v57 = this->posZ;
			if(Mth::floor(v57) - z == mat_1_2) {
				this->setPos(v56, (float)mat_1_1 + this->posY, v57);
			}
		}
	}
	this->applyNaturalSlowdown();
	v58 = this->posZ;
	Vec3 vec2{0, 0, 0};
	if(this->getPos(vec2, this->posX, this->posY, v58) && v72) {
		yDiff = (float)(posVec1.y - vec2.y) * 0.05;
		v68 = Mth::sqrt((float)(this->motionZ * this->motionZ) + (float)(this->motionX * this->motionX));
		if(v68 > 0.0) {
			this->motionX = (float)(this->motionX / v68) * (float)(v68 + yDiff);
			this->motionZ = (float)(this->motionZ / v68) * (float)(v68 + yDiff);
		}
		this->setPos(this->posX, vec2.y, this->posZ);
	}
	v59 = Mth::floor(this->posX);
	v60 = Mth::floor(this->posZ);
	if(v59 != x || v60 != z) {
		v61 = v60 - z;
		v62 = Mth::sqrt((float)(this->motionZ * this->motionZ) + (float)(this->motionX * this->motionX));
		this->motionX = v62 * (float)(v59 - x);
		this->motionZ = v62 * (float)v61;
	}
	if(id == goldenRailID) {
		totalSpeed = Mth::sqrt((float)(this->motionZ * this->motionZ) + (float)(this->motionX * this->motionX));
		if(totalSpeed > 0.01) {
			this->motionX = this->motionX + (float)((float)(this->motionX / totalSpeed) * 0.06);
			this->motionZ = this->motionZ + (float)((float)(this->motionZ / totalSpeed) * 0.06);
			return;
		}
		if(meta == 1) {
			if(this->level->isSolidBlockingTile(x - 1, y, z)) {
				v64 = 0.02;
			} else {
				if(!this->level->isSolidBlockingTile(x + 1, y, z)) {
					return;
				}
				v64 = -0.02;
			}
			this->motionX = v64;
		} else {
			if(meta) {
				return;
			}
			if(this->level->isSolidBlockingTile(x, y, z - 1)) {
				v65 = 0.02;
			} else {
				if(!this->level->isSolidBlockingTile(x, y, z + 1)) {
					return;
				}
				v65 = -0.02;
			}
			this->motionZ = v65;
		}
	}
}
void Minecart::setCustomDisplay(bool_t a2) {
	this->synchedEntityData.set<int8_t>(22, a2);
}
void Minecart::setCustomName(const std::string& a2) {
	this->field_118 = a2;
}
void Minecart::setDamage(float a2) {
	this->synchedEntityData.set<float>(19, a2);
}
void Minecart::setDisplayData(int32_t a2) {
	Tile* tile = this->getDisplayTile();
	int32_t bid = tile ? tile->blockID : 0;
	this->synchedEntityData.set<int32_t>(20, (uint16_t)bid | (a2 << 16));
	this->setCustomDisplay(1);
}
void Minecart::setDisplayOffset(int32_t a2) {
	this->synchedEntityData.set(21, a2);
	this->setCustomDisplay(1);
}
void Minecart::setDisplayTile(int32_t a2) {
	int32_t v4 = a2 | (this->getDisplayData() << 16);
	this->synchedEntityData.set(20, v4);
	this->setCustomDisplay(1);
}
void Minecart::setHurtDir(int32_t a2) {
	this->synchedEntityData.set(18, a2);
}
void Minecart::setHurtTime(int32_t a2) {
	this->synchedEntityData.set(17, a2);
}

Minecart::~Minecart() {
}
void Minecart::remove() {
	Entity::remove();
}
void Minecart::lerpTo(float a2, float a3, float a4, float a5, float a6, int32_t a7) {
	this->field_128 = a4;
	this->field_120 = a2;
	this->field_124 = a3;
	this->field_12C = a5;
	this->field_130 = a6;
	this->field_11C = a7 + 2;
}
void Minecart::lerpMotion(float a2, float a3, float a4) {
	this->motionX = a2;
	this->field_134 = a2;
	this->motionY = a3;
	this->field_138 = a3;
	this->motionZ = a4;
	this->field_13C = a4;
}
void Minecart::tick() {
	float newMotionY; // s15
	float posY; // r5
	float posZ; // r7
	float posX; // r0
	int32_t blockX; // r8
	int32_t blockY; // r5
	int32_t blockZ; // r7
	int32_t id; // r9
	int32_t meta; // r0
	float prevZ; // s10
	float v14; // s11
	float v15; // s15
	float v16; // s10
	double v17; // r0
	bool_t isInReverse; // r3
	float v19; // s15
	float v20; // s15
	float v21; // r0
	float v22; // s15
	float v23; // s16
	float minX; // s11
	float v25; // s17
	float minZ; // s12
	float maxX; // s13
	float maxZ; // s14
	Level* level; // r0
	int32_t v36; // r8
	Entity* v43; // r3

	if(this->getHurtTime() > 0) {
		this->setHurtTime(this->getHurtTime() - 1);
	}
	if(this->getDamage() > 0.0) {
		this->setDamage(this->getDamage() - 1.0);
	}
	if(this->posY < -64.0) {
		this->outOfWorld();
	}
	newMotionY = this->motionY - 0.04;
	posY = this->posY;
	posZ = this->posZ;
	posX = this->posX;
	this->prevY = posY;
	this->prevZ = posZ;
	this->prevX = posX;
	this->motionY = newMotionY;
	blockX = Mth::floor(posX);
	blockY = Mth::floor(posY);
	blockZ = Mth::floor(posZ);
	if(BaseRailTile::isRail(this->level, blockX, blockY - 1, blockZ)) {
		--blockY;
	}
	id = this->level->getTile(blockX, blockY, blockZ);
	if(BaseRailTile::isRail(id)) {
		meta = this->level->getData(blockX, blockY, blockZ);
		this->moveAlongTrack(blockX, blockY, blockZ, 0.4, 0.0078125, id, meta);
		if(id == Tile::activatorRail->blockID) {
			this->activateMinecart(blockX, blockY, blockZ, 0);
		}
	} else {
		this->comeOffTrack(0.4);
	}
	this->checkInsideTiles();
	prevZ = this->prevZ;
	v14 = this->prevX - this->posX;
	v15 = this->posZ;
	this->pitch = 0.0;
	v16 = prevZ - v15;
	if((float)((float)(v16 * v16) + (float)(v14 * v14)) > 0.001) {
		v17 = atan2(v16, v14);
		isInReverse = this->isInReverse;
		v19 = v17;
		v20 = (float)(v19 * 180.0) / 3.1416;
		this->yaw = v20;
		if(isInReverse) {
			this->yaw = v20 + 180.0;
		}
	}
	v21 = fmodf(this->yaw - this->prevYaw, 360.0);
	v22 = v21;
	if(v21 >= 180.0) {
		v22 = v21 - 360.0;
	}
	if(v22 < -180.0) {
		v22 = v22 + 360.0;
	}
	if(v22 < -170.0 || v22 >= 170.0) {
		v23 = this->yaw + 180.0;
		this->isInReverse ^= 1u;
		this->yaw = v23;
	}
	this->setRot(this->yaw, this->pitch);
	minX = this->boundingBox.minX;
	v25 = this->boundingBox.maxY + 0.0;
	minZ = this->boundingBox.minZ;
	maxX = this->boundingBox.maxX;
	maxZ = this->boundingBox.maxZ;
	level = this->level;
	std::vector<struct Entity*> ents = std::vector<Entity*>(*this->level->getEntities(this, {minX - 0.2f, this->boundingBox.minY, minZ - 0.2f, maxX + 0.2f, v25, maxZ + 0.2f}));
	for(auto&& e : ents){
		if(e != this->rider) {
			if(e->isPushable()) {
				if(e->getEntityTypeId() == 84) {
					e->push(this);
				}
			}
		}
	}
	if(this->rider) {
		if(this->rider->isDead) {
			if(this->rider->ridingAt == this) {
				this->rider->ridingAt = 0;
			}
			this->rider = 0;
		}
	}
	if(!this->level->isClientMaybe) {
		if(fabsf(this->posX - this->field_144) > 0.1 || fabsf(this->posY - this->field_148) > 0.05 || fabsf(this->posZ - this->field_14C) > 0.1 || fabsf(this->field_150 - this->pitch) > 1.0 || fabsf(this->field_154 - this->yaw) > 1.0) {
			MoveEntityPacket_PosRot v65(this);
			this->level->rakNetInstance->send(v65);

			SetEntityMotionPacket v64(this);
			this->level->rakNetInstance->send(v64);
			this->field_144 = this->posX;
			this->field_148 = this->posY;
			this->field_14C = this->posZ;
			this->field_150 = this->pitch;
			this->field_154 = this->yaw;
		}
		v43 = this->rider;
		if ( this->linkedEntity != v43 )
		{
			this->linkedEntity = v43;
			SetEntityLinkPacket *v48 = new SetEntityLinkPacket(0, this->rider ? this->rider->entityId : 0, this->entityId); // r5
			this->level->rakNetInstance->send(v48);
		}
	}
}
float Minecart::getRideHeight() {
	return (float)(this->entityHeight * 0.0) - 0.3;
}
float Minecart::getShadowRadius() {
	return 0;
}
float Minecart::getShadowHeightOffs() {
	return 0;
}
void Minecart::push(Entity* a2) {
	float v4; // s17
	float v5; // s16
	float v6; // s15
	float v7; // s16
	float v8; // s19
	float v9; // s15
	float v10; // s14
	float v11; // s18
	float v12; // s19
	float posZ; // s13
	float v15; // s15
	float v17; // s15
	float v19; // s14
	float v20; // s15
	float motionX; // s24
	float v22; // s20
	float motionZ; // s23
	float v24; // s22
	float v28; // s20
	float v29; // s17

	if(!this->level->isClientMaybe && a2 != (Minecart*)this->rider) {
		if(a2->isMob() && !a2->isPlayer() && !this->getType() && (float)((float)(this->motionZ * this->motionZ) + (float)(this->motionX * this->motionX)) > 0.01 && !this->rider && !a2->ridingAt) {
			a2->ride(this);
		}
		v4 = a2->posX - this->posX;
		v5 = a2->posZ - this->posZ;
		if((float)((float)(v5 * v5) + (float)(v4 * v4)) >= 0.0001) {
			v6 = Mth::sqrt((float)(v5 * v5) + (float)(v4 * v4));
			v7 = v5 / v6;
			v8 = v4 / v6;
			v9 = 1.0 / v6;
			if(v9 > 1.0) {
				v9 = 1.0;
			}
			v10 = 1.0 - this->field_D4;
			v11 = (float)((float)((float)(v7 * v9) * 0.1) * v10) * 0.5;
			v12 = (float)((float)((float)(v8 * v9) * 0.1) * v10) * 0.5;
			if(a2->getEntityTypeId() == 84) {
				posZ = a2->posZ;
				v15 = this->posZ;

				Vec3 result = Vec3(a2->posX - this->posX, 0, posZ - v15).normalized();
				v17 = (float)(this->yaw * 3.1416) / 180.0;
				v19 = Mth::cos(v17);
				v20 = Mth::sin(v17);
				Vec3 v32 = Vec3(v19, 0, v20).normalized();
				if(fabsf((float)((float)(result.y * v32.y) + (float)(result.x * v32.x)) + (float)(result.z * v32.z)) >= 0.8) {
					motionX = a2->motionX;
					v22 = this->motionX;
					motionZ = a2->motionZ;
					v24 = this->motionZ;
					if(((Minecart*)a2)->getType() == 2 && this->getType() != 2) {
						this->motionX = this->motionX * 0.2;
						this->motionZ = this->motionZ * 0.2;
						this->push(a2->motionX - v12, 0.0, a2->motionZ - v11);
						a2->motionX = a2->motionX * 0.95;
						a2->motionZ = a2->motionZ * 0.95;
					} else if(((Minecart*)a2)->getType() == 2 || this->getType() != 2) {
						this->motionX = this->motionX * 0.2;
						v28 = (float)(motionX + v22) * 0.5;
						this->motionZ = this->motionZ * 0.2;
						v29 = (float)(motionZ + v24) * 0.5;
						this->push(v28 - v12, 0.0, v29 - v11);
						a2->motionX = a2->motionX * 0.2;
						a2->motionZ = a2->motionZ * 0.2;
						a2->push(v28 + v12, 0.0, v29 + v11);
					} else {
						a2->motionX = a2->motionX * 0.2;
						a2->motionZ = a2->motionZ * 0.2;
						a2->push(v12 + this->motionX, 0.0, v11 + this->motionZ);
						this->motionX = this->motionX * 0.95;
						this->motionZ = this->motionZ * 0.95;
					}
				}
			} else {
				this->push(-v12, 0.0, -v11);
				a2->push(v12 * 0.25, 0.0, v11 * 0.25);
			}
		}
	}
}
void Minecart::push(float a2, float a3, float a4) {
	Entity::push(a2, a3, a4);
}
bool_t Minecart::isPickable() {
	return !this->isDead;
}
bool_t Minecart::isPushable() {
	return 1;
}
bool_t Minecart::hurt(Entity* a2, int32_t a3) {
	int32_t v8; // r6
	float posX; // s23
	float posY; // s18
	Level* level; // r9
	float posZ; // s22w
	int32_t v20; // r8

	if(!this->level->isClientMaybe && !this->isDead) {
		this->setHurtDir(-this->getHurtDir());
		this->setHurtTime(10);
		this->markHurt();
		this->setDamage(this->getDamage() + (float)(10 * a3));
		if(!a2) {
			this->level->addParticle(PT_SMOKE, this->posX, this->posY, this->posZ, 0.0, 0.0, 0.0, 0);
LABEL_20:
			this->remove();
			return 1;
		}
		if(a2->isPlayer() && ((Player*)a2)->abilities.instabuild) {
			v20 = 1;
		} else {
			if(this->getDamage() <= 40.0) {
				return 1;
			}
			v20 = 0;
		}
		if(this->rider) {
			this->rider->ride(this);
		}
		v8 = 4;
		do {
			posX = this->posX;
			posY = this->posY;
			level = this->level;
			posZ = this->posZ;

			this->level->addParticle(PT_SMOKE, (posX + (float)(this->level->random.nextFloat() * 0.3)) - 0.15, posY + (float)(this->level->random.nextFloat() * 0.1), (float)(posZ + (float)(this->level->random.nextFloat() * 0.3)) - 0.15, 0.0, 0.0, 0.0, 0);
			--v8;
		} while(v8);
		if(v20 && !this->hasCustomName()) {
			goto LABEL_20;
		}
		Minecart::destroy(this);
	}
	return 1;
}
void Minecart::animateHurt() {
	this->setHurtDir(-this->getHurtDir());
	this->setHurtTime(10);
	this->setDamage(this->getDamage() + (float)(this->getDamage() * 10.0));
}
int32_t Minecart::getEntityTypeId() const {
	return 84;
}
void Minecart::readAdditionalSaveData(CompoundTag* a2) {
	if(a2->getByte("CustomDisplayTile")) {
		this->setDisplayTile(a2->getInt("DisplayTile"));
		this->setDisplayData(a2->getInt("DisplayData"));
		this->setDisplayOffset(a2->getInt("DisplayOffset"));
	}
	if(a2->contains("CustomName") && a2->getString("CustomName").size() != 0) {
		this->field_118 = a2->getString("CustomName");
	}
}
void Minecart::addAdditonalSaveData(CompoundTag* a2) {
	if(this->hasCustomDisplay()) {
		a2->putByte("CustomDisplayTile", 1);
		a2->putInt("DisplayTile", this->getDisplayTile() ? this->getDisplayTile()->blockID : 0);
		a2->putInt("DisplayData", this->getDisplayData());
		a2->putInt("DisplayOffset", this->getDisplayOffset());
	}

	if(this->field_118.size() != 0) {
		a2->putString("CustomName", this->field_118);
	}
}
void Minecart::activateMinecart(int32_t, int32_t, int32_t, bool_t) {
}
