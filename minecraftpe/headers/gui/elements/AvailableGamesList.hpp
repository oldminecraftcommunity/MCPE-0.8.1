#pragma once
#include <gui/elements/ScrolledSelectionList.hpp>
#include <vector>

struct PingedCompatibleServer;
struct AvailableGamesList: ScrolledSelectionList
{
	int32_t selectedItem;
	std::vector<PingedCompatibleServer> servers;
	AvailableGamesList(Minecraft*, int32_t, int32_t);

	virtual ~AvailableGamesList();
	virtual int32_t getNumberOfItems();
	virtual void selectItem(int32_t, bool_t);
	virtual bool_t isSelectedItem(int32_t);
	virtual void renderItem(int32_t, int32_t, int32_t, int32_t, Tesselator&);
	virtual void renderBackground();

};
