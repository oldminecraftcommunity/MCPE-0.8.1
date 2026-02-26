#include <input/UnifiedTurnBuild.hpp>
#include <entity/Entity.hpp>
#include <Minecraft.hpp>
#include <Config.hpp>
#include <utils.h>

UnifiedTurnBuild::UnifiedTurnBuild(int32_t a2, int32_t a3, int32_t a4, float a5, float a6, IInputHolder* a7, Minecraft* a8) :
	field_34(1, -1, -1, 0, 0), field_4C(1, -1, -1, 0, 0), field_64(1, -1, -1, 0, 0), field_7C(1, -1, -1, 0, 0), field_94(1, -1, -1, 0, 0){
	this->curTime = -1.0;
	this->field_1C = a2;
	this->field_34.field_4 = 1;
	this->field_28 = 0;
	this->field_20 = 0;
	this->field_2C = 0;
	this->field_30 = 0;
	this->field_AC = a7;
	this->field_B4 = 0.0;
	this->field_B8 = 0.0;
	this->field_BC = 0;
	this->field_100 = 0.0;
	this->field_104 = a5;
	this->field_10C = 0;
	this->field_118 = 0;
	this->field_11C = 0;
	this->field_11D = 0;
	this->field_11E = 0;
	this->field_120 = 0;
	this->field_D0.field_4 = 0;
	this->options = &a8->options;
	this->field_108 = a6;
	this->onConfigChanged(createConfig(a8));
	double TimeS = getTimeS();
	this->field_F8 = TimeS;
	this->field_110 = TimeS;
}
float UnifiedTurnBuild::getSpeedSquared(Entity* a1){
	float v1; // s13
	float v2; // s15
	float v3; // s14

	v1 = a1->posX - a1->prevX;
	v2 = a1->posY - a1->prevY;
	v3 = a1->posZ - a1->prevZ;
	return (float)((float)(v2 * v2) + (float)(v1 * v1)) + (float)(v3 * v3);
}

UnifiedTurnBuild::~UnifiedTurnBuild() {
}
void UnifiedTurnBuild::onConfigChanged(const Config& a2) {
	float v2; // s15
	int v3; // s10
	float maxX; // s12
	float minX; // s11
	float v9; // s10
	float v10; // s13
	float minY; // s12
	float maxY; // s13
	float v13; // s10
	float v14; // s15
	RectangleArea* v20; // [sp+8h] [bp-18h] BYREF
	TouchAreaModel::Area* v21; // [sp+Ch] [bp-14h] BYREF

	v2 = (float)a2.field_4;
	v3 = a2.field_0;
	maxX = this->field_4C.maxX;
	minX = this->field_4C.minX;

	this->field_34.field_4 = 1;
	this->field_34.minX = 0.0;
	this->field_34.minY = 0.0;
	this->field_34.maxY = v2;
	this->field_34.maxX = (float)v3;
	v9 = (float)((float)(maxX - minX) * 0.05) + 10.0;
	v10 = maxX + v9;
	minY = this->field_4C.minY;
	this->field_4C.maxX = v10;
	maxY = this->field_4C.maxY;
	this->field_4C.minX = minX - v9;
	v13 = (float)((float)(maxY - minY) * 0.05) + 10.0;
	this->field_4C.maxY = maxY + v13;
	this->field_94.minX = this->field_94.minX - 10.0;
	this->field_94.maxX = this->field_94.maxX + 10.0;
	this->field_94.minY = this->field_94.minY - 10.0;
	v14 = this->field_94.maxY + 10.0;
	this->field_4C.minY = minY - v13;
	this->field_94.maxY = v14;
	this->field_D0.clear();
	this->field_D0.areas1.push_back(&this->field_34);
	this->field_D0.areas2.push_back(&this->field_4C);
	this->field_D0.areas2.push_back(&this->field_7C);
	this->field_C0.clear();

	TouchAreaModel::Area* v15 = new TouchAreaModel::Area(&this->field_D0);
	v15->field_4 = 100;
	this->field_C0.areas.emplace_back(v15);
}
Vec3 UnifiedTurnBuild::getTurnDelta() {
	printf("UnifiedTurnBuild::getTurnDelta - not implemented\n");
	//TODO touchscreen support
	return Vec3(0, 0, 0);
}
bool_t UnifiedTurnBuild::tickBuild(Player*, BuildActionIntention*) {
	printf("UnifiedTurnBuild::tickBuild - not implemented\n");
	//TODO touchscreen support
	return 0;
}
