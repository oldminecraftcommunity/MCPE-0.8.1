#pragma once
#include <input/MouseDevice.hpp>

struct Multitouch
{
	static int32_t _activePointerCount;
	static int32_t _activePointerThisUpdateCount;
	static bool_t _wasPressed[12];
	static bool_t _wasReleased[12];
	static bool_t _wasPressedThisUpdate[12];
	static bool_t _wasReleasedThisUpdate[12];
	static MouseDevice _pointers[12];
	static std::vector<MouseAction> _inputs;
	static int32_t _activePointerThisUpdateList[12];
	static int32_t _activePointerList[12];
	static int32_t _index;

	static void commit();
	static void feed(int8_t, int8_t, int16_t, int16_t, int8_t);
	static void reset();
	static void resetThisUpdate();
};
