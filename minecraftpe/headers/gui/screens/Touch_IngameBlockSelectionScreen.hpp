#pragma once
#include <gui/Screen.hpp>
#include <gui/buttons/Touch_THeader.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/pane/Touch_IInventoryPaneCallback.hpp>
namespace Touch {
	struct InventoryPane;

	struct IngameBlockSelectionScreen: Screen, Touch::IInventoryPaneCallback
	{
		int32_t field_58;
		int8_t field_5C, field_5D, field_5E, field_5F;
		Touch::InventoryPane* field_60;
		Touch::THeader selectBlocksHeader;
		Touch::TButton backButton, craftButton, armorButton, menuButton;
		int32_t field_178, field_17C, field_180, field_184;
		int32_t field_188, field_18C, field_190, field_194;

		IngameBlockSelectionScreen();
		int32_t getSlotPosX(int32_t);
		int32_t getSlotPosY(int32_t);
		void renderDemoOverlay();

		virtual ~IngameBlockSelectionScreen();
		virtual void render(int32_t, int32_t, float);
		virtual void init();
		virtual void setupPositions();
		virtual void tick();
		virtual void removed();
		virtual bool_t hasClippingArea(IntRectangle&);
		virtual void buttonClicked(Button*);
		virtual void mouseClicked(int32_t, int32_t, int32_t);
		virtual void mouseReleased(int32_t, int32_t, int32_t);
		virtual bool_t addItem(const InventoryPane*, int32_t);
		virtual bool_t isAllowed(int32_t);
		virtual std::vector<const ItemInstance*> getItems(const InventoryPane*);
	};
}
