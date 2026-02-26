#include <rendering/tileentity/ChestRenderer.hpp>
#include <tile/entity/ChestTileEntity.hpp>

ChestRenderer::ChestRenderer() : TileEntityRenderer(), field_8(0), field_1A8(1){

}
ChestRenderer::~ChestRenderer() {
}
void ChestRenderer::render(struct TileEntity* tee, float x, float y, float z, float a6, bool_t a7) {
	ChestTileEntity* te = (ChestTileEntity*)tee;
	int32_t level;		// r5
	int32_t v12;		// r7
	Tile* tile;			// r10
	int32_t data;		// r0
	float v15;			// r0
	float v16;			// r0
	float v17;			// r1
	float v18;			// r2
	ChestModel* v19;	// r7
	float v20;			// s18
	float modelOffsetX; // r0
	float v22;			// s15

	if(te->isUnpaired) {
		if(te->level) {
			v12 = 0;
			tile = te->getTile();
			data = te->getData();
			level = data;
			if(tile) {
				if(!data) {
					level = te->getData();
				}
			}
		} else {
			v12 = 1;
			level = 0;
		}
		if(!v12) {
			te->setupLighting(a7, a6);
		}
		glPushMatrix();
		glTranslatef(x, y + 1.0, z + 1.0);
		glScalef(1.0, -1.0, -1.0);
		glTranslatef(0.5, 0.5, 0.5);
		if(v12) {
			v16 = -1.0;
			v17 = 0.0;
			v18 = 0.0;
		} else {
			if(level == 2) {
				v15 = 180.0;
			} else if(level == 3) {
				v15 = 0.0;
			} else if(level == 4) {
				v15 = 90.0;
			} else if(level == 5) {
				v15 = -90.0;
			} else {
				v15 = 0.0;
			}
			glRotatef(v15, 0.0, 1.0, 0.0);
			v16 = -0.5;
			v17 = -0.5;
			v18 = -0.5;
		}
		glTranslatef(v16, v17, v18);
		if(te->pair) {
			v19 = &this->field_1A8;
			this->bindTexture("item/chest/double_normal.png");
			if(level == 2 || level == 5) {
				v20 = -1.0;
			} else {
				v20 = 1.0;
			}
			modelOffsetX = te->getModelOffsetX();
			glTranslatef(modelOffsetX * v20, 0.0, 0.0);
		} else {
			v19 = &this->field_8;
			this->bindTexture("item/chest/normal.png");
		}
		v22 = 1.0 - (float)(te->field_88 + (float)((float)(te->field_84 - te->field_88) * a6));
		v19->field_18.xRotAngle = -(float)(0.5 * (float)((float)(1.0 - (float)((float)(v22 * v22) * v22)) * 3.1416));
		v19->render();
		glPopMatrix();
	}
}
