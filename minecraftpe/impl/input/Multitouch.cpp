#include <input/Multitouch.hpp>
int32_t Multitouch::_activePointerCount;
int32_t Multitouch::_activePointerThisUpdateCount;
bool_t Multitouch::_wasPressed[12];
bool_t Multitouch::_wasReleased[12];
bool_t Multitouch::_wasPressedThisUpdate[12];
bool_t Multitouch::_wasReleasedThisUpdate[12];
MouseDevice Multitouch::_pointers[12];
std::vector<MouseAction> Multitouch::_inputs;

int32_t Multitouch::_index = -1;
int32_t Multitouch::_activePointerList[12] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int32_t Multitouch::_activePointerThisUpdateList[12] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
