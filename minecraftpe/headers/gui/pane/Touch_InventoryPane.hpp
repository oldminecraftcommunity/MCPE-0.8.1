#pragma once
#include <gui/pane/ScrollingPane.hpp>
#include <AppPlatform.hpp>
#include <rendering/MeshBuffer.hpp>
#include <rendering/entity/ItemRenderChunkType.hpp>

struct ItemInstance;
struct Tesselator;
struct Minecraft;
namespace Touch {
	struct IInventoryPaneCallback;
	struct InventoryPane: ScrollingPane, AppPlatform::Listener
	{
		IntRectangle field_228;
		int32_t field_238;
		RectangleArea* field_23C;
		Touch::IInventoryPaneCallback* callback;
		Minecraft* minecraft;
		int32_t field_248, field_24C, field_250, field_254;
		float field_258;
		int32_t field_25C, invTicker, field_264;
		bool_t renderDecorations;
		int8_t field_269, field_26A, field_26B;
		MeshBuffer field_26C, field_294, field_2BC;
		int32_t field_2E4, field_2E8, field_2EC, field_2F0;
		int8_t field_2F4, field_2F5, field_2F6, field_2F7;

		InventoryPane(Touch::IInventoryPaneCallback*, Minecraft*, const IntRectangle&, int32_t, float, int32_t, int32_t, int32_t, bool_t);
		void buildInventoryItemsChunk(ItemRenderChunkType);
		void drawScrollBar(ScrollBar&);
		void renderSelectedItem(std::vector<ScrollingPane::GridItem>&, std::vector<const ItemInstance*>, Tesselator&, ScrollingPane::GridItem*&, float&, float&);
		void setRenderDecorations(bool_t);
		void tick();

		virtual ~InventoryPane();
		virtual void renderBatch(std::vector<ScrollingPane::GridItem>&, float, float, float);
		virtual bool_t onSelect(int32_t, bool_t);
		virtual void refreshItems();
		virtual void onAppSuspended();
		virtual void onAppResumed();
	};
}
