#pragma once
#include <tile/entity/TileEntity.hpp>

struct SignTileEntity: TileEntity
{
	std::string textLines[4];
	int32_t field_6C;
	bool_t editable;
	byte field_71, field_72, field_73;

	SignTileEntity();
	bool_t isEditable();
	void setEditable(bool_t);

	virtual ~SignTileEntity();
	virtual bool_t shouldSave();
	virtual void load(struct CompoundTag*);
	virtual bool_t save(struct CompoundTag*);
	virtual void setLevelAndPos(struct Level*, int32_t, int32_t, int32_t);
	virtual struct Packet* getUpdatePacket();
	virtual void onUpdatePacket(struct CompoundTag*);
	virtual float getShadowRadius();
};
