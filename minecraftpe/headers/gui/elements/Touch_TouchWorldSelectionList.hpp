#pragma once
#include <gui/elements/RolledSelectionListH.hpp>
#include <vector>
#include <level/LevelSummary.hpp>

namespace Touch {
	struct TouchWorldSelectionList: RolledSelectionListH
	{
		float field_5C, field_60, field_64, field_68;
		int32_t selectedItem;
		int8_t field_70, field_71, field_72, field_73;
		int32_t field_74;
		std::vector<struct LevelSummary> field_78;
		std::vector<std::vector<std::string>> field_84;
		std::vector<std::string> field_90;
		int8_t field_9C, field_9D, field_9E, field_9F;
		LevelSummary field_A0;
		int32_t field_B8, field_BC, field_C0, field_C4, field_C8;

		TouchWorldSelectionList(struct Minecraft*, int32_t, int32_t);
		void commit(void);
		void stepLeft(void);
		void stepRight(void);
		void tweenInited(void);

		virtual ~TouchWorldSelectionList();
		virtual bool_t capXPositon();
		virtual void tick();
		virtual int32_t getNumberOfItems();
		virtual void selectStart(int32_t, int32_t, int32_t);
		virtual void selectCancel();
		virtual void selectItem(int32_t, bool_t);
		virtual bool_t isSelectedItem(int32_t);
		virtual float getPos(float);
		virtual void touched();
		virtual void renderItem(int32_t, int32_t, int32_t, int32_t, Tesselator&);
		virtual void renderBackground();
	};
}
