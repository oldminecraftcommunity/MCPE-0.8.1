#include <entity/LocalPlayer.hpp>
#include <Minecraft.hpp>
#include <gui/screens/ChestScreen.hpp>
#include <gui/screens/FurnaceScreen.hpp>
#include <gui/screens/InBedScreen.hpp>
#include <gui/screens/StonecutterScreen.hpp>
#include <gui/screens/TextEditScreen.hpp>
#include <gui/screens/WorkbenchScreen.hpp>
#include <input/KeyboardInput.hpp>
#include <inventory/Inventory.hpp>
#include <math/Mth.hpp>
#include <math/SmoothFloat.hpp>
#include <nbt/CompoundTag.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/AnimatePacket.hpp>
#include <network/packet/ContainerSetSlotPacket.hpp>
#include <network/packet/MovePlayerPacket.hpp>
#include <network/packet/PlayerArmorEquipmentPacket.hpp>
#include <network/packet/PlayerInputPacket.hpp>
#include <network/packet/SetEntityLinkPacket.hpp>
#include <network/packet/SetHealthPacket.hpp>
#include <tile/Tile.hpp>
#include <tile/entity/TileEntity.hpp>
#include <tile/material/Material.hpp>
#include <item/Item.hpp>
#include <input/Keyboard.hpp>
#include <network/packet/DropItemPacket.hpp>
#include <network/packet/PlayerActionPacket.hpp>
#include <network/packet/ContainerClosePacket.hpp>
#include <entity/player/User.hpp>
#include <network/packet/EntityEventPacket.hpp>
#include <perf/Stopwatch.hpp>
#include <network/packet/PlayerEquipmentPacket.hpp>
#include <level/Level.hpp>

