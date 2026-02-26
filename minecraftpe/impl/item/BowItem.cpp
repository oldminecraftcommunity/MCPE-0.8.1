#include <item/BowItem.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <entity/Arrow.hpp>
#include <inventory/Inventory.hpp>

BowItem::BowItem(int32_t id)
	: Item(id) {
	this->maxStackSize = 1;
	this->setMaxDamage(384);
	int32_t v29 = 0;
	this->field_10 = 0;
	this->field_C = 3;
	do {
		int32_t v31 = v29++;
		this->textures[v31] = this->getTextureUVCoordinateSet("bow_pulling", v31);
	} while(v29 != 3);
}

float BowItem::_getLaunchPower(int32_t a2) {
	int32_t v2; // r0

	v2 = this->getMaxUseDuration() - a2;
	if((float)((float)((float)((float)((float)v2 / 20.0) + (float)((float)v2 / 20.0)) + (float)((float)((float)v2 / 20.0) * (float)((float)v2 / 20.0))) / 3.0) <= 1.0) {
		return (float)((float)((float)((float)v2 / 20.0) + (float)((float)v2 / 20.0)) + (float)((float)((float)v2 / 20.0) * (float)((float)v2 / 20.0))) / 3.0;
	} else {
		return 1.0;
	}
}

BowItem::~BowItem() {
}
TextureUVCoordinateSet* BowItem::getIcon(int32_t a2, int32_t a3, bool_t a4) {
	if(a3) return &this->textures[a3 - 1];
	return &this->iconUV;
}
ItemInstance* BowItem::use(ItemInstance* a2, Level* a3, Player* a4) {
	if(a4->abilities.instabuild || a4->hasResource(Item::arrow->itemID)) {
		a4->startUsingItem(ItemInstance(*a2), this->getMaxUseDuration());
	}
	return a2;
}
int32_t BowItem::getMaxUseDuration() {
	return 72000;
}
int32_t BowItem::getUseAnimation() {
	return 4;
}
void BowItem::releaseUsing(ItemInstance* a2, Level* a3, Player* a4, int32_t a5) {
	float LaunchPower; // s16
	float f; // r0
	Arrow* v10; // r6
	LaunchPower = this->_getLaunchPower(a5);
	if(LaunchPower >= 0.1) {
		if(!a4->abilities.instabuild) {
			a2->hurtAndBreak(1, a4);
			if(!a2->count) {
				a4->inventory->clearSlot(a4->inventory->selectedSlot);
			}
			a4->inventory->removeResource(Item::arrow->itemID);
		}
		f = Item::random.nextFloat();
		a3->playSound(a4, "random.bow", 1.0, (float)(1.0 / (float)((float)(f * 0.4) + 1.2)) + (float)(LaunchPower * 0.5));
		if(!a3->isClientMaybe) {
			v10 = new Arrow(a3, a4, LaunchPower + LaunchPower);
			if(LaunchPower == 1.0) {
				v10->critical = 1;
			}
			a3->addEntity(v10);
		}
	}
}

int32_t BowItem::getAnimationFrameFor(Mob * a2) {
		int32_t dur = a2->getUseItemDuration();
		if(dur) return (int32_t)(float)((float)(this->_getLaunchPower(dur) * 0.99) * (float)this->field_C) + 1;
		return 0;
	}
