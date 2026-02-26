#pragma once
#include <_types.h>
#include <gui/buttons/Button.hpp>

struct Minecraft;
struct IntRectangle;
struct NinePatchLayer;

namespace Touch{
	struct TButton : Button{
		NinePatchLayer* field_2C, * field_30;

		TButton(int32_t, int32_t, int32_t, int32_t, int32_t, const std::string&, Minecraft*);
		TButton(int32_t, int32_t, int32_t, const std::string&, struct Minecraft*);
		TButton(int32_t, const std::string&, struct Minecraft*);

		void init(Minecraft*);
		void init(Minecraft*, const std::string&, const IntRectangle&, const IntRectangle&, int32_t, int32_t, int32_t, int32_t);
		virtual ~TButton();
		virtual void renderBg(Minecraft*, int32_t, int32_t);
	};
}