LocalPlayer::LocalPlayer(Minecraft* a2, Level* a3, User* a4, int32_t a5, bool_t a6)
	: Player(a3, a6)
	, inventoryMenu(this->inventory) {
	this->moveInput = 0;
	this->allowAutojump = 1;
	this->minecraft = a2;
	this->currentItemID = -1;
	this->currentItemMeta = -1;
	this->field_DCC = 1000000.0;
	this->lastSentArmorHash = 0;
	this->dimension = a5;
	this->_init();
	if(a4) {
		this->username = a4->username;
	}
	this->inventoryMenu.setListener(this);
}
void LocalPlayer::_init() {
	this->field_DC0 = 0;
	this->flyToggleCounter = 0;
	this->field_D84 = 0;
	this->field_D88 = 0;
	this->field_D8C = 0;
	this->field_D8D = 0;
	ItemInstance* sel = this->inventory->getSelected();
	this->currentItemID = sel ? sel->getId() : 0;
	this->currentItemMeta = sel ? sel->getAuxValue() : 0;
}
void LocalPlayer::calculateFlight(float a2, float a3, float a4) {
	Minecraft* minecraft; // r2
	float v6;			  // s15
	float v9;			  // s18

	minecraft = this->minecraft;
	v6 = minecraft->options.field_F4;
	if(Keyboard::_states[103] == 1) {
		v9 = 0.2;
	} else {
		v9 = 0.0;
	}
	if(Keyboard::_states[103] == 1) {
		v9 = v6 * v9;
	}
	if(Keyboard::_states[102] == 1) {
		v9 = -0.2;
	}
	if(Keyboard::_states[102] == 1) {
		v9 = v6 * v9;
	}
	this->field_D90 = this->field_D9C.getNewDeltaValue(a2 * v6, minecraft->options.sensitity * 0.35) * 10.0;
	this->field_D94 = this->field_DA8.getNewDeltaValue(v9, this->minecraft->options.sensitity * 0.35) * 10.0;
	this->field_D98 = this->field_DB4.getNewDeltaValue(a4 * v6, this->minecraft->options.sensitity * 0.35) * 10.0;
}
float LocalPlayer::getFieldOfViewModifier(){
	float v1; // s18
	float v3; // s17
	float v4; // s17
	float v5; // s15
	float v6; // s15

	v1 = 1.1;
	if ( !this->abilities.flying )
	{
		v1 = 1.0;
	}
	v3 = this->getBaseSpeed();
	v4 = v1
		 * (float)((float)((float)((float)(v3 * this->getWalkingSpeedModifier()) / 0.1)
						   + 1.0)
				   * 0.5);
	if ( this->isUsingItem() && Item::bow == this->getUseItem()->itemClass )
	{
		if ( Item::bow )
		{
			v6 = (float)this->getTicksUsingItem() / 20.0;
			if ( v6 > 1.0 )
			{
				v5 = 1.0;
			}
			else
			{
				v5 = v6 * v6;
			}
			return v4 * (float)(1.0 - (float)(v5 * 0.15));
		}
	}
	return v4;
}
void LocalPlayer::hurtTo(int32_t a2){
	int32_t health; // r2
	int32_t v3; // r3
	int32_t v5; // r2

	health = this->health;
	v3 = health - a2;
	if ( health - a2 > 0 )
	{
		this->prevHealthMaybe = health;
		v5 = this->field_118;
		this->field_BC0 = v3;
		this->field_DC = v5;
		this->minecraft->player->hasArmorMaybe = 1;
		this->actuallyHurt(v3);
		this->minecraft->player->hasArmorMaybe = 0;
		this->field_148 = 10;
		this->hurtTime = 10;
	}
	else
	{
		this->health = a2;
	}
}
bool_t LocalPlayer::isSolidTile(int32_t a2, int32_t a3, int32_t a4) {
	int32_t v4; // r0

	v4 = this->level->getTile(a2, a3, a4);
	if(v4 <= 0) {
		return 0;
	}
	return Tile::tiles[v4]->material->isSolid();
}
void LocalPlayer::releaseAllKeys() {
	if(this->moveInput) {
		this->moveInput->releaseAllKeys();
	}
}
void LocalPlayer::respawn() {
	this->minecraft->respawnPlayer();
}
void LocalPlayer::sendPosition() {
	MovePlayerPacket v18(this->entityId, this->posX, this->posY - this->ridingHeight, this->posZ, this->pitch, this->yaw, this->headYaw);

	this->minecraft->rakNetInstance->send(v18);
	this->field_BC8 = this->posX;
	this->field_BCC = this->posY;
	this->field_BD0 = this->posZ;
	this->field_DCC = this->headYaw;
	this->field_BD4 = this->pitch;
	this->field_BD8 = this->yaw;
	if(this->isRiding()) {
		PlayerInputPacket v17(this->moveStrafe, this->moveStrafe, this->isJumping, this->isSneaking());
		this->minecraft->rakNetInstance->send(v17);
	}
}
void LocalPlayer::setKey(int32_t a2, bool_t a3) {
	this->moveInput->setKey(a2, a3);
}
void LocalPlayer::updateArmorTypeHash() {
	int32_t hash = this->getArmorTypeHash();
	if(hash != this->lastSentArmorHash) {
		PlayerArmorEquipmentPacket v3(this);
		this->minecraft->rakNetInstance->send(v3);
		this->lastSentArmorHash = hash;
	}
}

LocalPlayer::~LocalPlayer() {
}
void LocalPlayer::reset() {
	Player::reset();
	this->_init();
}
void LocalPlayer::move(float a2, float a3, float a4) {
	Minecraft* minecraft; // r6
	float field_BC; // r6
	int32_t v9; // r3
	float posX; // s19
	float posZ; // s20
	float v12; // s18
	float v13; // s21
	int32_t v14; // r6
	Tile* v15; // r0
	int32_t v16; // r6
	float v17; // s18
	int32_t v18; // r7
	int32_t v19; // r8
	int32_t v20; // r6

	minecraft = this->minecraft;
	if(this == minecraft->player && minecraft->options.enableNoclipMaybe) {
		this->noclip = 1;
		field_BC = this->field_BC;
		this->calculateFlight(a2, a3, a4);
		this->fallDistance = 0.0;
		this->motionY = 0.0;
		Entity::move(this->field_D90, this->field_D94, this->field_D98);
		this->onGround = 1;
		this->field_BC = field_BC;
	} else {
		v9 = this->field_DC0;
		if(v9 > 0) {
			this->field_DC0 = v9 - 1;
			this->moveInput->jumpingMaybe = 1;
		}
		posX = this->posX;
		posZ = this->posZ;
		Entity::move(a2, a3, a4);
		v12 = this->posX;
		v13 = this->posZ;
		if(this->field_DC0 <= 0 && this->allowAutojump && !this->isRiding()) {
			v16 = Mth::floor(posX + posX);
			if(v16 != Mth::floor(v12 + v12) || (v14 = Mth::floor(posZ + posZ), v14 != Mth::floor(v13 + v13))) {
				v17 = sqrt((float)((float)(a4 * a4) + (float)(a2 * a2)));
				v18 = Mth::floor((float)(a2 / v17) + this->posX);
				v19 = Mth::floor((float)(a4 / v17) + this->posZ);
				v20 = this->level->getTile(v18, (int32_t)(float)(this->posY - 1.0), v19);
				if(this->isSolidTile(v18, (int32_t)(float)(this->posY - 1.0), v19) && !this->isSolidTile(v18, (int32_t)this->posY, v19) && !this->isSolidTile(v18, (int32_t)(float)(this->posY + 1.0), v19) && v20 != Tile::fence->blockID && v20 != Tile::fenceGate->blockID && v20 != Tile::stoneSlabHalf->blockID && v20 != Tile::woodSlabHalf->blockID && v20 != Tile::trapdoor->blockID && v20 != Tile::sign->blockID && v20 != Tile::wallSign->blockID && v20 != Tile::cobbleWall->blockID && v20 != Tile::woolCarpet->blockID && v20 != Tile::web->blockID) {
					v15 = Tile::tiles[v20];
					if(v15) {
						if(v15->getRenderShape() != 10) {
							this->field_DC0 = 1;
						}
					}
				}
			}
		}
	}
}
#include <fh_frameanimod.hpp>

