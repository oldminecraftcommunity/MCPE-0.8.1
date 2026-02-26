#pragma once
#include <gui/elements/RolledSelectionListV.hpp>
#include <vector>
struct PingedCompatibleServer;
namespace Touch {
	struct AvailableGamesList: RolledSelectionListV
	{
		int32_t field_6C, selectedItem;
		std::vector<PingedCompatibleServer> servers;
		AvailableGamesList(Minecraft* mc, int32_t w, int32_t h);

		virtual ~AvailableGamesList();
		virtual int32_t getNumberOfItems();
		virtual void selectStart(int32_t);
		virtual void selectCancel();
		virtual void selectItem(int32_t, bool_t);
		virtual bool_t isSelectedItem(int32_t);
		virtual void renderItem(int32_t, int32_t, int32_t, int32_t, Tesselator&);
		virtual void renderBackground();
	};
}
