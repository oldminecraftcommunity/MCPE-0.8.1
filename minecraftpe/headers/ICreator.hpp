#pragma once
#include <_types.h>
#include <sstream>

struct IPosTranslator;

struct ICreator
{
	struct TileEvent
	{
		int32_t field_0, field_4, field_8, field_C, field_10;

		void write(std::basic_stringstream<char_t>&, IPosTranslator&);
	};
};
