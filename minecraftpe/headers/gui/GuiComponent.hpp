#pragma once
#include <_types.h>
#include <string>

struct GuiComponent{
	float zLayer;

	GuiComponent(void);
	virtual ~GuiComponent();
	void blit(float, float, int32_t, int32_t, float, float, int32_t, int32_t);
	void blit(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void drawCenteredString(struct Font*, const std::string&, int32_t, int32_t, int32_t);
	void drawRect(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void drawRect(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void drawString(struct Font*, const std::string&, int32_t, int32_t, int32_t);
	void fill(float, float, float, float, int32_t);
	void fill(int32_t, int32_t, int32_t, int32_t, int32_t);
	void fillGradient(float, float, float, float, int32_t, int32_t);
	void fillGradient(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	void fillHorizontalGradient(float, float, float, float, int32_t, int32_t);
	void fillHorizontalGradient(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);

};
