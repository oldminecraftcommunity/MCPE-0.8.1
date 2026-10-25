#pragma once
#include <IConfigListener.hpp>
#include <gui/GuiComponent.hpp>
#include <util/Random.hpp>
#include <rendering/MeshBuffer.hpp>
#include <input/ITurnInput.hpp>
#include <AppPlatform.hpp>
#include <util/GuiMessage.hpp>

struct Gui : GuiComponent, IConfigListener, AppPlatform::Listener{
	static float InvGuiScale; //0.333333
	static float GuiScale;
	static const float DropTicks; //40.0

	float field_10;
	std::string field_14;
	int32_t field_18;
	std::vector<GuiMessage> chatMessages;
	Random randomInst;
	struct Minecraft* minecraftInst;
	int32_t field_9FC;
	float field_A00;
	std::string nowPlayingMessage;
	int32_t nowPlayingLeft;
	bool field_A0C;
	float field_A10;
	bool invUpdated;
	int32_t field_A18, field_A1C;
	double field_A20;
	int32_t field_A28;
	int32_t slotsAmount;
	MeshBuffer outerBreakRingMesh, innerBreakRingMesh;
	float slotDropCounter;
	int32_t slotToDrop;
	std::string tipMessage;
	float tipTimeLeft, tipMessageLength;
	bool field_A94;

	static float floorAlignToScreenPixel(float);

	Gui(struct Minecraft* mc);
	void addMessage(const std::string&, const std::string&, int32_t);
	float cubeSmoothStep(float, float, float);
	void displayClientMessage(const std::string&);
	void flashSlot(int32_t);
	int32_t getNumSlots();
	struct RectangleArea getRectangleArea(int32_t);
	int32_t getSlotIdAt(int32_t, int32_t);
	int32_t getSlotPos(int32_t, int32_t&, int32_t&);
	void handleClick(int32_t, int32_t, int32_t);
	void handleKeyPressed(int32_t);
	void inventoryUpdated();
	bool_t isInside(int32_t, int32_t);
	static int32_t itemCountItoa(char_t*, int32_t);
	void onLevelGenerated();
	void postError(int32_t);
	void render(float, bool_t, int32_t, int32_t);
	void renderBubbles();
	void renderChatMessages(int32_t, int32_t, uint32_t, bool_t, struct Font*);
	void renderDebugInfo(void);
	void renderHearts();
	void renderOnSelectItemNameText(int32_t, struct Font*, int32_t);
	void renderProgressIndicator(bool_t, int32_t, int32_t, float);
	void renderSleepAnimation(int32_t, int32_t);
	void renderSlot(int32_t, int32_t, int32_t, float);
	void renderSlotText(const struct ItemInstance*, float, float, bool_t, bool_t);
	void renderToolBar(float, float);
	void renderVignette(float, int32_t, int32_t);
	void resetItemNameOverlay();
	void setNowPlaying(const std::string&);
	void setScissorRect(const struct IntRectangle&);
	void showTipMessage(const std::string&);
	void texturesLoaded(struct Textures*);
	void tick();
	void tickItemDrop(void);
	virtual ~Gui();

	virtual void onAppSuspended();
	virtual void onConfigChanged(const struct Config&);

};
