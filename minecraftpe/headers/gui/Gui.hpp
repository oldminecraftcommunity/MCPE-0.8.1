#pragma once
#include <_types.h>
#include <gui/GuiComponent.hpp>
#include <util/Random.hpp>
#include <rendering/MeshBuffer.hpp>
#include <util/area/RectangleArea.hpp>
#include <AppPlatform.hpp>
#include <util/GuiMessage.hpp>

struct Gui : GuiComponent, AppPlatform::Listener{
	static float InvGuiScale; //0.333333
	static float GuiScale;
	static float DropTicks; //40.0

	//int32_t field_8; vt
	//int32_t field_C; vt
	float field_10;
	std::string field_14;
	int32_t field_18;
	std::vector<GuiMessage> chatMessages;
	Random randomInst;
	struct Minecraft* minecraftInst;
	int32_t field_9FC;
	float field_A00;
	std::string field_A04;
	int32_t field_A08;
	int8_t field_A0C;
	int8_t al1, al2, al3;
	float field_A10;
	int8_t invUpdated;
	int8_t al4, al5, al6;
	int32_t field_A18, field_A1C, field_A20, field_A28;
	int32_t slotsAmount;
	MeshBuffer meshBuffer1, meshBuffer2;
	float field_A80;
	int32_t field_A84;
	std::string tipMessage;
	float field_A8C, field_A90;
	int8_t field_A94, field_A95, field_A96, field_A97;

	static float floorAlignToScreenPixel(float);

	Gui(struct Minecraft* mc);
	void addMessage(const std::string&, const std::string&, int32_t);
	float cubeSmoothStep(float, float, float);
	void displayClientMessage(const std::string&);
	void flashSlot(int32_t);
	int32_t getNumSlots();
	RectangleArea getRectangleArea(int32_t);
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
