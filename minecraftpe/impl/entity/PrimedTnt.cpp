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

void PrimedTnt::tick() {
	this->motionY -= 0.04f;
	this->prevX = this->posX;
	this->prevY = this->posY;
	this->prevZ = this->posZ;

	this->move(this->motionX, this->motionY, this->motionZ);

	this->motionX *= 0.98f;
	this->motionY *= 0.98f;
	this->motionZ *= 0.98f;
	if(this->onGround) {
		this->motionX *= 0.7f;
		this->motionZ *= 0.7f;
		this->motionY *= -0.5f;
	}
	this->ticksUntilExplode -= 1;
	if(!this->level->isClient && this->ticksUntilExplode <= 0){
		this->remove();
		this->explode();
	}else{
		this->level->addParticle(PT_SMOKE, this->posX, this->posY + 0.5f, this->posZ, 0, 0, 0, 0);
	}
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
