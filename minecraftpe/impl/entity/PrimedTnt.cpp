#include <entity/PrimedTnt.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>
#include <nbt/CompoundTag.hpp>

PrimedTnt::PrimedTnt(Level* a2)
	: Entity(a2) {
	this->ticksUntilExplode = 80;
	this->entityRenderId = TNT;
	this->field_FC = 1;
	this->setSize(0.98, 0.98);
	this->ridingHeight = this->entityHeight * 0.5;
}
PrimedTnt::PrimedTnt(Level* a2, float x, float y, float z)
	: PrimedTnt(a2) {
	this->setPos(x, y, z);
	float v8 = Mth::random();
	float v9 = (float)((float)((float)(v8 * 3.1416) + (float)(v8 * 3.1416)) * 0.017453);
	float v10 = Mth::sin(v9) * -0.02;
	this->motionY = 0.2;
	this->motionX = v10;
	float v11 = Mth::cos(v9) * -0.02;
	this->prevX = x;
	this->field_110 = 0;
	this->prevY = y;
	this->prevZ = z;
	this->motionZ = v11;
}
void PrimedTnt::explode() {
	this->level->explode(0, this->posX, this->posY, this->posZ, 3.1);
}

PrimedTnt::~PrimedTnt() {
}
void PrimedTnt::tick() {
	float motionY;	 // s15
	float motionX;	 // r1
	float posZ;		 // r3
	float v5;		 // s12
	float motionZ;	 // s13
	bool_t onGround; // r3
	float v8;		 // s14
	Level* level;	 // r0
	int32_t v10;	 // r3

	motionY = this->motionY - 0.04;
	motionX = this->motionX;
	this->prevX = this->posX;
	this->prevY = this->posY;
	posZ = this->posZ;
	this->motionY = motionY;
	this->prevZ = posZ;
	this->move(motionX, motionY, this->motionZ);
	v5 = this->motionX * 0.98;
	motionZ = this->motionZ;
	onGround = this->onGround;
	v8 = this->motionY * 0.98;
	this->motionX = v5;
	this->motionY = v8;
	this->motionZ = motionZ * 0.98;
	if(onGround) {
		this->motionZ = (float)(motionZ * 0.98) * 0.7;
		this->motionX = v5 * 0.7;
		this->motionY = v8 * -0.5;
	}
	level = this->level;
	v10 = this->ticksUntilExplode - 1;
	this->ticksUntilExplode = v10;
	if(level->isClientMaybe || v10 > 0) {
		level->addParticle(PT_SMOKE, this->posX, this->posY + 0.5, this->posZ, 0.0, 0.0, 0.0, 0);
	} else {
		this->remove();
		this->explode();
	}
}
float PrimedTnt::getShadowRadius() {
	return 0;
}
float PrimedTnt::getShadowHeightOffs() {
	return 0;
}
bool_t PrimedTnt::isPickable() {
	return !this->isDead;
}
int32_t PrimedTnt::getEntityTypeId() const {
	return 65;
}
void PrimedTnt::readAdditionalSaveData(CompoundTag* a2) {
	this->ticksUntilExplode = a2->getByte("Fuse");
}
void PrimedTnt::addAdditonalSaveData(CompoundTag* a2) {
	a2->putByte("Fuse", this->ticksUntilExplode);
}