char_t _D6E065B0 = 0;
void LocalPlayer::tick() {
	Player::tick();

	if(animstate.active) {
		animstate.ticks += 1;
		Frame* f = &selectedAnimation->frames[animstate.frame];

		if(animstate.ticks > f->duration) {
			animstate.ticks = 0;
			++animstate.frame;
		}
		if(animstate.frame >= selectedAnimation->frames.size()) {
			animstate.active = 0;
			selectedAnimation = 0;

		}
	}

	if(this->isJumping && this->isRiding()) {
		this->ride(0);
		SetEntityLinkPacket v24(0, this->entityId, this->ridingAt ? this->ridingAt->entityId : 0);
		this->minecraft->rakNetInstance->send(v24);
	}

	if(!this->item.isNull()) {
		ItemInstance* sel = this->inventory->getSelected();
		if(sel && *sel == this->item) {
			this->useItemDuration = this->useItemDuration - 1;
			if(this->useItemDuration <= 25) {
				int32_t v6 = this->useItemDuration << 30;
				if(v6 == 0) {
					this->spawnEatParticles(sel, 5);
				}
			}
			if(this->useItemDuration == 0) {
				if(this->level->isClientMaybe) {
					EntityEventPacket v23(this->entityId, 9);
					this->level->rakNetInstance->send(v23);
				} else {
					this->completeUsingItem();
				}
			}
		} else {
			this->stopUsingItem();
		}
	}
	if(this->minecraft->isOnline()) {
		if(this->isRiding() || fabsf(this->posX - this->field_BC8) > 0.1 || fabsf(this->posY - this->field_BCC) > 0.01 || fabsf(this->posZ - this->field_BD0) > 0.1 || fabsf(this->field_BD4 - this->pitch) > 1.0 || fabsf(this->field_BD8 - this->yaw) > 1.0 || fabsf(this->field_DCC - this->headYaw) > 1.0) {
			this->sendPosition();
		}
		if(this->level->isClientMaybe) {
			static Stopwatch sw; //no name
			sw.start();
			this->inventoryMenu.broadcastChanges();
			sw.stop();
			for(int32_t i = 0; i != 4; ++i) {
				ItemInstance& v12 = this->armorSlots[i];
				if(!(v12 == this->field_DD4[i])) {
					this->field_DD4[i] = v12;
					ContainerSetSlotPacket v23(0, 120, i, v12);
					this->minecraft->rakNetInstance->send(v23);
				}
			}
		}
		ItemInstance* sel = this->inventory->getSelected();
		int32_t auxv, id;
		if(sel) {
			if(sel->count <= 0) {
				id = 0;
			} else {
				id = sel->getId();
			}
			if(sel->count > 0) {
				auxv = sel->getAuxValue();
			} else {
				auxv = 0;
			}
		} else {
			id = 0;
			auxv = 0;
		}

		if((this->currentItemID != id) || (this->currentItemMeta != auxv)) {
			this->currentItemID = id;
			this->currentItemMeta = auxv;
			int32_t ls = this->inventory->getLinkedSlot(this->inventory->selectedSlot);
			PlayerEquipmentPacket v23(this->entityId, id, auxv, ls);
			this->minecraft->rakNetInstance->send(v23);
		}
	}
	this->updateArmorTypeHash();
	if(!this->minecraft->currentScreen) {
		if(this->currentContainer) {
			if(!_D6E065B0) {
				this->minecraft->gui.postError(1);
				_D6E065B0 = 1;
			}
		}
	}
}

