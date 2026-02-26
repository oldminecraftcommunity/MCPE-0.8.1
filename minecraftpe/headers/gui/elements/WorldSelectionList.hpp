#pragma once
#include <gui/elements/RolledSelectionListH.hpp>
#include <level/LevelSummary.hpp>
#include <vector>

struct WorldSelectionList: RolledSelectionListH
{
	float field_5C, field_60, field_64, field_68;
	int32_t field_6C, field_70;
	std::vector<LevelSummary> field_74;
	std::vector<std::vector<std::string>> field_80;
	std::vector<std::string> field_8C;
	int8_t field_98, field_99, field_9A, field_9B;
	LevelSummary field_9C;
	int32_t field_B4, field_B8, field_BC, field_C0;

	WorldSelectionList(Minecraft*, int32_t, int32_t);
	void commit();
	void stepLeft();
	void stepRight();
	void tweenInited();

	virtual ~WorldSelectionList();
	virtual int32_t capXPosition();
	virtual void tick();
	virtual int32_t getNumberOfItems();
	virtual void selectItem(int32_t, bool_t);
	virtual bool_t isSelectedItem(int32_t);
	virtual float getPos(float);
	virtual void touched();
	virtual void renderItem(int32_t, int32_t, int32_t, int32_t, Tesselator&);
	virtual void renderBackground();

};
