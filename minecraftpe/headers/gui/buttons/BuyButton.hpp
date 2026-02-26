#pragma once
#include <_types.h>
#include <gui/buttons/ImageButton.hpp>
struct BuyButton : ImageButton{
	BuyButton(int32_t);
	virtual ~BuyButton();
	virtual void render(struct Minecraft*, int32_t, int32_t);
};
