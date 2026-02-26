#include <math/Vec3.hpp>
#include <math.h>

Vec3 Vec3::ZERO(0, 0, 0);
Vec3 Vec3::ONE(1, 1, 1);

Vec3 Vec3::UNIT_X(1, 0, 0);
Vec3 Vec3::NEG_UNIT_X(-1, 0, 0);

Vec3 Vec3::UNIT_Y(0, 1, 0);
Vec3 Vec3::NEG_UNIT_Y(0, -1, 0);

Vec3 Vec3::UNIT_Z(0, 0, 1);
Vec3 Vec3::NEG_UNIT_Z(0, 0, -1);
Vec3::Vec3() {
}
Vec3::Vec3(float x, float y, float z){
	//XXX contains n == 0 ? 0 : n everywhere
	if(x == 0) x = 0;
	this->x = x;
	if(y == 0) y = 0;
	this->y = y;
	if(z == 0) z = 0;
	this->z = z;
}
float Vec3::distanceTo(const Vec3& v){
	float dy = v.y - this->y;
	float dz = v.z - this->z;
	float dx = v.x - this->x;

	return sqrt(dy*dy + dx*dx + dz*dz);
}
float Vec3::distanceToSqr(const Vec3& v) const{
	float dy = v.y - this->y;
	float dz = v.z - this->z;
	float dx = v.x - this->x;

	return dy*dy + dx*dx + dz*dz;
}
#define MINCLIPVAL 0.0000001
bool_t Vec3::clipX(const Vec3& a2, float a3, Vec3& a4) const{
	float dx = a2.x - this->x;
	float dy = a2.y - this->y;
	float dz = a2.z - this->z;

	if(dx*dx < MINCLIPVAL) return 0;
	float v10 = (a3 - this->x) / dx;
	if((v10 < 0) || (v10 > 1)) return 0;

	a4.x = this->x + (dx*v10);
	a4.y = this->y + (dy*v10);
	a4.z = this->z + (dz*v10);
	return 1;
}
bool_t Vec3::clipY(const Vec3& a2, float a3, Vec3& a4) const{
	float dx = a2.x - this->x;
	float dy = a2.y - this->y;
	float dz = a2.z - this->z;

	if(dy*dy < MINCLIPVAL) return 0;
	float v9 = (a3 - this->y) / dy;
	if((v9 < 0) || (v9 > 1)) return 0;

	a4.y = this->y + (dy*v9);
	a4.x = this->x + (dx*v9);
	a4.z = this->z + (dz*v9);
	return 1;
}
bool_t Vec3::clipZ(const Vec3& a2, float a3, Vec3& a4) const{
	float dx = a2.x - this->x;
	float dy = a2.y - this->y;
	float dz = a2.z - this->z;

	if(dz*dz < MINCLIPVAL) return 0;
	float v9 = (a3 - this->z) / dz;
	if((v9 < 0) || (v9 > 1)) return 0;

	a4.x = this->x + (dx * v9);
	a4.z = this->z + (dz * v9);
	a4.y = this->y + (dy * v9);
	return 1;
}
void Vec3::yRot(float v){
	double v2;
	float v4, v5;
	float zCoord;
	float xc, zc;

	v2 = v;
	v4 = cos(v);
	v5 = sin(v2);

	zCoord = this->z;
	xc = (zCoord * v5) + (this->x * v4);
	zc = (zCoord * v4) + (this->x * v5);

	this->x = xc;
	this->z = zc;
}
Vec3 Vec3::normalized(void){
	float length;

	length = sqrt((this->y*this->y)+(this->x*this->x)+(this->z*this->z));

	if(length >= 0.0001){
		return Vec3(this->x / length, this->y / length, this->z / length);
	}
	return Vec3::ZERO;
}
void Vec3::xRot(float v){
	double v2;
	float v4, v5;
	float yCoord, zCoord;

	v2 = v;
	v4 = cos(v);
	v5 = sin(v2);

	yCoord = this->y;
	zCoord = this->z;

	this->y = (zCoord * v5) + (yCoord * v4);
	this->z = (zCoord * v4) + (yCoord * v5);
}
