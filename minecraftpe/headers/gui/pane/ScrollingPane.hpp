#pragma once
#include <gui/GuiComponent.hpp>
#include <util/IntRectangle.hpp>
#include <util/area/RectangleArea.hpp>
#include <vector>
#include <gui/elements/ScrollBar.hpp>
#include <Timer.hpp>
#include <math/Vec3.hpp>

struct ScrollingPane: GuiComponent
{
	struct GridItem
	{
		int32_t field_0, field_4, field_8;
		float field_C, field_10;
		bool_t field_14, field_15, field_16, field_17;
		GridItem();
		GridItem(int32_t f0, int32_t f4, int32_t f8, float fc, float f10);
	};

	int32_t field_4, field_8, field_C, field_10, field_14, field_18;
	float field_1C, field_20, field_24, field_28;
	IntRectangle field_2C, field_3C, field_4C;
	RectangleArea field_5C, field_74;
	std::vector<float> float_vec;
	int32_t field_98, field_9C, field_A0, field_A4;
	int32_t field_A8, field_AC, field_B0, field_B4;
	float field_B8, field_BC, field_C0, field_C4;
	int32_t field_C8, field_CC;
	float field_D0;
	int32_t field_D4, field_D8;
	int8_t field_DC, field_DD, field_DE, field_DF;
	Vec3 _contentOffset;
	Vec3 field_EC;
	int32_t field_F8;
	float field_FC, field_100, field_104;
	float field_108, field_10C;
	int32_t field_110;
	float field_114, field_118, field_11C;
	float field_120, field_124, field_128, field_12C;
	int32_t field_130;
	float field_134, field_138, field_13C;
	Vec3 field_140;
	float field_14C, field_150, field_154;
	int8_t field_158, field_159, field_15A, field_15B;
	float field_15C;
	int32_t field_160, field_164;
	int32_t field_168, field_16C, field_170;
	int8_t field_174, field_175, field_176, field_177;
	int32_t field_178, field_17C, field_180, field_184;
	int32_t field_188, field_18C, field_190, field_194;
	int32_t field_198, field_19C, field_1A0;
	char_t* field_1A4;
	int32_t field_1A8;
	ScrollBar verticalScrollbar, field_1C4;
	int32_t field_1DC, field_1E0, field_1E4, field_1E8;
	Timer timer;
	int8_t field_210, field_211, field_212, field_213;
	float field_214, field_218;
	int8_t field_21C, field_21D, field_21E, field_21F;


	ScrollingPane(int32_t, const IntRectangle&, const IntRectangle&, int32_t, int32_t, float, const IntRectangle&);
	void _onSelect(int32_t);
	void addDeltaPos(float, float, float, int32_t);
	void adjustContentSize();
	void beginTracking(float, float, int32_t);
	Vec3* contentOffset();
	Vec3* getContentOffset();
	bool_t getGridItemFor_slow(int32_t, ScrollingPane::GridItem&);
	ScrollingPane::GridItem getItemForPos(float, float, bool_t);
	ScrollBar* getVerticleScrollBar();
	void handleUserInput();
	void hideScrollIndicators();
	void onHoldItem();
	bool_t queryHoldTime(int32_t*, int32_t*);
	void refreshPane();
	void render(int32_t, int32_t, float);
	void setContentOffset(Vec3);
	void setContentOffset(float, float);
	void setContentOffsetWithAnimation(Vec3, bool_t);
	void setSelected(int32_t, bool_t);
	void snapContentOffsetToBounds(bool_t);
	void startDecelerationAnimation(bool_t);
	void stepThroughDecelerationAnimation(bool_t);
	void stopDecelerationAnimation();
	void tick();
	void touchesBegan(float, float, int32_t);
	void touchesCancelled(float, float, int32_t);
	void touchesEnded(float, float, int32_t);
	void touchesMoved(float, float, int32_t);
	void translate(float, float);
	void updateHorizontalScrollIndicator();
	void updateScrollFade(ScrollBar&);
	void updateVerticalScrollIndicator();

	virtual ~ScrollingPane();
	virtual void renderBatch(std::vector<ScrollingPane::GridItem>&, float, float, float);
	virtual void renderItem(ScrollingPane::GridItem&, float);
	virtual void didEndDragging();
	virtual void didEndDecelerating();
	virtual void willBeginDecelerating();
	virtual void willBeginDragging();
	virtual bool_t onSelect(int32_t, bool_t);
	virtual void refreshItems();
};
