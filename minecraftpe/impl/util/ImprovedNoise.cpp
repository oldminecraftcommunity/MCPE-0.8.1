#include <util/ImprovedNoise.hpp>

ImprovedNoise::ImprovedNoise(Random* random){
	this->init(random);
}
ImprovedNoise::ImprovedNoise(void){
	Random v2(1);
	this->init(&v2);
}
ImprovedNoise::~ImprovedNoise(void){

}
void ImprovedNoise::init(Random* a2){
	float xFloat, yFloat, zFloat;
	int32_t index;
	int32_t rand, swpElement;

	xFloat = a2->nextFloat(); //inlined x3
	yFloat = a2->nextFloat();
	zFloat = a2->nextFloat();

	this->xCoord = xFloat*256;
	this->yCoord = yFloat*256;
	this->zCoord = zFloat*256;

	for(index = 0; index != 256; ++index){
		this->permutations[index] = index;
	}

	for(index = 0; index != 256; ++index){
		rand = a2->genrand_int32() % (256 - index) + index;
		swpElement = this->permutations[index];
		this->permutations[index] = this->permutations[rand];
		this->permutations[rand] = swpElement;
		this->permutations[index + 256] = this->permutations[index];
	}
}
float ImprovedNoise::lerp(float a2, float a3, float a4){
	return a3 + (float)((float)(a4 - a3) * a2);
}
float ImprovedNoise::grad(int32_t a2, float a3, float a4, float a5){
	uint32_t v6;
	float v7;

	v6 = a2 & 0xF;
	if(v6 > 7){
		v7 = a4;
		if(v6 == 12) goto LABEL_8;
	}else{
		v7 = a3;
		if((a2 & 0xFu) <= 3){
			a3 = a4;
			goto LABEL_8;
		}
	}
	if(v6 != 14) a3 = a5;

LABEL_8:
	if((a2 & 1) != 0)v7 = -v7;
	if((a2 & 2) != 0) a3 = -a3;

	return v7 + a3;
}
float ImprovedNoise::grad2(int32_t a2, float a3, float a4){
	uint32_t v5;
	float v6;

	v5 = a2 & 0xF;
	v6 = (float)(int32_t)(1 - (((uint32_t)a2 >> 3) & 1)) * a3;
	if(v5 <= 3) a3 = 0.0;
	else if(v5 != 12 && v5 != 14) a3 = a4;

	if((a2 & 1) != 0) v6 = -v6;
	if((a2 & 2) != 0) a3 = -a3;
	return v6 + a3;
}
float ImprovedNoise::noise(float x, float y, float z){
	x += this->xCoord;
	y += this->yCoord;
	z += this->zCoord;

	int32_t floorX = (int32_t) x;
	int32_t floorY = (int32_t) y;
	int32_t floorZ = (int32_t) z;

	if(x < (float)floorX) --floorX;
	if(y < (float)floorY) --floorY;
	if(z < (float)floorZ) --floorZ;

	int32_t X = floorX & 0xff;
	int32_t Y = floorY & 0xff;
	int32_t Z = floorZ & 0xff;

	x -= floorX;
	y -= floorY;
	z -= floorZ;

	float fX = FADE(x);
	float fY = FADE(y);
	float fZ = FADE(z);

	int32_t A = this->permutations[X] + Y;
	int32_t AA = this->permutations[A] + Z;
	int32_t AB = this->permutations[A + 1] + Z;

	int32_t B = this->permutations[X + 1] + Y;
	int32_t BA = this->permutations[B] + Z;
	int32_t BB = this->permutations[B + 1] + Z;

	return this->lerp(fZ,
		this->lerp(fY,
			this->lerp(fX, this->grad(this->permutations[AA], x, y, z), this->grad(this->permutations[BA], x-1, y, z)),
			this->lerp(fX, this->grad(this->permutations[AB], x, y-1, z), this->grad(this->permutations[BB], x-1, y-1, z))
		),
		this->lerp(fY,
			this->lerp(fX, this->grad(this->permutations[AA+1], x, y, z-1), this->grad(this->permutations[BA + 1], x-1, y, z-1)),
			this->lerp(fX, this->grad(this->permutations[AB+1], x, y-1, z-1), this->grad(this->permutations[BB + 1], x-1, y-1, z-1))
		)
	);
}
float ImprovedNoise::getValue(float x, float y){
	return this->noise(x, y, 0);
}
float ImprovedNoise::getValue(float x, float y, float z){
	return this->noise(x, y, z);
}
void ImprovedNoise::add(float* noises, float x, float y, float z, int32_t width, int32_t height, int32_t depth, float scaleX, float scaleY, float scaleZ, float scale){

	if(height == 1){
		int32_t j3 = 0;
		float d12 = 1/scale;
		for(int32_t w = 0; w < width; ++w){
			float xFull = (x + (float)w) * scaleX + this->xCoord;
			int32_t floorXFull = (int32_t)xFull;
			if(xFull < (float)floorXFull) --floorXFull;
			int32_t k4 = floorXFull & 0xff;
			xFull -= floorXFull;

			float xFullLerp = FADE(xFull);
			for(int32_t d = 0; d < depth; ++d){
				float zFull = (z + (float)d) * scaleZ + this->zCoord;
				int32_t zFloor = (int32_t) zFull;
				if(zFull < (float)zFloor) --zFloor;
				int32_t l5 = zFloor & 0xff;
				zFull -= zFloor;
				float zFullLerp = FADE(zFull);
				int32_t l = this->permutations[k4] + 0;
				int32_t j1 = this->permutations[l] + l5;
				int32_t k1 = this->permutations[k4 + 1] + 0;
				int32_t l1 = this->permutations[k1] + l5;

				float d9 = this->lerp(xFullLerp, this->grad2(this->permutations[j1], xFull, zFull), this->grad(this->permutations[l1], xFull - 1, 0, zFull));
				float d11 = this->lerp(xFullLerp, this->grad(this->permutations[j1 + 1], xFull, 0, zFull - 1), this->grad(this->permutations[l1 + 1], xFull - 1, 0, zFull - 1));
				float d23 = this->lerp(zFullLerp, d9, d11);
				noises[j3] += d23 * d12;
				++j3;
			}
		}
		return;
	}

	int32_t i1 = 0;
	float d7 = 1 / scale;
	int32_t i2 = -1;
	float d13 = 0;
	float d15 = 0;
	float d16 = 0;
	float d18 = 0;
	for(int32_t i5 = 0; i5 < width; i5++){
		float d20 = (x + (float)i5) * scaleX + xCoord;
		int32_t k5 = (int32_t) d20;
		if(d20 < k5) --k5;
		int32_t i6 = k5 & 0xff;
		d20 -= k5;
		float d22 = FADE(d20);
		for(int32_t j6 = 0; j6 < depth; j6++){
			float d24 = (z + (float)j6) * scaleZ + zCoord;
			int32_t k6 = (int32_t)d24;
			if(d24 < k6) --k6;
			int32_t l6 = k6 & 0xff;
			d24 -= k6;
			float d25 = FADE(d24);
			for(int32_t i7 = 0; i7 < height; i7++){
				float d26 = (y + (float)i7) * scaleY + yCoord;
				int32_t j7 = (int32_t)d26;
				if(d26 < j7) --j7;
				int32_t k7 = j7 & 0xff;
				d26 -= j7;
				float d27 = FADE(d26);
				if(i7 == 0 || k7 != i2){
					i2 = k7;
					int32_t j2 = permutations[i6] + k7;
					int32_t k2 = permutations[j2] + l6;
					int32_t l2 = permutations[j2 + 1] + l6;
					int32_t i3 = permutations[i6 + 1] + k7;
					int32_t k3 = permutations[i3] + l6;
					int32_t l3 = permutations[i3 + 1] + l6;
					d13 = lerp(d22, grad(permutations[k2], d20, d26, d24), grad(permutations[k3], d20 - 1, d26, d24));
					d15 = lerp(d22, grad(permutations[l2], d20, d26 - 1, d24), grad(permutations[l3], d20 - 1, d26 - 1, d24));
					d16 = lerp(d22, grad(permutations[k2 + 1], d20, d26, d24 - 1), grad(permutations[k3 + 1], d20 - 1, d26, d24 - 1));
					d18 = lerp(d22, grad(permutations[l2 + 1], d20, d26 - 1, d24 - 1), grad(permutations[l3 + 1], d20 - 1, d26 - 1, d24 - 1));
				}
				float d28 = lerp(d27, d13, d15);
				float d29 = lerp(d27, d16, d18);
				float d30 = lerp(d25, d28, d29);
				noises[i1] += d30 * d7;
				++i1;
			}
		}
	}
}

int32_t ImprovedNoise::hashCode(void){
	int32_t v1, v2;

	v1 = 0;
	v2 = 4711;
	do{
		v2 = this->permutations[v1] + 37 * v2; //TODO check somehow
	}while(v1 != 2048);

	return v2;
}
