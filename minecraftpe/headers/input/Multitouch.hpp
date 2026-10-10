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

	static void commit() {
		int32_t v1; // r4
		int32_t v2; // r3
		int32_t v3; // r3
		v1 = 0;
		Multitouch::_activePointerCount = 0;
		Multitouch::_activePointerThisUpdateCount = 0;
		do {
			if (Multitouch::_pointers[v1].isButtonDown(1)) {
				v2 = Multitouch::_activePointerCount;
				Multitouch::_activePointerList[Multitouch::_activePointerCount] = v1;
				Multitouch::_activePointerCount = v2 + 1;
			} else if (!Multitouch::_wasReleased[v1]) {
				goto LABEL_6;
			}

			v3 = Multitouch::_activePointerThisUpdateCount;
			Multitouch::_activePointerThisUpdateList[Multitouch::_activePointerThisUpdateCount] = v1;
			Multitouch::_activePointerThisUpdateCount = v3 + 1;
			LABEL_6: ++v1;
		} while (v1 != 12);
	}
	static void feed(char a1, char a2, int16_t a3, int16_t a4, char a5) {
		uint32_t v7;
		v7 = (uint8_t) (a5);
		if ((uint8_t) (a5) >= 0xBu) {
			v7 = 0xBu;
		}
		Multitouch::_inputs.push_back(MouseAction(a1, a2, a3, a4, v7));
		Multitouch::_pointers[v7].feed(a1, a2, a3, a4);
		if (a1) {
			if (a2 == 1) {
				Multitouch::_wasPressed[v7] = 1;
				Multitouch::_wasPressedThisUpdate[v7] = 1;
			} else if (!a2) {
				Multitouch::_wasReleased[v7] = 1;
				Multitouch::_wasReleasedThisUpdate[v7] = 1;
			}
		}
	}
	static void reset() {
		int32_t v0; // r4
		v0 = 0;
		Multitouch::_inputs.clear();
		Multitouch::_index = -1;
		do {
			Multitouch::_pointers[v0].reset();
			Multitouch::_wasPressed[v0] = 0;
			Multitouch::_wasReleased[v0++] = 0;
		} while (v0 != 12);
	}
	static void resetThisUpdate() {
		int32_t i; // r3
		for (i = 0; i != 12; ++i) {
			Multitouch::_wasPressedThisUpdate[i] = 0;
			Multitouch::_wasReleasedThisUpdate[i] = 0;
		}
	}
};
