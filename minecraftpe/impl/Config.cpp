#include <Config.hpp>
#include <gui/Gui.hpp>
#include <Minecraft.hpp>

Config createConfig(Minecraft* mc) {
	float v4; // s15
	int32_t v5; // r0
	int32_t v6; // r1
	float v7; // s15
	int32_t v8; // s13
	float field_C88; // r1
	float v10; // s14
	float field_C8C; // r0
	float field_C90; // r1
	Config res; // r0

	v4 = Gui::GuiScale;
	res.guiScale = Gui::GuiScale;
	v5 = mc->field_1C;
	v6 = mc->field_20;
	res.mc = mc;
	v7 = 1.0 / v4;
	res.field_0 = v5;
	res.field_4 = v6;
	res.guiScaleNorm = v7;
	v8 = v6;
	field_C88 = mc->field_C88;
	res.field_18 = mc->field_C84;
	res.field_1C = field_C88;
	v10 = (float)v5 * v7;
	field_C8C = mc->field_C8C;
	field_C90 = mc->field_C90;
	res.options = &mc->options;
	res.field_20 = field_C8C;
	res.field_24 = field_C90;
	res.field_10 = (int32_t)v10;
	res.field_14 = (int32_t)(float)((float)v8 * v7);
	return res;
}
