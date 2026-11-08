#include <entity/PrimedTnt.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>
#include <nbt/CompoundTag.hpp>

PrimedTnt::PrimedTnt(Level* a2)
	: Entity(a2) {
	this->ticksUntilExplode = 80;
	this->entityRenderId = TNT;
	this->field_FC = 1;
	this->setSize(0.98f, 0.98f);
	this->ridingHeight = this->entityHeight * 0.5f;
}
PrimedTnt::PrimedTnt(Level* a2, float x, float y, float z)
	: Entity(a2) {
	this->ticksUntilExplode = 80;
	this->entityRenderId = TNT;
	this->field_FC = 1;
	this->setSize(0.98f, 0.98f);
	this->ridingHeight = this->entityHeight * 0.5f;

	this->setPos(x, y, z);
	float v9 = (Mth::random() * Mth::PI) * 2 * Mth::DEGRAD;
	this->motionX = Mth::sin(v9) * -0.02f;
	this->motionY = 0.2f;
	this->motionZ = Mth::cos(v9) * -0.02f;
	this->prevX = x;
	this->prevY = y;
	this->prevZ = z;
	this->field_110 = 0;
}
void PrimedTnt::explode() {
	this->level->explode(0, this->posX, this->posY, this->posZ, 3.1f);
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
