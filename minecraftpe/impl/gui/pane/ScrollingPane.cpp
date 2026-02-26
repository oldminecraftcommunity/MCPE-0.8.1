#include <gui/pane/ScrollingPane.hpp>
#include <math.h>
#include <utils.h>
#include <input/Mouse.hpp>
#include <string.h>
ScrollingPane::GridItem::GridItem() {
}
ScrollingPane::GridItem::GridItem(int32_t f0, int32_t f4, int32_t f8, float fc, float f10) {
	this->field_0 = f0;
	this->field_4 = f4;
	this->field_8 = f8;
	this->field_C = fc;
	this->field_10 = f10;
}

ScrollingPane::ScrollingPane(int32_t a2, const IntRectangle& a3, const IntRectangle& a4, int32_t a5, int32_t a6, float a7, const IntRectangle& a8)
	: GuiComponent()
	, field_2C(a3)
	, field_3C(a4)
	, field_4C({0, 0, 1, 1})
	, field_5C(1, a3.minX, a3.minY, a3.minX + a3.width, a3.minY + a3.height)
	, field_74(1, a3.minX, a3.minY, a3.minX + a3.width, a3.minY + a3.height)
	, _contentOffset(0, 0, 0)
	, field_EC(0, 0, 0)
	, field_140(0, 0, 0) {
	float v12 = a5;
	this->field_24 = a7;
	this->field_4 = a2;
	this->field_1C = 0;
	this->field_10 = a6;
	this->field_14 = 0;
	this->field_20 = 0;
	this->field_18 = 0;
	this->field_28 = 1.0 / a7;
	this->field_9C = 0;
	this->field_A0 = 0;
	this->field_A4 = 0;
	this->field_B8 = -1;
	this->field_A8 = 0;
	this->field_AC = 0;
	this->field_B0 = 0;
	this->field_98 = -1;
	this->field_D0 = 0.95;
	this->field_BC = 0;
	this->field_C0 = 0;
	this->field_C4 = 0;
	this->field_C8 = 0;
	this->field_CC = 0;
	this->field_DC = 0;
	this->field_DD = 0;
	this->field_DE = 0;
	this->field_DF = 0;
	this->field_FC = 0;
	this->field_100 = 0;
	this->field_104 = 0;
	this->field_108 = 0;
	this->field_10C = 0;
	this->field_110 = 0;
	this->field_114 = 0;
	this->field_118 = 0;
	this->field_11C = 0;
	this->field_128 = 0;
	this->field_12C = 0;
	this->field_130 = 0;
	this->field_134 = 0;
	this->field_138 = 0;
	this->field_13C = 0;
	this->field_14C = 0;
	this->field_150 = 0;
	this->field_154 = 0;
	this->field_160 = a3.minX;
	this->field_164 = a3.minY;
	this->field_168 = a3.width;
	this->field_16C = a3.height;
	this->timer.timeScale = 1;
	this->timer.adjustTime = 1;
	this->verticalScrollbar.color = 0;
	this->field_1C4.color = 0;
	this->field_1DC = 0;
	this->timer.passedTime = 0;
	this->field_1E0 = 0;
	this->timer.ticksPerSecond = 60;
	this->field_174 = 1;
	this->field_184 = -1;
	this->field_188 = -1;
	this->field_1A8 = -1;
	this->verticalScrollbar.field_14 = -1;
	this->field_1C4.field_14 = -1;
	this->field_1E4 = 1;
	this->field_1E8 = 1;
	int32_t timeMs = getTimeMs();
	this->field_210 = 0;
	this->field_211 = 0;
	this->field_21C = 1;
	this->field_214 = -9999;
	this->field_218 = -9999;
	this->timer.lastMs = timeMs;
	this->timer.lastMsSysTime = timeMs;
	this->timer.lastTime = (float)timeMs / 1000;
	float v31, v32, v33, v34;
	if(a8.width <= 0) {
		v31 = a4.minX;
		v32 = a4.minY;
		v33 = a4.width;
		v34 = a4.height;
	} else {
		v31 = a8.minX;
		v32 = a8.minY;
		v33 = a8.width;
		v34 = a8.height;
	}
	this->field_4C.minX = v31;
	this->field_4C.minY = v32;
	this->field_4C.width = v33;
	this->field_4C.height = v34;
	if(a5 <= 0 && (v12 = this->field_2C.width / this->field_4C.width, v12 <= 0)) {
		this->field_8 = 1;
	} else {
		this->field_8 = v12;
	}

	this->field_C = (a6 - 1) / this->field_8 + 1;
	this->float_vec.reserve(0x200 / 4); //TODO check
	this->field_178 = 0;
	this->field_17C = 1;
	this->field_1A4 = new int8_t[a6];
	int32_t v40 = 0;
	while(v40 < a6) {
		this->field_1A4[v40++] = 0;
	}
	int32_t v41 = this->field_2C.minX;
	int32_t v42 = this->field_2C.width;
	this->verticalScrollbar.field_C = 2.3333;
	this->verticalScrollbar.field_8 = 2.3333;
	this->field_1C4.field_C = 2.3333;
	int32_t v43 = v41 + v42;
	int32_t v44 = this->field_2C.minY;
	this->field_1C4.field_8 = 2.3333;
	this->verticalScrollbar.field_4 = 0;
	int32_t v45 = v43;
	int32_t v46 = this->field_2C.height;
	this->field_1C4.field_0 = 0;
	this->verticalScrollbar.field_0 = (float)v45 - 2.3333;
	this->field_1C4.field_4 = (float)(v44 + v46) - 2.3333;
}
void ScrollingPane::_onSelect(int32_t a2) {
	if((this->field_4 & 0x20) != 0) {
		this->field_1A4[a2] = this->onSelect(a2, this->field_1A4[a2] ^ 1);
	} else {
		bool_t v7 = this->onSelect(a2, 1);
		int32_t v8 = this->field_1A8;
		if(a2 != v8) {
			if(v7) {
				this->onSelect(v8, 0);
				this->field_1A8 = a2;
			}
		}
	}
	this->field_21C = 1;
}
void ScrollingPane::addDeltaPos(float x, float y, float z, int32_t n) {
	if(z > 0) {
		Vec3 v11(x, y, 0);
		Vec3 v12(this->field_BC - v11.x, this->field_C0 - v11.y, this->field_C4 - v11.z);
		Vec3 v10((1.0 / z) * v12.x, (1.0 / z) * v12.y, (1.0 / z) * v12.z);
		this->float_vec.push_back(v10.x);
		this->float_vec.push_back(v10.y);
		this->field_BC = x;
		this->field_C0 = y;
		this->field_C4 = 0;
		this->field_B8 += z;
	}
}
void ScrollingPane::adjustContentSize() {
	int32_t v1 = this->field_8 * this->field_4C.width;
	int32_t w = this->field_2C.width;
	if(v1 < w) this->field_1E4 = w;
	else this->field_1E4 = v1;
	int32_t v3 = this->field_C * this->field_4C.height;
	int32_t h = this->field_2C.height;
	if(v3 < h) this->field_1E8 = h;
	else this->field_1E8 = v3;
}
void ScrollingPane::beginTracking(float a2, float a3, int32_t a4) {
	if(!this->field_DE) {
		this->stopDecelerationAnimation();
		this->adjustContentSize();
		int32_t v7 = this->field_168;
		int32_t v8 = this->field_16C - this->field_1E8;
		int32_t v9 = this->field_1E4;
		this->field_130 = 0;
		this->field_12C = v8;
		this->field_128 = (v7 - v9);
		this->snapContentOffsetToBounds(0);
		float v10 = this->_contentOffset.y;
		float v11 = this->_contentOffset.z;
		this->field_134 = this->_contentOffset.x;
		this->field_138 = v10;
		this->field_13C = v11;
		this->field_140.x = a2;
		this->field_140.y = a3;
		this->field_140.z = 0;
		this->field_15C = a4;
		Vec3* v12 = this->contentOffset();
		float v13 = v12->y;
		float v14 = v12->z;
		this->field_14C = v12->x;
		this->field_150 = v13;
		this->field_154 = v14;
		this->field_DC = 0;
		this->field_DE = 1;
		this->field_175 = 0;
	}
}

