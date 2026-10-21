#include <Config.hpp>
#include <Minecraft.hpp>

Config createConfig(Minecraft* mc) {
	Config res;
	res.guiScale = Gui::GuiScale;
	res.mc = mc;
	res.width = mc->width;
	res.height = mc->height;
	res.guiScaleNorm = 1.0 / Gui::GuiScale;
	res.field_18 = mc->pixelsPerMillimeter;
	res.field_1C = mc->field_C88;
	res.options = &mc->options;
	res.field_20 = mc->field_C8C;
	res.field_24 = mc->field_C90;
	res.field_10 = (int32_t)(res.width * res.height);
	res.field_14 = (int32_t)(res.height * res.guiScaleNorm);
	return res;
}
