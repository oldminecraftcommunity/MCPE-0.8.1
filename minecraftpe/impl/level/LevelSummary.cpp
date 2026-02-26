#include <level/LevelSummary.hpp>

LevelSummary::LevelSummary() {
	this->field_0 = "";
	this->field_4 = "";
}

LevelSummary::LevelSummary(const LevelSummary& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
	this->field_14 = a2.field_14;
}
LevelSummary::LevelSummary(LevelSummary&& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	a2.field_0 = "";
	a2.field_4 = "";
	this->field_8 = a2.field_8;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
	this->field_14 = a2.field_14;
}
LevelSummary& LevelSummary::operator=(const LevelSummary& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
	this->field_14 = a2.field_14;
	return *this;
}

bool LevelSummary::operator<(const LevelSummary& a2) const
{
	return this->field_8 > a2.field_8;
}

LevelSummary& LevelSummary::operator=(LevelSummary&& a2){
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	this->field_8 = a2.field_8;
	this->field_C = a2.field_C;
	this->field_10 = a2.field_10;
	this->field_14 = a2.field_14;
	return *this;
}
