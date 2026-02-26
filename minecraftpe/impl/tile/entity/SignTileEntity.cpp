#include <tile/entity/SignTileEntity.hpp>
#include <level/Level.hpp>
#include <tile/Tile.hpp>
#include <network/packet/EntityDataPacket.hpp>
#include <util/Util.hpp>

SignTileEntity::SignTileEntity()
	: TileEntity(4) {
	this->field_6C = -1;
	this->editable = 1;
	this->renderId = TER_SIGN;
}
bool_t SignTileEntity::isEditable() {
	return this->editable;
}
void SignTileEntity::setEditable(bool_t a2) {
	this->editable = a2;
}
SignTileEntity::~SignTileEntity() {
}
bool_t SignTileEntity::shouldSave() {
	return 1;
}
void SignTileEntity::load(struct CompoundTag* a2) {
	this->editable = 0;
	TileEntity::load(a2);
	this->textLines[0] = a2->getString("Text1");
	this->textLines[1] = a2->getString("Text2");
	this->textLines[2] = a2->getString("Text3");
	this->textLines[3] = a2->getString("Text4");

	for(int32_t i = 0; i < 4; ++i) {
		if(Util::utf8len(this->textLines[i]) > 15) {
			this->textLines[i] = Util::utf8substring(this->textLines[i], 0, 15);
		}
	}
}
bool_t SignTileEntity::save(struct CompoundTag* a2) {
	if(TileEntity::save(a2)) {
		a2->putString("Text1", this->textLines[0]);
		a2->putString("Text2", this->textLines[1]);
		a2->putString("Text3", this->textLines[2]);
		a2->putString("Text4", this->textLines[3]);
		return 1;
	}
	return 0;
}
void SignTileEntity::setLevelAndPos(struct Level* level, int32_t x, int32_t y, int32_t z) {
	TileEntity::setLevelAndPos(level, x, y, z);
	if(level->getTile(x, y, z) != Tile::sign->blockID) {
		this->setRemoved();
	}
}
Packet* SignTileEntity::getUpdatePacket() {
	CompoundTag tag;
	this->save(&tag);
	EntityDataPacket* pk = new EntityDataPacket(this->posX, this->posY, this->posZ, &tag);
	return pk;
}

void SignTileEntity::onUpdatePacket(struct CompoundTag* a2) {
	this->load(a2);
}
float SignTileEntity::getShadowRadius() {
	if(this->getTile() == Tile::sign) return 0.2;
	return 0;
}
