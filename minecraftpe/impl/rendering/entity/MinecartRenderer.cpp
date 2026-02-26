#include <rendering/entity/MinecartRenderer.hpp>
#include <entity/Minecart.hpp>
#include <math.h>
#include <math/Vec3.hpp>
#include <math/Mth.hpp>

MinecartRenderer::MinecartRenderer()
	: EntityRenderer()
	, tileRenderer(0)
	, mmodel() {
}
void MinecartRenderer::renderMinecartContents(Entity* a2, float a3, Tile* a4, int32_t a5) {
	glPushMatrix();
	this->tileRenderer.renderTile(a4, a5, 1);
	glPopMatrix();
}

MinecartRenderer::~MinecartRenderer() {
}
void MinecartRenderer::render(Entity* e_, float x, float y, float z, float a6, float a7) {
	Minecart* e = (Minecart*)e_;
	float v11; // s23
	int32_t v13; // r4
	uint64_t v15; // r4
	float prevPosX; // s20
	float v17; // s15
	float prevPosY; // s19
	float prevPosZ; // s17
	float prevPitch; // s28
	float v21; // s20
	float v22; // s19
	float v23; // s17
	float v24; // s28
	float v25; // s20
	float v26; // s17
	float v27; // s22
	float v28; // s21
	float v29; // s20
	float v30; // s15
	float v31; // s15
	float xx; // s22
	float yy; // s21
	float zz; // s20
	float v35; // s27
	float v36; // s28
	float v37; // s16
	float v38; // s15
	float v39; // s16
	int32_t HurtDir; // r0
	int32_t DisplayOffset; // r11
	Tile* DisplayTile; // r5
	int32_t DisplayData; // r10
	int32_t isFancy; // r0

	v11 = z;
	glPushMatrix();
	this->bindTexture("entity/minecart.png");
	v13 = 493286711 * e->entityId;
	v15 = v13 * v13 * 4392167121L + v13 * 98761L;
	glTranslatef((float)((float)((float)((float)((v15 >> 16) & 7) + 0.5) * 0.125) - 0.5) * 0.004, (float)((float)((float)((float)((v15 >> 20) & 7) + 0.5) * 0.125) - 0.5) * 0.004, (float)((float)((float)((float)((v15 >> 24) & 7) + 0.5) * 0.125) - 0.5) * 0.004);
	prevPosX = e->prevPosX;
	v17 = e->posX - prevPosX;
	prevPosY = e->prevPosY;
	prevPosZ = e->prevPosZ;
	prevPitch = e->prevPitch;
	Vec3 v45{0, 0, 0};
	v21 = prevPosX + (float)(v17 * a7);
	v22 = prevPosY + (float)((float)(e->posY - prevPosY) * a7);
	v23 = prevPosZ + (float)((float)(e->posZ - prevPosZ) * a7);
	v24 = prevPitch + (float)((float)(e->pitch - prevPitch) * a7);
	if (e->getPos(v45, v21, v22, v23) )
	{
		Vec3 v46{0, 0, 0}; // [sp+28h] [bp-Ch] BYREF
		Vec3 v47{0, 0, 0}; // [sp+34h] [bp+0h] BYREF
		if ( !e->getPosOffs(v46, v21, v22, v23, 0.3) )
		{
			v46 = v45;
		}
		if ( !e->getPosOffs(v47, v21, v22, v23, -0.3) )
		{
			v47 = v45;
		}
		v25 = v45.x - v21;
		v26 = v45.z - v23;
		v27 = v47.x - v46.x;
		v28 = v47.y - v46.y;
		y = y + (float)((float)((float)(v46.y + v47.y) * 0.5) - v22);
		if ( (float)(v47.x - v46.x) == 0.0 )
		{
			v27 = 0.0;
		}
		if ( (float)(v47.y - v46.y) == 0.0 )
		{
			v28 = 0.0;
		}
		x = x + v25;
		v29 = v47.z - v46.z;
		if ( (float)(v47.z - v46.z) == 0.0 )
		{
			v29 = 0.0;
		}
		v11 = z + v26;
		v30 = sqrt((float)((float)((float)(v28 * v28) + (float)(v27 * v27)) + (float)(v29 * v29)));
		if ( v30 != 0.0 )
		{
			v31 = sqrt((float)((float)((float)(v28 * v28) + (float)(v27 * v27)) + (float)(v29 * v29)));
			if ( v31 >= 0.0001 )
			{
				xx = v27 / v31;
				yy = v28 / v31;
				zz = v29 / v31;
				if ( xx == 0.0 )
				{
					xx = 0.0;
				}
				if ( yy == 0.0 )
				{
					yy = 0.0;
				}
				if ( zz == 0.0 )
				{
					zz = 0.0;
				}
			}
			else
			{
				xx = Vec3::ZERO.x;
				yy = Vec3::ZERO.y;
				zz = Vec3::ZERO.z;
			}
			v35 = atan2(zz, xx);
			a6 = (float)(v35 * 180.0) / 3.1416;
			v36 = atan(yy);
			v24 = v36 * 73.0;
		}
	}
	glTranslatef(x, y, v11);
	glRotatef(180.0 - a6, 0.0, 1.0, 0.0);
	glRotatef(-v24, 0.0, 0.0, 1.0);
	v37 = (float)e->getHurtTime() - a7;
	v38 = e->getDamage() - a7;
	if ( v38 < 0.0 )
	{
		v38 = 0.0;
	}
	if ( v37 > 0.0 )
	{
		v39 = (float)((float)(v37 * Mth::sin(v37)) * v38) / 10.0;
		HurtDir = e->getHurtDir();
		glRotatef(v39 * (float)HurtDir, 1.0, 0.0, 0.0);
	}
	DisplayOffset = e->getDisplayOffset();
	DisplayTile = e->getDisplayTile();
	DisplayData = e->getDisplayData();
	if ( DisplayTile )
	{
		glPushMatrix();
		this->bindTexture("terrain-atlas.tga");
		glScalef(0.75, 0.75, 0.75);
		glTranslatef(0.0, (float)DisplayOffset * 0.0625, 0.0);
		this->renderMinecartContents(e, a7, DisplayTile, DisplayData);
		glPopMatrix();
	}
	glScalef(-1.0, -1.0, 1.0);
	isFancy = this->isFancy();
	e->setupLighting(isFancy, a7);
	this->bindTexture("entity/minecart.png");
	this->mmodel.render(e, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0625);
	glPopMatrix();
}
