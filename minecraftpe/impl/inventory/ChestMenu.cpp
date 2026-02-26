#include <inventory/ChestMenu.hpp>
#include <tile/entity/ChestTileEntity.hpp>

ChestMenu::ChestMenu(ChestTileEntity* a2)
	: ContainerMenu(a2, a2->id) {
	this->field_24 = a2;
	this->field_28 = -1;
	if(a2->pair) {
		this->field_28 = a2->pair->id;
	}
}

ChestMenu::~ChestMenu() {
}
bool_t ChestMenu::tileEntityDestroyedIsInvalid(int32_t a2) {
	return this->field_1C == a2 || this->field_28 == a2;
}