void LocalPlayer::ride(Entity* a2) {
	Level* level; // r3

	if(a2) {
		if(!this->ridingAt) {
			this->minecraft->gui.showTipMessage("Tap Jump to leave the minecart");
		}
	}
	Player::ride(a2);
	level = this->level;
	if(!level->isClientMaybe) {
		SetEntityLinkPacket v9(0, this->entityId, this->ridingAt ? this->ridingAt->entityId : 0); // [sp+8h] [bp-30h] BYREF
		this->minecraft->rakNetInstance->send(v9);
	}
}
bool_t LocalPlayer::isSneaking() {
	return this->moveInput->sneakingMaybe;
}
void LocalPlayer::causeFallDamage(float a2) {
	int32_t v4; // r6

	v4 = (int32_t)ceil((float)(a2 - 3.0));
	if(v4 > 0 && this->level->isClientMaybe) {
		SetHealthPacket v5(v4 - 64);
		this->minecraft->rakNetInstance->send(v5);
	}
	Mob::causeFallDamage(a2);
}
void LocalPlayer::readAdditionalSaveData(CompoundTag* a2) {
	Player::readAdditionalSaveData(a2);
	this->score = a2->getInt("Score");
}
void LocalPlayer::addAdditonalSaveData(CompoundTag* a2) {
	Player::addAdditonalSaveData(a2);
	a2->putInt("Score", this->score);
}
void LocalPlayer::actuallyHurt(int32_t a2) {
	Screen* currentScreen; // r0

	currentScreen = this->minecraft->currentScreen;
	if(currentScreen) {
		if(currentScreen->closeOnPlayerHurt()) {
			if(this->currentContainer) {
				this->closeContainer();
			} else {
				this->minecraft->setScreen(0);
			}
		}
	}
	Mob::actuallyHurt(a2);
}
void LocalPlayer::aiStep() {
	Minecraft* minecraft;	  // r3
	KeyboardInput* moveInput; // r0
	Screen* currentScreen;	  // r3
	bool_t jumpingMaybe;	  // r5
	KeyboardInput* v6;		  // r3
	bool_t flying;			  // r2
	float strafeInput;		  // s14
	float forwardInput;		  // s15

	--this->flyToggleCounter;
	--this->field_D84;
	--this->field_D88;
	minecraft = this->minecraft;
	moveInput = this->moveInput;
	currentScreen = minecraft->currentScreen;
	jumpingMaybe = moveInput->jumpingMaybe;
	if(!currentScreen || currentScreen->field_C) {
		moveInput->tick(this);
	}
	v6 = this->moveInput;
	if(v6->sneakingMaybe && this->ySize < 0.2) {
		this->ySize = 0.2;
	}
	this->field_B7C = 1.0;
	if(this->abilities.mayfly) {
		if(!jumpingMaybe && v6->jumpingMaybe) // enable/disable flying
		{
			if(this->flyToggleCounter > 0) {
				flying = this->abilities.flying;
				this->flyToggleCounter = 0;
				this->abilities.flying = !flying;
			} else {
				this->flyToggleCounter = 7;
			}
		}
		if(this->abilities.flying) {
			strafeInput = v6->strafeInput;
			forwardInput = v6->forwardInput;
			if(strafeInput < 0.0) {
				strafeInput = -strafeInput;
			}
			if(forwardInput < 0.0) {
				forwardInput = -forwardInput;
			}
			if(strafeInput > forwardInput) {
				forwardInput = strafeInput;
			}
			if(forwardInput < 0.01) {
				this->field_B7C = 0.75;
			}
			if(v6->field_B) {
				this->motionY = this->motionY + 0.15;
			}
			if(v6->field_C) {
				this->motionY = this->motionY - 0.15;
			}
		}
	}
	if(this->isUsingItem()) {
		this->moveInput->strafeInput = this->moveInput->strafeInput * 0.35;
		this->moveInput->forwardInput = this->moveInput->forwardInput * 0.35;
	}
	Mob::aiStep();
	Player::aiStep();
	this->headYaw = this->yaw;
	if(this->interpolateOnly()) {
		this->updateAi();
	}
}
void LocalPlayer::swing() {
	Mob::swing();
	if(this->field_B6C == -1) {
		AnimatePacket v2(this->entityId, 1);
		v2.packetReliabilityMaybe = PacketReliability::UNRELIABLE;
		v2.packetPriorityMaybe = PacketPriority::MEDIUM_PRIORITY;
		this->minecraft->rakNetInstance->send(v2);
	}
}
void LocalPlayer::updateAi() {
	bool_t v3; // r3

	Player::updateAi();
	this->moveStrafe = this->moveInput->strafeInput;
	this->moveForward = this->moveInput->forwardInput;
	if(moveInput->jumpingMaybe) {
		v3 = 1;
	} else {
		v3 = this->field_DC0 > 0;
	}
	this->isJumping = v3;
}
void LocalPlayer::take(Entity*, int32_t) {
}
void LocalPlayer::drop(const ItemInstance* a2, bool_t a3) {
	if(a2) {
		if(this->level->isClientMaybe) {
			DropItemPacket pk(this->entityId, 0, *a2);
			this->minecraft->rakNetInstance->send(pk);
		} else {
			Player::drop(a2, a3);
		}
	}
}
void LocalPlayer::startCrafting(int32_t, int32_t, int32_t, int32_t a5) {
	if(!this->minecraft->isCreativeMode()) {
		this->minecraft->setScreen(new WorkbenchScreen(a5));
	}
}
void LocalPlayer::startStonecutting(int32_t, int32_t, int32_t) {
	if(!this->minecraft->isCreativeMode()) {
		this->minecraft->setScreen(new StonecutterScreen());
	}
}
void LocalPlayer::openContainer(ChestTileEntity* a2) {
	if(!this->minecraft->isCreativeMode()) {
		this->minecraft->setScreen(new ChestScreen(this, a2));
	}
}
void LocalPlayer::openFurnace(FurnaceTileEntity* a2) {
	if(!this->minecraft->isCreativeMode()) {
		this->minecraft->setScreen(new FurnaceScreen(this, a2));
	}
}
void LocalPlayer::displayClientMessage(const std::string& a2) {
	this->minecraft->gui.displayClientMessage(a2);
}
void LocalPlayer::animateRespawn() {
}
int32_t LocalPlayer::startSleepInBed(int32_t a2, int32_t a3, int32_t a4) {
	int32_t r = Player::startSleepInBed(a2, a3, a4);
	if(!r) {
		this->minecraft->setScreen(new InBedScreen());
	}
	return r;
}
void LocalPlayer::stopSleepInBed(bool_t a2, bool_t a3, bool_t a4) {
	if(this->level->isClientMaybe) {
		PlayerActionPacket v10(this->entityId, 0, 0, 0, 0, 6);
		this->minecraft->rakNetInstance->send(v10);
	}
	this->minecraft->setScreen(0);
	Player::stopSleepInBed(a2, a3, a4);
}
void LocalPlayer::openTextEdit(TileEntity* a2) {
	if(a2->type == 4) {
		this->minecraft->setScreen(new TextEditScreen((SignTileEntity*)a2));
	}
}
bool_t LocalPlayer::isLocalPlayer() {
	return 1;
}
void LocalPlayer::closeContainer() {
	if(this->level->isClientMaybe) {
		ContainerClosePacket v3(this->currentContainer->field_0);
		this->minecraft->rakNetInstance->send(v3);
	}
	Player::closeContainer();
	this->minecraft->setScreen(0);
}
void LocalPlayer::refreshContainer(BaseContainerMenu*, const std::vector<ItemInstance>) {
}
void LocalPlayer::slotChanged(BaseContainerMenu* a2, int32_t a3, const ItemInstance& a4, bool_t a5) {
	if(this->level->isClientMaybe && a2 == &this->inventoryMenu) {
		ContainerSetSlotPacket v8(0, 0, a3, a4);
		this->minecraft->rakNetInstance->send(v8);
	}
}