Vec3* ScrollingPane::contentOffset() {
	return &this->_contentOffset;
}
Vec3* ScrollingPane::getContentOffset() {
	return &this->_contentOffset;
}
bool_t ScrollingPane::getGridItemFor_slow(int32_t a2, ScrollingPane::GridItem& a3) {
	ScrollingPane::GridItem v14 = this->getItemForPos(0, 0, 0);
	int32_t v6 = v14.field_4;
	int32_t v7 = v14.field_8;
	ScrollingPane::GridItem v15 = this->getItemForPos(this->field_2C.width - 1, this->field_2C.height - 1, 0);
	int32_t v8 = this->field_8;
	float v9 = (float)((float)this->field_2C.minX - this->field_1C) + (float)(v14.field_C - (float)v6);
	float v10 = (float)((float)this->field_2C.minY - this->field_20) + (float)(v14.field_10 - (float)v7);
	int32_t v11 = a2 / v8;
	a3.field_0 = a2;
	a3.field_C = v9 + (float)(this->field_4C.width * (a2 % v8));
	int32_t height = this->field_4C.height;
	a3.field_4 = a2 % v8;
	a3.field_8 = a2 / v8;
	a3.field_10 = v10 + (float)(height * (a2 / v8));
	return a2 % v8 >= v6 && a2 % v8 <= v15.field_4 && v11 >= v7 && v11 <= v15.field_8;
}
ScrollingPane::GridItem ScrollingPane::getItemForPos(float a3, float a4, bool_t a5) {
	float v5 = a4;
	float v8 = a3;
	if(a5) {
		v8 = a3 - this->field_2C.minX;
		v5 = a4 - this->field_2C.minY;
	}
	float v9 = v8 + this->field_1C;
	float v10 = v5 + this->field_20;
	if((this->field_4 & 4) != 0) v9 = fmod(v9, this->field_4C.width * this->field_8);
	if((this->field_4 & 8) != 0) v10 = fmod(v10, this->field_4C.height * this->field_C);
	int32_t v11 = this->field_8;
	float v12 = v9 / (float)this->field_4C.width;
	float height = this->field_4C.height;
	float v14 = v10 / height;
	int32_t v15 = (int32_t)v12;
	return ScrollingPane::GridItem(v15 + v11 * (int32_t)v14, v15, (int32_t)v14, v12, v14);
}
ScrollBar* ScrollingPane::getVerticleScrollBar() {
	return &this->verticalScrollbar;
}
void ScrollingPane::handleUserInput() {
	bool_t isButtonDown = Mouse::isButtonDown(1);
	float v3 = (float)Mouse::getX() * this->field_28;
	float v4 = (float)Mouse::getY() * this->field_28;
	int32_t timeMs = getTimeMs();
	bool_t isInside = this->field_5C.isInside(v3, v4);
	bool_t v7 = v3 != this->field_214 || v4 != this->field_218;
	int32_t v8 = this->field_17C;
	this->field_214 = v3;
	this->field_218 = v4;
	if(v8 > 0 && this->field_211) {
		if(!isButtonDown) {
			this->touchesEnded(v3, v4, timeMs);
			goto LABEL_16;
		}
	} else if(!isButtonDown) goto LABEL_12;

	if(!this->field_211 && isInside) {
		this->touchesBegan(v3, v4, timeMs);
		goto LABEL_16;
	}

LABEL_12:
	if(this->field_178 > 0 && v7 && isButtonDown) {
		this->touchesMoved(v3, v4, isButtonDown);
	}
LABEL_16:
	if(this->field_184 >= 0 && (this->field_4 & 0x400) == 0 && getTimeMs() - this->field_184 > 149) {
		this->onHoldItem();
	}
	this->field_211 = isButtonDown;
}
void ScrollingPane::hideScrollIndicators() {
	this->verticalScrollbar.field_14 = 0;
	this->field_1C4.field_14 = 0;
}
void ScrollingPane::onHoldItem() {
	printf("AAA\n");
	int32_t v2 = this->field_18C;
	if(v2 != -1 && !this->field_DC) {
		if(this->field_DE) {
			this->_onSelect(v2);
		}
	}
	this->field_184 = -1;
}
bool_t ScrollingPane::queryHoldTime(int32_t* a2, int32_t* a3) {
	bool_t v4 = this->field_DC;
	if(this->field_DC) return 0;
	if(this->field_188 >= 0) {
		ScrollingPane::GridItem it = this->getItemForPos(this->field_214, this->field_218, 1);
		if(it.field_0 == this->field_18C) {
			*a2 = it.field_0;
			*a3 = getTimeMs() - this->field_188;
			return 1;
		}
		this->field_188 = -1;
	}

	return v4;
}
void ScrollingPane::refreshPane() {
	this->field_21C = 1;
}
void ScrollingPane::render(int32_t a2, int32_t a3, float a4) {
	this->handleUserInput();
	this->timer.advanceTime();
	if(this->field_210) {
		int32_t v6 = this->field_178;
		if(!v6) {
			while(v6 < this->timer.ticks) {
				this->stepThroughDecelerationAnimation(0);
				++v6;
			}
			this->field_170 = getTimeMs();
		}
	}
	if(this->field_21C) {
		this->field_21C = 0;
		this->refreshItems();
	}
	std::vector<ScrollingPane::GridItem> v24;
	ScrollingPane::GridItem v25 = this->getItemForPos(0, 0, 0);
	int32_t v7 = v25.field_8;
	int32_t v8 = v25.field_4;
	int32_t v9 = v25.field_8;
	ScrollingPane::GridItem v26 = this->getItemForPos(this->field_2C.width - 1, this->field_2C.height - 1, 0);
	float v10 = (float)((float)this->field_2C.minX - this->field_1C) + (float)(v25.field_C - (float)v8);
	float v11 = (float)((float)this->field_2C.minY - this->field_20) + (float)(v25.field_10 - (float)v7);
	while(v9 <= v26.field_8) {
		for(int32_t i = v8; i <= v26.field_4; ++i) {
			int32_t v12 = this->field_8;
			if(v9 >= 0) {
				int32_t v13 = i + v12 * v9;
				if(v13 >= 0 && v13 < this->field_10) {
					int32_t v14 = this->field_4;
					if((v14 & 4) != 0 || i >= 0 && i < v12) {
						int32_t width = this->field_4C.width;
						float v23 = this->field_4C.height * v9;
						float fc = v10 + (float)(width * i);
						ScrollingPane::GridItem v27(v13, (int32_t)fc, (int32_t)(v11 + v23), fc, v11 + v23);
						//TODO v28 = (v14 & 0x20) != 0 ? this->field_1A4[v13] : (v13 == this->field_1A8)
						//used later for (&griditem->field_10)+1 which doesnt exist

						v24.emplace_back(v27);
					}
				}
			}
		}
		++v9;
	}
	this->renderBatch(v24, a4, this->field_1C, this->field_20);
}
void ScrollingPane::setContentOffset(Vec3 a2) {
	this->setContentOffsetWithAnimation(a2, 0);
}
void ScrollingPane::setContentOffset(float a2, float a3) {
	Vec3 v4(a2, a3, 0);
	this->setContentOffsetWithAnimation(v4, 0);
}
void ScrollingPane::setContentOffsetWithAnimation(Vec3 a2, bool_t a5) {
	this->_contentOffset = a2;
	this->field_1C = -this->_contentOffset.x;
	this->field_20 = -this->_contentOffset.y;
	if(!a5) {
		int32_t v4 = this->field_4;
		if((v4 & 0x200) != 0) {
			if((v4 & 1) == 0) this->updateHorizontalScrollIndicator();
		}
		if((this->field_4 & 2) == 0) this->updateVerticalScrollIndicator();
	}
}
void ScrollingPane::setSelected(int32_t a2, bool_t a3) {
	if((this->field_4 & 0x20) != 0) {
		this->field_1A4[a2] = a3;
	} else if(a3) {
		this->field_1A8 = a2;
	} else if(a2 == this->field_1A8) {
		this->field_1A8 = -1;
	}
	this->field_21C = 1;
}
void ScrollingPane::snapContentOffsetToBounds(bool_t a2) {
	int32_t v4;
	float v5, v6, v7, v8, xc, yc;
	if(this->field_DF) {
		v4 = this->field_168;
		v5 = floorf(this->_contentOffset.x / (float)v4 + 0.5);
		v6 = this->field_16C;
		v7 = v5 * v4;
		v8 = floorf(this->_contentOffset.y / v6 + 0.5) * v6;
LABEL_14:
		this->setContentOffsetWithAnimation(Vec3(v7, v8, 0), a2); //TODO check does it use 0
		return;
	}
	if((this->field_4 & 0x10) == 0) {
		xc = this->_contentOffset.x;
		v7 = this->field_128;
		v8 = this->field_12C;
		yc = this->_contentOffset.y;
		if(v7 < xc) v7 = this->_contentOffset.x;
		if(v7 > 0) v7 = 0;

		if(v8 < yc) v8 = this->_contentOffset.y;
		if(v8 > 0) v8 = 0;

		if(v7 != xc || v8 != yc) goto LABEL_14;
	}
}
void ScrollingPane::startDecelerationAnimation(bool_t a2) {
	Vec3 v28(this->_contentOffset.x - this->field_14C, this->_contentOffset.y - this->field_150, 0);
	float v4 = ((float)getTimeMs() - this->field_15C) / 15;
	Vec3 v29(v28.x / v4, v28.y / v4, 0);
	float xc = v29.x;
	float yc = v29.y;
	float zc = v29.z;
	memset(&v29, 0, sizeof(v29));
	this->field_FC = xc;
	this->field_100 = yc;
	this->field_104 = zc;
	float v8 = this->field_12C;
	int32_t v9 = this->field_130;
	this->field_108 = this->field_128;
	this->field_10C = v8;
	this->field_110 = v9;
	float v10 = v29.y;
	float v11 = v29.z;
	this->field_114 = v29.x;
	this->field_118 = v10;
	this->field_11C = v11;
	uint8_t v12 = (uint8_t)this->field_DF;
	if(this->field_DF) {
		float v13 = this->field_168;
		float v14 = this->field_128;
		float v15 = this->field_EC.x / v13;
		float v16 = floorf(v15);
		float v17 = this->field_EC.y;
		float v18 = this->field_12C;
		float v19 = v16 * v13;
		if(v14 >= v16 * v13) v19 = v14;
		this->field_108 = v19;
		float v20 = this->field_16C;
		float v21 = v17 / v20;
		float v22 = floorf(v21) * v20;
		if(v18 >= v22) v22 = v18;
		this->field_10C = v22;
		float v23 = ceilf(v15) * v13;
		if(v23 >= 0) v23 = 0;
		this->field_114 = v23;
		float v24 = ceilf(v21) * v20;
		if(v24 >= 0) v24 = 0;
		this->field_118 = v24;
	}
	this->field_120 = 0.03;
	this->field_124 = 0.08;
	float v25;
	if(v12) {
		v25 = 1.3333;
		this->field_120 = 0.15;
	} else {
		v25 = 0.3333;
	}

	if(a2 || fabsf(this->field_FC) > v25 || fabsf(this->field_100) > v25) {
		this->field_DD = 1;
		this->field_210 = 1;
		this->field_170 = getTimeMs();
		this->willBeginDecelerating();
	}
}
void ScrollingPane::stepThroughDecelerationAnimation(bool_t a2) {
	if(this->field_DD) {
		int32_t timeMs = getTimeMs();
		int32_t v6;
		if(a2) v6 = 0;
		else v6 = (int32_t)floorf((float)((float)((float)(timeMs - this->field_170) / 16.667) + 0.5) - 1.0);
		for(int32_t i = 0; i < v6; ++i) {
			this->stepThroughDecelerationAnimation(1);
		}
		float v8 = this->contentOffset()->x + this->field_FC;
		float v9 = this->contentOffset()->y + this->field_100;

		if((this->field_4 & 0x10) != 0) {
			float v10 = this->field_128;
			if(v10 < v8) v10 = v8;
			if(v10 > 0) v10 = 0;
			bool_t v11 = v10 == v8;
			if(v10 != v8) v8 = v10;
			float v12 = this->field_12C;
			if(!v11) this->field_FC = 0;
			if(v12 < v9) v12 = v9;
			if(v12 > 0) v12 = 0;
			if(v12 != v9) {
				v9 = v12;
				this->field_100 = 0;
			}
		}
		if(a2) {
			this->contentOffset()->x = v8;
			this->contentOffset()->y = v9;
		} else {
			this->setContentOffset(v8, v9);
		}

		if(!this->field_DF) {
			this->field_FC = this->field_FC * 0.95;
			this->field_100 = this->field_100 * 0.95;
		}

		float v13, v14;
		if(a2 || (v13 = fabsf(this->field_FC), v13 > 0.05) || (v14 = fabsf(this->field_100), v14 > 0.05) || (this->hideScrollIndicators(), v13 > 0.01) || v14 > 0.01) {
			if((this->field_4 & 0x10) == 0) {
				float v16 = this->field_108;
				float v17;
				if(v8 >= v16 && (v16 = this->field_114, v8 <= v16)) v17 = 0;
				else v17 = v16 - v8;
				float v18 = this->field_10C;
				float v19;
				if(v9 >= v18 && (v18 = this->field_118, v9 <= v18)) v19 = 0;
				else v19 = v18 - v9;

				if(v17 != 0) {
					float v20 = this->field_FC;
					if((v17 * v20) > 0) this->field_FC = v17 * this->field_124;
					else this->field_FC = v20 + (v17 * this->field_120);
				}
				if(v19 != 0) {
					float v21 = this->field_100;
					if((v19 * v21) > 0) this->field_100 = v19 * this->field_124;
					else this->field_100 = v21 + (v19 * this->field_120);
				}
			}
			if(!a2) this->field_170 = timeMs;
		} else {
			this->field_DD = 0;
			this->didEndDecelerating();
		}
	}
}
void ScrollingPane::stopDecelerationAnimation() {
	this->field_DD = 0;
	this->field_210 = 0;
}
void ScrollingPane::tick() {
	if((this->field_4 & 0x200) != 0) {
		this->updateScrollFade(this->verticalScrollbar);
		this->updateScrollFade(this->field_1C4);
	}
}
void ScrollingPane::touchesBegan(float a2, float a3, int32_t a4) {
	int32_t v7;
	int32_t timeMs;
	if(this->field_174) {
		this->field_17C = 1;
		this->beginTracking(a2, a3, a4);
		this->field_178 = 2;
		ScrollingPane::GridItem r = this->getItemForPos(a2, a3, 1);
		v7 = r.field_0;
		if(r.field_0 < 0 || r.field_0 >= this->field_10) {
			this->field_18C = -1;
			this->field_184 = -1;
			this->field_188 = -1;
		} else {
			if(!this->field_74.isInside(a2, a3)) v7 = -1;
			this->field_18C = v7;
			if(this->field_74.isInside(a2, a3)) timeMs = getTimeMs();
			else timeMs = -1;
			this->field_184 = timeMs;
			this->field_188 = timeMs;
		}
	}
}
void ScrollingPane::touchesCancelled(float a2, float a3, int32_t a4) {
	ScrollingPane::touchesEnded(a2, a3, a4);
}
void ScrollingPane::touchesEnded(float a2, float a3, int32_t a4) {
	this->field_188 = -1;
	uint8_t v5 = (uint8_t)this->field_DC;
	this->field_17C = 0;
	this->field_DE = 0;
	if(v5) {
		int32_t v8 = this->field_F8;
		this->field_DC = 0;
		if((float)(a4 - v8) <= 100) {
			this->field_EC.x = this->_contentOffset.x;
			this->field_EC.y = this->_contentOffset.y;
			this->field_EC.z = this->_contentOffset.z;
			this->startDecelerationAnimation(0);
		}
		this->didEndDragging();
	}
	if(!this->field_DD) {
		float v13 = this->field_20;
		if(v13 >= 0 && v13 <= this->field_2C.height) {
			this->snapContentOffsetToBounds(1);
			this->hideScrollIndicators();
		} else {
			this->field_EC.x = this->_contentOffset.x;
			this->field_EC.y = this->_contentOffset.y;
			this->field_EC.z = this->_contentOffset.z;
			this->startDecelerationAnimation(1);
		}
	}
	Vec3 v17(a2, a3, 0);
	if(((this->field_140.y - v17.y) * (this->field_140.y - v17.y) + (this->field_140.x - v17.x) * (this->field_140.x - v17.x) + (this->field_140.z - v17.z) * (this->field_140.z - v17.z)) <= 36.0) {
		if(this->field_18C >= 0) this->_onSelect(this->field_18C);
	}
	this->field_178 = 0;
}

