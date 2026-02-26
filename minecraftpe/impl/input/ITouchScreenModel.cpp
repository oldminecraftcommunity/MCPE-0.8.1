#include <input/ITouchScreenModel.hpp>
#include <input/MouseAction.hpp>
ITouchScreenModel::~ITouchScreenModel() {
}
int32_t ITouchScreenModel::getPointerId(const MouseAction& a2) {
	return (uint8_t)a2.field_A;
}
int32_t ITouchScreenModel::getPointerId(int32_t a2, int32_t a3, int32_t a4) {
	return a4;
}
