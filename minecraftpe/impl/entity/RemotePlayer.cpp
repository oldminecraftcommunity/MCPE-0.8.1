#include <entity/RemotePlayer.hpp>
#include <inventory/Inventory.hpp>

RemotePlayer::RemotePlayer(Level* a2, bool_t a3) : Player(a2, a3){
	this->_usingItem = 0;
	this->field_CB4 = 1;
}

RemotePlayer::~RemotePlayer() {
}
void RemotePlayer::tick() {
	const ItemInstance* v3; // r0
	ItemInstance* v4;		// r5

	Player::tick();
	if(!this->_usingItem && this->getSharedFlag(4)) {
		this->_usingItem = 1;
		v3 = this->inventory->getItem(9);
		v4 = (ItemInstance*)v3;
		if(v3) {
			if(v3->itemClass) {
				this->startUsingItem(ItemInstance(*v3), v4->getMaxUseDuration());
			}
		}
	} else if(this->_usingItem && !this->getSharedFlag(4)) {
		this->stopUsingItem();
		this->_usingItem = 0;
	}
	if(!this->item.isNull()) {
		--this->useItemDuration;
	}
}
void RemotePlayer::aiStep() {
	this->updateAttackAnim();
	Player::aiStep();
}
