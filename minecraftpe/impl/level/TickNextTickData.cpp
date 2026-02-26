#include <level/TickNextTickData.hpp>

int32_t TickNextTickData::C = 0;

TickNextTickData::TickNextTickData(int32_t x, int32_t y, int32_t z, int32_t a5){
	this->z = z;
	this->x = x;
	this->y = y;
	TickNextTickData::C += 1;
	this->field_10 = a5;
	this->id = TickNextTickData::C;
}

int32_t TickNextTickData::hashCode(){
	return this->field_10 + ((this->y + ((this->z + (this->x << 10)) << 7)) << 8);
}

bool_t TickNextTickData::operator<(const TickNextTickData& a2) const{
	if(this->delay < a2.delay) return 1;
	if(this->delay <= a2.delay) return this->id < a2.delay;
	return 0;
}

bool_t TickNextTickData::operator==(const TickNextTickData& a2) const{
	if(this->x == a2.x && this->y == a2.y && this->z == a2.z){
		return this->field_10-a2.field_10 + (this->field_10 == a2.field_10) + a2.field_10 - this->field_10;
	}
	return 0;
}

void TickNextTickData::setDelay(int32_t d){
	this->delay = d;
}
