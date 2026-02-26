#include <entity/ServerPlayer.hpp>
#include <Minecraft.hpp>
#include <inventory/BaseContainerMenu.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/SetHealthPacket.hpp>
#include <network/packet/ContainerSetSlotPacket.hpp>
#include <network/packet/TakeItemEntityPacket.hpp>
#include <network/packet/AnimatePacket.hpp>
#include <network/packet/ContainerSetDataPacket.hpp>
#include <network/packet/EntityEventPacket.hpp>
#include <network/packet/ContainerOpenPacket.hpp>
#include <tile/entity/FurnaceTileEntity.hpp>
#include <inventory/FurnaceMenu.hpp>
#include <network/packet/SetEntityLinkPacket.hpp>
#include <network/packet/ContainerClosePacket.hpp>
#include <network/packet/ChatPacket.hpp>
#include <network/packet/HurtArmorPacket.hpp>
#include <tile/entity/ChestTileEntity.hpp>
#include <inventory/ChestMenu.hpp>
#include <network/packet/ContainerSetContentPacket.hpp>

ServerPlayer::ServerPlayer(Minecraft* a2, Level* a3)
	: Player(a3, a2->isCreativeMode()) {
	this->minecraft = a2;
	this->lastSentHealth = -999;
	this->field_D60 = 1;
	this->field_CB4 = 1;
	this->stepHeight = 0;
}
void ServerPlayer::disconnect() {
	Entity* rider; // r0

	rider = this->rider;
	if(rider) {
		rider->ride(this);
	}
	if(this->isSleeping()) {
		this->stopSleepInBed(1, 0, 0);
	}
}
void ServerPlayer::doCloseContainer() {
	this->setContainerMenu(0);
}
void ServerPlayer::nextContainerCounter() {
	int32_t v1; // r3

	v1 = this->field_D60 + 1;
	if(v1 > 99) {
		v1 = 1;
	}
	this->field_D60 = v1;
}
void ServerPlayer::setContainerMenu(BaseContainerMenu* a2) {
	if(this->currentContainer != a2) {
		if(this->currentContainer) {
			delete this->currentContainer;
		}
		this->currentContainer = a2;
		if(a2) {
			a2->field_0 = this->field_D60;
			this->currentContainer->setListener(this);
		}
	}
}
void ServerPlayer::setPlayerInput(float a2, float a3, bool_t a4, bool_t a5) {
	if(this->ridingAt) {
		if(a2 >= -1.0 && a2 <= 1.0) {
			this->moveStrafe = a2;
		}
		if(a3 >= -1.0 && a3 <= 1.0) {
			this->moveForward = a3;
		}
		this->isJumping = a4;
		this->setSneaking(a5);
	}
}

ServerPlayer::~ServerPlayer() {
	this->setContainerMenu(0);
}
void ServerPlayer::tick() {
	Player::tick();
	if(!this->item.isNull()) {
		--this->useItemDuration;
	}
	if(this->currentContainer) {
		this->currentContainer->broadcastChanges();
	}
	if(this->health != this->lastSentHealth) {
		this->lastSentHealth = this->health;
		SetHealthPacket pk(this->health);
		this->minecraft->rakNetInstance->send(this->rakNetGUID, pk);
	}
	this->pushEntities();
}
void ServerPlayer::ride(Entity* a2) {
	Player::ride(a2);
	SetEntityLinkPacket v6(0, this ? this->entityId : 0, this->ridingAt ? this->ridingAt->entityId : 0);
	this->minecraft->rakNetInstance->send(v6);
}
void ServerPlayer::aiStep() {
	this->updateAttackAnim();
	Player::aiStep();
}
void ServerPlayer::hurtArmor(int32_t a2) {
	HurtArmorPacket v4(a2);
	this->minecraft->rakNetInstance->send(this->rakNetGUID, v4);
}
bool_t ServerPlayer::hasResource(int32_t) {
	return 1;
}
void ServerPlayer::completeUsingItem() {
	EntityEventPacket pk(this->entityId, 9);
	this->minecraft->rakNetInstance->send(this->rakNetGUID, pk);
	Player::completeUsingItem();
}
void ServerPlayer::take(Entity* a2, int32_t a3) {
	TakeItemEntityPacket v9(this->entityId, a2->entityId);
	this->minecraft->rakNetInstance->send(v9);
	Player::take(a2, a3);
}
void ServerPlayer::openContainer(ChestTileEntity* a2) {
	this->nextContainerCounter();
	int32_t v4 = this->field_D60;
	int8_t v5 = a2->getContainerSize();
	int32_t posZ = a2->posZ;
	int32_t posX = a2->posX;
	int32_t posY = a2->posY;
	int8_t v9 = v5;
	ContainerOpenPacket v14(v4, 0, v9, posX, posY, posZ);
	this->minecraft->rakNetInstance->send(v14);
	this->setContainerMenu(new ChestMenu(a2));
}
void ServerPlayer::openFurnace(FurnaceTileEntity* a2) {
	this->nextContainerCounter();
	ContainerOpenPacket v13(this->field_D60, 2, a2->getContainerSize(), a2->posX, a2->posY, a2->posZ);
	this->minecraft->rakNetInstance->send(this->rakNetGUID, v13);
	this->setContainerMenu(new FurnaceMenu(a2));
}
void ServerPlayer::displayClientMessage(const std::string& a2) {
	ChatPacket v5(a2, 1);
	this->minecraft->rakNetInstance->send(this->rakNetGUID, v5);
}
void ServerPlayer::stopSleepInBed(bool_t a2, bool_t a3, bool_t a4) {
	if(this->isSleeping()) {
		AnimatePacket v8(this->entityId, 3);
	}
	Player::stopSleepInBed(a2, a3, a4);
}
void ServerPlayer::closeContainer() {
	ContainerClosePacket v3(this->currentContainer->field_0);
	this->minecraft->rakNetInstance->send(this->rakNetGUID, v3);
	this->doCloseContainer();
}
void ServerPlayer::setContainerData(BaseContainerMenu* a2, int32_t a3, int32_t a4) {
	ContainerSetDataPacket v10(a3, a4, a2->field_0);
	this->minecraft->rakNetInstance->send(this->rakNetGUID, v10);
}
void ServerPlayer::slotChanged(BaseContainerMenu* a2, int32_t a3, const ItemInstance& a4, bool_t a5){
	int32_t v8; // r8

	if ( !a5 )
	{
		v8 = a2->field_0;
		ContainerSetSlotPacket v9(0, v8, a3, a4); // [sp+4h] [bp-44h] BYREF
		this->minecraft->rakNetInstance->send(this->rakNetGUID, v9);
	}
}
void ServerPlayer::refreshContainer(BaseContainerMenu* a2, const std::vector<ItemInstance>& a3) {
	//TODO check
	ContainerSetContentPacket v10(a2->field_0, a2->getItems(), 0); //inlined
	this->minecraft->rakNetInstance->send(v10);
}
