#include <inventory/FurnaceMenu.hpp>
#include <tile/entity/FurnaceTileEntity.hpp>
#include <inventory/IContainerListener.hpp>

FurnaceMenu::FurnaceMenu(FurnaceTileEntity* a2)
	: BaseContainerMenu(2) {
	this->tileEntity = a2;
	this->field_20 = 0;
	this->field_24 = 0;
	this->field_28 = 0;
	this->field_1C = a2->id;
}

FurnaceMenu::~FurnaceMenu() {
}
std::vector<ItemInstance> FurnaceMenu::getItems() {
	std::vector<ItemInstance> result;
	for(int32_t i = 0; i < this->tileEntity->getContainerSize(); ++i) {
		result.push_back(*this->tileEntity->getItem(i));
	}
	return result;
}
void FurnaceMenu::setSlot(int32_t a2, ItemInstance* a3) {
	this->tileEntity->setItem(a2, a3);
}
void FurnaceMenu::setData(int32_t a2, int32_t a3) {
	if(a2) {
		if(a2 == 1) {
			this->tileEntity->burnTime = a3;
		} else if(a2 == 2) {
			this->tileEntity->field_6C = a3;
		}
	} else {
		this->tileEntity->cookTime = a3;
	}
}
void FurnaceMenu::setListener(IContainerListener* a2) {
	BaseContainerMenu::setListener(a2);
	if(a2) {
		a2->setContainerData(this, 0, this->tileEntity->cookTime);
		a2->setContainerData(this, 1, this->tileEntity->burnTime);
		a2->setContainerData(this, 2, this->tileEntity->field_6C);
	}
}
void FurnaceMenu::broadcastChanges(){
	IContainerListener *containerListener; // r0
	int32_t cookTime; // r3
	int32_t burnTime; // r3
	int32_t v5; // r3

	BaseContainerMenu::broadcastChanges();
	containerListener = this->containerListener;
	if ( containerListener )
	{
		cookTime = this->tileEntity->cookTime;
		if ( cookTime != this->field_20 )
		{
			containerListener->setContainerData(
				this,
				0,
				cookTime);
			this->field_20 = this->tileEntity->cookTime;
		}
		burnTime = this->tileEntity->burnTime;
		if ( burnTime != this->field_24 )
		{
			this->containerListener->setContainerData(
				this,
				1,
				burnTime);
			this->field_24 = this->tileEntity->burnTime;
		}
		v5 = this->tileEntity->field_6C;
		if ( v5 != this->field_28 )
		{
			this->containerListener->setContainerData(
				this,
				2,
				v5);
			this->field_28 = this->tileEntity->field_6C;
		}
	}
}
bool_t FurnaceMenu::tileEntityDestroyedIsInvalid(int32_t a2) {
	return a2 == this->field_1C;
}
