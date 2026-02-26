#pragma once
#include <gui/buttons/Button.hpp>

struct Minecraft;

namespace Touch {
	struct THeader: Button
	{
		int32_t field_30;

		THeader(int32_t, const std::string&);
		THeader(int32_t, int32_t, int32_t, const std::string&);
		THeader(int32_t, int32_t, int32_t, int32_t, int32_t, const std::string&);

		virtual ~THeader();
		virtual void render(Minecraft*, int32_t, int32_t);
		virtual void renderBg(Minecraft*, int32_t, int32_t);
	};
}
