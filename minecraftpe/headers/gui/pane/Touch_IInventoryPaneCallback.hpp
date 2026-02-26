#pragma once
#include <_types.h>
#include <vector>

struct ItemInstance;
namespace Touch {
	struct InventoryPane;
	struct IInventoryPaneCallback
	{
		virtual ~IInventoryPaneCallback();
		virtual bool_t addItem(const Touch::InventoryPane*, int32_t) = 0;
		virtual bool_t isAllowed(int32_t) = 0;
		virtual std::vector<const ItemInstance*> getItems(const Touch::InventoryPane*) = 0;

	};
}
