#pragma once
#include <rendering/model/Model.hpp>
#include <math/Mth.hpp>

struct SpiderModel: Model
{
	struct Eyes: Model
	{
		ModelPart field_1C;

		Eyes() :
				field_1C(32, 4, 64, 32) {
			this->field_5 = 1;
			this->field_1C.setModel(this);
			this->field_1C.addBox(-4.0f, -4.0f, -8.0f, 8.0f, 8.0f, 8.0f, 0.0f);
			this->field_1C.setPos(0, 15, -3);
		}

		virtual ~Eyes() {
		}
		virtual void render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
			this->setupAnim(a3, a4, a5, a6, a7, a8);
			glEnable(GL_POLYGON_OFFSET_FILL);
			this->field_1C.render(a8);
			glDisable(GL_POLYGON_OFFSET_FILL);
		}
		virtual void setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {
			this->field_1C.yRotAngle = a5 / (180.0f / 3.1416f);
			this->field_1C.xRotAngle = a6 / (180.0f / 3.1416f);
		}

	};

	ModelPart field_1C, field_9C, field_11C, field_19C;
	ModelPart field_21C, field_29C, field_31C, field_39C;
	ModelPart field_41C, field_49C, field_51C;

	SpiderModel() :
			field_1C(32, 4, 64, 32), field_9C(0, 0, 64, 32), field_11C(0, 12, 64, 32), field_19C(18, 0, 64, 32), field_21C(18, 0, 64, 32), field_29C(18, 0, 64, 32), field_31C(18, 0, 64, 32), field_39C(18, 0, 64, 32), field_41C(18, 0, 64, 32), field_49C(18, 0, 64, 32), field_51C(18, 0, 64, 32) {
		this->field_1C.setModel(this);
		this->field_9C.setModel(this);
		this->field_11C.setModel(this);
		this->field_19C.setModel(this);
		this->field_21C.setModel(this);
		this->field_29C.setModel(this);
		this->field_31C.setModel(this);
		this->field_39C.setModel(this);
		this->field_41C.setModel(this);
		this->field_49C.setModel(this);
		this->field_51C.setModel(this);
		this->field_1C.addBox(-4.0, -4.0, -8.0, 8, 8, 8, 0.0);
		this->field_1C.setPos(0.0, 15.0, -3.0);
		this->field_9C.addBox(-3.0, -3.0, -3.0, 6, 6, 6, 0.0);
		this->field_9C.setPos(0.0, 15.0, 0.0);
		this->field_11C.addBox(-5.0, -4.0, -6.0, 10, 8, 12, 0.0);
		this->field_11C.setPos(0.0, 15.0, 9.0);
		this->field_19C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_19C.setPos(-4.0, 15.0, 2.0);
		this->field_21C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_21C.setPos(4.0, 15.0, 2.0);
		this->field_29C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_29C.setPos(-4.0, 15.0, 1.0);
		this->field_31C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_31C.setPos(4.0, 15.0, 1.0);
		this->field_39C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_39C.setPos(-4.0, 15.0, 0.0);
		this->field_41C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_41C.setPos(4.0, 15.0, 0.0);
		this->field_49C.addBox(-15.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_49C.setPos(-4.0, 15.0, -1.0);
		this->field_51C.addBox(-1.0, -1.0, -1.0, 16, 2, 2, 0.0);
		this->field_51C.setPos(4.0, 15.0, -1.0);
	}

	virtual ~SpiderModel() {
	}
	virtual void render(Entity* a2, float a3, float a4, float a5, float a6, float a7, float a8) {
		this->setupAnim(a3, a4, a5, a6, a7, a8);
		this->field_1C.render(a8);
		this->field_9C.render(a8);
		this->field_11C.render(a8);
		this->field_19C.render(a8);
		this->field_21C.render(a8);
		this->field_29C.render(a8);
		this->field_31C.render(a8);
		this->field_39C.render(a8);
		this->field_41C.render(a8);
		this->field_49C.render(a8);
		this->field_51C.render(a8);
	}
	virtual void setupAnim(float a2, float a3, float a4, float a5, float a6, float a7) {
		this->field_1C.yRotAngle = a5 / (float) ((180.0f / 3.1416f));
		this->field_1C.xRotAngle = a6 / (float) ((180.0f / 3.1416f));
		this->field_21C.zRotAngle = 3.1416f * 0.25f;
		float v15 = a2 * 0.6662f;
		float v16 = (float) (((float) ((3.1416f + 3.1416f)) * 0.0f)) * 0.25f;
		float v17 = -(float) ((3.1416f * 0.25f));
		this->field_19C.zRotAngle = v17;
		float v18 = (float) ((3.1416f * 0.25f)) * 0.74f;
		this->field_29C.zRotAngle = v17 * 0.74f;
		this->field_39C.zRotAngle = v17 * 0.74f;
		this->field_31C.zRotAngle = v18;
		this->field_41C.zRotAngle = v18;
		this->field_49C.zRotAngle = v17;
		this->field_51C.zRotAngle = 3.1416f * 0.25f;
		this->field_21C.yRotAngle = v17;
		this->field_29C.yRotAngle = 3.1416f * 0.125f;
		this->field_19C.yRotAngle = 3.1416f * 0.25f;
		float v19 = -(float) ((3.1416f * 0.125f));
		this->field_31C.yRotAngle = v19;
		this->field_39C.yRotAngle = v19;
		this->field_41C.yRotAngle = 3.1416f * 0.125f;
		this->field_49C.yRotAngle = v17;
		this->field_51C.yRotAngle = 3.1416f * 0.25f;
		float v20 = (float) (((float) ((3.1416f + 3.1416f)) + (float) ((3.1416f + 3.1416f)))) * 0.25f;
		float v21 = -(float) ((0.4f * Mth::cos((float) ((v15 + v15)) + v16)));
		float v31 = (float) (-(float) ((0.4f * Mth::cos((float) ((v15 + v15)) + v20)))) * a3;
		float v22 = v21 * a3;
		float v32 = (float) (-(float) ((0.4f * Mth::cos((float) ((v15 + v15)) + (float) (((float) ((3.1416f + 3.1416f)) * 0.25f)))))) * a3;
		float v23 = (float) (((float) ((3.1416f + 3.1416f)) * 3.0f)) * 0.25f;
		float v24 = (float) (-(float) ((0.4f * Mth::cos((float) ((v15 + v15)) + v23)))) * a3;
		float v25 = fabsf(Mth::sin(v15 + v16) * 0.4f) * a3;
		float v26 = fabsf(Mth::sin(v15 + v20) * 0.4f) * a3;
		float v27 = Mth::sin(v15 + (float) (((float) ((3.1416f + 3.1416f)) * 0.25f))) * 0.4f;
		float v28 = Mth::sin(v15 + v23);
		this->field_21C.yRotAngle = v17 - v22;
		this->field_31C.yRotAngle = v19 - v31;
		float v29 = fabsf(v27) * a3;
		this->field_19C.yRotAngle = (float) ((3.1416f * 0.25f)) + v22;
		this->field_29C.yRotAngle = (float) ((3.1416f * 0.125f)) + v31;
		this->field_39C.yRotAngle = v32 - (float) ((3.1416f * 0.125f));
		this->field_41C.yRotAngle = (float) ((3.1416f * 0.125f)) - v32;
		this->field_49C.yRotAngle = v24 - (float) ((3.1416f * 0.25f));
		this->field_51C.yRotAngle = (float) ((3.1416f * 0.25f)) - v24;
		this->field_19C.zRotAngle = v25 - (float) ((3.1416f * 0.25f));
		float v30 = fabsf(v28 * 0.4f) * a3;
		this->field_29C.zRotAngle = (float) ((v17 * 0.74f)) + v26;
		this->field_21C.zRotAngle = (float) ((3.1416f * 0.25f)) - v25;
		this->field_31C.zRotAngle = v18 - v26;
		this->field_39C.zRotAngle = (float) ((v17 * 0.74f)) + v29;
		this->field_41C.zRotAngle = v18 - v29;
		this->field_49C.zRotAngle = v30 - (float) ((3.1416f * 0.25f));
		this->field_51C.zRotAngle = (float) ((3.1416f * 0.25f)) - v30;
	}


};