void ScrollingPane::touchesMoved(float a2, float a3, int32_t a4) {
	this->field_175 = 1;
	Vec3 v20(a2, a3, 0);
	float v6 = v20.x - this->field_140.x;
	float v7 = v20.y - this->field_140.y;
	if(!this->field_DC && (fabsf(v6) >= 5 && (this->field_4 & 1) == 0 || fabsf(v7) >= 5 && (this->field_4 & 2) == 0)) {
		this->willBeginDragging();
		int32_t v19 = this->field_4;
		this->field_DC = 1;
		this->field_159 = 1;
		if((v19 & 0x200) != 0) {
			if((v19 & 1) == 0 && this->field_1E4 > this->field_168) this->field_1C4.field_14 = 1;

			if((v19 & 2) == 0 && this->field_1E8 > this->field_16C) this->verticalScrollbar.field_14 = 1;
		}
	}
	if(this->field_DC) {
		int32_t v8 = this->field_4;
		float v9 = this->field_128;
		float xc, yc;
		if((v8 & 1) != 0) xc = this->_contentOffset.x;
		else xc = this->field_134;
		if((v8 & 1) == 0) xc = v6 + xc;

		if((v8 & 2) != 0) yc = this->_contentOffset.y;
		else yc = this->field_138;
		if((v8 & 2) == 0) yc = v7 + yc;

		if((v8 & 0x10) != 0) {
			if(v9 >= xc) xc = this->field_128;
			if(xc > 0) xc = 0;
			if(this->field_12C >= yc) yc = this->field_12C;
			if(yc > 0) yc = 0;
		} else {
			float v12;
			if(xc >= v9) {
				if(xc <= 0) v12 = 0;
				else v12 = 0.5;
				if(xc > 0) v12 = xc * v12;
			} else {
				v12 = (float)(xc - v9) * 0.5;
			}
			xc = xc - v12;
			float v13 = this->field_12C;
			float v14;
			if(yc >= v13) {
				if(yc <= 0) v14 = 0;
				else v14 = 0.5;
				if(yc > 0) v14 = yc * v14;
			} else {
				v14 = (float)(yc - v13) * 0.5;
			}
			yc = yc - v14;
		}
		if(this->field_159) {
			float v15 = v20.x;
			float v16 = v20.y;
			float zc = v20.z;
			this->field_159 = 0;
			this->field_140.x = v15;
			this->field_140.y = v16;
			this->field_140.z = zc;
		} else {
			this->setContentOffset(xc, yc);
			this->field_F8 = a4;
		}
	}
}
void ScrollingPane::translate(float a2, float a3) {
	float v3;
	int32_t minY;
	float v5;
	v3 = this->field_5C.minX + a2;
	this->field_2C.minX += (int32_t)a2;
	minY = this->field_2C.minY;
	this->field_5C.minX = v3;
	v5 = this->field_5C.maxX + a2;
	this->field_2C.minY = minY + (int32_t)a3;
	this->field_5C.maxX = v5;
	this->field_5C.minY = this->field_5C.minY + a3;
	this->field_5C.maxY = this->field_5C.maxY + a3;
	this->field_74.minX = this->field_74.minX + a2;
	this->field_74.maxX = this->field_74.maxX + a2;
	this->field_74.minY = this->field_74.minY + a3;
	this->field_74.maxY = this->field_74.maxY + a3;
	this->field_1C4.field_0 = this->field_1C4.field_0 + a2;
	this->field_1C4.field_4 = this->field_1C4.field_4 + a3;
	this->verticalScrollbar.field_0 = this->verticalScrollbar.field_0 + a2;
	this->verticalScrollbar.field_4 = this->verticalScrollbar.field_4 + a3;
}
void ScrollingPane::updateHorizontalScrollIndicator() {
	int32_t v2 = this->field_4;
	float v3;
	if((v2 & 1) != 0) v3 = 1;
	else {
		v3 = 1;
		if((v2 & 0x200) != 0) v3 = 6;
	}
	int32_t v4 = this->field_168;
	int32_t v5 = this->field_1E4;
	float v6 = (float)v4;
	float v7 = floorf((float)((float)(v4 / v5) * (float)((float)v4 - v3)) + 0.5);
	if(v7 <= 11.333) v7 = 11.333;
	float xc = this->_contentOffset.x;

	float v10;
	if(xc <= 0) {
		if(xc < (v4 - v5)) {
			float v11 = (float)((float)(v7 + (float)v5) - v6) + this->contentOffset()->x;
			if(v11 < 2.3333) v11 = 2.3333;
			v7 = floorf(v11 + 0.5);
			v10 = (float)((float)this->field_168 - v7) - v3;
		} else {
			v10 = (float)((float)-xc / (float)(v5 - v4)) * (float)((float)(v6 - v3) - v7);
		}
	} else {
		float v9 = v7 - xc;
		if(v9 < 2.3333) v9 = 2.3333;
		v10 = 1;
		v7 = floorf(v9 + 0.5);
	}
	this->field_1C4.field_8 = v7;
	this->field_1C4.field_0 = v10 + this->field_2C.minX;
}
void ScrollingPane::updateScrollFade(ScrollBar& a2) {
	if(a2.field_14 == 1) {
		float v2 = a2.color + 0.33;
		a2.color = v2;
		if(v2 >= 1) {
			a2.color = 1;
			a2.field_14 = -1;
		}
	}
	if(a2.field_14 == 0) {
		float v3 = a2.color - 0.1;
		a2.color = v3;
		if(v3 <= 0) {
			a2.color = 0;
			a2.field_14 = -1;
		}
	}
}
void ScrollingPane::updateVerticalScrollIndicator() {
	int32_t v2 = this->field_4;
	float v3;
	if((v2 & 2) != 0) v3 = 1;
	else {
		v3 = 1;
		if((v2 & 0x200) != 0) v3 = 6;
	}
	int32_t v4 = this->field_16C;
	int32_t v5 = this->field_1E8;
	float v6 = v4;
	float v7 = floorf((float)((float)(v4 / v5) * (float)((float)v4 - v3)) + 0.5);
	if(v7 <= 11.333) v7 = 11.333;
	float yc = this->_contentOffset.y;
	float v9, v10, v11, minY;
	if(yc <= 0) {
		if(yc < (float)(v4 - v5)) {
			v11 = (float)((float)(v7 + (float)v5) - v6) + this->contentOffset()->y;
			if(v11 < 2.3333) v11 = 2.3333;
			v7 = floorf(v11 + 0.5);
			v10 = (float)((float)this->field_16C - v7) - v3;
		} else {
			v10 = (float)((float)-yc / (float)(v5 - v4)) * (float)((float)(v6 - v3) - v7);
		}
	} else {
		v9 = v7 - yc;
		if(v9 < 2.3333) v9 = 2.3333;
		v10 = 1;
		v7 = floorf(v9 + 0.5);
	}
	minY = this->field_2C.minY;
	this->verticalScrollbar.field_C = v7;
	this->verticalScrollbar.field_4 = v10 + minY;
}

ScrollingPane::~ScrollingPane() {
	if(this->field_1A4) delete[] this->field_1A4;
}
void ScrollingPane::renderBatch(std::vector<ScrollingPane::GridItem>& a2, float a3, float a4, float a5) {
	for(auto& v7: a2) {
		this->renderItem(v7, a3);
	}
}
void ScrollingPane::renderItem(ScrollingPane::GridItem&, float) {
}
void ScrollingPane::didEndDragging(){
}
void ScrollingPane::didEndDecelerating() {
}
void ScrollingPane::willBeginDecelerating() {
}
void ScrollingPane::willBeginDragging() {
}
bool_t ScrollingPane::onSelect(int32_t a2, bool_t a3) {
	return a3;
}
void ScrollingPane::refreshItems(){}
